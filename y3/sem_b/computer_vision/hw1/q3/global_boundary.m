clear all, clc;
load('sq.mat');
load('sq1.mat');

header = ['Question 3\n'...
          'Seperating an object by finding the global boundry\n\n\n'];
      
fprintf(header)

% A - C
fprintf('sq.mat:\n')
figure(1), title('SQ')
sq_sigma = get_maximal_sigma(sq);

fprintf('\nsq1.mat:\n')
% D
figure(2), title('SQ1')
sq1_sigma = get_maximal_sigma(sq1);

fprintf('\ne.\n')
danswer = ['The maximum sigma can be calculated with the following formula:\n' ... 
          'max_sigma = (mean2(sq) - mean(sq(sq<mean2(sq)))) / 3 - 1\n' ...
          'we know that beyond 3 sigma border, lies 0.1%% of the pixels\n' ...
          'threfore we calculate the distance between lower "model" and the mean divide by 3\n'];
fprintf(danswer)




