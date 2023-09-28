#!/usr/bin/env python

# Copyright (c) 2021, maxon motor ag
# All rights reserved.
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# * Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
# * Neither the name of the University of California, Berkeley nor the
#   names of its contributors may be used to endorse or promote products
#   derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Copyright 2021 by maxon motor ag
# All rights reserved.
# @file python_example_1dof_ppm.py
# @author Cyril Jourdan
# @date Nov 24, 2021
# @brief Example code to control one EPOS4 with ROS1 ros_canopen
# This program sends a discrete sinusoidal wave of target position, to be used in PPM 
# Contact: cyril.jourdan@roboprotos.com

import rospy
import math
from std_msgs.msg import Float64 

def epos4_cmd():
    rospy.init_node('maxon_epos4_ros_canopen_python_example', anonymous=True) # initialize the ROS node
    pub_pos = rospy.Publisher('/maxon/canopen_motor/base_link1_joint_position_controller/command', Float64, queue_size=1) # define a publisher
    loop_rate = 50.0 # hz
    period_sec = 60.0 # s
    amplitude = 100000 # inc
    step = 0
    rate = rospy.Rate(loop_rate) 
    while not rospy.is_shutdown():
        cmd_pos = amplitude*math.sin((step/loop_rate)*2*math.pi/period_sec) # calculate a new target position
        pub_pos.publish(cmd_pos) # publish the new target position to the command topic
        step += 1 # increment step
        rate.sleep() # sleep to enforce a 50 Hz loop

if __name__ == '__main__':
    try:
        epos4_cmd() # call the loop function
    except rospy.ROSInterruptException:
        pass
