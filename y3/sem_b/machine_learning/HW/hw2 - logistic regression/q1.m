clc, clear, close all;
addpath([genpath('./functions') genpath('./materials')])
% addpath(genpath('./materials'))
load emaildata1.mat;

% A) plot the data
figure('Name', 'Display Data')
pos_ind = find(y==1);
neg_ind = find(y==0);

scatter(X(pos_ind,1),X(pos_ind,2),'go', 'filled'), hold on
scatter(X(neg_ind,1),X(neg_ind,2),'rd', 'filled')

X_org = X;

% B) Automatic mail classification ( Linear )
% Initialization
m=length(y);
X = [ones(m,1) X_org];

% Applying gradient descent
alpha=0.7;
[theta_lin, J] = invoke_gd(X, y, alpha);

figure('Name', 'Linear Model')
subplot(1,2,1);
plot_decision_plain(X, y, theta_lin, @draw_boundary_linear_line);
grid

subplot(1,2,2);
plot(1:length(J), J)

% C) Automatic mail classification ( Quadratic )

X_quad=[ones(m,1) X_org X_org(:,1).^2]; % adding a first column of ones

alpha=3;
[theta_quad, J] = invoke_gd(X_quad, y, alpha);

figure('Name', 'Quadratic Model')
subplot(1,2,1);
plot_decision_plain(X_quad, y, theta_quad, @draw_boundary_quadric_line);
grid
subplot(1,2,2);
plot(1:length(J), J)

% D) Plot J according to iteration number and alpha

figure('Name', 'J acording to alpha'), title('J acording to alpha');
i = 1;
for alpha = linspace(0.7,4,9)
    [theta, J] = invoke_gd(X_quad, y, alpha);
    subplot(3,3,i);
    plot(1:length(J), J), title(sprintf('alpha = %g', alpha)), axis([0 length(J) 0 0.3]), grid
    i = i+1;
end

% E) Testing new data

load 'email_test_data'

X_test = [ones(25,1) Xtest Xtest(:,1).^2];
figure('Name', 'Predict with Quadratic model')
predicted_y = predict(X_test, ytest, theta_quad, @draw_boundary_quadric_line);
difference = ytest(:) - predicted_y(:);
wrong_predict_quad = sum(difference ~= 0);


X_test = [ones(25,1) Xtest];
figure('Name', 'Predict with Linear model')
predicted_y = predict(X_test, ytest, theta_lin, @draw_boundary_linear_line);
difference = ytest(:) - predicted_y(:);
wrong_predict_lin = sum(difference ~= 0);

fprintf('Quadratic prediction results: %g\n', wrong_predict_quad)
fprintf('Linear prediction results: %g\n', wrong_predict_lin)



