clear
clc
global N M
N=4;            %状态维度
M=2;            %观测维度

%设置实验的统计数据
global Xestimate
global Xreal
global Ymeasure
global Pestimate
global curr
global recursiveTime
recursiveTime = 300;
curr = 1;
Xestimate = zeros(N,recursiveTime);
Xreal = zeros(N,recursiveTime);
Ymeasure = zeros(M,recursiveTime);
Pestimate = zeros(N,N,recursiveTime);


global A
global Q
global R
global q
global r
q=5;          %过程标准差
r=5;          %测量标准差
Q=q^2*eye(N);   %过程方差
R=r^2*eye(M);   %测量值的方差 
A = eye(4) + diag(ones(1, 2), 2);

%初始状态设置：
s=linspace(0,0,N)';              %初始状态
x=s+q*randn(N,1);                       
P = eye(N);                               
Xestimate(:,curr) = x;
Pestimate(:,:,curr) = P;


%观测模型相关参数
global C
C = [eye(2),zeros(2)];


%gui
global guicount
guicount = 0;
img=ones(900,900);
imshow(img);
hold on
set(gcf,'WindowButtonMotionFcn','mouseTrackerCallBack');
title('红:估计,绿:测量,蓝:真实值')


estiErr = sum(sum(((Xestimate(1:2,30:end) - Xreal(1:2,30:end)).^2)))
mesureErr = sum(sum(((Ymeasure(:,30:end) - Xreal(1:2,30:end)).^2)))