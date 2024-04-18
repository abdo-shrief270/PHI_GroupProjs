clc,clear,close all
load Task_4_Data.txt
x=Task_4_Data';
max_dis=3;

subplot(421);
tmp=x(1,:);
cond=zeros(1,length(tmp));
for i=1:length(tmp)
    cond(i)=tmp(i)>max_dis;
end
for i=1:length(tmp)-1
    if cond(i) == 0
        plot(i-1:i,tmp(1,i:i+1),'b','linewidth',2);grid on
        hold on
    else
        plot(i-1:i,tmp(1,i:i+1),'r','linewidth',2);grid on
        hold on
    end
    i=i+1;
end
xlabel('Time');
ylabel('Distance');
title('Right Distance');

subplot(422);
plot(x(2,:),'b','linewidth',2);grid on
xlabel('Time');
ylabel('Distance');
title('Front Distance');

subplot(423);

tmp=x(3,:);
cond=zeros(1,length(tmp));
for i=1:length(tmp)
    cond(i)=tmp(i)>max_dis;
end
for i=1:length(tmp)-1
    if cond(i) == 0
        plot(i-1:i,tmp(1,i:i+1),'b','linewidth',2);grid on
        hold on
    else
        plot(i-1:i,tmp(1,i:i+1),'r','linewidth',2);grid on
        hold on
    end
    i=i+1;
end
xlabel('Time');
ylabel('Distance');
title('Left Distance');

subplot(424);
plot(x(4,:),'b','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Tracking Error');

subplot(425);
plot(x(5,:),'b','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Propotional Gain');

subplot(426);
plot(x(6,:),'b','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Total PID');

subplot(427);
plot(x(7,:),'b','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('PWM Right');

subplot(428);
plot(x(8,:),'b','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Pwm Left');
