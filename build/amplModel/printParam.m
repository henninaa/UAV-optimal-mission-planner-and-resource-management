function [ output_args ] = printParam( filename, paramName, D, xyz )
%PRINTPARAM Summary of this function goes here
%   Detailed explanation goes here

fid = fopen(filename,'wt');
string1 = '';

string1 = [string1 'param '];
string1 = [string1 paramName];
string1 = [string1 ': '];

for i = 1:D/2
   
    string1 = [string1 num2str(i)];
    string1 = [string1 ' '];
    
end

string1 = [string1 ':='];
fprintf(fid, '%s\n', string1);

for i = 1:D
    string1 = [num2str(i) ' '];
    for j=1:D/2
        theta = 2*pi*i / D;
        phi = 2*pi*j / D;
        if xyz == 'x'
            string1 = [string1 num2str(cos(theta) * sin(phi),'%f')];
        elseif xyz == 'y'
            string1 = [string1 num2str(sin(theta) * sin(phi),'%f')];  
        elseif xyz == 'z'
            string1 = [string1 num2str(cos(phi),'%f')];
        end
        string1 = [string1 ' '];
        
    end
    
    if i == D
        string1 = [string1 ';'];
    end
    fprintf(fid, '%s\n', string1);
end

fclose(fid);
