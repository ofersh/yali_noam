function [ data ] = image2blocks( img )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
[nrows, ncols] = size(img);
N = min([nrows ncols]);
multiplier = round(N / 15);
new_size = multiplier*15;
crop_img = img(1:new_size, 1:new_size);

C = mat2cell(crop_img, repelem(15, multiplier), repelem(15, multiplier));

num_of_digits = multiplier * multiplier; 
data = zeros(num_of_digits, 15*15);
for ind = 1:num_of_digits
   c_mat = cell2mat(C(ind));
   data(ind, :) = c_mat(:)'; 
end

end

