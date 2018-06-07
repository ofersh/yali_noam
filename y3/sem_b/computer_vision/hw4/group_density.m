function [ mu, sigma ] = group_density( file_name )

    C = objects_features(file_name);
    n = length(C);
    mu = sum(C) / n;
    sigma = sum((C-mu).^2) / n;

end

