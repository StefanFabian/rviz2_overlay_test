#ifndef OVERLAY_TEST__OVERLAY_TEST_HPP_
#define OVERLAY_TEST__OVERLAY_TEST_HPP_

#include "overlay_test/visibility_control.h"
#include <rviz_common/display.hpp>

namespace overlay_test
{

class OverlayTestDisplay : public rviz_common::Display
{
public:
  OverlayTestDisplay();

  virtual ~OverlayTestDisplay();

  void onInitialize() override;
};

}  // namespace overlay_test

#endif  // OVERLAY_TEST__OVERLAY_TEST_HPP_
