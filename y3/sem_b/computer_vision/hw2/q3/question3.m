clc, clear all;

image = imread('cell1.bmp');

[seg_im, vals] = segmentation(image);

fprintf('q3\n')
fprintf('For cell1.bmp:\n')
for val=vals(1 : end-1)
    c = circularity(seg_im, val);
    fprintf('For object of value %3g the circularity is %.3g\n', val, c)
end

fprintf('\nFor cell2.bmp:\n')
image = imread('cell2.bmp');
[seg_im, vals] = segmentation(image);
for val=vals(1 : end-1)
    c = circularity(seg_im, val);
    fprintf('For object of value %3g the circularity is %.3g\n', val, c)
end


