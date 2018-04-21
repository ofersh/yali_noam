function [ perim ] = myPerim( image, val )
    perim = 0;
    [nrows, ncols] = size(image);
    for x = 1:ncols
        for y = 1:nrows
            if image(y, x) == val
                k = 0;
                for i = -1:1
                    for j = -1:1
                        if x+i < 1 || y+j < 1 
                            continue
                        end
                        if image(y+j, x+i) == 255
                            k = k + 1;
                            break;
                        end
                    end
                    if k ~= 0
                        break
                    end
                end
                if k ~= 0
                    perim = perim + 1;
                    k = 0;
                end
            end
        end
    end


end

