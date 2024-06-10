//
// Created by stefan on 10.06.24.
//

#ifndef RVIZ_WRAPPER_H
#define RVIZ_WRAPPER_H

namespace Ogre {
    class RenderTargetListener;
    class SceneManager;
}

namespace rviz_common
{
class DisplayContext;
}
namespace rviz_rendering
{
class RenderWindow;
}

void prepareOverlays(Ogre::SceneManager *scene_manager);

void addRenderTargetListener(rviz_common::DisplayContext *context, Ogre::RenderTargetListener *listener);



#endif //RVIZ_WRAPPER_H
