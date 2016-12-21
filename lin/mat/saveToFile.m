function [ ] = saveToFile( fileName, lat, long )
%SAVETOFILE Summary of this function goes here
%   Detailed explanation goes here

s = size(lat);

lat1(s(2), s(3)) = 0;
lat1(:,:) = lat(1,:,:);
long1(s(2), s(3)) = 0;
long1(:,:) = long(1,:,:);

saveSucess = false;
    while saveSucess == false
         saveSucess = true;
        try
            save(fileName, 'lat1', 'long1', '-ascii', '-append');
        catch
            saveSucess = false;
        end
    end

end

