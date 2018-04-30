clear; clc; close all;
addpath(addpath([genpath('./functions') genpath('./materials')]))

% A) Scatter the data
data = load('email_data.txt');
X = data(:, [1, 2]); y = data(:, 3);

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

% C) Create decision plain

alpha = 0.1;
num_iters = 7000;
lambda = 1.03;
X_poly = mapFeature(X(:,1), X(:,2));
theta_poly =  zeros(1, size(X_poly,2));
[theta, J] = gd_reg(X_poly, y, theta_poly, alpha, num_iters, lambda);

% D) Plot decision plain
plotDecisionBoundary(theta, X_poly, y)

% E) Comparing different lambdas

figure('Name', 'Comparing Lambda')
i=1;
best_lambda = 0;
best_j = inf;
for lambda = linspace(0,1,9)
    
    [~, J] = gd_reg(X_poly, y, theta_poly, alpha, num_iters, lambda);
    subplot(3,3,i);
    plot(1:num_iters, J); title(sprintf('lambda = %g', lambda))
    grid
    i = i+1;
    if J(end) < best_j
       best_lambda = lambda;
       best_j = J(end);
    end
    
end

fprintf('Best lambda = %g\n', best_lambda);


% F) Testing the model

[test_theta, J] = gd_reg(X_poly, y, theta_poly, alpha, num_iters, best_lambda);
load emaildata3.mat

testX_poly = mapFeature(X(:,1), X(:,2));
z = test_theta' * testX_poly';
predicted_y = sigmoid(z);

predicted_y(predicted_y>0.5) = 1;
predicted_y(predicted_y<=0.5) = 0;
fprintf('Pause started\n')
pause()
close 1
plotDecisionBoundary(test_theta, testX_poly, y); hold on

difference = y(:) - predicted_y(:);
wrong_predict = sum(difference ~= 0);
fprintf('Wrong prediction results: %g\n', wrong_predict)


% G) using fminunc to find the theta
fprintf('Pause started\n')
pause()
close 1
data = load('email_data.txt');
fminunc_X_poly = data(:, [1, 2]); fminunc_y = data(:, 3);

fminunc_X_poly = mapFeature(fminunc_X_poly(:,1), fminunc_X_poly(:,2));
fminunc_theta =  zeros(1, size(fminunc_X_poly,2));

costFunc = @(fminunc_theta)question2g(fminunc_theta, fminunc_X_poly, fminunc_y);

[fminunc_theta,y]=fminunc(costFunc, fminunc_theta);
fprintf('fminunc found theta:\n')
plotDecisionBoundary(fminunc_theta(:), fminunc_X_poly, fminunc_y)


