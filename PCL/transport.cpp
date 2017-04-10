#include <iostream>

#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common_headers.h>

pcl::PointCloud<pcl::PointXYZ>::Ptr makeBall(){
     pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
     for (float angle(0.0); angle <= 360.0; angle += 5){
         for (float anglez(-90.0); anglez <= 90.0; anglez += 5){
             pcl::PointXYZ point;
             point.z = sinf (pcl::deg2rad(anglez));
             float r = cosf (pcl::deg2rad(anglez));
             point.x = r*cosf (pcl::deg2rad(angle));
             point.y = r*sinf (pcl::deg2rad(angle));
             cout<<point.z<<endl;
             source_cloud->points.push_back(point);

         }
     }
     return source_cloud;
 }
pcl::PointCloud<pcl::PointXYZ>::Ptr makeLine(){
     pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
     for (float length(0.0); length <= 3.0; length += 0.02){
             pcl::PointXYZ point;
             point.z = length;
             point.x = length;
             point.y = length;
             source_cloud->points.push_back(point);
     }
     return source_cloud;
 }
pcl::PointCloud<pcl::PointXYZ>::Ptr makeRectangle4(const pcl::PointXYZ &tl,
                                                     const pcl::PointXYZ &tr,
                                                     const pcl::PointXYZ &bl,
                                                     const pcl::PointXYZ &br){
        pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
        Eigen::Vector3f dirh,dirw;
        float height,width,stepw,steph;
        height = sqrtf((tr.x-tl.x)*(tr.x-tl.x) + (tr.y-tl.y)*(tr.y-tl.y) + (tr.z-tl.z)*(tr.z-tl.z));
        width = sqrtf((bl.x-tl.x)*(bl.x-tl.x)+ (bl.y-tl.y)*(bl.y-tl.y) + (bl.z-tl.z)*(bl.z-tl.z));
        steph = height/100.0;
        stepw = width/100.0;

        dirh(0) = (tl.x - bl.x)/height;
        dirh(1) = (tl.y - bl.y)/height;
        dirh(2) = (tl.z - bl.z)/height;

        dirw(0) = (tr.x - tl.x)/width;
        dirw(1) = (tr.y - tl.y)/width;
        dirw(2) = (tr.z - tl.z)/width;


        for (float hi(0.0); hi <= height; hi += steph){
            for (float wi(0.0); wi <= width; wi += stepw){
                pcl::PointXYZ point;
                point.x = bl.x + hi*dirh(0) + wi*dirw(0);
                point.y = bl.y + hi*dirh(1) + wi*dirw(1);
                point.z = bl.z + hi*dirh(2) + wi*dirw(2);
                source_cloud->points.push_back(point);
            }
        }
        return source_cloud;
    }
pcl::PointCloud<pcl::PointXYZ>::Ptr makeRectangle(){
    pcl::PointXYZ tl(0.0,3.0,0.0);
    pcl::PointXYZ tr(3.0,3.0,0.0);
    pcl::PointXYZ bl(0.0,0.0,0.0);
    pcl::PointXYZ br(3.0,0.0,0.0);
    return makeRectangle4(tl,tr,bl,br);

}
pcl::PointCloud<pcl::PointXYZ>::Ptr makeFline(float length){
    pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
    for (float l(0.0); l <= length; l += 0.02){
            pcl::PointXYZ point;
            point.z = -l;
            point.x = 0;
            point.y = 0;
            source_cloud->points.push_back(point);
    }
    return source_cloud;

}

pcl::PointCloud<pcl::PointXYZ>::Ptr makeObject(float x,float y, float z){
    pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
    pcl::PointXYZ point;
    point.z = x;
    point.x = y;
    point.y = z;
    source_cloud->points.push_back(point);
    return source_cloud;

}
pcl::PointCloud<pcl::PointXYZ>::Ptr makeTrans(const pcl::PointXYZ &start,const Eigen::Vector3f &trans){
    pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
    float norm = sqrtf(trans(0)*trans(0) + trans(1)*trans(1) + trans(2)*trans(2));
    for (float l(0.0); l <= norm; l += 0.02){
            pcl::PointXYZ point;
            point.x = start.x +l*trans(0)/norm ;
            point.y = start.y +l*trans(1)/norm ;
            point.z = start.z +l*trans(2)/norm ;
            source_cloud->points.push_back(point);
    }
    return source_cloud;

}
int
main (int argc, char** argv)
{


  pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud = makeRectangle();
  pcl::PointCloud<pcl::PointXYZ>::Ptr fline = makeFline(10.0);

  pcl::PointCloud<pcl::PointXYZ>::Ptr object = makeObject(10.0,10.0,10.0);


  float theta = M_PI/4; // The angle of rotation in radians


  Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();
  //transform_2.rotate (Eigen::AngleAxisf (theta, Eigen::Vector3f::UnitZ()));
  Eigen::Vector3f trans(5.0,1.0,1.0);
  transform_2.translate(trans);
  pcl::PointCloud<pcl::PointXYZ>::Ptr transLine = makeTrans(pcl::PointXYZ(0.0,0.0,0.0),trans);



  pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
  pcl::transformPointCloud (*source_cloud, *transformed_cloud, transform_2);

  pcl::PointCloud<pcl::PointXYZ>::Ptr fline_trans (new pcl::PointCloud<pcl::PointXYZ> ());
  pcl::transformPointCloud (*fline, *fline_trans, transform_2);



  pcl::visualization::PCLVisualizer viewer ("Matrix transformation example");


  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
          source_cloud_color_handler (source_cloud, 255, 255, 255);
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
          transformed_cloud_color_handler (transformed_cloud, 230, 20, 20); // Red
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
          fline_color_handler (fline, 255, 255, 255); // blue
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
          fline_trans_color_handler (fline_trans, 230, 20, 20); // Red
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
          object_color_handler (object, 0, 255, 0); // green
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
          otrans_color_handler (transLine, 0, 255, 0); // green


  viewer.addPointCloud (transLine, otrans_color_handler, "trans");

  viewer.addPointCloud (object, object_color_handler, "object");
  viewer.addPointCloud (fline_trans, fline_trans_color_handler, "fline_trans");
  viewer.addPointCloud (fline, fline_color_handler, "fline");
  viewer.addPointCloud (transformed_cloud, transformed_cloud_color_handler, "transformed_cloud");
  viewer.addPointCloud (source_cloud, source_cloud_color_handler, "original_cloud");


  viewer.addCoordinateSystem (1.0,"coord",0);
  viewer.setBackgroundColor(0.5, 0.5, 0.5, 0);
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "original_cloud");
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloud");


  while (!viewer.wasStopped ()) { // Display the visualiser until 'q' key is pressed
    viewer.spinOnce ();
  }

  return 0;
}
