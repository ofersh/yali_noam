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



