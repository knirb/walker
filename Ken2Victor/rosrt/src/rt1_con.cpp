//////////////////////////////////////////////////////////////////////////
//
//		[ROS] RT1 cmd_vel control center
//
//		Subscribe: /rt1_con
//		Publish: /cmd_vel
//
//////////////////////////////////////////////////////////////////////////
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <geometry_msgs/Twist.h>
#include "geometry_msgs/Vector3Stamped.h"
#include

std::string mode;
bool command_move;
bool backward_only = false;
double lin_vel,ang_vel;
double difL,difF,difR;

geometry_msgs::Twist velocity_compute()
{
	geometry_msgs::Twist computed;
    //NEW Intuitive Passive braking
    //Forward
    if(difF>20){
        if(computed.linear.x>0)computed.linear.x = 0;
        else if(computed.linear.x<0)computed.linear.x *=1.3; //Easier Back
        }
    else{
        if(computed.linear.x>0)computed.linear.x*=(0.0025)*pow(difF-20,2);
    }
    if(computed.angular.z>0){
    //Left
        if(difL>20){
            computed.angular.z=0;
        }
        else computed.angular.z*=(0.0025)*pow(difL-20,2);
    }
    else if(computed.angular.z<0){
    //Right
        if(difR>20){
            computed.angular.z=0;
        }
        else computed.angular.z*=(0.0025)*pow(difR-20,2);
    }

    return computed;
}

void Callback_vel(const geometry_msgs::Twist &twist)
{
	lin_vel = twist.linear.x;
	ang_vel = twist.angular.z;
	command_move=true;
}

void Callback_difficulty(const geometry_msgs::Vector3Stamped &diff)
{
    difL=diff.vector.x;
    difF=diff.vector.y;
    difR=diff.vector.z;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "rt1control");
    ros::NodeHandle n;
    geometry_msgs::Twist computed_vel;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    ros::Subscriber sub_vel = n.subscribe("/rt1_con/vel", 10, Callback_vel);
    ros::Subscriber sub_difficulty = n.subscribe("/rt1_con/difficulty", 10, Callback_difficulty);
    ros::Rate rate(10);
    while(ros::ok())
    {
     	if (command_move){
     		computed_vel = velocity_compute();
        pub.publish(computed_vel);
        command_move=false;
    	}
        rate.sleep();
        ros::spinOnce();
    }


    return 0;
}
