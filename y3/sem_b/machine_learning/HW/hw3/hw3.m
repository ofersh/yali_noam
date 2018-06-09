%% SVM and Perceptron HW:

%% q3 - svm_test and svm_train:
%   
%   function [accuaracy] = svm_test( theta, X_test, y_test)
%   
%       predicted_y = theta' * X_test;
%       comparison_y = sign(predicted_y) - y_test;
%       accuaracy = sum(comparison_y ~= 0) / length(y_test);
%       
%   end
%   
%   function [theta] = svm_train( X, y )
%   
%   d = size(X,2);
%   H = eye(d);
%   f = zeros(d,1);
%   Dy = diag(y);
%   A = Dy*X;
%   b = ones(size(y));
%   
%   theta = quadprog(H, f, -A, -b);
%   
%   
%   end

%% q4-5 - Visualization of HyperPlane and Margin:
% For both Perceptron and SVM.

clc; clear; close all;
addpath(genpath('./materials'))

load data1.mat
[normX, sDev, means] = data_normalization(X);

[perc_theta, k] = my_perceptron_train(normX, y);
svm_theta = svm_train(normX, y);

figure('Name', 'Data1')
set(gcf, 'Position', [300, 300, 1300, 650]);
subplot(1,2,1)
title('Data1'); hold on;
plot_data_svm_percep(normX, svm_theta, perc_theta);
subplot(1,2,2)
plot_data_svm_percep(normX, svm_theta, perc_theta);
legend('off');
xlim([-1 1]); ylim([-1 1]);

load data2.mat
[normX, sDev, means] = data_normalization(X);

[perc_theta, k] = my_perceptron_train(normX, y);
svm_theta = svm_train(normX, y);

figure('Name', 'Data2')
set(gcf, 'Position', [300, 300, 1300, 650]);
subplot(1,2,1)
title('Data2'); hold on;
plot_data_svm_percep(normX, svm_theta, perc_theta);
subplot(1,2,2)
plot_data_svm_percep(normX, svm_theta, perc_theta);
legend('off');
xlim([-0.5 0.5]); ylim([-0.5 0.5]);





