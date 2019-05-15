function phi=xyz_to_phi(xy_dis,z,l)
	phi(1) = atan(xy_dis/abs(z))/pi*180;
    phi2 = sqrt(xy_dis^2 + z^2)/(2*l);
	if phi2>1
        phi(2)=90;
    else
        phi(2)=asin(phi2)/pi*180;
	phi(3) = 90;
end