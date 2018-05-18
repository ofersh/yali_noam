function [ ePoints ] = findEdgePoints( im )

    [I,J] = find(im>0);
    ePoints = [I J] - size(im)/2;


end

