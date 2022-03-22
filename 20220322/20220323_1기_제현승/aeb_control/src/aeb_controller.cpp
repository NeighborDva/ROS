#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Range.h"
#include "nav_msgs/Odometry.h"


std_msgs::Bool flag_AEB;
geometry_msgs::Twist cmd_vel_msg;
std_msgs::Float32 delta_range;
nav_msgs::Odometry pos, delta_pos, past_pos;
double past_range = 0.0;
geometry_msgs::Twist v; //Speed

void UltraSonarCallback(const sensor_msgs::Range::ConstPtr& msg)
{
	//ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	//ROS_INFO("Sonar Range: [%f]", msg->range);
	
	if(msg -> range <= 1.0)
	{
		ROS_INFO("AEB_Activation!!");
		flag_AEB.data = true;
	}
	else
	{
		flag_AEB.data = false;
	}
	
	delta_range.data = msg->range - past_range;
	//ROS_INFO("Delta Sonar Range: [%f]", delta_range.data);
	past_range = msg->range;
}

void UltraSonarCallback2(const sensor_msgs::Range::ConstPtr& msg)
{
	//ROS_INFO("Sonar2 Seq: [%d]", msg->header.seq);
	//ROS_INFO("Sonar2 Range: [%f]", msg->range);
	
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
	//ROS_INFO("Cmd_vel : linear_x [%f]",msg.linear.x); //speed
	cmd_vel_msg.linear.x = msg.linear.x;
	//ROS_INFO("Cmd_vel : angular_z [%f]",msg.angular.z);//steer
	cmd_vel_msg.angular.z = msg.angular.z;
}

void odomCallback(const nav_msgs::Odometry& msg)
{
	ROS_INFO("Pos : x-[%.2lf] y-[%.2lf]", msg.pose.pose.position.x, msg.pose.pose.position.y);
	pos.pose.pose.position.x = msg.pose.pose.position.x;
	pos.pose.pose.position.y = msg.pose.pose.position.y;
	
	delta_pos.pose.pose.position.x = pos.pose.pose.position.x - past_pos.pose.pose.position.x ;
	delta_pos.pose.pose.position.y = pos.pose.pose.position.y - past_pos.pose.pose.position.y ;
	
	ROS_INFO("Delta Pos : x-[%.2lf] y-[%.2lf]", delta_pos.pose.pose.position.x,delta_pos.pose.pose.position.y);
	
	past_pos.pose.pose.position.x  = pos.pose.pose.position.x;
	past_pos.pose.pose.position.y  = pos.pose.pose.position.y;
	
	v.linear.x= delta_pos.pose.pose.position.x / 0.02; //50hz -> t=1/50=0.02
	v.linear.y= delta_pos.pose.pose.position.y / 0.02; //50hz -> t=1/50=0.02
	
	ROS_INFO("Vx: [%.2lf] Vy: [%.2lf]", v.linear.x, v.linear.y);
	
}


int main(int argc, char **argv)
{
	int count = 0;
	
	ros::init(argc, argv,"aeb_controller");
	
	ros::NodeHandle n;
	
	ros::Rate loop_rate(10);
	//ros::Rate loop_rate(1);
	past_pos.pose.pose.position.x =0.0;
	past_pos.pose.pose.position.y =0.0;
	v.linear.x = 0.0 ;
	v.linear.y = 0.0 ;
	std::string odom_sub_topic = "/ackermann_steering_controller/odom"; //50hz
	
	// ros::Publisher pub1 = n.advertise<std_msgs::Bool>("/AEB", 1000);
	ros::Publisher aeb_pub = n.advertise<std_msgs::Bool>("/aeb_activation_flag", 1);
	 ros::Publisher cmd_pub = n.advertise<geometry_msgs::Twist>("/ackermann_steering_controller/cmd_vel", 10);
	 ros::Publisher delta_range_pub = n.advertise<std_msgs::Float32>("/delta_range", 10);
	 ros::Publisher v_pub = n.advertise<geometry_msgs::Twist>("/v_speed", 10);
	 
	
	ros::Subscriber sub_odom = n.subscribe(odom_sub_topic, 10, &odomCallback); 
	ros::Subscriber sub = n.subscribe("range", 1000, UltraSonarCallback);
	ros::Subscriber sub2 = n.subscribe("/RangeSonar1", 1000, UltraSonarCallback2); //package: ultra_sonar_test -> ultra_sonar_test_node 
	ros::Subscriber cmd_sub = n.subscribe("/cmd_vel", 10, CarControlCallback);
	while(ros::ok())
	{
		delta_range_pub.publish(delta_range);
		v_pub.publish(v);
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
