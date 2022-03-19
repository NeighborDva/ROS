#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Range.h"

std_msgs::Bool flag_AEB;
geometry_msgs::Twist cmd_vel_msg;

void UltraSonarCallback(const sensor_msgs::Range::ConstPtr& msg)
{
	ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	ROS_INFO("Sonar Range: [%f]", msg->range);
	
	if(msg -> range <= 1.0)
	{
		ROS_INFO("AEB_Activation!!");
		flag_AEB.data = true;
	}
	else
	{
		flag_AEB.data = false;
	}
}

void UltraSonarCallback2(const sensor_msgs::Range::ConstPtr& msg)
{
	ROS_INFO("Sonar2 Seq: [%d]", msg->header.seq);
	ROS_INFO("Sonar2 Range: [%f]", msg->range);
	
	if(msg -> range <= 1.0)
	{
		ROS_INFO("AEB_Activation!! ");
		flag_AEB.data = true;
	}
	else
	{
		flag_AEB.data = false;
	}
}


void CarControlCallback(const geometry_msgs::Twist& msg)
{
	ROS_INFO("Cmd_vel : linear_x [%f]",msg.linear.x); //speed
	cmd_vel_msg.linear.x = msg.linear.x;
	ROS_INFO("Cmd_vel : angular_z [%f]",msg.angular.z);//steer
	cmd_vel_msg.angular.z = msg.angular.z;
}

int main(int argc, char **argv)
{
	int count = 0;
	
	ros::init(argc, argv,"aeb_controller");
	
	ros::NodeHandle n;
	
	ros::Rate loop_rate(10);
	//ros::Rate loop_rate(1);
	
	// ros::Publisher pub1 = n.advertise<std_msgs::Bool>("/AEB", 1000);
	ros::Publisher aeb_pub = n.advertise<std_msgs::Bool>("/aeb_activation_flag", 1);
	 ros::Publisher cmd_pub = n.advertise<geometry_msgs::Twist>("/ackermann_steering_controller/cmd_vel", 10);
	 
	
	ros::Subscriber sub = n.subscribe("range", 1000, UltraSonarCallback);
	ros::Subscriber sub2 = n.subscribe("/RangeSonar1", 1000, UltraSonarCallback2); //package: ultra_sonar_test -> ultra_sonar_test_node 
	ros::Subscriber cmd_sub = n.subscribe("/cmd_vel", 10, CarControlCallback);
	while(ros::ok())
	{
		if((count % 10)==0) //rate -> 1
		{
			aeb_pub.publish(flag_AEB);
		}
		
		if(flag_AEB.data == true)
		{
			cmd_vel_msg.linear.x = 0;
			cmd_pub.publish(cmd_vel_msg);
		}
		else
		{
			cmd_pub.publish(cmd_vel_msg);
		}
		
		
		loop_rate.sleep();
		ros::spinOnce();
		++count;
	}
	
	return 0;
}
