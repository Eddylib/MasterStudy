# PCL Library Codes

This directory list code about PCL, a great tool to draw the result of the SLAM. The Point
Cloud Library (PCL) is a standalone, large scale, open project for 2D/3D image and point
cloud processing.

Installation
------------
```
git clone https://github.com/Eddylib/MasterStudy
cd MasterStudy
vim CMakeLists.txt #select modules PCL
mkdir build
cmake ..
make
```
`Note`

Usually, the PCL Library is installed by ROS. On Ubuntu14, its version is 1.7. But I find some bugs in it. The scale 
of axis x and axis y are different, which may be some other settings in the code but I didn't find. So, directly I 
get the code and compile&install it.  But in Cmake, I didn't find a good mechanism to deal with multipy versions of
libraries. What I can do is just change the version in `find_package` instruction (but not helpful, lib linked to 1.8
but head files is 1.7). And then I directly change the `PCL_INCLUDE_DIRS` to somewhere contains the head file of v-1.8.
For now, all works well.



`pcd_write.cpp`
------------

Just some example code from officer website.


`transport.cpp`
------------

Example code from officer website. And tried to change the shape and transport. Works well.

`visualizer.cpp`
------------

Just some example code from officer website. Will be discussed later.




