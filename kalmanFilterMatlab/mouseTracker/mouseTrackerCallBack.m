function [] = mouseTrackerCallBack()
%MOUSETRACKERCALLBACK 程序核心部分以回调函数的形式实现
%
    global Xestimate
    global Xreal
    global Ymeasure
    global Pestimate
    global curr
    global recursiveTime
    global Q
    global R
    global r
    global N M
    global C
    global A
    
    global guicount
    guicount = guicount+1;
    if(mod(guicount,10) == 1)
        if(curr < recursiveTime)
            curr = curr + 1;
        %[ xnew,Pnew ] = kalmanFilter( x,P,A,v,Q,y,C,R )
        %获取观测值，观测值就是鼠标值加上一个噪声
            currPt = get(gca, 'CurrentPoint');
            %需根据模型更改的部分
                Xreal(1:2,curr) = currPt(1,1:2)';
                Ymeasure(:,curr) = Xreal(1:2,curr) + r*randn(M,1);
            %注意，为了较好的表示平移，采用齐次坐标
            xin = Xestimate(:,curr-1);
            Pin = Pestimate(:,:,curr-1);
            Qin = Q;
            yin = Ymeasure(:,curr);1;
            Vin = linspace(0,0,N)';
            Cin = C;
            Rin = R;
            %准备状态转移矩阵
            %模型是匀速模型
            %A 需要根据不同模型来给定
            Ain = A;
            
            %带入卡尔曼滤波
            [Xout,Pout] =...
            kalmanFilter(xin,Pin,Ain,Vin,Qin,yin,Cin,Rin );
            Xestimate(:,curr) = Xout;
            Pestimate(:,:,curr-1) = Pout;
            
            %绘图
            plot([Xestimate(1,curr) Xreal(1,curr)],[Xestimate(2,curr) Xreal(2,curr)],'r')
            plot(Xreal(1,curr),Xreal(2,curr),'b.')
            plot([Ymeasure(1,curr) Xreal(1,curr)],[Ymeasure(2,curr) Xreal(2,curr)],'g') 
        end
    end

end

