function q3b2g(im)

figure(), image(im), colormap(gray(2)), title('Original');

% B
imEdges = edge(im, 'canny');
figure(), image(imEdges), colormap(gray(2)), title('canny Edges');

% C
edgesPoint = findEdgePoints(imEdges);

% D
diameter = @(im) round(norm(size(im)));

d = diameter(imEdges);
parameterPlain = zeros(d, 180);

% E
Rho = @(x,y, theta) round(x*cos(theta) + y * sin(theta) + d/2);

for J = 1:length(edgesPoint)
    for i=1:180
        theta = deg2rad(i);
        x = edgesPoint(J,1);
        y = edgesPoint(J,2);
        r = Rho(x, y, theta);
        parameterPlain(r, i) = parameterPlain(r, i) + 1;
    end
end
figure(), image(parameterPlain), colormap(gray(32)), title('Parameter plain');

% F
thresh = 20;

parameterPlain(parameterPlain<thresh) = 0;
temp = parameterPlain;
parameterPlain2Plot = zeros(size(parameterPlain));
bolding = -1:1;

while 1
    [val, ind] = max(temp(:));
    if val == 0
        break
    end
    [indI, indJ] = ind2sub(size(temp), ind);
    area = -10:10;
    temp(area + indI, area + indJ) = 0;
    parameterPlain(area + indI, area + indJ) = 0;
    parameterPlain(ind) = 1;
    parameterPlain2Plot(bolding + indI, bolding + indJ) = 128;
    fprintf("Found line: r = %g, theta = %g\n",indI - d/2,indJ);
end
figure(), image(parameterPlain2Plot), colormap(gray(128)), title('Corner Dots');

line_angles = sum(parameterPlain);
oneLines = find(line_angles == 1) -1;
oneLines(oneLines<1) = [];
line_angles(oneLines) = line_angles(oneLines) + 1 ;

single_line_angles = line_angles;
single_line_angles(single_line_angles>1) = 1;
vertical_lines = single_line_angles(1:90) + single_line_angles(91:180);
vertical_lines(vertical_lines < 2) = 0;
if find(vertical_lines > 1)
    fprintf("There are Vertical lines!!\n");
end
parllel_lines_angles = find(line_angles>1);
if find(parllel_lines_angles > 1)
    for angle=parllel_lines_angles
        fprintf("There are %g parrellel lines with angle: %g\n", line_angles(angle), angle);
    end
end

end

