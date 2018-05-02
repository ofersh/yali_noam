clear; clc; close all;
addpath(addpath([genpath('./functions') genpath('./materials')]))

% F) Testing the model

% Generating theta with optimal lambda
alpha = 0.1;
lambda = 0;
num_iters = 7000;

data = load('email_data.txt');
X = data(:, [1, 2]); y = data(:, 3);
X_poly = mapFeature(X(:,1), X(:,2));
theta_poly =  zeros(1, size(X_poly,2));
[theta, J] = gd_reg(X_poly, y, theta_poly, alpha, num_iters, lambda);

load emaildata3.mat

testX_poly = mapFeature(X(:,1), X(:,2));
z = theta' * testX_poly';
predicted_y = sigmoid(z);

predicted_y(predicted_y>0.5) = 1;
predicted_y(predicted_y<=0.5) = 0;

plotDecisionBoundary(theta, testX_poly, y); hold on
