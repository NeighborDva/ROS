#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Range.h"
#include "nav_msgs/Odometry.h"

//0331 과제
int cnt=0;
float sum =0;
float range_data = 0;
std_msgs::Float64 range_avg;

void rangeCallback(const sensor_msgs::Range::ConstPtr& msg)
{
	range_data = msg -> range;
	if(cnt<5)
	{
		sum = sum + range_data;
		cnt++; 
	}
	else
	{
		range_avg.data = sum/5 ;
		sum=0;
		cnt=0;
	}
}


int main(int argc, char **argv)
{
	int count = 0;
	int stop_sec = 0;
	ros::init(argc, argv,"sonar_avg_filter_node");
	
	ros::NodeHandle n;
	
	ros::Rate loop_rate(10);
	//ros::Rate loop_rate(1);
	
	// ros::Publisher pub1 = n.advertise<std_msgs::Bool>("/AEB", 1000);
	 ros::Publisher range_avg_pub = n.advertise<std_msgs::Float64>("/range_avg", 10);
	
	 
	

	ros::Subscriber sub1 = n.subscribe("range", 1000, rangeCallback);
	
	while(ros::ok())
	{
		range_avg_pub.publish(range_avg);
		
		loop_rate.sleep();
		ros::spinOnce();
		++count;
	}
	
	return 0;
}
