function [ max_sig ] = get_maximal_sigma( sq, str )

sq = uint8(sq);

figure('Name', str), subplot(2,2,1), histogram(sq), title('Original histogram');

sigma = 10/255;
gaus_10 = imnoise(sq, 'gaussian', 0, sigma^2);
subplot(2,2,2), histogram(gaus_10, 255), title('Gaussian sigma=10 histogram');
fprintf('a. The global boundry can be found without error\n')

max_sig = (mean2(sq) - mean(sq(sq<mean2(sq)))) / 3 - 1;
sigma = max_sig/255;
gaus_15 = imnoise(sq, 'gaussian', 0, sigma^2);
subplot(2,2,3), histogram(gaus_15, 255), title('max Gaussian noise');
fprintf('b. The global error free boundry can be found with max sigma 15 gaussian noise\n')

sigma = 50/255;
gaus_50 = imnoise(sq, 'gaussian', 0, sigma^2);
subplot(2,2,4), histogram(gaus_50, 255), title('Gaussian sigma=50 histogram');
fprintf('c. The global boundry can not be found\n')



end

