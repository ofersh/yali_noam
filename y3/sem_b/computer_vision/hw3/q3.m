%% q3
clc; clear; close all;
addpath(genpath('./materials'))
OB1 = imread('object1.bmp');
R2 = imread('object2.bmp');
C3 = imread('object3.bmp');

%% Image: object1.bmp
q3b2g(OB1);
%% Image: object2.bmp
q3b2g(R2);
%% Image: object3.bmp
q3b2g(C3);