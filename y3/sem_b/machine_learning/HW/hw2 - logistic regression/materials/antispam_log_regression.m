%% e-mail anti spam using logistic regression
clc
%load data
load emaildata1
% X is the feature matrix (each row represents one e-mail)
% y - the corresponding label

% plotting the data
plotdata(X,y), grid, xlabel('first feature'),
    ylabel('second feature')
figure(1)
pause

%% Initialization
m=length(y);
alpha=0.1;
X1=[ones(m,1) X X(:,2).^2]; % adding a first column of ones
theta=zeros(size(X1,2),1);

%% computing cost function and gradient
[J,grad]=costF_log(theta,X1,y)

%% Applying gradient descent
num_iters=7000;
[theta,J]=gd(X1,y,theta,alpha,num_iters);
hold on

line([min(X1(:,2)),max(X1(:,2))],...
    [(-theta(1)-theta(2)* min(X1(:,2)))/theta(3),...
    (-theta(1)-theta(2)* max(X1(:,2)))/theta(3)],...
    'LineWidth', 5, 'Color', 'b')
grid

figure(2), plot(1:num_iters,J), grid



