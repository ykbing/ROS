 #include "ros/ros.h"
 #include "std_msgs/Int8.h"
 #include "std_msgs/Bool.h"       // boolean data
 #include "std_msgs/String.h"
 #include "std_msgs/Float32.h"
 #include "sensor_msgs/Range.h"   // ultrasonic sensor message
 #include "geometry_msgs/Twist.h" // cmd_vel
 #include "nav_msgs/Odometry.h"
 
 std_msgs::Bool flag_AEB;
 geometry_msgs::Twist cmd_vel_msg;
 std_msgs::Float32 delta_range;
 std_msgs::Float32 old_sonar_range;
 nav_msgs::Odometry pos, delta_pos, past_pos, velocity;
 
 void UltraSonarCallback(const sensor_msgs::Range::ConstPtr& msg)
 {
	 //ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	// ROS_INFO("Sonar Range: [%f]", msg->range);
	 
	 if(msg->range<=1.8)
	 {
		 //ROS_INFO("AEB_Activation!!");
		 flag_AEB.data = true;
	 }
	 else
	 {
		 flag_AEB.data = false;
	 }
	 
        delta_range.data = old_sonar_range.data - msg->range;	
	   // ROS_INFO("delta_range: [%f]",delta_range.data);
	    old_sonar_range.data = msg->range;
	 
 }

 
 void CarControlCallback(const geometry_msgs::Twist& msg)
 {
	 //ROS_INFO("Cmd_vel : linear_x [%f]", msg.linear.x);
	 
	  cmd_vel_msg = msg;
	 //ROS_INFO("Cmd_vel : linear_x [%f]", msg.linear.x);
 }
 
 void odomCallback(const nav_msgs::Odometry& msg)
{
    //ROS_INFO("%.2f %.2f",msg.pose.pose.position.x, msg.pose.pose.position.y);
	pos.pose.pose.position.x=msg.pose.pose.position.x;
	pos.pose.pose.position.y=msg.pose.pose.position.y;
	
	delta_pos.pose.pose.position.x=pos.pose.pose.position.x-past_pos.pose.pose.position.x;
	delta_pos.pose.pose.position.y=pos.pose.pose.position.y-past_pos.pose.pose.position.y;
	
	past_pos.pose.pose.position.x = msg.pose.pose.position.x;
	past_pos.pose.pose.position.y = msg.pose.pose.position.y;

	velocity.pose.pose.position.x=delta_pos.pose.pose.position.x/0.02; 
	velocity.pose.pose.position.y=delta_pos.pose.pose.position.y/0.02; 
		
	ROS_INFO("vx= [%f] , vy= [%f]",velocity.pose.pose.position.x,velocity.pose.pose.position.y);	
	
}
	 
 /*void UltraSonarCallback2(const sensor_msgs::Range::ConstPtr& msg)
{
	 ROS_INFO("Sonar2 Seq: [%d]", msg->header.seq);
	 ROS_INFO("Sonar2 Range: [%f]", msg->range);
 }*/
	 
 
 int main(int argc, char **argv)
 {
	 int count = 0;
	 old_sonar_range.data = 0;
	 
	 ros::init(argc, argv, "aeb_controller");  // node name
	 
	 ros::NodeHandle n;
	 
	 std::string odom_sub_topic = "/ackermann_steering_controller/odom";
	 
	 ros::Subscriber sub = n.subscribe("/range", 1000, UltraSonarCallback);
	 //ros::Subscriber sub2 = n.subscribe("/RangeSonar1", 1000, UltraSonarCallback2);
	 ros::Subscriber cmd_vel_sub = n.subscribe("/cmd_vel", 10, &CarControlCallback); 
	 ros::Subscriber sub_odom = n.subscribe(odom_sub_topic, 10, &odomCallback);
	 
	 ros::Publisher pub_aeb_activation_flag = n.advertise<std_msgs::Bool>("aeb_activation_flag", 1);
	 ros::Publisher pub_cmd_vel = n.advertise<geometry_msgs::Twist>("/ackermann_steering_controller/cmd_vel", 10); 
	 ros::Publisher pub_velocity = n.advertise<nav_msgs::Odometry>("/velocity", 10);
	 
	  ros::Rate loop_rate(10);

 while(ros::ok())
 {
	 if((count % 10) == 0)
	 {
		 pub_aeb_activation_flag.publish(flag_AEB);
	 }
	 
	 if(flag_AEB.data == true)
	 {
		 cmd_vel_msg.linear.x = 0;
		 pub_cmd_vel.publish(cmd_vel_msg);
	 }
	 
	 else
	 {
		 pub_cmd_vel.publish(cmd_vel_msg);
	 }
	 
	 
	 loop_rate.sleep();
	 ros::spinOnce();
	 ++count;
 }
 return 0;
	
}
