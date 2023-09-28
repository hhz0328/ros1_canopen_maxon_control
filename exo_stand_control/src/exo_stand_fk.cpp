#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>

// C++正运动学fk规划，提供关节角度，实现外骨骼机器人的运动

int main(int argc, char **argv)
{
    /* code */
    ros::init(argc, argv, "exo_stand_fk");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    moveit::planning_interface::MoveGroupInterface leg("maxon");

    leg.setGoalJointTolerance(0.001);

    leg.setMaxAccelerationScalingFactor(0.2);
    leg.setMaxVelocityScalingFactor(0.2);

    // 控制机械臂先回到初始化位置
    leg.setNamedTarget("start");

    leg.move();
    sleep(1);

    // double targetPose[4] = {-0.373, 0, -0.772, 0.7416};
    // std::vector<double> right_joint_positions(2);
    // std::vector<double> left_joint_positions(2);
    // right_joint_positions[0] = targetPose[0];
    // right_joint_positions[1] = targetPose[1];
    // left_joint_positions[0] = targetPose[2];
    // left_joint_positions[1] = targetPose[3];

    double targetPose[2] = {-1.20252, 1.19553};
    std::vector<double> leg_joint_positions(2);
    leg_joint_positions[0] = targetPose[0];
    leg_joint_positions[1] = targetPose[1];

    leg.setJointValueTarget(leg_joint_positions);
    
    leg.move();
    sleep(1);

    // 控制机械臂先回到初始化位置
    leg.setNamedTarget("start");

    leg.move();
    sleep(1);

    ros::shutdown();

    return 0;
}
