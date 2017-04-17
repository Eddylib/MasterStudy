//
// Created by libaoyu on 17-4-14.
//
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/CameraInfo.h"
#include <sstream>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
    ros::init(argc, argv, "calib_talker");

    /**
     * NodeHandle is the main access point to communications with the ROS system.
     * The first NodeHandle constructed will fully initialize this node, and the last
     * NodeHandle destructed will close down the node.
     */
    ros::NodeHandle n;

    /**
     * The advertise() function is how you tell ROS that you want to
     * publish on a given topic name. This invokes a call to the ROS
     * master node, which keeps a registry of who is publishing and who
     * is subscribing. After this advertise() call is made, the master
     * node will notify anyone who is trying to subscribe to this topic name,
     * and they will in turn negotiate a peer-to-peer connection with this
     * node.  advertise() returns a Publisher object which allows you to
     * publish messages on that topic through a call to publish().  Once
     * all copies of the returned Publisher object are destroyed, the topic
     * will be automatically unadvertised.
     *
     * The second parameter to advertise() is the size of the message queue
     * used for publishing messages.  If messages are published more quickly
     * than we can send them, the number here specifies how many messages to
     * buffer up before throwing some away.
     */
    ros::Publisher chatter_pub = n.advertise<sensor_msgs::CameraInfo>("camera_info_katti_3", 1000);

    ros::Rate loop_rate(10);

    /**
     * A count of how many messages we have sent. This is used to create
     * a unique string for each message.
     */
    float fx,fy,cx,cy;
    /*
     *
		fx_ = info->P[0];
		fy_ = info->P[5];
		cx_ = info->P[2];
		cy_ = info->P[6];
     * */
    fx = 707.0912f;
    fy = 707.0912f;
    cx = 601.8873;
    cy = 183.1104;

    /*
     *
			fx_ = info->K[0];
			fy_ = info->K[4];
			cx_ = info->K[2];
			cy_ = info->K[5];
     *
     * */
    sensor_msgs::CameraInfo camera;
    camera.P[0] = fx;
    camera.P[5] = fy;
    camera.P[2] = cx;
    camera.P[6] = cy;

    camera.K[0] = fx;
    camera.K[4] = fy;
    camera.K[2] = cx;
    camera.K[5] = cy;

    camera.height = 480;
    camera.width = 640;

    int count = 0;
    while (ros::ok())
    {
        /**
         * This is a message object. You stuff it with data, and then publish it.
         */
        /*std_msgs::String msg;

        std::stringstream ss;
        ss <<camera<< count;
        msg.data = ss.str();*/


        /**
         * The publish() function is how you send messages. The parameter
         * is the message object. The type of this object must agree with the type
         * given as a template parameter to the advertise<>() call, as was done
         * in the constructor above.
         */
        chatter_pub.publish(camera);

        ros::spinOnce();

        loop_rate.sleep();
        ++count;
    }


    return 0;
}
