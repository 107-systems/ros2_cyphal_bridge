/**
 * Copyright (c) 2022 LXRobotics GmbH.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/l3xz/graphs/contributors.
 */

#ifndef COMMON_SENSOR_INTERFACE_ANGLE_POSITION_SENSOR_H_
#define COMMON_SENSOR_INTERFACE_ANGLE_POSITION_SENSOR_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include "Base.h"

#include <memory>
#include <optional>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace common::sensor::interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AnglePositionSensor : public Base
{
public:
           AnglePositionSensor(std::string const & name);
  virtual ~AnglePositionSensor() { }

  std::optional<float> get() const;
  virtual std::string toStr() const override;

protected:
  void set(float const val);

private:
  std::optional<float> _val;
};

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef std::shared_ptr<AnglePositionSensor> SharedAnglePositionSensor;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* common::sensor::interface */

#endif /* COMMON_SENSOR_INTERFACE_ANGLE_POSITION_SENSOR_H_ */
