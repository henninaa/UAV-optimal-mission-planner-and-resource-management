classdef Plotter
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        UAVattitudeArray
        UAVpositionArray
        shipsPositionsArray
        shipsAttitudeArray
        basePosition = [0; 0; 0];
        
    end
    
    methods
        
        function obj = Plotter()
            
            
        end
        
        function plot3D(obj, fig)
            
            shipS = size(obj.shipsPositionsArray);
            UAVS = size(obj.UAVpositionArray);
            
            figure(fig);
            hold off;
            grid on;
            plot3(obj.basePosition(1),obj.basePosition(2),obj.basePosition(3), 'x');
            hold on;
            
            d(shipS(2),3) = 0;
            
            for i=1:shipS(1)
                d(:,:) = obj.shipsPositionsArray(i,:,:);
                plot3(d(:,1)',d(:,2)',d(:,3)', '-');
            end
            for i=1:UAVS(1)
                d(:,:) = obj.UAVpositionArray(i,:,:);
                plot3(d(:,1)',d(:,2)',d(:,3)', 'x');
            end
            
            axis([0 500 0 500 0 10]);
            grid on;
        end
        
        function obj = addUAVdata2(obj, X)
            s = size(X);
            
            for i=1:s(1)
            obj.UAVpositionArray(i, end, 1:3) = X(i,1:3);
            obj.UAVattitudeArray(i, 1:3) = X(i,4:6);
            end
        end
        
        function obj = addUAVData(obj, X)
           
            s=size(X);
            if isempty(obj.UAVpositionArray)
                for i=1:s(1)
                obj.UAVpositionArray(i, 1, :) = X(i, 1:3);
                obj.UAVattitudeArray(i, 1, :) = X(i, 4:6);
                end
            
            else
                s2=size(obj.UAVpositionArray);
                for i=1:s(1)
                obj.UAVpositionArray(i, s2(2)+1, 1:3) = X(i, 1:3);
                obj.UAVattitudeArray(i, s2(2)+1, 1:3) = X(i, 4:6);
                end
                
            end
            
        end
        
        function obj = addShipData(obj, X)
           
            s=size(X);
            if isempty(obj.shipsPositionsArray)
                for i=1:s(1)
                obj.shipsPositionsArray(i, 1, :) = X(i, 1:3);
                obj.shipsAttitudeArray(i, 1, :) = X(i, 4:6);
                end
            
            else
                s2=size(obj.shipsPositionsArray);
                for i=1:s(1)
                obj.shipsPositionsArray(i, s2(2)+1, 1:3) = X(i, 1:3);
                obj.shipsAttitudeArray(i, s2(2)+1, 1:3) = X(i, 4:6);
                end
                
            end
            
        end
        
        function obj = setBase(obj, p)
           
            obj.basePosition = p;
            
        end
        
        function obj = resetPlot(obj)
            
        end
        
    end
    
end

