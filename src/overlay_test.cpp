#include "overlay_test/overlay_test.hpp"
#include "qopengl_wrapper.hpp"
#include <rclcpp/rclcpp.hpp>
#include "rviz_wrapper.h"

#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlay.h>
#include <Overlay/OgrePanelOverlayElement.h>
#include <RenderSystems/GL/OgreGLHardwarePixelBuffer.h>
#include <RenderSystems/GL/OgreGLTexture.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreMaterialManager.h>
#include <OgreRectangle2D.h>
#include <OgreRenderQueue.h>
#include <OgreRenderTargetListener.h>
#include <OgreSceneNode.h>
#include <OgreTechnique.h>
#include <OgreTextureManager.h>
#include <OgrePass.h>



namespace overlay_test
{

OverlayTestDisplay::OverlayTestDisplay()
{
}

OverlayTestDisplay::~OverlayTestDisplay()
{
}

  class Listener : public Ogre::RenderTargetListener {
public:
  Listener(int width, int height, GLuint texture_id) : wrapper_(width, height, texture_id) {}

  void postViewportUpdate(const Ogre::RenderTargetViewportEvent &) override {
    wrapper_.draw();
  }

private:
  QOpenGLWrapper wrapper_;
};

void OverlayTestDisplay::onInitialize()
{
  Ogre::MaterialPtr material_ = Ogre::MaterialManager::getSingleton().create("hector_rviz_overlay_OverlayMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  material_->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
  const int width = 200, height=200;
  // Create a texture from an array
  Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual(
    "my_texture", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    Ogre::TEX_TYPE_2D, width, height, 0, Ogre::PF_R8G8B8A8, Ogre::TU_DYNAMIC_WRITE_ONLY);

  // Lock the texture buffer for writing
  Ogre::HardwarePixelBufferSharedPtr pixelBuffer = texture->getBuffer();
  pixelBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
  const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();

  // Get a pointer to the pixel data
  uint8_t* pixels = static_cast<uint8_t*>(pixelBox.data);

  // Populate the pixel data from your array
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      // Assuming your array is a 1D array
      int index = y * width + x;

      // Set the pixel color values
      pixels[index * 4 + 0] = index % 255/* red component */;
      pixels[index * 4 + 1] = (index + 100) % 255/* green component */;
      pixels[index * 4 + 2] = (index + 50) % 255/* blue component */;
      pixels[index * 4 + 3] = 200/* alpha component */;
    }
  }
  Ogre::GLHardwarePixelBuffer *glBuffer = dynamic_cast<Ogre::GLHardwarePixelBuffer*>(pixelBuffer.get());
  Ogre::GLTexture *glTexture = dynamic_cast<Ogre::GLTexture*>(texture.get());
  RCLCPP_INFO(rclcpp::get_logger("OverlayTestDisplay"), "GL Texture: %p, GL Buffer %p", (void*)glTexture, (void*)glBuffer);

  // Unlock the texture buffer
  pixelBuffer->unlock();
  addRenderTargetListener(context_, new Listener(width, height, glTexture->getGLID()));

  // Set the texture to the material
  material_->getTechnique(0)->getPass(0)->createTextureUnitState("my_texture");
  // Ogre::Rectangle2D *rect = new Ogre::Rectangle2D(true);
  // rect->setCorners(-1.0, 0.0, 0.0, -1.0);
  // rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
  // Ogre::AxisAlignedBox aabInf;
  // aabInf.setInfinite();
  // rect->setBoundingBox(aabInf);
  // rect->setMaterial(material_);
  // scene_node_->attachObject(rect);

  prepareOverlays(scene_manager_);
  Ogre::OverlayManager &overlay_manager = Ogre::OverlayManager::getSingleton();
  Ogre::Overlay *overlay_ = overlay_manager.create("hector_rviz_overlay");
  Ogre::PanelOverlayElement *overlay_panel_ = dynamic_cast<Ogre::PanelOverlayElement *>(overlay_manager.createOverlayElement("Panel", "hector_rviz_overlay_Panel"));
  overlay_panel_->setPosition(0, 0);
  overlay_panel_->setDimensions(0.5, 0.5);
  overlay_panel_->setMaterialName("hector_rviz_overlay_OverlayMaterial" );
  // overlay_panel_->setMaterial(clearMat);
  overlay_->add2D(overlay_panel_);
  overlay_->show();
}

}  // namespace overlay_test

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS( overlay_test::OverlayTestDisplay, rviz_common::Display )
