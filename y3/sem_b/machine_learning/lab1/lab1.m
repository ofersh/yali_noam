clear all, close all
f = inline('0.5 * theta.^2+5*sin(theta)');
df = inline('theta+5*cos(theta)');

theta_axis=linspace(-5,5,10000);
faxis = linspace(-5 , 20, 10000);

figure(1), plot(theta_axis, f(theta_axis), 'b')
xlabel('theta'), ylabel('J(theta)'), grid, hold on

alpha = 0.2;
theta = zeros(5000);
theta(1) = 5;
max_iter = 5000;
i = 1;

emin = 1e-6;
while i < max_iter
    dtheta = -alpha * df(theta(i));
    theta(i+1) = theta(i) + dtheta;
    x0 = theta(i);
    x1 = theta(i+1);
    y0 = f(x0);
    y1 = f(x1);
    plot(x0, y0, 'rx', x0, y0, '-')
    line([x0 x1], [y0 y1], 'Color', 'r', 'LineWidth', 0.5)
    figure(1)
    pause(0.1)
    if abs(y1-y0) < emin, break,end
   i = i + 1; 
end
fprintf('Number of iterations = %f\n', i)
theta(i)