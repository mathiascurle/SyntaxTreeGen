#pragma once
#include "imgui.h"
#include "rlImGui.h"
#include "shared_data.hpp"

namespace Gui {

inline bool bViewIsOpen = true;

inline void draw() {
  rlImGuiBegin();
#ifdef IMGUI_HAS_DOCK
  ImGui::DockSpaceOverViewport(
      0, NULL,
      ImGuiDockNodeFlags_PassthruCentralNode); // set
                                               // ImGuiDockNodeFlags_PassthruCentralNode
                                               // so that we can see the
                                               // raylib contents behind the
                                               // dockspace
#endif
  ImGui::SetNextWindowPos(
      ImVec2(Globals.config.fWinWidth - Globals.config.winWidthImGui, 0));
  ImGui::SetNextWindowSize(
      ImVec2(Globals.config.winWidthImGui, Globals.config.fWinHeight));

  //////////////////////
  /// Put stuff here ///
  //////////////////////
  if (ImGui::Begin("Side bar", &Gui::bViewIsOpen,
                   ImGuiWindowFlags_NoTitleBar)) {
    if (ImGui::CollapsingHeader("Node management")) {
    }
  }
  ImGui::End();
  //////////////////////

  rlImGuiEnd();
}

} // namespace Gui
