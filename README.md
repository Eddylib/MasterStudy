#Master Study Project of Eddylib

This project is used to record the coding during the study, building with a standard project structure.The description of detail lie in corresponding directorys.


`Eigen`
------------

 A subdirectory to learn Eigen ---- a linear algebra c++ library. Now, I'm just at beginning.

* Initializing of `Matrix` and `Vertex` in matrixAndVertex.cpp.
* Linear solver to solve equations in linerSolver.cpp.


`Boost`
------------

 A subdirectory to learn Boost ---- a c++ library encapsulates most features of various system.

* thread.cpp shows codes that depict the features of thread.All work well on Ubuntu 14.04


`Sophus`
------------

A library encapsulates opitions of `Lie Group` a wonderful tools to implement robotics movement.

* Sophusdoc.cpp lists much operations of `Lie Group`.It will be used one day!


`kalmanFilterMatlab`
------------

A directory includes some matlab codes.For convenient, I implement `Kalman Filter` with matlab.See details in README.md in `kalmanFilterMatlab` 

* falseEKF directory lists inchoate code based on othesrs to implement a mouse tracker.
* mouseTracker directory lists new code reconstructed by me.It is a non linear problem but I build a linear motion model to solve it. Unsuccessful.The readme.md in the mouseTracker updated.


`traitCPP`
------------

This directory list code about trait skills.But it lost. I may write it back later.


Installation
------------
```
git clone https://github.com/Eddylib/MasterStudy
cd MasterStudy
vim CMakeLists.txt #select modules
mkdir build
cmake ..
make
```
