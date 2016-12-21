classdef ShipsList
    %SHIPSLIST Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        ships
        results
    end
    
    methods
        
        function obj = ShipsList(p0)
            
            ships(1) = Ship(p0);
            obj.ships = ships;
            
            obj.results(1, 1, 6) = 0;
            
        end
        
        function [obj, X] = tick(obj)
           global tickCount;
            
            s = size(obj.ships);
            X(s(2),6) = 0;
            
            for i=1:s(2)
                [obj.ships(i),X(i,:)] = obj.ships(i).tick();
            end
            
            obj.results(:, tickCount, :) = X;
            
        end
        
        function obj = addShip(obj, p0)
           
            obj.ships(end+1) = Ship(p0);
            
            obj.results(end+1, 1, 6) = 0;
        end
        
        function obj = setGoal(obj, ship_n, goal)
           
            obj.ships(ship_n) = obj.ships(ship_n).setGoal(goal);
        end
        
        function r = getResults(obj)
           
            r = obj.results;
            
        end
    end

end

