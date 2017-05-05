//
// Created by libaoyu on 17-4-19.
//
// LGS system implemented in lsd slam system
// This code designed to test it
// This code implements the Gauss-Newton algrithm. for general no linear systems.
//
//
//
//  Jocabian need all observed data.
//  Jij is the jocabian of the ith observed y with respect of jth beta
//


#include <Eigen/Core>
#include <Eigen/Cholesky>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
using namespace std;
typedef Eigen::Matrix2f Matrix2x2;
typedef Eigen::Vector2f Vector2;
//this class modified from lsd slam system
class LGS2
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    Matrix2x2 A;
    Vector2 b;

    float error;
    size_t num_constraints;

    inline void initialize(const size_t maxnum_constraints)
    {
        A.setZero();
        b.setZero();
        error = 0;
        this->num_constraints = 0;
    }

    inline void finishNoDivide()
    {
    }
    inline void update(const Vector2& J, const float& res, const float& weight)
    {
        A.noalias() += J * J.transpose() * weight;
        b.noalias() += J * (res * weight);
        error += res * res * weight;
        num_constraints += 1;
    }

private:
};
// function beta1*x^2 + beta1*y^2
//

typedef Eigen::Matrix<float,7,2> Mat72;
typedef Eigen::Matrix<float,7,1> Vector7;
void Jacobian(Mat72 &jocb,const float *x,const Vector2& beta){
    for(int i=0;i<7;i++){
        float b2_x = (beta[1] + x[i]);
        jocb(i,0) = x[i]/b2_x;
        jocb(i,1) = -1.0*(x[i]*beta[0])/(b2_x*b2_x);
    }
}
void resdual(Vector7& res,const float *x,const float *y,const Vector2& beta){
    for(int i=0;i<7;i++){
        res[i] = y[i] -  beta[0]*x[i]/(beta[1]+x[i]);
    }
}
void JacobainOnce(Vector2& jocb,float x,const Vector2& beta){
    float b2_x = (beta[1] + x);
    jocb[0] = x/b2_x;
    jocb[1] = -1.0*(x*beta[0])/(b2_x*b2_x);
}
float resdualOnce(float x,float y,const Vector2& beta){
    return y - beta[0]*x/(beta[1]+x);
}
int main(){
    // this method reduse the demand of storage.
    //
    float S[] = {0.038,0.194,0.425,0.626,1.253,2.500,3.740};
    float rate[] = {0.050,0.127,0.094,0.2122,0.2729,0.2665,0.3317};
    // this example comes from wiki at https://en.wikipedia.org/wiki/Gauss-Newton_algorithm
    //rate = v * s /(k + s), x = s; beta1 = v, beta2 = k
    //j.beta1 = - x / (beta2 + x); j.beta2 =beta1*x/(beta2 + x)^2;
    //init beta1 = 0.9, beta2 = 0.2
    LGS2 ls;
    Vector2 beta(0,1.2),inc(0.0,0.0);
    int maxiterate = 100;
    for(int k=0;k<maxiterate;k++){
        ls.initialize(1);
        for(int i=0;i<sizeof(S)/sizeof(float);i++){
            Vector2 jacobainonce;
            JacobainOnce(jacobainonce,S[i],beta);
            float res = resdualOnce(S[i],rate[i],beta);
            ls.update(jacobainonce,res,1.0);
        }
        Matrix2x2 A = ls.A;
        Vector2 b = ls.b;
        inc = A.ldlt().solve(b);
        beta = beta + inc;
        cout<<beta.transpose()<<endl;
    }
    cout<<"final:\n"<<beta.transpose()<<endl;
}
int simple_method(){
    float S[] = {0.038,0.194,0.425,0.626,1.253,2.500,3.740};
    float rate[] = {0.050,0.127,0.094,0.2122,0.2729,0.2665,0.3317};
    //rate = v * s /(k + s), x = s; beta1 = v, beta2 = k
    //j.beta1 = - x / (beta2 + x); j.beta2 =beta1*x/(beta2 + x)^2;
    //init beta1 = 0.9, beta2 = 0.2
    Vector2 beta(0.9,0.2),inc(0.0,0.0);
    for(int i=0;i<100;i++){
        Mat72 jocb;
        Vector7 res;
        Jacobian(jocb,S,beta);
        Matrix2x2 A = jocb.transpose()*jocb;
        resdual(res,S,rate,beta);
        Vector2 b = jocb.transpose()*res;
        inc = A.ldlt().solve(b);
        beta = beta + inc;
    }
    cout<<beta.transpose()<<endl;
}