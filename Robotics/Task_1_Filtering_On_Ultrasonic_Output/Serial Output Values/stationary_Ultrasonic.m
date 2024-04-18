clc,clear,close all
load Data_WithOut_filter_Moving.txt
load Data_With_5_Average_Moving.txt
load Data_With_10_Average_Moving.txt
load Data_With_50_Average_Moving.txt

subplot(2,2,1)
plot(Data_WithOut_filter_Moving','k','linewidth',1),grid on
axis([1 500 2 402])
xlabel('Time');
ylabel('Distance');
title('Distance without average');

subplot(2,2,2)
plot(Data_With_5_Average_Moving','b','linewidth',1),grid on
axis([1 500 2 402])
xlabel('Time');
ylabel('Distance');
title('Distance with average 5');

subplot(2,2,3)
plot(Data_With_10_Average_Moving','r','linewidth',1),grid on
axis([1 500 2 402])
xlabel('Time');
ylabel('Distance');
title('Distance with average 10');

subplot(2,2,4)
plot(Data_With_50_Average_Moving','g','linewidth',1),grid on
axis([1 500 2 402])
xlabel('Time');
ylabel('Distance');
title('Distance with average 50');