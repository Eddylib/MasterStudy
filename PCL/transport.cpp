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
int
main (int argc, char** argv)
{


  pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud = makeLine();


  /* Reminder: how transformation matrices work :

           |-------> This column is the translation
    | 1 0 0 x |  \
    | 0 1 0 y |   }-> The identity 3x3 matrix (no rotation) on the left
    | 0 0 1 z |  /
    | 0 0 0 1 |    -> We do not use this line (and it has to stay 0,0,0,1)

    METHOD #1: Using a Matrix4f
    This is the "manual" method, perfect to understand but error prone !
  */
  float theta = M_PI/4; // The angle of rotation in radians

  /*  METHOD #2: Using a Affine3f
    This method is easier and less error prone
  */
  Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();
  // Define a translation of 2.5 meters on the x axis.
  //transform_2.translation() << 0.0, 0.0, 2.0;

  // The same rotation matrix as before; theta radians arround Z axis
  transform_2.rotate (Eigen::AngleAxisf (theta, Eigen::Vector3f::UnitZ()));

  // Print the transformation
  printf ("\nMethod #2: using an Affine3f\n");
  std::cout << transform_2.matrix() << std::endl;

  // Executing the transformation
  pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
  // You can either apply transform_1 or transform_2; they are the same
  pcl::transformPointCloud (*source_cloud, *transformed_cloud, transform_2);

  // Visualization
  printf(  "\nPoint cloud colors :  white  = original point cloud\n"
      "                        red  = transformed point cloud\n");
  pcl::visualization::PCLVisualizer viewer ("Matrix transformation example");

   // Define R,G,B colors for the point cloud
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_cloud_color_handler (source_cloud, 255, 255, 255);
  // We add the point cloud to the viewer and pass the color handler
  viewer.addPointCloud (source_cloud, source_cloud_color_handler, "original_cloud");

  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_handler (transformed_cloud, 230, 20, 20); // Red
  viewer.addPointCloud (transformed_cloud, transformed_cloud_color_handler, "transformed_cloud");
  std::string a("cloud");
  //viewer.addCoordinateSystem (1.0,a,0);
  viewer.addCoordinateSystem (1.0,"coord",0);
  viewer.setBackgroundColor(0.5, 0.5, 0.5, 0); // Setting background to a dark grey
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "original_cloud");
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloud");
  //viewer.setPosition(800, 400); // Setting visualiser window position

  while (!viewer.wasStopped ()) { // Display the visualiser until 'q' key is pressed
    viewer.spinOnce ();
  }

  return 0;
}
