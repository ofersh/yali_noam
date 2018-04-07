function [] = plot_contour( X, y, theta )
% Grid for contour plot of gradient descent
    theta0=linspace(0, 70, 500);
    theta1=linspace(0, 20, 500);
    J =zeros(length(theta0),length(theta1));
    % a matrix of J values for each theta
    for i = 1:length(theta0)
        for j = 1:length(theta1)
            thetamatrix = [theta0(i) theta1(j)];
            J(i,j) = cost_computation(X, y, thetamatrix);
        end
    end
    % contour plot using a logarithmic scale
    contour(theta0, theta1, J, logspace(-3, 4))
    xlabel('\theta_0'); ylabel('\theta_1');
    hold on;
    plot(theta(1), theta(2), 'bx', 'MarkerSize', 5, 'LineWidth', 2);
    % theta(1) and theta(2) are the values computed by gradient descent
end

