%% prepare workspace
clear variables; close all; clc;

%%
data = csvread('bresenham.csv');
x = data(:,1);
y = data(:,2);
t = 1:numel(x);
figure;
plot(x,y,'.'); hold on; plot([x(1) x(end)], [y(1) y(end)]);plot(x(end),y(end),'ro');
%plot3(t,x,y);
%xlim([0,4096]); ylim([0,4096]);

%%