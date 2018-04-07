addpath(genpath('../q1'))
data = csvread('kleibers_law_data.csv',1);
mass = data(:,1);
metabolism = data(:,2);

% A
mass_log = log(mass);
metabolism_log = log(metabolism);
figure(1), scatter(mass_log, metabolism_log, 'k.'), xlabel('log(mass)'),
ylabel('log(metabolism)');

% B
% We will use a linear regrssion model on log of Mass and Metabolism.
X = [ones(size(mass)), mass_log];
y = metabolism_log;
[theta, J] = gradiant_descent(X, y, [0 0], 0.01, 400);
fprintf('\nq3.b:\n')
fprintf('Our linear model will be: ln(y) = theta0 + theta1*ln(x)\n')
fprintf('Found theta for our linear model:\ntheta(0) = %g\ntheta(1) = %g\n', theta)

% C
fprintf('\nq3.c:\n')
fprintf('The formula for mass(x) and metabolism(y) is:\ny = exp(%.3g*ln(x) + %.3g)\n', theta)


% D
hx = @(theta, x) exp(theta(1) + theta(2) * log(x));


mass = 10;
cal = 4.18;
metabo = hx(theta, mass);
calories = metabo/cal;
fprintf('\nq3.d:\n')
fprintf('Mamal of 10kg mass Consume: %.3gKcal\n', calories);

% E
metabo = 1.63;
hxInv = @(theta, y) exp((log(y) - theta(1))/theta(2));
mass = hxInv(theta, metabo);
millig = mass * 1e6;
fprintf('\nq3.e:\n');
fprintf('The mass of mamal which has metabolism of 1.63kJoul is: %.3gmg\n', millig)

