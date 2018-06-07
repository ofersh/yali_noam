function [ theta, k ] = my_perceptron_train( X, y )

    ind = 1;
    theta = X(ind,:) * y(ind);
    k = 1;
    
    while ind ~= length(X)
        ind = ind + 1;
        k = k + 1;
        err = sign(theta*X(ind,:)') * y(ind);
        if err < 0 
           theta = theta + X(ind,:) * y(ind);
           ind = 1 ;
        end
    end
end

