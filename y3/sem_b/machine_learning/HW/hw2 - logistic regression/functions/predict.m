function [ classified_y ] = predict( X, y, theta, decision_plain)    

    z = theta' * X';
    predicted_y = sigmoid(z);
    
    predicted_y(predicted_y>0.5) = 1;
    predicted_y(predicted_y<=0.5) = 0;

    classified_y  = predicted_y;
    
    plot_decision_plain(X, y, theta, decision_plain)
    
    
end

