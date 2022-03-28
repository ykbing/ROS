 #include "ros/ros.h"
 #include "std_msgs/Int8.h"
 #include "std_msgs/Bool.h"       // boolean data
 #include "std_msgs/String.h"
 #include "std_msgs/Float32.h"
 #include "sensor_msgs/Range.h"   // ultrasonic sensor message
 #include "geometry_msgs/Twist.h" // cmd_vel
 #include "nav_msgs/Odometry.h"
 
 #define frequency_odom_pub 50    //hz
 #define place_x 3
 
 std_msgs::Bool flag_AEB;
 std_msgs::Float32 delta_range;
 std_msgs::Float32 old_sonar_range;
 geometry_msgs::Twist cmd_vel_msg;
 
 float x, y;                           // vehicle position[m/s]
 float delta_x, delta_y;
 float vx, vy;                         // vehicle velocity[m/s]
 float aeb_collision__distance = 200;  // enagementdistance[m]
 
 void odomCallback(const nav_msgs::Odometry& msg) // vehicle position
{
    float old_x, old_y;
    
    old_x = x;
    old_y = y;
    
    ROS_INFO("%.2lf %.2lf", msg.pose.pose.position.x, msg.pose.pose.position.y);
    
    x = msg.pose.pose.position.x;
    y = msg.pose.pose.position.y;
	
	delta_x = x - old_x;
	delta_y = y - old_y;
	
	vx = delta_x * frequency_odom_pub;    // velocity = delta_x / delta_t => frequency = 1 / delta_t
	vy = delta_y * frequency_odom_pub;    // so, velocity = delta_x * frequency
		
	ROS_INFO("vx= [%f] , vy= [%f]", vx, vy);
	
	if(place_x <= x)
	{
		cmd_vel_msg.linear.x = 0; 
	}
}

 void UltraSonarCallback(const sensor_msgs::Range::ConstPtr& msg)
 {
	 //ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	 //ROS_INFO("Sonar Range: [%f]", msg->range);
	 
	 aeb_collision__distance = vx * (0.7 + 0.1) * 0.22778 * 2.5; // 1m/s = 0.22778km/h
	 
	 if(msg->range <= aeb_collision__distance) 
	 {
		 ROS_INFO("AEB_Activation!!");
		 flag_AEB.data = true;
	 }
	 else
	 {
		 flag_AEB.data = false;
	 }
	 
 }

 
 void CarControlCallback(const geometry_msgs::Twist& msg)
 {
	 //ROS_INFO("Cmd_vel : linear_x [%f]", msg.linear.x);
	 
	  cmd_vel_msg = msg;
	 //ROS_INFO("Cmd_vel : linear_x [%f]", msg.linear.x);
 }
	 
 
 int main(int argc, char **argv)
 {
	 int count = 0;
	 old_sonar_range.data = 0;
	 
	 ros::init(argc, argv, "aeb_controller");  // node name
	 
	 ros::NodeHandle n;
	 
	 std::string odom_sub_topic = "/ackermann_steering_controller/odom";
	 
	 ros::Subscriber sub = n.subscribe("/range", 1000, UltraSonarCallback);
	 ros::Subscriber cmd_vel_sub = n.subscribe("/cmd_vel", 10, &CarControlCallback); 
	 ros::Subscriber sub_odom = n.subscribe(odom_sub_topic, 10, &odomCallback);
	 
	 ros::Publisher pub_aeb_activation_flag = n.advertise<std_msgs::Bool>("aeb_activation_flag", 1);
	 ros::Publisher pub_cmd_vel = n.advertise<geometry_msgs::Twist>("/ackermann_steering_controller/cmd_vel", 10); 
	 
	  ros::Rate loop_rate(10);        // 10Hz

 while(ros::ok())
 {
	 if((count % 10) == 0)
	 {
		 pub_aeb_activation_flag.publish(flag_AEB);
	 }
	 
	 if(flag_AEB.data == true)
	 {
		 if(cmd_vel_msg.linear.x > 0)
		 {
			cmd_vel_msg.linear.x = 0; 
		 }
		 pub_cmd_vel.publish(cmd_vel_msg);
	 }
	 
	 else
	 {
		 pub_cmd_vel.publish(cmd_vel_msg);
	 }
	 
	//aeb_collision__distance = vx * (1 / 10); // Because, loop_rate(10)
	 
	 ROS_INFO("Odom : [%6.3f %6.3f] m | Velocity : [%6.3f %6.3f] m/s", x, y, vx, vy);
	 ROS_INFO("Collision Distance : %6.3f", aeb_collision__distance);
	 
	 loop_rate.sleep();
	 ros::spinOnce();
	 ++count;
 }
 return 0;
	
}
