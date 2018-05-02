function [ theta, J ] = gd_reg ( X, y, theta, alpha, max_iter, lambda )
    J = zeros(1, max_iter) ;
    for i = 1:max_iter
        [J(i), grad] = costFunctionWithBias(theta , X, y, lambda);

        theta = theta(:) - alpha * grad(:);
    end
end

