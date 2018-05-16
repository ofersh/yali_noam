clc; clear; close all;

addpath(genpath('./materials'))

OB1 = imread('object1.bmp');
R2 = imread('object2.bmp');
C3 = imread('object3.bmp');

OB1Canoby = edge(OB1, 'canny');
R2D2 = edge(R2, 'canny');
C3PO = edge(C3, 'canny');

tmp = zeros(size(OB1));

OB1Edges = findEdgePoints(OB1Canoby);
R2Edges = findEdgePoints(R2D2);
C3Edges = findEdgePoints(C3PO);

radius = @(im) norm(size(im));

X = OB1;
XEdges = OB1Edges;
parameterPlain = zeros(radius(X), 180);


