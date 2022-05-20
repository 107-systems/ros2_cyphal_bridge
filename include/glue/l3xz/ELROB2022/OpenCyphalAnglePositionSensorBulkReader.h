/**
 * Copyright (c) 2022 LXRobotics GmbH.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/l3xz/graphs/contributors.
 */

#ifndef GLUE_L3XZ_ELROB2022_OPEN_CYPHAL_ANGLE_POSITION_SENSOR_BULK_READER_H_
#define GLUE_L3XZ_ELROB2022_OPEN_CYPHAL_ANGLE_POSITION_SENSOR_BULK_READER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include "OpenCyphalAnglePositionSensor.h"

#include <map>
#include <mutex>

#include <canard.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace glue::l3xz::ELROB2022
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class OpenCyphalAnglePositionSensorBulkReader
{
public:
  OpenCyphalAnglePositionSensorBulkReader(SharedOpenCyphalAnglePositionSensor angle_sensor_femur_leg_front_left,
                                          SharedOpenCyphalAnglePositionSensor angle_sensor_tibia_leg_front_left,
                                          SharedOpenCyphalAnglePositionSensor angle_sensor_femur_leg_middle_left,
                                          SharedOpenCyphalAnglePositionSensor angle_sensor_tibia_leg_middle_left,
                                          SharedOpenCyphalAnglePositionSensor angle_sensor_femur_leg_back_left,
                                          SharedOpenCyphalAnglePositionSensor angle_sensor_tibia_leg_back_left,
                                          SharedOpenCyphalAnglePositionSensor angle_sensor_femur_leg_front_right,
                                          SharedOpenCyphalAnglePositionSensor angle_sensor_tibia_leg_front_right,
                                          SharedOpenCyphalAnglePositionSensor angle_sensor_femur_leg_middle_right,
                                          SharedOpenCyphalAnglePositionSensor angle_sensor_tibia_leg_middle_right,
                                          SharedOpenCyphalAnglePositionSensor angle_sensor_femur_leg_back_right,
                                          SharedOpenCyphalAnglePositionSensor angle_sensor_tibia_leg_back_right)
  : NODE_ID_TO_FEMUR_ANGLE_POSITION_SENSOR_MAP
  {
    {1, angle_sensor_femur_leg_front_left},
    {2, angle_sensor_femur_leg_middle_left},
    {3, angle_sensor_femur_leg_back_left},
    {4, angle_sensor_femur_leg_back_right},
    {5, angle_sensor_femur_leg_middle_right},
    {6, angle_sensor_femur_leg_front_right},
  }
  , NODE_ID_TO_TIBIA_ANGLE_POSITION_SENSOR_MAP
  {
    {1, angle_sensor_tibia_leg_front_left},
    {2, angle_sensor_tibia_leg_middle_left},
    {3, angle_sensor_tibia_leg_back_left},
    {4, angle_sensor_tibia_leg_back_right},
    {5, angle_sensor_tibia_leg_middle_right},
    {6, angle_sensor_tibia_leg_front_right},
  }
  { }

  void update_femur_angle(CanardNodeID const node_id, float const femur_angle_deg)
  {
    std::lock_guard<std::mutex> lock(_mtx);
    _femur_angle_map[node_id] = femur_angle_deg;
  }
  void update_tibia_angle(CanardNodeID const node_id, float const tibia_angle_deg)
  {
    std::lock_guard<std::mutex> lock(_mtx);
    _tibia_angle_map[node_id] = tibia_angle_deg;
  }

  /* It's not really a bulk read but a bulk copy
   * of all received data so far.
   */
  void doBulkRead()
  {
    std::lock_guard<std::mutex> lock(_mtx);

    for (auto [id, sensor] : NODE_ID_TO_FEMUR_ANGLE_POSITION_SENSOR_MAP) {
      if (_femur_angle_map.count(id) > 0) {
        NODE_ID_TO_FEMUR_ANGLE_POSITION_SENSOR_MAP.at(id)->update(_femur_angle_map.at(id));
      }
    }

    for (auto [id, sensor] : NODE_ID_TO_TIBIA_ANGLE_POSITION_SENSOR_MAP) {
      if (_femur_angle_map.count(id) > 0) {
        NODE_ID_TO_TIBIA_ANGLE_POSITION_SENSOR_MAP.at(id)->update(_tibia_angle_map.at(id));
      }
    }
  }

private:
  std::mutex _mtx;

  std::map<CanardNodeID, float> _femur_angle_map;
  std::map<CanardNodeID, float> _tibia_angle_map;

  std::map<CanardNodeID, SharedOpenCyphalAnglePositionSensor> const NODE_ID_TO_FEMUR_ANGLE_POSITION_SENSOR_MAP;
  std::map<CanardNodeID, SharedOpenCyphalAnglePositionSensor> const NODE_ID_TO_TIBIA_ANGLE_POSITION_SENSOR_MAP;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* glue::l3xz::ELROB2022 */

#endif /* GLUE_L3XZ_ELROB2022_OPEN_CYPHAL_ANGLE_POSITION_SENSOR_BULK_READER_H_ */
