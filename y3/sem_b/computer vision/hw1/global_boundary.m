load('sq.mat');
load('sq1.mat');

sq_sigma = get_maximal_sigma(sq, 'SQ');
sq1_sigma = get_maximal_sigma(sq1, 'SQ1');

fprintf('\n')
fprintf('\n')
fprintf('') 

%{
d. the maximum sigma can be calculated with the following formula:

    max_sigma = (mean2(sq) - mean(sq(sq<mean2(sq)))) / 3 - 1

    we know that beyond 3 sigma border, lies 0.1% of the pixels
    threfore we calculate the distance between lower "modle" and the mean divide by 3
%}

sigma = 70/255;
gaus_15 = imnoise(sq, 'gaussian', 0, sigma^2);
figure(1), subplot(2,2,3), histogram(gaus_10), title('max Gaussian noise');
fprintf('b. The global error free boundry can be found with max sigma 15 gaussian noise\n')

