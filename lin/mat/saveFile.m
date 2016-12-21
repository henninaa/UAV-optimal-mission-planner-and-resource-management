function [ ] = saveFile( fileName, n, lat, long )
%SAVEFILE Summary of this function goes here
%   Detailed explanation goes here


saveSucess = false;
    while saveSucess == false
         saveSucess = true;
        try
            save(strcat(fileName, '.txt'), 'n', '-ascii');
        catch
            saveSucess = false;
        end
    end
    
    for j = 1:n
       saveToFile(strcat(fileName, '.txt'), lat(j,:,:), long(j,:,:)); 
    end


    saveSucess = false;
    while saveSucess == false
         saveSucess = true;
        try
            save(strcat(fileName, '.mat'), 'n', 'lat', 'long');
        catch
            saveSucess = false;
        end
    end
    
end

