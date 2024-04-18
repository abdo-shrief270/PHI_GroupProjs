clc,clear,close all
load Data_WithOut_filter_Moving.txt
x=Data_WithOut_filter_Moving';
windowSize = 5; 
b = (1/windowSize)*ones(1,windowSize);
a = 1;

y = filter(b,a,x);

plot(x)
hold on
plot(y);grid on
axis([1 500 2 402])
xlabel('Time');
ylabel('Distance');
title('Filtering using filter function');
legend('Input Data','Filtered Data')