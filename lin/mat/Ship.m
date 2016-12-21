classdef Ship
    %SHIP Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        
        position = [0; 0; 0];
        attitude = [0; 0; 0];
        angle = 0;
        velocity = [0; 0; 0];
        absolute_velocity = 0;
        march_speed = 30;
        startPosition = [0; 0; 0];
        goalPosition= [0; 0; 0];
        travel_distance = 0;
        
        inTransition = false;
    end
    
    methods
        
        function obj = Ship(position)
            obj.position = position;
        end
        
        function [obj] = setGoal(obj, goal)
          
            obj.goalPosition = goal;
            obj.travel_distance = sqrt((obj.goalPosition(1) - obj.startPosition(1))^2 + (obj.goalPosition(2) - obj.startPosition(2)));
            obj.inTransition = true;
            
        end
        
        function [obj, X] = tick(obj)
            
            global tickLength;
            
            X(6) = 0;
            X(1:3) = obj.position;
            X(4:6) = obj.attitude;
            
            if obj.inTransition == false
                return
            end
            
            remaining_distance = sqrt((obj.goalPosition(1) - obj.position(1))^2 + (obj.goalPosition(2) - obj.position(2)));
            
            if(remaining_distance < 3)
                obj.goalPosition = obj.position;
                obj.velocity = [0; 0; 0];
                obj.inTransition = false;
                return
            end
            
            
            distance_traveled = obj.travel_distance - remaining_distance;
            
            factor = min( (distance_traveled/obj.travel_distance) *2 + 0.1, 2)/2;
            
            if factor == 1
               obj.angle = atan2(obj.goalPosition(2) - obj.position(2), obj.goalPosition(1) - obj.position(1));
                
            else
                obj.angle = obj.angle + (atan2(obj.goalPosition(2) - obj.position(2), obj.goalPosition(1) - obj.position(1)) - obj.angle)/4;
                
            end
            
            obj.attitude = [cos(obj.angle); sin(obj.angle); 0];
            
            obj.absolute_velocity = obj.absolute_velocity + (obj.march_speed - obj.absolute_velocity) * factor;
            obj.absolute_velocity = min(obj.absolute_velocity, remaining_distance);
            
            obj.velocity = [obj.absolute_velocity * cos(obj.angle); obj.absolute_velocity * sin(obj.angle); 0];
            
            obj.position = obj.position + (obj.velocity / tickLength);
            
            X(1:3) = obj.position;
            X(4:6) = obj.attitude;
            
        end
    end
    
end

