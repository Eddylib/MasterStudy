/*
    this cpp is used to study the so3 part of sophus
    Eddylib 2017.3.2
*/
#include <iostream>
#include<cmath>

#include <so3.hpp>
#include <rxso3.hpp>
#include <Eigen/Geometry>
#include <unsupported/Eigen/MatrixFunctions>
using namespace Sophus;
using namespace Eigen;
using namespace std;



typedef double Scalar;

typedef SO3Group<Scalar> SO3Type;
typedef SO3Type::Point Point;

Scalar normVector3d(const Vector3d &vec3){
    return sqrt(vec3(0)*vec3(0)
                    +vec3(1)*vec3(1)
                    +vec3(2)*vec3(2));
}
void normalize(Vector3d &vec3){
    vec3 = vec3/normVector3d(vec3);
}
Matrix3d hatVectpr3d(const Vector3d &vec3){
    Matrix3d a;
    a<<0.0,-1*vec3(2),vec3(1), vec3(2),0.0,-1*vec3(0), -1*vec3(1),vec3(0),0.0;
    return a;
}
Vector3d iHatM3d(const Matrix3d &mat3){
    return Vector3d(mat3(2,1),mat3(0,2),mat3(1,0));
}
SO3Type getDefaultSO3Group(){
    /*first to create a Eigen::Quaternion
    for understandility to creat Quaternion with Eigen::AngleAxis
    see doc for detail
    */
    cout<<"created a SO3 decipts a 0.25pi's rotation among z axis"<<endl;
    Vector3d axis(0,0,1);
    Scalar rotateAngle = 0.25*M_PI;
    Quaternion<Scalar> rotQuaternion(AngleAxisd(rotateAngle, axis));

    /*
        then use the quaternion to create a SO3 group
        now we create a so3group which represent a rotation
        that rotate 0.25*PI around axis [1 1 0]
    */
    return SO3Type(rotQuaternion);
}
void adjoint(){
    // for so3 the adjoint returns the SO3 group element
    // of corresponding so3 algebra element
    cout<<"Function adjoint"<<endl;

    Point point(1,1,0);
    SO3Type so3group = getDefaultSO3Group();
    cout<<"matrix and the adjoint of so3 algebra: \n"<<so3group.Adj()<<endl;
    /* so what's the meaning of adjoint?
        if Ad is adjoint transform of A, then
        for all X, Ad*X = A*X*A^-1
        Lets see
    */
    cout<<"Ad*X: \n"<<so3group.Adj()*point<<endl;
    cout<<"Ahat(X)A^-1: \n"<<iHatM3d(so3group.Adj()*hatVectpr3d(point)*so3group.inverse().Adj())<<endl;
}
void expLog(){
    cout<<"Function: log"<<endl;
    Point point(1,1,0);
    SO3Type so3group = getDefaultSO3Group();
    /* the log operation carry out the rotation angles
       on x,y,z axis.
    */
    cout<<"log(created SO3):\n"<<so3group.log()/M_PI<<endl;

    /* the exp operation on vertex3 carrys out the rotation matrix */
    cout<<"SO3:\n"<<SO3Type::exp(so3group.log()).matrix()<<endl;
}
void expMap(){
    cout<<"Function: exp "<<endl;
    /*
     * vector to SO3 through exp map
    */
    cout<<"v:\n"<<Vector3d(0.0,0.0,0.25*M_PI)<<endl;
    cout<<"exp(hat(v)) = SO3:\n"<<(SO3Type::hat(Vector3d(0.0,0.0,0.25*M_PI))).exp()<<endl;
}
void lieBracket(){
    cout<<"Function: lieBracket "<<endl;
    /*
        liebracket = vee(hat(a)hat(b) = hat(b)hat(a))
    */
    Point xa(1.0,2.0,3.0), xb(0.3,0.4,1.5);

    cout<<"sophus result:\n"<< SO3Type::lieBracket(xa,xb) <<endl;
    cout<<"calculate:\n"<<
          SO3Type::vee(
              SO3Type::hat(xa)*SO3Type::hat(xb) -
              SO3Type::hat(xb)*SO3Type::hat(xa))
    <<endl;

}
void mapAndMult(){
    cout<<"Function: multipy "<<endl;
    cout<<"mult "<<endl;
    /*
        fast mult
    */
    Scalar databuff[SO3Type::num_parameters];
    Map<SO3Type> a(databuff);
    SO3Type so3group1 = getDefaultSO3Group();
    SO3Type so3group2 = getDefaultSO3Group();
    a=so3group1;
    Map<SO3Type> b(so3group2.data());
    a.fastMultiply(b);

    cout<<"fast multipy:\n"<<a.matrix()<<endl;
    cout<<"general multipy:\n"
       <<(so3group1*so3group2).matrix()<<endl;

}
void veeHat(){
    cout<<"Function: vee and hat "<<endl;
    Vector3d rotate(1,2,3);
    cout<<"vector:\n"<<rotate<<endl;
    cout<<"hat(vector):\n"<<SO3Type::hat(rotate)<<endl;
    cout<<"vee(hat(vector)):\n"<<SO3Type::vee(SO3Type::hat(rotate))<<endl;
}
int main()
{
    veeHat();
}
