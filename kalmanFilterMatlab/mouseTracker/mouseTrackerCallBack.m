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
    global N
    global C
    
    global guicount
    guicount = guicount+1;
    if(mod(guicount,10) == 1)
        if(curr < recursiveTime)
            curr = curr + 1;
        %[ xnew,Pnew ] = kalmanFilter( x,P,A,v,Q,y,C,R )
        %获取观测值，观测值就是鼠标值加上一个噪声
            currPt = get(gca, 'CurrentPoint');
            Xreal(:,curr) = currPt(1,1:2)';
            Ymeasure(:,curr) = Xreal(:,curr) + r*randn(N,1);
            %注意，为了较好的表示平移，采用齐次坐标
            xin = [Xestimate(:,curr-1);1];
            zeroN = linspace(0,0,N);
            Pin = [Pestimate(:,:,curr-1) zeroN';zeroN,0;];
            Qin = [Q zeroN';zeroN,0;];
            yin = [Ymeasure(:,curr);1];
            Vin = [0;0;0];
            Cin = [C zeroN';zeroN,1;];
            Rin = [R zeroN';zeroN,0;];
            %准备状态转移矩阵
            %模型是匀速模型，根据齐次坐标，
            %较好得出，如果有前两个点，那么根据前两个点的速度来构造转移矩阵，否则使用单位矩阵来代替。
            %要达到X(k)=A*X(k-1), 的目的，且这个A是根据前两个点的速度来得到的
            if(curr > 2)
                A = [   1 0 Xestimate(1,curr-1) - Xestimate(1,curr-2)
                        0 1 Xestimate(2,curr-1) - Xestimate(2,curr-2)
                        0 0 1];
            else
                A = [   1 0 0
                        0 1 0
                        0 0 1];
            end
            
            %带入卡尔曼滤波
            [Xout,Pout] =...
            kalmanFilter(xin,Pin,A,Vin,Qin,yin,Cin,Rin );
            Xestimate(:,curr) = Xout(1:2,1);
            Pestimate(:,:,curr-1) = Pout(1:2,1:2);
            
            %绘图
            plot([Xestimate(1,curr) Xreal(1,curr)],[Xestimate(2,curr) Xreal(2,curr)],'r')
            plot(Xreal(1,curr),Xreal(2,curr),'b.')
            plot([Ymeasure(1,curr) Xreal(1,curr)],[Ymeasure(2,curr) Xreal(2,curr)],'g') 
        end
    end

end

