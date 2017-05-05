//
// Created by libaoyu on 17-4-18.
//

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/CameraInfo.h"
#include "sensor_msgs/Image.h"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#include <stdio.h>
#include <algorithm>


/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
 using namespace std;

class CameraCatcher{
    ros::NodeHandle nh;
    string channel_video;
    ros::Subscriber video_subscriber;
    string fileSavePath;
    string fileSaveName;
    long count;
    string makefilename(){
        string a;
        char buf[10];
        for(int i=0;i<10;i++){
            buf[i] = '0';
        }
        buf[9] = 0;
        long tmpcount = count,j=0;
        while(tmpcount > 0){
            buf[j++] = tmpcount % 10 + '0';
            tmpcount /= 10;
        }
        cout<< "buf info: " <<buf<<endl;
        a = buf;
        reverse(a.begin(),a.end());
        return  a+".png";
    }
    void img_topic_handler(const sensor_msgs::ImageConstPtr img){
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::MONO8);
        fileSaveName = makefilename();
        if(fileSavePath.back() != '/'){
            cout<<"writing "<<fileSavePath+"/"+fileSaveName<<endl;
            cv::imwrite(fileSavePath+"/"+fileSaveName,cv_ptr->image);
        }
        else{
            cout<<"writing "<<fileSavePath+fileSaveName<<endl;
            cv::imwrite(fileSavePath+fileSaveName,cv_ptr->image);
        }
        count++;
    }
public: CameraCatcher(string pathsv);
};
CameraCatcher::CameraCatcher(string pathsv){
    channel_video = nh.resolveName("image");
    video_subscriber = nh.subscribe(channel_video,1,&CameraCatcher::img_topic_handler,this);
    count = 0;
    fileSavePath = pathsv;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "calib_talker");
    string destination;
    int hz;
    if(!ros::param::get("~dist", destination))
    {
        printf("need destination! (set using _dist:=xxx)\n");
        exit(0);
    }
    cout<<destination<<endl;
    if(!ros::param::get("~hz", hz))
    {
        printf("use default frequence 10hz(set using _hz:=xxx)\n");
        hz = 10;
    }
    boost::filesystem::path destinationpth(destination);
    if(!boost::filesystem::is_directory(destinationpth)){
        printf("bad destination path!\n");
        exit(0);
    }
    CameraCatcher catcher(destination);
    ros::Rate loop_rate(hz);
    while(ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
