function [theta, J] = gd_2018(X,y, theta, alpha, max_iter)
        
    for iter = 1 : max_iter
        [J(iter), grad] = cost_log(theta, X, y);
    end
end

