clear all;
addpath(genpath('../q1'))
data = csvread('kleibers_law_data.csv',1);
mass = data(:,1);
metabolism = data(:,2);

% A
mass_log = log(mass);
metabolism_log = log(metabolism);
figure(1), scatter(mass_log, metabolism_log, 'k.'), xlabel('log(mass)'),
ylabel('log(metabolism)'), hold on;

% B
% We will use a linear regrssion model on log of Mass and Metabolism.
X = [ones(size(mass_log)), mass_log];
y = metabolism_log;
[theta, J] = gradiant_descent(X, y, [0 0], 0.01, 2000);
fprintf('\nq3.b:\n')
fprintf('Our linear model will be: ln(y) = theta0 + theta1*ln(x)\n')
fprintf('Found theta for our linear model:\ntheta(0) = %g\ntheta(1) = %g\n', theta)


% C
fprintf('\nq3.c:\n')
fprintf('The formula for mass(x) and metabolism(y) is:\ny = exp(%.3g*ln(x) + %.3g)\n', theta)


% D
ln_hx = @(theta, x) theta(1) + theta(2) * x;
ln_kjoul = ln_hx(theta, X);
plot(X, ln_kjoul)

mass = 10;
ln_mass = log(mass);
cal = 4.18;
ln_metabo = ln_hx(theta, ln_mass);
calories = exp(ln_metabo)/cal;
fprintf('\nq3.d:\n')
fprintf('Mamal of 10kg mass Consume: %.3gKcal\n', calories);

% E
metabo = 1.63;
ln_metabo = log(1.63);
ln_hxInv = @(theta, y) (y - theta(1))/theta(2);
ln_mass = ln_hxInv(theta, ln_metabo);
millig = exp(ln_mass)*1e6;
fprintf('\nq3.e:\n');
fprintf('The mass of mamal which has metabolism of 1.63kJoul is: %.3gmg\n', millig)

