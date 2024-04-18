clc,clear;
close all;
load Ali_Data_Capetured.txt
%% Setup Parameters

% Message
Fm=100;
Am=4;
t=0:0.001:Fm;

% Carrier
Fc=10*Fm;
Ac=1;

% Bit Number of Quantization 
n_bit = 4;
%% Message Signal

mt=Ali_Data_Capetured';

subplot(3,2,1);
plot(mt,'m','linewidth',1.5);grid on
xlabel('Time [SEC]');
ylabel('Amplitude');
title('Message');


%% Carrier Signal

ct=Ac/2.*square(2*pi*Fc*t)+Ac/2;

subplot(3,2,2);
plot(ct,'b','linewidth',1.5);grid on
xlabel('Time [SEC]');
ylabel('Amplitude');
title('Carrier');

%% PAM Ideal
subplot(3,2,3);
stem(mt,'g','linewidth',1.5);grid on
xlabel('Time [SEC]');
ylabel('Amplitude');
title('PAM Ideal');

%% PAM Natural
st=ct.*mt;

subplot(3,2,4);
plot(t,mt,'m',t,st,'k','linewidth',1.5);grid on
xlabel('Time [SEC]');
ylabel('Amplitude');
title('PAM Natural');
legend('Message','PAM Natural','location','best');

%% PAM Flat-Top

stFt=zeros(1,length(t));

for i = 2:length(t)
    if ct(i) == 1 && ct(i-1) == 0
        stFt(i) = ct(i) * mt(i); 
    elseif ct(i) == 1 && ct(i-1) == 1
        stFt(i) = stFt(i-1); 
    else
        stFt(i) = 0; 
    end
end

subplot(3,2,5);
plot(t,mt,'m',t,stFt,'k','linewidth',1.5);grid on
xlabel('Time [SEC]');
ylabel('Amplitude');
title('PAM Flat-Top');
legend('Message','PAM Flat-Top','location','best');

%% Quantization 

n_level = 2^n_bit ;
mt_min = min(mt);
mt_max = max(mt);
step_size = (mt_max-mt_min)/n_level;

qt = mt / step_size ;
qt = round(qt);
qt = qt * step_size;

subplot(3,2,6);
plot(t,mt,'m',t,qt,'k',t,mt-qt,'r','linewidth',1.5);grid on
xlabel('Time [SEC]');
ylabel('Amplitude');
title('Quantized Signal');
legend('Message','Quantized Signal','Quantization Error','location','best');