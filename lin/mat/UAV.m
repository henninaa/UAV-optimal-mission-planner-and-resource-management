classdef UAV
    
    properties
        mass;
        inertia;
        length;
        width;
        height;
        pos = [0; 0; 0];
        attitude = [0; 0; 0]; % 
        attitude_dot = [0; 0; 0]; % 
        v = [1; 1; 0];
        v_dot = [0; 0; 0];
        V_a = 0;
        sideslip = 0;
        
        X_lat;
        X_long;
        X_dot_lat;
        X_dot_long;
        
        pos_star = [0; 0; 0];
        v_star = [0; 0; 0];
        attitude_star = [0; 0; 0];
        attitude_dot_star = [0;0;0];
        
        A_latteral;
        B_latteral;
        A_longditudinal;
        B_longditudinal;
        
        tau; % av, el, thrust
        
        thrust = 0;
        actuators = [0; 0; 0]; %aviator_l, aviator_r, rudder
        mpc;
        AIcontrol;
        regulator;
        
    end
    
    methods
       
        function obj = UAV(mass, inertia, length, width, height)
            obj.mass = mass;
            obj.inertia = inertia;
            obj.length = length;
            obj.width = width;
            obj.height = height;
            obj.mpc = MPC;
            obj.AIcontrol = TRex;
            obj.regulator = PID;
            
            obj.tau = [0;0;0];
            
            obj = obj.setA_latteral();
            obj = obj.setA_longditudinal();
            obj = obj.setB_latteral();
            obj = obj.setB_longditudinal();
        end
        
        function [obj, X] = tick(obj)
            
            %//obj = obj.dynamics();
            %//obj = obj.kinematics();
            
           %// X(6) = [obj.pos obj.attitude];
           
           obj = obj.setA_latteral();
           obj = obj.setB_latteral();
           obj = obj.setA_longditudinal();
           obj = obj.setB_longditudinal();
           
           obj = obj.updateState();
           
           X(6) = 0;
           
           X(1:3) = obj.pos;
           X(4:6) = obj.attitude;
            
        end
        
        function obj = setInitialState(obj, X, X_dot)
           
            
            obj.v = X_dot(1:3);
            obj.pos = X(1:3);
            obj.attitude = X(4:6);
            obj.attitude_dot = X_dot(4:6);
            
            obj.X_lat = [X_dot(2); X_dot(4); X_dot(6); X(4); X(6)];
            
            obj.X_long = [X_dot(1); X_dot(3); X_dot(2); X(5); X(3)];
            
        end
        
        function obj =  kinematics(obj)
            
        end
        
        function obj = dynamics(obj)
            
        end
        
        function obj = setA_latteral(obj)
            
            obj.A_latteral(5,5) = 0;
            
            rho = 1;
            S = 1;
            b = 1;
            v_s = obj.v_star(2);
            m = obj.mass;
            V_a_s = length(obj.v_star);
            C_Y_p = 1;
            p_s = obj.attitude_dot_star(1);
            C_Y_r = 1;
            r_star = obj.attitude_dot_star(3);
            
            C_Y_0 = 1;
            C_Y_beta = 1;
            beta_star = obj.sideslip;
            
            g = 9.1;
            
            
            obj.A_latteral = [0         0           0           g           0;
                        0           0           0           0           0;
                        0           0           0           0           0;
                        0           1           0           0           0;
                        0           0           0           0           0];
            
        end
        
       
        function obj = setB_latteral(obj)
            
           obj.B_latteral = [0          0;
                            0           0;
                            0           0;
                            0           0;
                            0           0];
            
        end
        
        
        
        function obj = setLinearizationPointLatteral(obj, v, p, r, phi, psi)
            
        end
        
        function obj = setA_longditudinal(obj)
            
            
            g = 9.1;
            
            
            
           obj.A_longditudinal = [0         0           0           g           0;
                        0           0           0           0           0;
                        0           0           0           0           0;
                        0           0           1           0           0;
                        0           0           0           0           0];
            
        end
        
        function obj = setB_longditudinal(obj)
            
           obj.B_longditudinal = [0          0;
                            0           0;
                            0           0;
                            0           0;
                            0           0];
            
        end
        
        function [a_lat, a_long] =  getA(obj)
        
            a_lat = obj.A_latteral;
            a_long = obj.A_longditudinal;
            
        end
    
        function [B_lat, B_long] = getB(obj)
            
            B_lat = obj.B_latteral;
            B_long = obj.B_longditudinal;
        end
        
        function obj = updateState(obj)
            
            global tickLength;
            
           oldX_dot_lat = obj.X_dot_lat;
           oldX_dot_long = obj.X_dot_long;
           
           oldX_lat = obj.X_lat;
           oldX_long = obj.X_long;
           A1 = obj.A_latteral * obj.X_lat;
           A2 = obj.B_latteral * [obj.tau(1); 0];
           obj.X_dot_lat = obj.A_latteral * obj.X_lat + obj.B_latteral * [obj.tau(1); 0];
           
           obj.X_dot_long = obj.A_longditudinal * obj.X_long + obj.B_longditudinal * obj.tau(2:3);
            
           obj.X_lat = obj.X_lat + (obj.X_dot_lat * tickLength);
           obj.X_long = obj.X_long + (obj.X_dot_long * tickLength);
           
           obj.v(1) = obj.X_long(1);
           obj.v(2) = obj.X_lat(1);
           obj.v(3) = obj.X_long(2);
           
           obj.attitude(1) = obj.X_lat(4);
           obj.attitude(2) = obj.X_long(4);
           obj.attitude(3) = obj.X_lat(5);
           
           obj.pos(1) = obj.pos(1) + ( 0.5 * (oldX_long(1) + obj.v(1)) * tickLength);
           obj.pos(2) = obj.pos(2) + ( 0.5 * (oldX_lat(1) + obj.v(2)) * tickLength);
           obj.pos(3) = obj.pos(3) + ( 0.5 * (oldX_long(2) + obj.v(3)) * tickLength);
           
        end
        
    end
        
end
