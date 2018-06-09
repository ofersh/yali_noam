function [ svm_margin, percept_margin ] = plot_data_svm_percep( X, svm_theta, percept_theta)

scatter(X(:,1), X(:,2), 'DisplayName', 'data'); hold on;
svm_margin = decision_boundry_line_with_borders(svm_theta, X, 'g', 'SVM');
percept_margin = decision_boundry_line_with_borders(percept_theta, X, 'r', 'Perceptron');
legend('Location', 'NW');
hold off;
end

