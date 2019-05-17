function ffc = face_from_camera2(face,frameSize,phi3,theta4)
    
    
	parameter_x = 0.0020;
	parameter_y = 0.0020;
	parameter_z = 7500;
    H = frameSize(1);
    W = frameSize(2);
    
    

    x_mid = face(1,1) + face(2,1) + face(3,1) + face(4,1);
    y_mid = face(1,2) + face(2,2) + face(3,2) + face(4,2);
	dx = x_mid/4 - W/2;
	dy = y_mid/4 - H/2;
    
    z = parameter_z/sqrt((face(3,1)-face(1,1))^2+(face(3,2)-face(1,2))^2);
	x = dx * parameter_x * z;
	y = dy * parameter_y * z;
    
    
    ty = phi3*pi/180;
    tz = -theta4*pi/180;
    Ry = [cos(ty) 0 sin(ty); 0 1 0; -sin(ty) 0 cos(ty)];
    Rz = [cos(tz) -sin(tz) 0; sin(tz) cos(tz) 0; 0 0 1];
    
    ffc =Ry*Rz*[z;-x;-y];
    ffc(4)=dy * parameter_y;
end