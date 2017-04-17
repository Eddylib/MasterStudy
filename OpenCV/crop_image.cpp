//
// Created by libaoyu on 17-4-17.
// used to crop image to wanted size.
//

#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"

using namespace std;
namespace boostfs = boost::filesystem;
string window_name = "disp window";


void get_names(string dir,vector<string> names){
    boostfs::path imgpath(dir);
    if(boostfs::exists(imgpath)){
        boostfs::directory_iterator item_begin(imgpath);
        boostfs::directory_iterator item_end;
        for(;item_begin != item_end;item_begin ++){
            if(boostfs::is_directory(*item_begin)){

            }else{
                cout<<item_begin->path().filename().string() <<endl;
                names.push_back(item_begin->path().filename().string());
            }
        }

    }
}
void write_one(const cv::Mat &src, string destination,string filename){
    cv::imwrite(destination+filename,src);
}
int main(int argc, char *argv[]){
    int left,top,bottom,right,width,height,croplr,croptb;
    cv::Mat imgsrc;
    if(argc >= 2);

    if(argc ==7){
        sscanf(argv[3],"%d",&top);
        sscanf(argv[4],"%d",&left);
        sscanf(argv[5],"%d",&width);
        sscanf(argv[6],"%d",&height);
        top--;
        left--;
        bottom = top + height;
        right = left + width;
    }else if(argc == 5){
        sscanf(argv[3],"%d",&croplr);
        sscanf(argv[4],"%d",&croptb);
        top = croptb;
        bottom = imgsrc.rows - croptb;
        left = croplr;
        right = imgsrc.cols - croplr;

    }else{
        cout<<"usage:"<<endl;
              //0         1              2                3                              4               5              6
        cout<<"this_exec image_file.xxx <to dir> <top position>                 <left>          <width>        <height>"<<endl;
        cout<<"this_exec image_file.xxx <to dir> <pixels croped left and right> <pixels croped top and buttom>"<<endl;

    }
    string from = argv[1];
    string to = argv[2];
    cv::Mat outmap;
    vector<string> names;
    //cv::imwrite("/home/libaoyu/Desktop/test.png",out);
    get_names(from,names);
    for(string file : names){
        imgsrc = cv::imread(file);
        outmap=imgsrc(cv::Range(top,bottom),cv::Range(left,right));
        write_one(outmap,to,file);
    }
    return 0;
}