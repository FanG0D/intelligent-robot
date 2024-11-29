#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

// 话题发布者定义
ros::Publisher action_pub;

// 处理cmd_vel话题的回调函数
void DirectionTrans(const geometry_msgs::Twist msg)
{
    double time = 2;
    geometry_msgs::Twist trans;
    trans.linear.x = (msg.linear.x) * time;
    trans.linear.y = (msg.linear.x) * time;
    trans.linear.z = msg.linear.z;
    trans.angular.x = (msg.angular.x) * time;
    trans.angular.y = (msg.angular.y) * time;
    trans.angular.z = msg.angular.z;

    // 发布转换数据
    action_pub.publish(trans);

    // 终端打印信息
    ROS_INFO("转换后的海龟X轴线速度为%f角速度为%f，y轴线速度为%f角速度为%f，z轴线速度为%f角速度为%f", trans.linear.x, trans.angular.x, trans.linear.y, trans.angular.y, trans.linear.z, trans.angular.z);
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    // runner节点初始化
    ros::init(argc, argv, "runner");

    // 节点管理
    ros::NodeHandle n;

    // 发布cmd_vel_modified话题
    action_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_modified", 10);

    // 订阅消息
    ros::Subscriber turtle_sub = n.subscribe("/turtle1/cmd_vel", 10, DirectionTrans);

    ros::spin();
    return 0;
}