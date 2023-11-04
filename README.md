# canopen_maxon_control
## 软件包更新时间
2023.7.28
## 1）功能介绍
使用了ros_control和ros_canopen官方提供的功能包，完成了can通讯驱动maxon电机，实现了ppm（位置模式）、pvm（速度模式）、csp（循环同步位置控制）三种模式的控制。
<br/>
![EPOS4_24_1 5_Compact-2_small](https://user-images.githubusercontent.com/66867384/143435983-b63cc9e0-8983-4f60-9cd4-cbe4f84f76f2.jpg)
  
![maxon_Logo_small](https://user-images.githubusercontent.com/66867384/143436010-5d3968e7-79f8-48b9-a35b-e5159ec20ee6.png)

![](https://github.com/hhz0328/ros_exoskeleton_maxon_simulation/blob/main/%E4%BB%BF%E7%9C%9F%E6%8E%A7%E5%88%B6%E6%A1%86%E6%9E%B6.jpg)
## 2）环境配置
（1）**用到的功能包**：ros_control、ros_canopen

（2）**编译过程**：将以上的功能包放入到 **/catkin_ws/src** ，再在 **/catkin_ws** 中打开终端用 **catkin_make** 命令进行编译
## 3）使用
- **（1）单个电机的ppm位置模式控制：**
```
  $ roscore
  $ sudo ip link set can0 type can bitrate 1000000
  $ sudo ip link set can0 up
  $ roslaunch maxon_epos4_ros_canopen maxon_epos4_canopen_motor_1dof_ppm.launch
  $ rosservice call /driver/init
  $ rostopic pub /canopen_motor/base_link1_joint_position_controller/command std_msgs/Float64 -- 1000
```
- **（2）双电机的pvm速度模式控制：**
```
  $ roscore
  $ sudo ip link set can0 type can bitrate 1000000
  $ sudo ip link set can0 up
  $ roslaunch maxon_epos4_ros_canopen maxon_epos4_canopen_motor_2dof_pvm.launch
  $ rosservice call /driver/init
  $ rosservice call /maxon/driver/set_object base_link1_joint '!!str6081' '!!str 1000' false
```
- **（3）多电机的csp循环同步位置模式控制（经过测试，可以稳定驱动4个电机）：**
```
  $ roscore
  $ sudo ip link set can0 type can bitrate 1000000
  $ sudo ip link set can0 up
  $ roslaunch maxon_epos4_ros_canopen maxon_epos4_canopen_motor_4dof_csp.launch
  $ rosservice call /driver/init
  $ roslaunch exo_stand_moveit_config demo.launch rviz_tutorial:=true
```
