clc,clear,close all
load Task_3_OutData.txt
x=Task_3_OutData';
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
axis([0 60 0 500])
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
