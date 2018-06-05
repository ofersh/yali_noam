function [accuaracy] = svm_test( theta, X_test, y_test)

    predicted_y = theta' * X_test;
    comparison_y = sign(predicted_y) - y_test;
    accuaracy = sum(comparison_y ~= 0) / length(y_test);
    
end

