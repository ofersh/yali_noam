function [ norm_data, sDev, means ] = data_normalization( X )
    means = mean(X);
    sDev = std(X);
    norm_data = (X - means)./sDev;
end

