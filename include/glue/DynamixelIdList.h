/**
 * Copyright (c) 2022 LXRobotics GmbH.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/l3xz_io/graphs/contributors.
 */

#ifndef GLUE_DYNAMIXEL_ID_LIST_H_
#define GLUE_DYNAMIXEL_ID_LIST_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <driver/dynamixel/Dynamixel.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace glue
{

/**************************************************************************************
 * CONSTANT
 **************************************************************************************/

static dynamixel::Dynamixel::IdVect const DYNAMIXEL_ID_LIST{1,2,3,4,5,6,7,8};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* glue */

#endif /* GLUE_DYNAMIXEL_ID_LIST_H_ */