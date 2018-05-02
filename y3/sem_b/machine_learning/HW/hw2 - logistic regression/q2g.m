clear; clc; close all;
addpath(addpath([genpath('./functions') genpath('./materials')]))

data = load('email_data.txt');
fminunc_X_poly = data(:, [1, 2]); fminunc_y = data(:, 3);

fminunc_X_poly = mapFeature(fminunc_X_poly(:,1), fminunc_X_poly(:,2));
fminunc_theta =  zeros(1, size(fminunc_X_poly,2));

costFunc = @(fminunc_theta)question2g(fminunc_theta, fminunc_X_poly, fminunc_y);

[fminunc_theta,y]=fminunc(costFunc, fminunc_theta);
fprintf('fminunc found theta:\n')

% Plot decision plain
plotDecisionBoundary(fminunc_theta', fminunc_X_poly, fminunc_y)

% Comparing different lambdas
figure('Name', 'Comparing Lambda')
i=1;
alpha = 0.1;
best_lambda = 0;
num_iters = 7000;
best_j = inf;
for lambda = linspace(0,1,9)
    costFunc = @(fminunc_theta) costFunctionWithBias(fminunc_theta, fminunc_X_poly, fminunc_y, lambda);
    [fminunc_theta, y]=fminunc(costFunc, fminunc_theta);
    [~, J] = gd_reg(fminunc_X_poly, fminunc_y, fminunc_theta', alpha, num_iters, lambda);
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

