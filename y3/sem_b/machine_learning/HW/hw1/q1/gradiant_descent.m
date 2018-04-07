function [ theta, J ] = gradiant_descent( X, y, theta, alpha, max_iter )

    if max_iter > 2000
        J=0;
        return
    end

    m = length(y);
    J = zeros(1, max_iter) ;
    for i = 1:max_iter
        err = y' - theta * X';
        J(i) = cost_computation(X, y, theta);
        DerivJ= - err*X/m;
        theta = theta - alpha * DerivJ;
        % q1.E:
        % figure(3), plot_contour(X, y, theta)
        % pause(0.001)
    end
end

