clc; clear; close all;
addpath([genpath('./materials') genpath('/home/noam/git/yali_noam/y3/sem_b/machine_learning/HW/hw3/libsvm/libsvm-3.22/matlab')])

%% q4

load data1.mat
[normX, sDev, means] = data_normalization(X);

[perc_theta, k] = my_perceptron_train(normX, y);
svm_theta = svm_train(normX, y);

figure('Name', 'Data1')
set(gcf, 'Position', [500, 500, 1000, 500])

subplot(1,2,1);
scatter(normX(:,1), normX(:,2), 'DisplayName', 'Data1'); hold on
legend('Location','NW')
subplot(1,2,2);
scatter(normX(:,1), normX(:,2), 'DisplayName', 'Data1'); hold on
d1_svm_geomLines = decision_boundry_line_with_borders(svm_theta, normX, 'g', 'SVM');
d1_perc_geomLines = decision_boundry_line_with_borders(perc_theta, normX, 'r', 'Perceptron');
legend('Location','NW')

load data2.mat
[normX, sDev, means] = data_normalization(X);

[perc_theta, k] = my_perceptron_train(normX, y);
svm_theta = svm_train(normX, y);

figure('Name', 'Data2')
set(gcf, 'Position', [500, 500, 900, 600])

scatter(normX(:,1), normX(:,2),'DisplayName', 'Data2'); hold on
d2_svm_geomLines = decision_boundry_line_with_borders(svm_theta, normX, 'g', 'SVM');
d2_perc_geomLines = decision_boundry_line_with_borders(perc_theta, normX, 'r', 'Perceptron');

legend('Location','NW')

%% q5
return
load handWrittenDigits.mat
[normX, sDev, means] = data_normalization(X);
model = svmtrain(y, normX);
load test_data.mat
[normX, sDev, means] = data_normalization(X);
[predicted_label, accuracy, decision_values] = svmpredict(y, normX, model);






