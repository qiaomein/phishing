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
data = csvread('stationary_chasing.csv');
chaseX = data(:,1); chaseY = data(:,2);
%randomX = data(:,4); randomY = data(:,5);

figure;
plot(chaseX,chaseY,'.'); hold on; 
%plot(randomX,randomY,'.');
hold on;
plot(chaseX(end),chaseY(end),'ro');
plot(chaseX(1),chaseY(1),'ro');
%%
%close all;
data = csvread('dynamic_chasing.csv');
chaseX = data(:,1); chaseY = data(:,2);
randomX = data(:,4); randomY = data(:,5);

figure;

plot(chaseX,chaseY,'.'); hold on; 
plot(randomX,randomY,'.');
legend('runner','chaser');
plot(chaseX(end),chaseY(end),'rx');
plot(chaseX(1),chaseY(1),'ro');

plot(randomX(end),randomY(end),'kx');
plot(randomX(1),randomY(1),'ko');
%%
data = csvread('test.csv');
chaseX = data(:,1); chaseY = data(:,2);
%randomX = data(:,4); randomY = data(:,5);

figure;

plot(chaseX,chaseY,'.'); hold on; 
%plot(randomX,randomY,'.');
legend('runner','chaser');
hold on;
plot(chaseX(end),chaseY(end),'rx');
plot(chaseX(1),chaseY(1),'ro');
