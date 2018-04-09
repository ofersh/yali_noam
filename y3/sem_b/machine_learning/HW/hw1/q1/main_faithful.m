clear all; clc;
load faithful.txt
X = [ones(length(faithful),1) faithful(:,1)];
y = faithful(:,2);

% A:
figure(1), scatter(X(:,2), y)
xlabel('Duration of minutes of the eruption')
ylabel('Time to next eruption (minutes)')
hold on

% B:
max_iter = 2000;
[theta, J, THETA] = gradiant_descent(X,y, [0 0], 0.03, max_iter);
hx = @(x) theta(1) + theta(2) * x;
figure(2), plot(1:max_iter, J), xlabel('Iterations'), ylabel('J(\theta)');
figure(1), plot(X(:,2), hx(X(:,2)))

% C:
% create anonymos function.
fprintf('Estimated time for next eruption:\n')
fprintf('Eruption duration - 1.5 min, next eruption time: %f min\n', hx(1.5))
fprintf('Eruption duration - 3 min, next eruption time: %f min\n', hx(3))
fprintf('Eruption duration - 5 min, next eruption time: %f min\n', hx(5))

% D:
% see cost_computation.m function.

% E: inside  gradiant descent function.
% q1.E:
figure(3), plot_contour(X, y, THETA)
