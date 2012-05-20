%% Trajectory simulation
clc;
clear all;
close all;

syms t

% Variables
R = 2.5;
i = 0;
theta = pi/9;   % Rotation about x axis
lambda = pi/6; % rotation about y axis
x_zero = 3;
y_zero = 3;
z_zero = 1;
l_rod = 6;

L = 8;
Cspring = 500
Fzero = 100
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

center = [x_zero y_zero  z_zero];
circle = [x_zero + R*cos(t) y_zero+R*sin(t)  z_zero];

R_lambda = [1 0 0;0 cos(lambda) sin(lambda);0 -sin(lambda) cos(lambda)];
R_theta = [cos(theta) 0 sin(theta);0 1 0; -sin(theta) 0 cos(theta)];

lambda_T = circle*R_lambda;
theta_lambda_T = lambda_T*R_theta;

final_center = (center*R_lambda)*R_theta;

    for t = 0:0.01:2*pi 
        
        i = i+1;
        
        point(1,i) = eval(theta_lambda_T(1));
        point(2,i) = eval(theta_lambda_T(2));
        point(3,i) = eval(theta_lambda_T(3));
    
    end


plot3(point(1,:),point(2, :),point(3,:),'DisplayName','x,y,z');figure(gcf);
hold on;
grid;
xlabel('X');
ylabel('Y');
zlabel('Z');

plot3(0, 0,0,'*','Color',[.6 .6 0]);
%%%%%%%%%%%%%%%%%%%
% To find min point and apicenter

min = 100;
max = 0;

min_index = 0;

for i = 1:1:629
    
    if(point(3,i) < min)
        min = point(3,i);
        point_min(1) = point(1,i);
        point_min(2) = point(2,i);
        point_min(3) = point(3,i);
        min_index = i;
    end
    
    if(point(3,i) > max)
        max = point(3,i);
        point_max(1) = point(1,i);
        point_max(2) = point(2,i);
        point_max(3) = point(3,i);
        max_index = i;
    end
      
end

apicenter(1) = point_min(1);
apicenter(2) = point_min(2);
apicenter(3) = l_rod + point_min(3)

plot3(apicenter(1,1), apicenter(1,2),apicenter(1,3),'*','Color',[0 0 0]);
plot3(point_min(1,1), point_min(1,2),point_min(1,3),'*','Color',[0 0 0]);

base_delx_cosine = (point_min(1)^2)*1
base_delz_cosine = point_min(3)*1

base_Ceff = (Cspring/(L^2))*base_delx_cosine + (Fzero/(L^2))*base_delz_cosine

u = -20;
k = 1;
while( u ~= 20)

    eta = (pi/180)*u;
    j = 1;   

    for  i = -100:1:200
        
        radial_dist = sqrt(point(1,min_index + i)^2 + point(3,min_index + i)^2);
        angle_point = acos(point(1,min_index + i)/radial_dist);
    
        displaced_angle = angle_point + eta;
        displaced_point(j,1,k) = u;
        displaced_point(j,2,k) = radial_dist*cos(displaced_angle);
        displaced_point(j,3,k) = point(2,min_index + i);
        displaced_point(j,4,k) = radial_dist*sin(displaced_angle);
        
        for m = -5:0.01:5
            apidisplaced_x = apicenter(1);
            apidisplaced_y = apicenter(2);
            apidisplaced_z = apicenter(3) + m;
            
            apiradius = sqrt((apidisplaced_x - displaced_point(j,2,k))^2 + (apidisplaced_y - displaced_point(j,3,k))^2 + (apidisplaced_z - displaced_point(j,4,k))^2  );    

            if( abs(apiradius - l_rod) < 0.01)
        
                displaced_point(j,5,k) = apiradius;
                displaced_point(j,6,k) = apidisplaced_x;
                displaced_point(j,7,k) = apidisplaced_y;
                displaced_point(j,8,k) = apidisplaced_z;
                break;
            end
            
        end
        
        cosine = (displaced_point(j,8,k) - displaced_point(j,4,k))/( sqrt( ( displaced_point(j,6,k) -  displaced_point(j,2,k))^2 + ( displaced_point(j,7,k) -  displaced_point(j,3,k))^2 + ( displaced_point(j,8,k) -  displaced_point(j,4,k))^2) );
        
        delx_cosine = ( displaced_point(j,2,k)^2)*(cosine^2);
        delz_cosine =  displaced_point(j,4,k)*cosine;
        
        point_Ceff = (Cspring/(L^2))*delx_cosine + (Fzero/(L^2))*delz_cosine;
        
        displaced_point(j,9,k) = point_Ceff;
        
        j = j + 1;
    end
     h = 1;
     for f = 2:-1:1.1

        min = 1000;
        
        for i = 1:1:301
    
            if( abs(displaced_point(i,9,k) - base_Ceff/f) < min)
            min = abs(displaced_point(i,9,k) - base_Ceff/f);
            ref_point(k,:,h) = displaced_point(i,:,k);
            end
    
        end
        h = h + 1;
     end
    

    for f = 1:2:9

        min = 1000;
        
        for i = 1:1:301
    
            if( abs(displaced_point(i,9,k) - base_Ceff*f) < min)
            min = abs(displaced_point(i,9,k) - base_Ceff*f);
            ref_point(k,:,h) = displaced_point(i,:,k);
            end
    
        end
        h = h+1;
    end
   
    
    u = u + 0.5;
    k = k + 1;
end

for i = 1:1:6
    scatter3(ref_point(:,2,i), ref_point(:,3,i),ref_point(:,4,i),5,[0 .2 0]);
    scatter3(ref_point(:,6,i), ref_point(:,7,i),ref_point(:,8,i),5,[.6 0 0]);
end

Ceff(:,:) =  ref_point(:,9,:);
   
delw(:,:) =  L.* tan(ref_point(:,1,:)*(pi/180));

Fe = Ceff(:,:).* delw(:,:);
   
figure
xlabel('Fe');
ylabel('Ceff');
grid;
hold on;

for i = 1:1:6
    plot(Fe(:,i), Ceff(:,i)); 
end

%%
j=1:1:8;
  
fid = fopen('point.h','w');

for k = 1:1:6
    fprintf(fid,'float array%d[80][15] = {',k);
    for i = 1:1:79
            fprintf(fid,'{ ');
            fprintf(fid,'%.2f, ',ref_point(i,j,k));
            fprintf(fid,'%.2f },',ref_point(i,9,k));
            fprintf(fid,'\n');
    end
    fprintf(fid,'{ ');
    fprintf(fid,'%.2f, ',ref_point(80,j,k));
    fprintf(fid,'%.2f }',ref_point(80,9,k));
    fprintf(fid,'};');
    fprintf(fid,'\n');
end
fclose(fid);

    
 



