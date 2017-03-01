count = count+1;
if(mod(count,10) == 1)
    z = h(s) + r*randn;                     
    sV(:)= s;                             %实际状态
    zV(:)  = z;                           %状态测量值
    [x1,A]=ekfmyappjaccsdf(xold,x); %计算f的雅可比矩阵，其中x1对应黄金公式line2
    P=A*P*A'+Q;         %过程方差预测，对应line3
    [z1,H]=ekfmyappjaccsdh(x1); %计算h的雅可比矩阵
    K=P*H'*inv(H*P*H'+R); %卡尔曼增益，对应line4
    xold=x;
    x=x1+K*(z-z1);        %状态EKF估计值，对应line5
    P=P-K*H*P;            %EKF方差，对应line6
    xV(:) = x;


    currPt = get(gca, 'CurrentPoint');
    xx = currPt(1,1);
    yy = currPt(1,2);%save


    s = [xx,yy]' + q*randn(2,1);  %update process, 数据是从函数理论值算出的。



    plot(xV(1),xV(2),'r.')
    plot(sV(1),sV(2),'b.')
    plot(zV(1),zV(2),'g.')
end
