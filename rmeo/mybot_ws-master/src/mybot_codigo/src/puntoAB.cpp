#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>  //libreria para mover la base acepta el goal para que el robot se mueva en la posicion y orientacion especifica
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_broadcaster.h>
#include <sstream>
 
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient; //permite comunicarse con las acciones 
 
 int main(int argc, char** argv){
 ros::init(argc, argv, "simple_navigation_goals");
 
 
  MoveBaseClient ac("move_base", true);

 
     while(!ac.waitForServer(ros::Duration(5.0))){
       ROS_INFO("Waiting for the move_base action server to come up");
     }
   
     move_base_msgs::MoveBaseGoal goal;
   
     
     goal.target_pose.header.frame_id = "map";
     goal.target_pose.header.stamp = ros::Time::now();
   
     goal.target_pose.pose.position.x = 0.5;
     goal.target_pose.pose.orientation.w = 1.0;
   
     ROS_INFO("Sending goal");
     ac.sendGoal(goal);
   
     ac.waitForResult();
   
     if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
       ROS_INFO("Robot se movera hacia adelante");
     else
       ROS_INFO("No se mueve por alguna razon");
   
     return 0;
   }