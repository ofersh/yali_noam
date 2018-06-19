function [ seg_pic, vals ] = segmentation( image )

if size(image,3) == 3
    gray_pic = rgb2gray(image);
else
    gray_pic = double(image);
end
gray_pic(gray_pic==255) = 1;
seg_pic = gray_pic;
[nrows, ncols] = size(gray_pic);
vals(1) = 1;
ind = 1;
for x = 2:ncols-1
    for y = 2:nrows-1
        if seg_pic(y, x) == 0
            seg_pic = region_grow(seg_pic, vals(ind), x, y);
            ind = ind + 1;
            vals(ind) = vals(ind-1) + 10;
        end
    end
end

    function [gray_pic] = region_grow(gray_pic, val, x, y)
        gray_pic(y, x) = val;
        [nrows, ncols] = size(gray_pic);
        for i = -1:1
            for j= -1:1
                if y+i < 1 || x+j < 1
                    continue
                end
                if y+i > nrows || x+j > ncols
                    break
                end
                if gray_pic(y+i, x+j)==0
                    gray_pic = region_grow(gray_pic, val, x+j, y+i);
                end
            end
        end
    end
end

