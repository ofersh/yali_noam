load Xcricket.mat
X = Xcricket(:,2);
y = Xcricket(:,1);
figure(1)
plot(X, y, 'rO')
grid

m = length(y);
X = [ones(m, 1) X];

theta = pinv(X' * X) * X' * y

x0 = 60
x1 = 100
y0 = theta(1) + theta(2)*x0
y1 = theta(1) + theta(2)*x1
hold on
line ([x0 x1], [y0 y1], 'lineWidth', 2)
