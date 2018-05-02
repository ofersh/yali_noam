clear; clc; close all;
addpath(addpath([genpath('./functions') genpath('./materials')]))

data = load('email_data.txt');
X = data(:, [1, 2]); y = data(:, 3);


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

