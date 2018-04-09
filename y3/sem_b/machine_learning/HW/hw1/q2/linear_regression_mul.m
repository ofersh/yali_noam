clc; clear all;
addpath(genpath('../q1'))
data = load('houses.txt');
X0 = ones(length(data), 1);

% A
[norm_data, sDev, means] = data_normalization(data);
X = [X0 norm_data(:,1:2)];
y = norm_data(:,3);
[theta, J, THETA] = gradiant_descent(X, y, [0 0 0], 0.01, 2000);
fprintf("The dimension of theta is: %dx%d\n", size(theta));
fprintf("generated theta: (%g, %g, %g)\n", theta);

% B
normalize = @(data, type) (data - means(type)) / sDev(type);
area = 1800;
rooms = 5;
norm_area = normalize(area, 1);
norm_rooms = normalize(rooms, 2);
hx = @(theta, X) theta*X';
norm_est_price = hx(theta, [1 norm_area norm_rooms]);
est_price = (norm_est_price * sDev(3)) + means(3);
fprintf("The estimated price of an 1800 sf of 5 rooms is: %g\n", est_price);

% C
X2 = [X0 data(:,1:2)];
y2 = data(:,3);
theta2 = ((X2'*X2)^-1)*X2'*y2;
est_price2 = hx(theta2', [1 area rooms]);

fprintf('------------------------------------\n');
fprintf("Using ((X'*X)^-1)*X'*y forumula:\n");
fprintf('Newly generated thetas are: (%g, %g, %g)\n',theta2);
fprintf("The estimated price of an 1800 sf of 5 rooms is: %g\n", est_price2);

