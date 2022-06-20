<a href="https://107-systems.org/"><img align="right" src="https://raw.githubusercontent.com/107-systems/.github/main/logo/107-systems.png" width="15%"></a>
:floppy_disk: L3X-Z
===================
L3X-Z base robot control package (ROS).

### Articles
* 2022/6/8: [L3X-Z - A OpenCyphal enabled hexapod robot for ELROB 2022](https://forum.opencyphal.org/t/l3x-z-a-opencyphal-enabled-hexapod-robot-for-elrob-2022/)

<p align="center">
  <a href="https://github.com/107-systems/l3xz"><img src="doc/img/2022-05-31-ELROB-2022-L3X-Z.jpg" width="40%"></a>
</p>

### Related Repositories
| Name | Description |
|-|-|
| [l3xz](https://github.com/107-systems/l3xz) | ROS based control software for L3X-Z, a mixed electric/hydraulic hexapod. |
| [l3xz_teleop](https://github.com/107-systems/l3xz_teleop) | Teleoperation for L3X-Z via PS3 joystick and ROS topics. |
| [l3xz_sweep_scanner](https://github.com/107-systems/l3xz_sweep_scanner) | ROS driver for Scanse Sweep 360° 2D LIDAR. |
| [l3xz_openmv_camera](https://github.com/107-systems/l3xz_openmv_camera) | ROS driver for OpenMV camera. |
| [l3xz-mapping](https://github.com/107-systems/l3xz-mapping) | Docker container containing the mapping stack for L3X-Z. |
| [l3xz-hw](https://github.com/107-systems/l3xz-hw) | L3X-Z Hexapod hardware design files (3D model, printed parts, etc.) |
| [l3xz-hw_leg-controller](https://github.com/107-systems/l3xz-hw_leg-controller) | L3X-Z Hexapod leg controller hardware design files |
| [l3xz-fw_aux-controller](https://github.com/107-systems/l3xz-fw_aux-controller) | Firmware for the auxiliary controller (alarm LEDs and emergency stop) |
| [l3xz-fw_leg-controller](https://github.com/107-systems/l3xz-fw_leg-controller) | Firmware for the leg controller. |
| [l3xz-fw_radiation_sensor](https://github.com/107-systems/l3xz-fw_radiation_sensor) | Firmware for the radiation sensor |

### Developer Setup
#### Target (Robot)
[Raspberry Pi 4/8 GB](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/), [Buster](https://www.raspberrypi.com/software/operating-systems/#raspberry-pi-os-legacy), [ROS Noetic Ninjemys](https://varhowto.com/install-ros-noetic-raspberry-pi-4/).
#### Host (Devlopment PC)
Ubuntu 20.04 LTS, [ROS Noetic Ninjemys](http://wiki.ros.org/noetic/Installation/Ubuntu).

### How-to-build
Install Dependencies:
* [orocos-kdl](https://github.com/orocos/orocos_kinematics_dynamics):
  * How-to-build from [source](https://github.com/orocos/orocos_kinematics_dynamics/blob/master/orocos_kdl/INSTALL.md)
  * Install a [prebuilt](https://github.com/107-systems/orocos-kdl-debian) Debian package

Build via [`catkin_make`](http://wiki.ros.org/catkin):
```bash
# Clone this repository into catkin_ws/src.
git clone https://github.com/107-systems/l3xz
# Invoke catkin_make from the catkin workspace root.
source /opt/ros/noetic/setup.bash
catkin_make
```

### How-to-run
```bash
source devel/setup.bash
roslaunch l3xz robot.launch
```
