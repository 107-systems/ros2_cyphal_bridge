/**
 * Copyright (c) 2022 LXRobotics GmbH.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/l3xz_io/graphs/contributors.
 */

#ifndef DYNAMIXEL_MX28_H_
#define DYNAMIXEL_MX28_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <memory>

#include <l3xz_io/control/dynamixel/Dynamixel.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace control
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class DynamixelMX28
{
public:

  DynamixelMX28(std::shared_ptr<Dynamixel> dyn_ctrl);

  std::optional<Dynamixel::IdVect> discover();


  void turnLedOn (Dynamixel::IdVect const & id_vect);
  void turnLedOff(Dynamixel::IdVect const & id_vect);

  void torqueOn (Dynamixel::Id const id);
  void torqueOn (Dynamixel::IdVect const & id_vect);
  void torqueOff(Dynamixel::IdVect const & id_vect);

  typedef std::tuple<Dynamixel::Id, float> AngleData;
  typedef std::map<Dynamixel::Id, float> AngleDataSet;

  std::optional<float> getAngle(Dynamixel::Id const id);
  AngleDataSet         getAngle(Dynamixel::IdVect const & id_vect);

  bool setAngle(Dynamixel::Id const id, float const angle_deg);
  bool setAngle(AngleDataSet const & angle_data_set);


private:

  std::shared_ptr<Dynamixel> _dyn_ctrl;

  enum class ControlTable : uint16_t
  {
    Torque_Enable   =  64,
    LED             =  65,
    GoalPosition    = 116,
    PresentPosition = 132,
  };
};

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef std::shared_ptr<DynamixelMX28> SharedMX28;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* control */

#endif /* DYNAMIXEL_MX28_H_ */