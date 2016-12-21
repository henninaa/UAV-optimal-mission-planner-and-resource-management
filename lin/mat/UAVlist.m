classdef UAVlist
    %UAVLIST Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
    
        UAVs
        results
        
    end
    
    methods
        
        function obj = UAVlist(n, mass, inertia, length, width, height)
            
            for i = 1:n
                tmp(i) = UAV(mass, inertia, length, width, height);
            end
            obj.UAVs = tmp;
            
        end
        
        function [obj, X] =  tick(obj)
            global tickCount;
            
            s = size(obj.UAVs);
            X(s(2),6) = 0;
            
            for i=1:s(2)
                [obj.UAVs(i), X(i,:)] = obj.UAVs(i).tick();
            end
            
            obj.results(:,tickCount,:) = X(:,:);
            
        end
        
        function obj = addUAV(obj, mass, inertia, length, width, height)
            
            obj.UAVs(end+1) = UAV(mass, inertia, length, width, height);
            
        end
        
        function obj = setInitialState(obj, uavNumber, X, X_dot)
           
            obj.UAVs(uavNumber) = obj.UAVs(uavNumber).setInitialState( X, X_dot);
            
        end
        
        function r = getResults(obj)
           
            r = obj.results;
            
        end
        
        function [A_lat, A_long] = getAmatrices(obj)
            s = size(obj.UAVs);
            A_lat(s(2), 5, 5) = 0;
            A_long(s(2), 5, 5) = 0;
            for i = 1:s(2)
                [A_lat(i,:,:), A_long(i, :, :)] = obj.UAVs(i).getA();
            end
            
        end
        
        function [B_lat, B_long] = getBmatrices(obj)
            s = size(obj.UAVs);
            B_lat(s(2), 5, 2) = 0;
            B_long(s(2), 5, 2) = 0;
            for i = 1:s(2)
                [B_lat(i,:,:), B_long(i, :, :)] = obj.UAVs(i).getB();
            end
            
        end
        
    end
    
end

