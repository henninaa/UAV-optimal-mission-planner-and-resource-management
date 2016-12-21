function [ vector ] = extractVector( input )
%EXTRACTVECTOR Summary of this function goes here
%   Detailed explanation goes here
    s=size(input);
    vector(s(1),6) = 0;
    vector(:,:) = input(:,1,:);

end

