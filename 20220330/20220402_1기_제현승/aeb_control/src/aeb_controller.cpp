#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Range.h"
#include "nav_msgs/Odometry.h"
#define move_stop_distance 2.0


//교수님
#define frequency_odom_pub 50

float x,y;
float delta_x, delta_y;
float vx,vy;

//
std_msgs::Bool flag_AEB;
std_msgs::Bool flag_STOP;
geometry_msgs::Twist cmd_vel_msg;
std_msgs::Float32 delta_range;
nav_msgs::Odometry pos, delta_pos, past_pos;
double past_range = 0.0;
geometry_msgs::Twist v; //Speed

//1.최초의 위치 기억후 최초의 위치와 현재위치의 델타를 구해서 하는 방법, 2.델타 pos를 누적해서 그거의 sqrt해서 거리 구하는 법 있음
float move_distance; 
float delta_x_sum=0.0, delta_y_sum = 0.0;

float aeb_collision_distance = 200;
float collision_distance = 0;


//0330 과제
geometry_msgs::Twist estimated_odom;
//0331 과제
int cnt=0;
float sum =0;
float range_avg = 0;
float range_data = 0;

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
		range_avg = sum/5 ;
		sum=0;
		cnt=0;
	}
}

void UltraSonarCallback(const sensor_msgs::Range::ConstPtr& msg)
{
	//ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	//ROS_INFO("Sonar Range: [%f]", msg->range);
	
	aeb_collision_distance = vx * (0.7 + 0.1) * 0.22778 * 2.1; //공주거리:0.1, 제동거리: 0.7 ,1m/sec = 0.22778 km/h, 안전계수:2.1
	
	if(msg -> range <= aeb_collision_distance)
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
//교수님
void odomCallback2(const nav_msgs::Odometry& msg)
{
	float old_x, old_y;
	old_x = x;
	old_y = y;
	
	//ROS_INFO("Pos : x-[%.2lf] y-[%.2lf]", msg.pose.pose.position.x, msg.pose.pose.position.y);
	x = msg.pose.pose.position.x;
	y = msg.pose.pose.position.y;
	
	estimated_odom.linear.x = msg.twist.twist.linear.x;
	estimated_odom.angular.z = msg.twist.twist.angular.z;
	
	delta_x = x - old_x;
	delta_y = y - old_y;
	delta_x_sum = delta_x_sum + delta_x;
	delta_y_sum = delta_y_sum + delta_y;
	
	vx = delta_x * frequency_odom_pub;
	vy = delta_y * frequency_odom_pub; 
	
	move_distance = sqrt(delta_x_sum * delta_x_sum + delta_y_sum * delta_y_sum);
	
	if(move_distance >= move_stop_distance)
	{
		ROS_INFO("Setted Distance_Arrived!! ");
		flag_AEB.data = true;
	}
	else
	{
		flag_AEB.data = false;
	}
}

int main(int argc, char **argv)
{
	int count = 0;
	int stop_sec = 0;
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
	 ros::Publisher estimated_odom_pub = n.advertise<geometry_msgs::Twist>("/estimated_odom", 10);
	 
	
	ros::Subscriber sub_odom = n.subscribe(odom_sub_topic, 10, &odomCallback2); 
	ros::Subscriber sub = n.subscribe("range", 1000, UltraSonarCallback);
	ros::Subscriber sub3 = n.subscribe("range", 1000, rangeCallback);
	ros::Subscriber sub2 = n.subscribe("/RangeSonar1", 1000, UltraSonarCallback2); //package: ultra_sonar_test -> ultra_sonar_test_node 
	ros::Subscriber cmd_sub = n.subscribe("/cmd_vel", 10, CarControlCallback);
	while(ros::ok())
	{
		estimated_odom_pub.publish(estimated_odom);
		delta_range_pub.publish(delta_range);
		v_pub.publish(v);
		if((count % 10)==0) //rate -> 1
		{
			aeb_pub.publish(flag_AEB);
		}
		if(flag_STOP.data == true)
		{	
			cmd_vel_msg.linear.x = 0;
			cmd_pub.publish(cmd_vel_msg);	
		}
		if(flag_AEB.data == true)
		{
			if(cmd_vel_msg.linear.x>0)cmd_vel_msg.linear.x = 0;
			cmd_pub.publish(cmd_vel_msg);
		}
		else
		{
			cmd_pub.publish(cmd_vel_msg);
		}
		//교수님
		//collision_distance = vx * (1/10.0); //0.1초마다 충돌거리 계산
		ROS_INFO("Odom : [%6.3lf %6.3lf] | Velocity : [%6.3lf %6.3lf]", x, y, vx, vy);
		//ROS_INFO("Delta Pos : x-[%.2lf] y-[%.2lf]", delta_x,delta_y);
		ROS_INFO("Collision Distance : %6.3lf", aeb_collision_distance);
		
		
		
		loop_rate.sleep();
		ros::spinOnce();
		++count;
	}
	
	return 0;
}
