function [ c ] = circularity( image, val )
% circularity Calculates circularity for segmented shape.
% c = circularity calculation.
% image = segmented image.
% val = segmented shape value.

    area = length(find(image == val));
    perim = myPerim(image, val);
    c = (4*pi*area)/perim^2;
end

