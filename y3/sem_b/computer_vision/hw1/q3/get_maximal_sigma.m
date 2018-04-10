function [ max_sig ] = get_maximal_sigma( sq )
    sq = uint8(sq);

    subplot(2,2,1), histogram(sq), title('Original');
    
    % A
    sigma = 10/255;
    gaus_10 = imnoise(sq, 'gaussian', 0, sigma^2);
    subplot(2,2,2), histogram(gaus_10, 255), title('Gaussian sigma=10');
    fprintf('a. The global boundry can be found without error\n')
    
    % B
    max_sig = (mean2(sq) - mean(sq(sq<mean2(sq)))) / 3 - 1;
    sigma = max_sig/255;
    gaus_max = imnoise(sq, 'gaussian', 0, sigma^2);
    subplot(2,2,3), histogram(gaus_max, 255), title(sprintf('max Gaussian sigma = %.3g', max_sig));
    fprintf('b. The global error free boundry can be found with max sigma %g gaussian noise\n', max_sig)

    % C
    sigma = 50/255;
    gaus_50 = imnoise(sq, 'gaussian', 0, sigma^2);
     subplot(2,2,4), histogram(gaus_50, 255), title('Gaussian sigma=50');
    fprintf('c. The global boundry can not be found\n')
end

