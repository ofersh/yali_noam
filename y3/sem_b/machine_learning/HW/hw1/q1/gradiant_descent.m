function [ theta, J, THETA ] = gradiant_descent( X, y, theta, alpha, max_iter )

    if max_iter > 2000
        J=0;
        return
    end

    m = length(y);
    J = zeros(1, max_iter) ;
    THETA = zeros(max_iter, size(theta, 2));
    for i = 1:max_iter
        err = y' - theta * X';
        J(i) = cost_computation(X, y, theta);
        DerivJ= - err*X/m;
        THETA(i, :) = theta;
        theta = theta - alpha * DerivJ;
    end
end

