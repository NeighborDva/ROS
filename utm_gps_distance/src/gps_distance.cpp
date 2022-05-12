
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/NavSatFix.h"
#include "geometry_msgs/Vector3.h" 
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <math.h>
#include "string"

double distance;

double pos_distance; 

geometry_msgs::Vector3 initial_pos_utm;

int ip=0;

geometry_msgs::PoseStamped outdoor_gps_utm_absolutePos;
geometry_msgs::PoseStamped outdoor_gps_utm_relativePos;
geometry_msgs::PoseStamped initial_pos;

int utm_zone = 52;

void poseCallback(const geometry_msgs::PoseStamped& msg)
{
	//절대좌표, 원점-> 적도, 동경 129도(52구역 기준)
	outdoor_gps_utm_absolutePos.pose.position.x = msg.pose.position.x;
	outdoor_gps_utm_absolutePos.pose.position.y = msg.pose.position.y;
	
	 if(ip==0)
    { //초기위치
		initial_pos_utm.x = outdoor_gps_utm_absolutePos.pose.position.x;
		initial_pos_utm.y = outdoor_gps_utm_absolutePos.pose.position.y;
		ip=1;
	}
	//거리계산
	distance = sqrt(pow(outdoor_gps_utm_absolutePos.pose.position.x - initial_pos_utm.x,2.0)+pow(outdoor_gps_utm_absolutePos.pose.position.y-initial_pos_utm.y,2.0));
	
	//상대좌표 계산(상대 좌표), 현재 위치가 원점
	 outdoor_gps_utm_relativePos.pose.position.x = outdoor_gps_utm_absolutePos.pose.position.x - initial_pos_utm.x;
	 outdoor_gps_utm_relativePos.pose.position.y = outdoor_gps_utm_absolutePos.pose.position.y - initial_pos_utm.y;
	 
	//상대 거리계산 
	pos_distance = sqrt(pow(outdoor_gps_utm_relativePos.pose.position.x,2.0)+pow(outdoor_gps_utm_relativePos.pose.position.y,2.0));
}


int main(int argc, char **argv)
{
  char buf[2];
  ros::init(argc, argv, "gps");
  ros::NodeHandle n;
 
  int coordinate_type = 0;
  int utm_zone = 0;
  char hemisphere='N';
  
   n.getParam("/coordinate_type", coordinate_type);
   n.getParam("/utm_zone", utm_zone);
  // n.getParam("/hemisphere", hemisphere);
    n.getParam("/initial_pos_x", initial_pos.pose.position.x);
    n.getParam("/initial_pos_y", initial_pos.pose.position.y);
   printf("%d",coordinate_type);
    ros::Subscriber subOGps = n.subscribe("/utm",10, &poseCallback);

  
 
  ros::Rate loop_rate(10);  // 10
  
 
  while (ros::ok())
  {	
	
	//ROS_INFO("Outdoor GPS lat : %6.3lf   long : %6.3lf  alt:%6.3lf  Yaw_d: %6.3lf %dN Utm_x:%6.3lf Utm_y:%6.3lf", outdoor_gps.x, outdoor_gps.y, outdoor_gps.z, yaw_d, utm_zone,outdoor_gps_utm.x,outdoor_gps_utm.y); 
  //ROS_INFO("Initial Pos lat : %.7lf   long : %.7lf UTM %d N %.7lf %.7lf",initial_pos.x,initial_pos.y,utm_zone,initial_pos_utm.x,initial_pos_utm.y);

   //ROS_INFO("Outdoor GPS lat : %.7lf   long : %.7lf UTM %d N %.7lf %.7lf", outdoor_gps_currentPos.x, outdoor_gps_currentPos.y,utm_zone,outdoor_gps_utm_currentPos.x,outdoor_gps_utm_currentPos.y); 
  
   printf("%d \n",coordinate_type);
   printf("initial pos utm zone:%d hemisphere: %c x: %.7lf y: %.7lf \n", utm_zone, hemisphere, initial_pos.pose.position.x, initial_pos.pose.position.y);
    

   if(coordinate_type == 0)
   {
	ROS_INFO("UTM  %d coordinate system", coordinate_type);
   ROS_INFO("Initial Pos UTM %d N %.7lf %.7lf",utm_zone,initial_pos_utm.x,initial_pos_utm.y);
  ROS_INFO("Relative Pos x; %.7lf y: %.7lf", outdoor_gps_utm_relativePos.pose.position.x, outdoor_gps_utm_relativePos.pose.position.y);
    ROS_INFO("Relative Pos Distance : %.8lf",pos_distance);
   }
   else{
	   ROS_INFO("UTM %d coordinate system",coordinate_type);
	    ROS_INFO("Abosolute Pos(UTM) %d N %.7lf %.7lf", utm_zone,outdoor_gps_utm_absolutePos.pose.position.x,outdoor_gps_utm_absolutePos.pose.position.y); 
	   ROS_INFO("Absolute Pos Distance : %.8lf",distance);
		}

	loop_rate.sleep();
    ros::spinOnce();
   
  }
  return 0;
}
