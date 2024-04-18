clc,clear,close all
load Beam_Balance_Data.txt
x=Beam_Balance_Data';
max_dis=3;

subplot(421);
plot(x(1,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Acc_rawX');

subplot(422);
plot(x(2,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Acc_rawY');

subplot(423);
plot(x(3,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Acc_rawZ');

subplot(424);
plot(x(4,:),'m','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Gyr_rawX');

subplot(425);
plot(x(5,:),'m','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Gyr_rawY');

subplot(426);
plot(x(6,:),'g','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('PWM Right');

subplot(427);
plot(x(7,:),'g','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('PWM Left');

subplot(428);
plot(x(6,:)-x(7,:),'r','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Diference of PWM');
