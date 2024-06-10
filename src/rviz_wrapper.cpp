//
// Created by stefan on 10.06.24.
//

#include "rviz_wrapper.h"

#include <rviz_common/display_context.hpp>
#include <rviz_common/render_panel.hpp>
#include <rviz_common/view_manager.hpp>
#include <rviz_rendering/render_window.hpp>
#include <rviz_rendering/render_system.hpp>

void prepareOverlays(Ogre::SceneManager *scene_manager) {

    rviz_rendering::RenderSystem::get()->prepareOverlays(scene_manager);
}


rviz_rendering::RenderWindow *getRenderWindow(rviz_common::DisplayContext *context)
{
    rviz_common::RenderPanel *render_panel = context->getViewManager()->getRenderPanel();
    return render_panel->getRenderWindow();
}

void addRenderTargetListener(rviz_common::DisplayContext *context, Ogre::RenderTargetListener *listener) {
    rviz_rendering::RenderWindow *render_window = getRenderWindow(context);
    rviz_rendering::RenderWindowOgreAdapter::addListener(render_window, listener);
}
