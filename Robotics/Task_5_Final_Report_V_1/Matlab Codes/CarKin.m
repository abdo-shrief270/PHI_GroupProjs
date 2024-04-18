%*******************************************************************
%*** Solving Differentially-Steered Vehicle kinematics equations ***
%*** Dr. Mohamed Hamdy El-siafy ************************************
%*******************************************************************

close all
clear
clf
r = 0.06; % wheel radious
l = 0.067; % distance between whel and center
fhiRDot = 255;  %right wheel velocity
fhiLDot = 255;  %Left wheel velocity

x0 = 0;
y0 = 0;
theta0 = pi/2;
tspan = [0 10];

xrdot = (r/2) * (fhiRDot + fhiLDot);
yrdot = 0;
omegadot =  (r/(2 * l))* (fhiRDot - fhiLDot);

syms x(t) y(t) theta(t)
ode1 = diff(x) == cos(theta) * xrdot;
ode2 = diff(y) == sin(theta) * xrdot;
ode3 = diff(theta) == omegadot;
odes = [ode1; ode2; ode3];
cond1 = x(0) == x0;
cond2 = y(0) == y0;
cond3 = theta(0) == theta0;
conds = [cond1; cond2; cond3];

S = dsolve(odes,conds);
disp('x(t)=')
disp(S.x)
disp('y(t)=')
disp(S.y)
disp('theta(t)=')
disp(S.theta)

figure
fplot(S.x, tspan, 'b','linewidth',2),hold on
fplot(S.y,tspan, 'r','linewidth',2)
fplot(S.theta,tspan, 'g','linewidth',2),grid on
legend('x','y','theta','Location','best')
title(' x, y and theta with respect to time')

figure
fplot(S.x,S.y,tspan,'linewidth',2),grid
title('XY trajectory')
