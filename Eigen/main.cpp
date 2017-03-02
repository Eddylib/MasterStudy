#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;
void atstart(){
    cout<<"functions of initialization"<<endl;
    MatrixXd m(2,2);
    m(0,0) = 1;
    m(1,0) = 2;
    m(0,1) = 3;
    m(1,1) = 4;

    MatrixXd m2(m);

    MatrixXd v3(2,1);
    v3(0) = 1;
    v3(1) = 2;
    MatrixXd v4(1,2);
    v4(0) = 1;
    v4(1) = 2;
    std::cout << v3*v4 << std::endl;
}
void baseoperate(){
    Matrix3f  a,b;
    a<<1,1,1,2,2,2,3,3,3;
    b = a;
    cout<<"2*b*4"<<endl;
    cout<<2*b*4<<endl;

    cout<<"a*b"<<endl;
    cout<<a*b<<endl;

    cout<<"transpose a"<<endl;
    cout<<a.transpose()<<endl;

    cout<<"conjugate a"<<endl;
    cout<<a.conjugate()<<endl;


    cout<<"adjoint a"<<endl;
    cout<<a.adjoint()<<endl;

    Vector3d v(1,1,0);
    Vector3d w(0,1,1);
    cout << "Dot product: " << v.dot(w) << endl;
    double dp = v.adjoint()*w; // automatic conversion of the inner product to a scalar
    cout << "Dot product via a matrix product: " << dp << endl;
    cout << "Cross product:\n" << v.cross(w) << endl;

}
void operationonmatrix(){
    Eigen::Matrix2d mat;
    mat << 1, 2,
           3, 4;
    cout << "Here is mat.sum():       " << mat.sum()       << endl;
    cout << "Here is mat.prod():      " << mat.prod()      << endl;
    cout << "Here is mat.mean():      " << mat.mean()      << endl;
    cout << "Here is mat.minCoeff():  " << mat.minCoeff()  << endl;
    cout << "Here is mat.maxCoeff():  " << mat.maxCoeff()  << endl;
    cout << "Here is mat.trace():     " << mat.trace()     << endl;
}
int main()
{
    operationonmatrix();
}
