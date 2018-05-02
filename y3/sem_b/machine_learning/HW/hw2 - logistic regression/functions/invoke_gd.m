function [ theta, J ] = invoke_gd( X, y, alpha )

    theta = zeros(size(X,2),1);
    num_iters=7000;
    [theta, J]=gd(X,y,theta,alpha,num_iters);


end

