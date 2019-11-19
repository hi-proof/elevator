/** Interface specs for a single door controller
 *
 * @todo Will need some syncronization systems
 * @todo realistically most of this code is the same as the floor, but like..
 * eh..
 *
 */

#pragma once

#ifndef HI_PROOF_DOOR_CONTROLLER_H_
#define HI_PROOF_DOOR_CONTROLLER_H_

#include "safety_critical_component.h"
#include "TeensyStep.h"
#include "Bounce2.h"

namespace hiproof {
namespace elevator {

class DoorController final : SafetyCriticalComponent {
 public:
  DoorController(const int d1_step_pin, const int d1_dir_pin,
                 const int d1_home_pin, const int d1_overrun_pin,
                 const int d2_step_pin, const int d2_dir_pin,
                 const int d2_home_pin, const int d2_overrun_pin);
  ~DoorController(){};
  void enterSafeMode();
  void emergencyStop();

  void open();
  void close();
  void update();

 private:
  static constexpr uint16_t kHomingSpeed = 1000;
  static constexpr uint16_t kHomingAccel = 1000;
  static constexpr uint16_t kMaxLiveSpeed = 1500;
  static constexpr uint16_t kMaxLiveAccel = 500;
  static constexpr uint16_t kDebounceInterval = 25;

  using DoorData = struct {
    Stepper stepper;
    Bounce home_pin;
    Bounce overrun_pin;
  };

  DoorData left_door_;
  DoorData right_door_;
  uint16_t run_speed{kMaxLiveSpeed};
  uint16_t run_accel{kMaxLiveAccel};

  static StepControl step_controller;
  static RotateControl rotate_controller;
};  // namespace elevator

}  // namespace elevator
}  // namespace hiproof

#endif  // HI_PROOF_DOOR_CONTROLLER_H_