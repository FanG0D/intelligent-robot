#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char **argv)
{
    // 初始化ROS节点，名称为“talker”
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;

    // 创建发布者，话题名称为“chatter”，消息类型为std_msgs::String
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10); // 设置发布频率为10Hz

    int count = 0;
    while (ros::ok())
    {
        // 创建消息
        std_msgs::String msg;
        std::stringstream ss;
        ss << "hello world " << count;
        msg.data = ss.str();

        // 输出发布的消息内容
        ROS_INFO("%s", msg.data.c_str());

        // 发布消息
        chatter_pub.publish(msg);

        // 确保按设定频率发布
        ros::spinOnce();
        loop_rate.sleep();
        ++count;
    }
    return 0;
}