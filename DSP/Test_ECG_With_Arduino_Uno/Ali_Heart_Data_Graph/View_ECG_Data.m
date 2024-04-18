clc,clear,close all
load Ali_Data_Capetured.txt
x=Ali_Data_Capetured';
x=x(1000:2000);

subplot(2,2,1);
plot(x);grid on
title('ECG Signal')
xlabel('Time');
ylabel('Magnitude');
subplot(2,2,2);
f=fft(x);
stem(abs(fftshift(f(2:end))));grid on
title('ECG Signal in Frequency Domain')
[b,a]=butterworth('band')
x2=bandpass(x,[1,100],5e3,'Steepness',0.95);
subplot(2,2,3);
plot(x2);grid on
title('ECG Signal')
xlabel('Time');
ylabel('Magnitude');
subplot(2,2,4);
f=fft(x2);
stem(abs(fftshift(f(2:end))));grid on
title('ECG Signal in Frequency Domain')