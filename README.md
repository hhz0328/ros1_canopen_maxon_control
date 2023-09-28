# canopen_maxon_control
## 1）功能介绍
使用了ros_control和ros_canopen官方提供的功能包，完成了can通讯驱动maxon电机，实现了ppm、pvm、csp三种模式的控制。
<br/>
![EPOS4_24_1 5_Compact-2_small](https://user-images.githubusercontent.com/66867384/143435983-b63cc9e0-8983-4f60-9cd4-cbe4f84f76f2.jpg)
  
![maxon_Logo_small](https://user-images.githubusercontent.com/66867384/143436010-5d3968e7-79f8-48b9-a35b-e5159ec20ee6.png)
## 2）环境配置
（1）**用到的功能包**：ros_control、ros_canopen

（2）**编译过程**：将以上的功能包放入到 **/catkin_ws/src** ，再在 **/catkin_ws** 中打开终端用 **catkin_make** 命令进行编译
