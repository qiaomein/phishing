%% prepare workspace
clear variables; close all; clc;

%% main
manual = [0 0 0].';

data = csvread('entropies.csv');

manual(1) = mean(data(:,1));
manual(2) = mean(data(:,2));
manual(3) = mean(data(:,3));

entropies = reshape(data,numel(data),1);

figure;
plot(entropies,0,'.'); %hold on; plot([0 3.5],[0 0]);
[idx, C] = kmeans(entropies,3);
manual = sort(manual)
C = sort(C)
hold on; plot(C,0,'.','MarkerSize',30);
