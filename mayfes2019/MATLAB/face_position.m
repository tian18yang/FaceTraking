function fp = face_position(phi,ffc,l,theta4)
	fp(1) = 2*l*sin(phi(2)*pi/180)*sin(phi(1)*pi/180)*cos(theta4*pi/180)+ffc(1);
	fp(2) = 2*l*sin(phi(2)*pi/180)*sin(phi(1)*pi/180)*sin(theta4*pi/180)+ffc(2);
	fp(3) = 2*l*sin(phi(2)*pi/180)*cos(phi(1)*pi/180)+ffc(3);
end