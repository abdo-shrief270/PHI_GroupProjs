clc,clear,close all
load Task_2_OutData.txt
x=Task_2_OutData';
subplot(221);
plot(x(1,:));grid on
xlabel('Time');
ylabel('Distance');
title('Right Distance');

subplot(222);
plot(x(2,:));grid on
xlabel('Time');
ylabel('Distance');
title('Front Distance');

subplot(223);
plot(x(3,:));grid on
xlabel('Time');
ylabel('Distance');
title('Left Distance');

subplot(224);
plot(x(4,:));grid on
xlabel('Time');
ylabel('Distance');
title('Diffrence (Error)');

figure
subplot(221);
plot(x(6,:));grid on
xlabel('Time');
ylabel('Magnitude');
title('PID (P)');

subplot(222);
plot(x(7,:));grid on
xlabel('Time');
ylabel('Magnitude');
title('PID (I)');

subplot(223);
plot(x(8,:));grid on
xlabel('Time');
ylabel('Magnitude');
title('PID (D)');

subplot(224);
plot(x(9,:));grid on
xlabel('Time');
ylabel('Magnitude');
title('Totla PID Controller');
