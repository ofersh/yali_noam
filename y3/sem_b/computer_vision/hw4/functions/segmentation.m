function [ seg_pic, vals ] = segmentation( image )

gray_pic = rgb2gray(image);
seg_pic = gray_pic;
[nrows, ncols] = size(gray_pic(:,:,1));
vals(1) = 1;
ind = 1;
for x = 2:ncols-1
    for y = 2:nrows-1
        if seg_pic(x,y) == 0
            seg_pic = region_grow(seg_pic, vals(ind), x, y);
            ind = ind + 1;
            vals(ind) = vals(ind-1) + 10;
        end
    end
end

    function [gray_pic] = region_grow(gray_pic, val, x, y)
        gray_pic(x,y) = val;
        [nrows, ncols] = size(gray_pic);
        for i = -1:1
            for j= -1:1
                if x+i < 1 || y+j < 1
                    continue
                end
                if x+i > nrows || y+j > ncols
                    break
                end
                if gray_pic(x+i, y+j)==0
                    gray_pic = region_grow(gray_pic, val, x+i, y+j);
                end
            end
        end
    end
end

