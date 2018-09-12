#include <ros/ros.h>
#include <iostream>
#include <geometry_msgs/Twist.h>
#include "keyboard.h"
double speed;
double rotate;
double speedmax = 0.3;
double speedmin = -0.3;
double rotatemax = 0.6;
double rotatemin = -0.6;
bool callback=false;

void Callback(const keyboard::Key &keydown)
{
	int button = keydown.code;
	if (button==273) speed=speedmax;//up
	else if (button==274) speed=speedmin;//down
	else speed = 0;
	if (button==275) rotate=rotatemin;//left
	else if (button==276) rotate=rotatemax;//right
	else rotate = 0;
	if (button==280) speed=0,rotate=0;
	if (speed<0) rotate=-rotate;
	callback = true;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv,"controller");
	ros::NodeHandle node;
	geometry_msgs::Twist command;
	ros::Publisher pub_move = node.advertise<geometry_msgs::Twist>("/rt1_con/vel", 10);
	ros::Subscriber key_sub = node.subscribe("/keyboard/keydown",10,Callback);
	ros::Rate rate(1);
	while(ros::ok())
	{
		command.linear.x = speed;
		command.angular.z = rotate;
		if (callback==true){
			pub_move.publish(command);
			callback = false;
		}
		rate.sleep();
		ros::spinOnce();
	}
	return 0;
}
