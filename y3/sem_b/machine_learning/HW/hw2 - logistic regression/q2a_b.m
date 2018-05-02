clear; clc; close all;
addpath(addpath([genpath('./functions') genpath('./materials')]))

data = load('email_data.txt');
X = data(:, [1, 2]); y = data(:, 3);

% A) Scatter the data
figure('Name', 'Scatter Data');
scatter_data(X, y);

% B) Try classify with logistic model
figure('Name', 'Classify with Logistic Model');
m=length(y);
X_quad=[ones(m,1) X X(:,1).^2]; % adding a first column of ones

alpha=3;
[theta_quad, J] = invoke_gd(X_quad, y, alpha);
subplot(1,2,1);
plot_decision_plain(X_quad, y, theta_quad, @draw_boundary_quadric_line);
axis([-1 1.5 -1 1.5]);
grid
subplot(1,2,2);
plot(1:length(J), J)

fprintf('We can see that the logistic model can not work well\n');
