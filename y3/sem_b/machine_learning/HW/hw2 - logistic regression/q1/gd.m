function [ theta, J ] = gd( X, y, theta, alpha, max_iter )

    m = length(y);
    J = zeros(1, max_iter) ;
    for i = 1:max_iter
        [J(i), grad] = costF_log(X, y, theta);
        theta = theta - alpha * grad;
    end
end

