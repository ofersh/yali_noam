% e-mail anti spam using logistic regression
clc, clear all, close all;
% load data
load emaildata1
% X is the feature matrix (each row represents one e-mail)
% y - the corresponding label

% plotting the data
pos_ind = find(y==1);
neg_ind = find(y==0);

scatter(X(pos_ind,2),X(pos_ind,1),'go', 'filled'), hold on
scatter(X(neg_ind,2),X(neg_ind,1),'rd', 'filled')
figure(1)

% Initialization
m=length(y);
alpha=0.8;
X_quad=[ones(m,1) X X(:,1).^2]; % adding a first column of ones
X = [ones(m,1) X];

theta = zeros(size(X,2),1);
theta_quad = zeros(size(X_quad,2),1);

% computing cost function and gradient
[J, grad] = costF_log(theta,X,y);

% Applying gradient descent
num_iters=7000;
[theta, J]=gd(X,y,theta,alpha,num_iters);
[theta_quad, J]=gd(X_quad,y,theta_quad,alpha,num_iters);
hold on

draw_boundary_linear_line(X, theta);
draw_boundary_quadric_line(X_quad, theta_quad);

% figure(2), plot(1:num_iters,J), grid

% line([min(X1(:,2)),max(X1(:,2))],...
%     [(-theta(1)-theta(2)* min(X1(:,2)))/theta(3),...
%     (-theta(1)-theta(2)* max(X1(:,2)))/theta(3)],...
%     'LineWidth', 5, 'Color', 'b')
grid


