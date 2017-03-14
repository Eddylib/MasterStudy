function [ xnew,Pnew ] = kalmanFilter( x,P,A,v,Q,y,C,R )
%KALMANFILTER 卡尔曼滤波核心公式
%   输入
%   x 上次迭代的后验位置                         N维列向量
%   P 上次迭代后验位置的协方差                    N*N方阵
%   A 运动模型                                N*N方阵 x(k) = Ax(k-1) + v(k) + w(k)   (w均值为0协方差矩阵为Q的高斯噪声)
%   v 系统输入                                N维列向量
%   Q 运动模型协方差                           噪声w的协方差矩阵
%   y 系统观测                                M维列向量
%   C 观测矩阵                                M*N矩阵，y(k) = C(k)x(k) + n(k) (n均值为0，协方差矩阵为R的高斯噪声)
%   R 观测数据协方差
%   输出
%   xnew 后验位置
%   Pnew 后验位置协方差
%   公式参见State Estimation for robotics P67 (3.120)
    

    N = length(x);
    %predictor
    Ptmp = A*P*A' + Q;
    xtmp = A*x + v;
    %kalman gain
    K = (Ptmp*C')/(C*Ptmp*C'+R);
    %corrector
    Pnew = (eye(N) - K*C)*Ptmp;
    xnew = xtmp + K*(y - C*xtmp);
end

