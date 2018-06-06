clear all, close all, clc;


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









