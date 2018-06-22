function [ perim ] = laplace_perim( image, val )

image(image ~= val) = 255;
dseg = double(image);
del_seg = del2(dseg);
perim = length(find(del_seg<0));
end

