%% prepare workspace
clear variables; close all; clc;

%% main
manual = [0 0 0].';

data = csvread('entropies.csv');

manual(1) = mean(data(:,1));
manual(2) = mean(data(:,2));
manual(3) = mean(data(:,3));

entropies = reshape(data,numel(data),1);
[idx, C] = kmeans(entropies,3);

manual = sort(manual);
C = sort(C);

writematrix([manual C],'thresholds.csv');
figure;
plot(data(:,1),0,'r.'); %hold on; plot([0 3.5],[0 0]);
hold on;
plot(data(:,2),0,'b.');
plot(data(:,3),0,'g.');
plot(C,0,'k.','MarkerSize',25);
plot(manual,0,'m.','MarkerSize',15);

title('K-means clustering centroids and data points');
