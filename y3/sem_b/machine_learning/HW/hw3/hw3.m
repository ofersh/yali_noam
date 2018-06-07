clc; clear; close all;
addpath([genpath('./materials') genpath('/home/noam/git/yali_noam/y3/sem_b/machine_learning/HW/hw3/libsvm/libsvm-3.22/matlab')])

%% q4

load data1.mat
[normX, sDev, means] = data_normalization(X);

[perc_theta, k] = my_perceptron_train(normX, y);
svm_theta = svm_train(normX, y);

figure('Name', 'Data1')

scatter(normX(:,1), normX(:,2)); hold on
d1_svm_geomLines = decision_boundry_line_with_borders(svm_theta, normX, 'g');
d1_perc_geomLines = decision_boundry_line_with_borders(perc_theta, normX, 'r');

load data2.mat
[normX, sDev, means] = data_normalization(X);

[perc_theta, k] = my_perceptron_train(normX, y);
svm_theta = svm_train(normX, y);

figure('Name', 'Data2')

scatter(normX(:,1), normX(:,2)); hold on
d2_svm_geomLines = decision_boundry_line_with_borders(svm_theta, normX, 'g');
d2_perc_geomLines = decision_boundry_line_with_borders(perc_theta, normX, 'r');


%% q5

load handWrittenDigits.mat
[normX, sDev, means] = data_normalization(X);
model = svmtrain(y, normX);
load test_data.mat
[normX, sDev, means] = data_normalization(X);
[predicted_label, accuracy, decision_values] = svmpredict(y, normX, model);






