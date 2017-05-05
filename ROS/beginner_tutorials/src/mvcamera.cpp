//
// Created by libaoyu on 17-4-25.
// This code is implemented to read image
// from a industrial camera. And publish it to the
// topic of mvcamera/image_raw
// todo add config features
// todo add multy camera support
//

#include <CameraApi.h>
#include <iostream>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <CameraDefine.h>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

#include <unistd.h>
#include <termios.h>
boost::mutex cameralock;

using namespace std;
class MVCamera;
struct termios;
MVCamera* globalcamera;
#define MV_CAMERA_MAX_WANTED 4
char getchNOEnter(){
    char buf = 0;
    struct termios stored_settings;
    struct termios new_settings;
    if(tcgetattr(0,&stored_settings) < 0)
        cout<<"error in tcgetattr: "<<__FILE__<<__LINE__<<endl;
    new_settings = stored_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;
    if(tcsetattr(0,TCSANOW,&new_settings) < 0)
        cout<<"error in tcsetattr: "<<__FILE__<<__LINE__<<endl;
    if(read(0,&buf,1)<0)
        cout<<"error in read: "<<__FILE__<<__LINE__<<endl;
    if(tcsetattr(0,TCSANOW,&stored_settings) < 0)
        cout<<"error in tcsetattr: "<<__FILE__<<__LINE__<<endl;
    return buf;
}

class MVCamera{
public:
    MVCamera(int id = 0); //id unused now
    void beginToWork(){
        CameraPlay(hCamera);
    }
    void pause(){
        CameraPause(hCamera);
    }
    void stopToWork(){
        CameraStop(hCamera);
    }
    int hCameraI(){
        return hCamera;
    }
    tSdkFrame *getImageProcessed(){
        CameraGetImageBuffer(
                hCamera,&currFrameCore.head,
                &currFrameCore.pBuffer,2000);
        currFrameProcessed.head = currFrameCore.head;
        CameraImageProcess(
                hCamera,
                currFrameCore.pBuffer,
                currFrameProcessed.pBuffer,
                &currFrameProcessed.head);
        CameraReleaseImageBuffer(hCamera,currFrameCore.pBuffer);
        return &currFrameProcessed;
    }
    ~MVCamera(){
        cout<<"un init camera."<<endl;
        stopToWork();
        CameraUnInit(hCamera);
    }
    const string& encoding(){
        return msgencoding;
    }
    tSdkCameraCapbility     capbility;
private:
    int                     iCameraCounts;
    tSdkCameraDevInfo       tCameraEnumList[MV_CAMERA_MAX_WANTED];
    int camIndex;                       //camera index (which i want in list)
    int                     hCamera;    //camera handler

    tSdkFrame currFrameCore;
    tSdkFrame currFrameProcessed;
    string msgencoding;
    int encodint;
    tSdkImageResolution resolution;
    void setResolution();
};
void MVCamera::setResolution(){
    resolution = capbility.pImageSizeDesc[0];
    // these code is useless...
    //resolution.iIndex = 0xFF;
    //resolution.iWidthZoomHd = 640;
    //resolution.iHeightZoomHd = 480;
    //resolution.iWidthZoomSw = 640;
    //resolution.iHeightZoomSw = 480;
    //resolution.iWidth = 1280;
    //resolution.iHeight = 960;
    CameraSetImageResolution(hCamera,&resolution);
}
MVCamera::MVCamera(int id){
    //just want MV_CAMERA_MAX_WANTED camera
    iCameraCounts = MV_CAMERA_MAX_WANTED;
    //discover the camera
    if(CameraEnumerateDevice(tCameraEnumList,&iCameraCounts)!= CAMERA_STATUS_SUCCESS){
        cout<<"Unable to discover camera"<<endl;
        exit(3);
    };
    if(iCameraCounts == 1){
        camIndex = 0;
    }else{
        cout<<"More than one camera found please config.(not implemented now)"<<endl;
    }

    int iStatus = -1;

    if((iStatus = CameraInit(&tCameraEnumList[camIndex],-1,-1,&hCamera)) != CAMERA_STATUS_SUCCESS){
        cout<<"Unable to initialize camera"<<endl;
        exit(3);
    };

    if((iStatus = CameraGetCapability(hCamera,&capbility)) != CAMERA_STATUS_SUCCESS){
        cout<<"Unable to get camera capability"<<endl;
        exit(3);
    };

    setResolution();

    if(capbility.sIspCapacity.bMonoSensor){
        encodint = CAMERA_MEDIA_TYPE_MONO8;
        msgencoding = "momo8";
    }else{
        encodint = CAMERA_MEDIA_TYPE_RGB8;
        msgencoding = "rgb8";
    }
    CameraSetIspOutFormat(hCamera,encodint);

    currFrameCore.pBuffer = NULL;
    currFrameProcessed.pBuffer = (unsigned char *)
            malloc(capbility.sResolutionRange.iHeightMax
                    *capbility.sResolutionRange.iWidthMax
                    *3);
    CameraSetAeState(hCamera,false);
    CameraSetExposureTime(hCamera,5000.0);
    CameraSetMirror(hCamera,0,false);
    CameraSetMirror(hCamera,1,true);

    beginToWork();

    cout<<"Camera initialized."<<endl;
}
void setCameraExposureTime(){
    double time;
    cameralock.lock();
    CameraGetExposureTime(globalcamera->hCameraI(),&time);
    cameralock.unlock();
    cout<<"current exposure time: "
        <<time
        <<"\n waitting for key: w/W to inc 1ms. s/S to dec 1ms"
        <<endl;
    bool stop = true;
    while(stop){
        switch (getchNOEnter()){
            case 'w':case 'W':
                time += 1000.0;
                /*if(time > globalcamera->capbility.sExposeDesc.uiExposeTimeMax)
                    time = globalcamera->capbility.sExposeDesc.uiExposeTimeMin;*/
                break;
            case 's':case 'S':
                time -= 1000.0;
                /*if(time < globalcamera->capbility.sExposeDesc.uiExposeTimeMin)
                    time = globalcamera->capbility.sExposeDesc.uiExposeTimeMax;*/
                break;
            default:
                break;
        }
        cameralock.lock();
        CameraSetExposureTime(globalcamera->hCameraI(),time);
        CameraGetExposureTime(globalcamera->hCameraI(),&time);
        cameralock.unlock();
        cout<<"current exposure time: "
            <<time
            <<endl;
    }
}
class Util{
public:
    static void convertFrameToImage(sCameraFrame* frame,
                                    sensor_msgs::ImagePtr &msg,
                                    const string& msgencoding,
                                    int outwidth,int outheight){
        int cvtype = CV_8UC1;
        string msgimgtype;
        if(frame->head.uiMediaType & CAMERA_MEDIA_TYPE_RGB)
            cvtype = CV_8UC3;
        cv::Mat cvmatin(frame->head.iHeight,frame->head.iWidth,cvtype,frame->pBuffer); // no copy here
        cv::Mat cvmatout;
        cv::resize(cvmatin,cvmatout,cv::Size(outwidth,outheight),0,0,cv::INTER_LINEAR);
        msg=cv_bridge::CvImage(std_msgs::Header(),msgencoding,cvmatout).toImageMsg();
    }
};
int main(int argc, char** argv){
    ros::init(argc,argv,"image_publisher_mvcamera");
    cout<<"This process publish mv camera frames\n"
        <<"w to up exposure time and s to down it"
        <<endl;
    ros::NodeHandle nh;

    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("mvcamera/image_raw",1);

    sensor_msgs::ImagePtr msg;
    //ros::Rate loop_rate(100);

    cameralock.lock();

    //todo: sCameraFrame shoulde not exist here one day I will refine it to provide a good lib
    MVCamera camera(0);
    sCameraFrame *mvframe = camera.getImageProcessed();
    cameralock.unlock();

    globalcamera = &camera;

    cout<<"format width height: "
        <<((mvframe->head.uiMediaType)==CAMERA_MEDIA_TYPE_RGB8?"RGB888":"UNKNOWN")
        <<" "
        <<mvframe->head.iWidth
        <<" "
        <<mvframe->head.iHeight<<endl;


    boost::thread fun_start(&setCameraExposureTime);
    while (ros::ok()){
        cameralock.lock();
        sCameraFrame *mvframe = camera.getImageProcessed();
        cameralock.unlock();
        Util::convertFrameToImage(mvframe,msg,camera.encoding(),640,480);
        pub.publish(msg);
        ros::spinOnce();
        //loop_rate.sleep();
    }

}