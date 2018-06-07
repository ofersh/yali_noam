
clear all, close all, clc;
addpath([genpath('./materials') genpath('./functions')])


%% Q 1

pd1 = makedist('Uniform', 'lower', 0, 'upper', 1);
pd2 = makedist('Uniform', 'lower', 0.8, 'upper', 1.8);

x = 0:0.1:2;

pdf1 = pdf(pd1,x);
pdf2 = pdf(pd2,x);

figure(1);
stairs(x, pdf1, 'b', 'linewidth', 2), hold on;
stairs(x, pdf2, 'r-.', 'linewidth', 2);
line([0.9 0.9], get(gca, 'ylim'),'color', 'k', 'linewidth', 2)
legend({"p(y | c_1)","p(y | c_2)" },'Location','NW')
hold off;

%% Q 2

figure(2);

data1 = [repelem(4,3) repelem(5,6) repelem(6,16) repelem(7,20) ...
    repelem(8,30) repelem(9,18) repelem(10,7)];
histogram(data1, 4:11), hold on;

data2 = [repelem(2,8) repelem(3,19) repelem(4,41) repelem(5,20) ...
    repelem(6,7) repelem(7,5)];
histogram(data2, 2:8);

dist_lm = mean([mean(data1) mean(data2)]);
line([dist_lm dist_lm], get(gca, 'ylim'),'color', 'g', 'linewidth', 2)

%% Q 3

letters = ['A' 'B' 'C' 'D' 'E' 'F' 'G' 'H' 'I' 'J' 'K' 'L' 'M' 'N' 'O' 'P' 'Q' 'R' 'S' 'T' 'U' 'V' 'W' 'X' 'Y' 'Z'];
num_edges = [2 0 2 0 3 3 2 4 2 2 4 2 2 2 0 1 1 2 2 3 2 2 2 4 3 2];
num_T = [2 1 0 0 1 1 0 2 0 0 2 0 0 0 0 1 1 2 0 1 0 0 0 4 1 0];
num_X = [0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0];

fprintf('P(letter=P|edges=1) = 0.5 | P and Q has 1 edge\n')
fprintf('P(letter=H|edges=4) = 1/3 | H K and X has 4 edges\n')
fprintf('P(letter=B|edges=0 and T=1) = 1 | only B has 0 edges and 1 T junction\n')


fprintf('ההתסברויות יקטנו. נצטרך לקחת בחשבון את הסבירות שבכתב היד יש את מספר הקצוות, צמתי ה T וצמתי ה X שאנו מצפים להם.')
fprintf('\n')

%% Q 5

[mu1 sigma1] = group_density('cell1.bmp');
[mu2 sigma2] = group_density('cell2.bmp');

group_prob = @(xi, mu, sigma) exp(-((xi-mu)^2 / (2*sigma))) / (2*pi*sigma) ^ (1/2);

C = objects_features('test.bmp');

cell1 = 0;
cell2 = 0;

% Most Likelihood
for c = C
   cell1_prob = group_prob(c, mu1, sigma1);
   cell2_prob = group_prob(c, mu2, sigma2);   
   
   if cell1_prob > cell2_prob
       cell1 = cell1 + 1;
   else
       cell2 = cell2 + 1;
   end
   
end

fprintf('According to %s: we have %g cell1 and %g cell2\n', 'most likelihood', cell1, cell2);
    
cell1 = 0;
cell2 = 0;

for c = C
    cell1_dist = (c - mu1) ^ 2;
    cell2_dist = (c - mu2) ^ 2;
    
   if cell1_dist < cell2_dist
       cell1 = cell1 + 1;
   else
       cell2 = cell2 + 1;
   end

end

fprintf('According to %s: we have %g cell1 and %g cell2\n', 'Smallest distance', cell1, cell2);








