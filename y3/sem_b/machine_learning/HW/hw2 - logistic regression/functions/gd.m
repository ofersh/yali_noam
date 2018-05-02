function [ theta, J ] = gd( X, y, theta, alpha, max_iter)
    [theta, J] = gd_reg( X, y, theta, alpha, max_iter, 0);
end

