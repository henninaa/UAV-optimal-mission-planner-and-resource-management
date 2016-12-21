function [ UAV_list ] = createUAVs(n, mass, inertia, length, width, height )
%CREATEUAVS Summary of this function goes here
%   Detailed explanation goes here
    

UAV_list(n) = UAV(mass, inertia, length, width, height);

end

