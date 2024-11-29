#include "ros/ros.h"             //引用ros的头文件
#include "geometry_msgs/Twist.h" //引用小海龟的消息类型

ros::Publisher transform_pub; // 定义一个话题的发布者transform_pub

void TransformCallback(const geometry_msgs::Twist msg) // 定义一个回调函数，用于海龟/turtle1/cmd_vel话题的订阅
{
    geometry_msgs::Twist transform; // 定义一个消息类型，用于处理cmd_vel的转换
    // 数据处理：将海龟cmd_vel中数据（线速度和角速度）的x,y,z坐标进行旋转，将x轴变成y轴，y轴变成x轴
    transform.linear.x = msg.linear.y;
    transform.linear.y = msg.linear.x;
    transform.linear.z = msg.linear.z;
    transform.angular.x = msg.angular.y;
    transform.angular.y = msg.angular.x;
    transform.angular.z = msg.angular.z;
    // 将处理后的数据发布出去
    transform_pub.publish(transform);
    // 通过ROS_INFO和ROS_WARN在终端中输出海龟的运动信息
    ROS_INFO("坐标变换后，小海龟x轴线速度为%f,y轴线速度为%f,z轴线速度为%f,", transform.linear.x, transform.linear.y, transform.linear.z);
    ROS_WARN("坐标变换后，小海龟x轴角速度为%f,y轴角速度为%f,z轴角速度为%f,", transform.angular.x, transform.angular.y, transform.angular.z);
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");                   // 中文字符不乱码
    ros::init(argc, argv, "transform_node"); // 初始化transform_node节点

    ros::NodeHandle n; // 定义节点管理者

    transform_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_cov", 10); // 发布一个叫做/cmd_vel_cov的话题

    ros::Subscriber turtle_sub = n.subscribe("/turtle1/cmd_vel", 10, TransformCallback); // 通过回调函数订阅/turtle1/cmd_vel

    ros::spin(); // 进行循环
    return 0;
}
