//////////////////////////////////////////////////////////////////////////
//
//		[ROS] RT1 Gather Data
//
//		Subscribe: /rosrt_rt1
//
//
//////////////////////////////////////////////////////////////////////////

#include "ros/ros.h"
#include "ros_start/Rt1Sensor.h"
#include <iostream>
#include <fstream>

double lin_vel, ang_vel, handle_force, handle_torque, acc_lin, acc_ang, handleadj_force, handleadj_torque;
double callback_done = false;

void getValues(const ros_start::Rt1Sensor &msg){
  lin_vel = msg.velocity.linear.x;
  ang_vel = msg.velocity.angular.x;
  handle_force = msg.handle.force.x;
  handle_torque = msg.handle.torque;
  acc_lin = msg.accel.linear.x;
  acc_ang = msg.accel.angular.x;
  handleadj_force = msg.handleadj.force;
  handleadj_torque = msg.handleadj.torque;
  message_arrived = true;
}

int main(int argc, char **argv){
  ros:init(argc, argv, "rt1data");
  ros::NodeHandle n;
  ros_start::Rt1Sensor msg;
  ros::Subscriber sub = n.subscribe("rosrt_rt1", 1000, getValues);

  std::fstream file;
  file.open("test.txt", std::fstream::out);
  file<<"test";
  while(ros::ok()){
    if(callback_done){

      callback_done = false;
    }
    ros::spinOnce();
  }
  file.close();
}
