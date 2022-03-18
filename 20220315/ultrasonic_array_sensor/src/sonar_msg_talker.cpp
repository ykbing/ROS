#include <ros/ros.h>
#include <ros/xmlrpc_manager.h>
#include <sensor_msgs/Range.h>
#include <sstream>



char frameid[] ="/sonar_ranger";

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Sonar_range_test_pub"); //node name
  ros::NodeHandle n;
   
  sensor_msgs::Range sonar_msg; //sonar_msg declare
  
  ros::Publisher pub_sonar1 = n.advertise<sensor_msgs::Range>("/RangeSonar1",1000); //topic name
  
  ros::Rate loop_rate(2); // 1sec repeat num
   
  std::cout<<ros::XMLRPCManager::instance()->getServerURI()<<std::endl;
  
  sonar_msg.header.frame_id =  frameid;
  sonar_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  sonar_msg.field_of_view = (float)(10.0/180.0) * 3.14;
  sonar_msg.min_range = 0.0;
  sonar_msg.max_range = 50.0; //[m]
  sonar_msg.range = -1.0;

  int count = 0;
  srand(time(NULL));
  while (ros::ok())
  {

    sonar_msg.header.stamp = ros::Time::now();    
    sonar_msg.range = (double)(rand()%30+1)/10;
    ROS_INFO("Sonar range =[%6.3lf]", sonar_msg.range);
    pub_sonar1.publish(sonar_msg);
    
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }


  return 0;
}
