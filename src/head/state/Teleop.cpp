/**
 * Copyright (c) 2022 LXRobotics GmbH.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/l3xz/graphs/contributors.
 */

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <head/state/Teleop.h>

#include <ros/console.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace head::state
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void Teleop::onEnter()
{

}

void Teleop::onExit()
{

}

StateBase * Teleop::update(HeadControllerInput const & input, HeadControllerOutput & output)
{
  /* No state transition if we do not even have
   * valid input data.
   */
  if (!input._angle_sensor_sensor_head_pan->get().has_value()) {
    ROS_ERROR("head::state::Teleop::update: no valid input data for %s", input._angle_sensor_sensor_head_pan->name().c_str());
    return this;
  }

  if (!input._angle_sensor_sensor_head_tilt->get().value()) {
    ROS_ERROR("head::state::Teleop::update: no valid input data for %s", input._angle_sensor_sensor_head_tilt->name().c_str());
    return this;
  }

  /* Calculate new values for sensor head, both pan and tilt joint
   * based on the input provided by the teleop node.
   */
  static float const MAX_ANGLE_INCREMENT_PER_CYCLE_DEG = 10.0f;

  float const pan_angle_actual = input._angle_sensor_sensor_head_pan->get().value();
  float const pan_angle_target = pan_angle_actual + (input._teleop_cmd.angular_velocity_head_pan * MAX_ANGLE_INCREMENT_PER_CYCLE_DEG);
  output._angle_actuator_sensor_head_pan->set(pan_angle_target);

  float const tilt_angle_actual = input._angle_sensor_sensor_head_tilt->get().value();
  float const tilt_angle_target = tilt_angle_actual + (input._teleop_cmd.angular_velocity_head_tilt * MAX_ANGLE_INCREMENT_PER_CYCLE_DEG);
  output._angle_actuator_sensor_head_tilt->set(tilt_angle_target);

  return this;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* head::state */