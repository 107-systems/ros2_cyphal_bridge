/**
 * Copyright (c) 2022 LXRobotics GmbH.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/ros2_cyphal_bridge/graphs/contributors.
 */

#ifndef ROS_ROS_BRIDGE_NODE_H_
#define ROS_ROS_BRIDGE_NODE_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <mutex>
#include <chrono>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <cyphal++/cyphal++.h>

#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/byte.hpp>
#include <std_msgs/msg/int8.hpp>
#include <std_msgs/msg/int16.hpp>
#include <std_msgs/msg/float32.hpp>
#include <std_msgs/msg/u_int64.hpp>
#include <std_msgs/msg/u_int16_multi_array.hpp>

#include <ros2_heartbeat/publisher/Publisher.h>
#include <ros2_loop_rate_monitor/Monitor.h>

#include "CanManager.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace l3xz
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class Node : public rclcpp::Node
{
public:
  Node();
  ~Node();


private:
  std::unique_ptr<CanManager> _can_mgr;

  static size_t constexpr CYPHAL_O1HEAP_SIZE = (cyphal::Node::DEFAULT_O1HEAP_SIZE * 16);
  static size_t constexpr CYPHAL_TX_QUEUE_SIZE = 256;
  static size_t constexpr CYPHAL_RX_QUEUE_SIZE = 256;
  cyphal::Node::Heap<CYPHAL_O1HEAP_SIZE> _node_heap;
  cyphal::Node _node_hdl;
  std::mutex _node_mtx;

  std::chrono::steady_clock::time_point const _node_start;

  heartbeat::Publisher::SharedPtr _heartbeat_pub;
  void init_heartbeat();

  cyphal::Publisher<uavcan::node::Heartbeat_1_0> _cyphal_heartbeat_pub;
  std::chrono::steady_clock::time_point _prev_heartbeat_timepoint;
  static std::chrono::milliseconds constexpr CYPHAL_HEARTBEAT_PERIOD{1000};
  void init_cyphal_heartbeat();

  cyphal::NodeInfo _cyphal_node_info;
  void init_cyphal_node_info();

  std::map<CanardPortID, rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr> _angle_actual_ros_pub;
  std::map<CanardPortID, cyphal::Subscription> _angle_actual_cyphal_sub;
  void init_cyphal_to_ros_angle_actual();

  std::map<CanardPortID, rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr> _tibia_endpoint_switch_ros_pub;
  std::map<CanardPortID, cyphal::Subscription> _tibia_endpoint_switch_cyphal_sub;
  void init_cyphal_to_ros_tibia_endpoint_switch();

  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr _estop_ros_pub;
  cyphal::Subscription _estop_cyphal_sub;
  void init_cyphal_to_ros_estop();

  rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr _radiation_tick_cnt_ros_pub;
  cyphal::Subscription _radiation_tick_cnt_cyphal_sub;
  void init_cyphal_to_ros_radiation_tick_cnt();

  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr _pressure_0_ros_pub, _pressure_1_ros_pub;
  cyphal::Subscription _pressure_0_cyphal_sub, _pressure_1_cyphal_sub;
  void init_cyphal_to_ros_pressure();

  rclcpp::Subscription<std_msgs::msg::Int8>::SharedPtr _light_mode_ros_sub;
  cyphal::Publisher<uavcan::primitive::scalar::Integer8_1_0> _light_mode_cyphal_pub;
  void init_ros_to_cyphal_light_mode();

  rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr _servo_pulse_width_ros_sub;
  cyphal::Publisher<uavcan::primitive::array::Natural16_1_0> _servo_pulse_width_cyphal_pub;
  void init_ros_to_cyphal_servo_pulse_width();

  rclcpp::Subscription<std_msgs::msg::Int8>::SharedPtr _pump_readiness_ros_sub;
  cyphal::Publisher<reg::udral::service::common::Readiness_0_1> _pump_readiness_cyphal_pub;
  void init_ros_to_cyphal_pump_readiness();

  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr _pump_rpm_setpoint_ros_sub;
  cyphal::Publisher<reg::udral::service::actuator::common::sp::Scalar_0_1> _pump_rpm_setpoint_cyphal_pub;
  void init_ros_to_cyphal_pump_setpoint();

  CanardMicrosecond micros();

  static std::chrono::milliseconds constexpr IO_LOOP_RATE{1};
  loop_rate::Monitor::SharedPtr _io_loop_rate_monitor;
  rclcpp::TimerBase::SharedPtr _io_loop_timer;
  void io_loop();
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* l3xz */

#endif /* ROS_ROS_BRIDGE_NODE_H_ */
