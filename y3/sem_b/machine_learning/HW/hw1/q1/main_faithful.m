load faithful.txt
X = [ones(length(faithful),1) faithful(:,1)];
y = faithful(:,2);

% A:
figure(1), scatter(X(:,2), y)

% B:
max_iter = 400;
[theta, j] = gradiant_descent(X,y, [0 0], 0.03, max_iter);
figure(2), plot(1:max_iter, J), xlabel('Iterations'), ylabel('J(\theta)');


% C:
% create anonymos function.
hx = @(x) theta(1) + theta(2) * x;
fprintf('Estimated time for next eruption:\n')
fprintf('Eruption duration - 1.5 next eruption time: %f\n', hx(1.5))
fprintf('Eruption duration - 3 next eruption time: %f\n', hx(3))
fprintf('Eruption duration - 5 next eruption time: %f\n', hx(5))

% D:
% see cost_computation.m function.

% E: inside  gradiant descent function.
