function [ C ] = objects_features( file_name )
%OBJECTS_FEATURES Summary of this function goes here
%   Detailed explanation goes here
    img = imread(file_name);

    [seg_im, vals] = segmentation(img);
    C = [];
    for val=vals(1 : end-1)
        c = circularity(seg_im, val);
        C = [C c];
    end

end

