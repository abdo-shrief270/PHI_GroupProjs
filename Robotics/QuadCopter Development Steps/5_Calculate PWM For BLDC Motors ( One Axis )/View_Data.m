clc,clear,close all
load Data_Captured_From_MPU6050_With_Powering_BLDC_Motors.txt
x1=Data_Captured_From_MPU6050_With_Powering_BLDC_Motors';
load Data_Captured_From_MPU6050_Without_Powering_BLDC_Motors.txt
x2=Data_Captured_From_MPU6050_Without_Powering_BLDC_Motors';

figure('Name','Data_Captured_From_MPU6050_Without_Powering_BLDC_Motors');
subplot(321);
plot(x2(1,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Acc rawX');

subplot(322);
plot(x2(2,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Error Angle');

subplot(323);
plot(x2(3,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Error Speed');

subplot(324);
plot(x2(4,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('PWM Right');

subplot(325);
plot(x2(5,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('PWM Left');

subplot(326);
plot(x2(4,:)-x2(5,:),'r','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Diference of PWM');



figure('Name','Data_Captured_From_MPU6050_With_Powering_BLDC_Motors');
subplot(321);
plot(x1(1,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Acc rawX');

subplot(322);
plot(x1(2,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Error Angle');

subplot(323);
plot(x1(3,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Error Speed');

subplot(324);
plot(x1(4,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('PWM Right');

subplot(325);
plot(x1(5,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('PWM Left');

subplot(326);
plot(x1(4,:)-x1(5,:),'r','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Diference of PWM');



figure
subplot(321);
plot(x2(1,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Acc rawX');

subplot(322);
plot(x1(1,:),'r','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Acc rawX With Powering BLDC Motor');

subplot(323);
plot(x2(2,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Error Angle');

subplot(324);
plot(x1(2,:),'r','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Error Angle With Powering BLDC Motor');

subplot(325);
plot(x2(3,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Error Speed');

subplot(326);
plot(x1(3,:),'r','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Error Speed With Powering BLDC Motor');


figure
subplot(321);
plot(x2(4,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('PWM Right');

subplot(322);
plot(x1(4,:),'r','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('PWM Right With Powering BLDC Motor');

subplot(323);
plot(x2(5,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('PWM Left');

subplot(324);
plot(x1(5,:),'r','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('PWM Left With Powering BLDC Motor');

subplot(325);
plot(x2(4,:)-x2(5,:),'k','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Diference of PWM');

subplot(326);
plot(x1(4,:)-x1(5,:),'r','linewidth',2);grid on
xlabel('Time');
ylabel('Magnitude');
title('Diference of PWM With Powering BLDC Motor');