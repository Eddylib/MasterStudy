//
// Created by libaoyu on 17-4-21.
//

#ifndef MASTERSTUDY_LGS6_H
#define MASTERSTUDY_LGS6_H

#include <Eigen/Core>
typedef Eigen::Matrix<float,6,6> Matrix6x6;
typedef Eigen::Matrix<float,6,1> Vector6;
//this class modified from lsd slam system
class LGS2
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    Matrix6x6 A;
    Vector6 b;

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
    inline void update(const Vector6& J, const float& res, const float& weight)
    {
        A.noalias() += J * J.transpose() * weight;
        b.noalias() += J * (res * weight);
        error += res * res * weight;
        num_constraints += 1;
    }
private:
};
#endif //MASTERSTUDY_LGS6_H
