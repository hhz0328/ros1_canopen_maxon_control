

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_srvs/Trigger.h>
#include <sensor_msgs/JointState.h>

using namespace std;

/*** global variables ***/
sensor_msgs::JointState joint_state;
bool js_arrived = false;

/** @brief Function that displays the menu in the terminal */
void display_menu()
{
	ROS_INFO("MENU");
	ROS_INFO("1 - driver init");
	ROS_INFO("2 - driver halt");
	ROS_INFO("3 - driver recover");
	ROS_INFO("4 - driver shutdown");
	ROS_INFO("5 - set Target Position");
	ROS_INFO("6 - get Position Actual Value");
	ROS_INFO("7 - Exit");
}

/** @brief Callback function for the Joint State subscriber */
void jointStateCallback(const sensor_msgs::JointState::ConstPtr& msg)
{
  joint_state = *msg;
  js_arrived = true;
}

/** @brief main function */
int main(int argc, char** argv)
{
	// Initialize the ROS node
	ros::init(argc, argv, "maxon_epos4_ros_canopen_cpp_example");
	ros::NodeHandle nh("~");

	// Variables
	int menu_i = 0; // integer to store the menu choice
	int cmd_pos_i = 0; // integer to store the target position
	std_msgs::Float64 cmd_pos; // float standard message corresponding to the command topic
	cmd_pos.data = 0;
	std_srvs::Trigger srv; // Trigger variable for calling driver services
	bool exit = false; // integer for controlling the loop

	// Service clients
	ros::ServiceClient clt_driver_init = nh.serviceClient<std_srvs::Trigger>("/maxon/driver/init");
	ros::ServiceClient clt_driver_halt = nh.serviceClient<std_srvs::Trigger>("/maxon/driver/halt");
	ros::ServiceClient clt_driver_recover = nh.serviceClient<std_srvs::Trigger>("/maxon/driver/recover");
	ros::ServiceClient clt_driver_shutdown = nh.serviceClient<std_srvs::Trigger>("/maxon/driver/shutdown");

	// Topic Publisher
	ros::Publisher pub_pos = nh.advertise<std_msgs::Float64>("/maxon/canopen_motor/base_link1_joint_position_controller/command", 1);

	// Topic Subscriber
	ros::Subscriber sub_js = nh.subscribe("/maxon/joint_states", 1, jointStateCallback); 

	// Display UI in terminal
	ROS_INFO("********************************************");
	ROS_INFO("maxon EPOS4 - ROS 1 ros_canopen example code");
	ROS_INFO("To be used with 1 EPOS4 with Node-ID 1");
	ROS_INFO("To run after roslaunch of a PPM example");
	ROS_INFO("********************************************");

	display_menu();

	while(!exit)
	{
		// Ask for user input
		ROS_INFO("Please enter a menu choice:");
		std::cin >> menu_i;

		switch(menu_i)
		{
			case 1:
				clt_driver_init.call(srv); // call init service
				break;

			case 2:
				clt_driver_halt.call(srv); // call halt service
				break;

			case 3:
				clt_driver_recover.call(srv); // call recover service
				break;

			case 4:
				clt_driver_shutdown.call(srv); // call shutdown service
				break;

			case 5:
				ROS_INFO("Enter a Target Position to send to Node-ID 1 in PPM:");
				std::cin >> cmd_pos_i;

				cmd_pos.data = (float)cmd_pos_i; // cast the integer to float and store in command data 

				// Publish the value to the controller
				pub_pos.publish(cmd_pos);

				ROS_INFO("Target Position sent with value = %f", cmd_pos.data);
				break;

			case 6:
				// Process subscriber callback
				ros::spinOnce();

				if(js_arrived) // check if the callback has been executed
				{				
					ROS_INFO("Position Actual Value = %f", joint_state.position[0]);

					js_arrived = false;
				}
				break;

			case 7:
				exit = true; // exit the while loop next time and then the main function
				break;

			default:
				ROS_ERROR("Please enter a correct menu value!");
		}
	}

	return 0;
}
