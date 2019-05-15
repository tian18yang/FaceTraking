function bcp = best_camera_position(fp,d,l,ffc3)
	x=fp(1);
    y=fp(2);
    z=fp(3);
	xydis = sqrt(x*x + y*y);
	if xydis>d && ((xydis-d)^2 + z^2 > 4*l^2)
        disp('far');
		bcp(1) = 90+atan(sqrt(x*x+y*y)/z)/pi*180;
		bcp(2) = 180;
		bcp(3) = 90;
		%bcp(4) = atan(y/x)/pi*180;
    elseif xydis<d
        disp('near');
        X = x-x*d/xydis;
        Y = y-y*d/xydis;
        XY_dis = -sqrt(X^2+Y^2);
        phi = xyz_to_phi(XY_dis,z,l);
        phi(3)=ffc3;
        bcp123 = phi_to_theta(phi);
        bcp(1) = bcp123(1);
        bcp(2) = bcp123(2);
		bcp(3) = bcp123(3);
		%bcp(4) = atan(y/x)/pi*180;
    else
        disp('mid');
        X = x-x*d/xydis;
        Y = y-y*d/xydis;
        XY_dis = sqrt(X^2+Y^2);
        phi = xyz_to_phi(XY_dis,z,l);
        phi(3)=ffc3;
        bcp123 = phi_to_theta(phi);
        bcp(1) = bcp123(1);
        bcp(2) = bcp123(2);
		bcp(3) = bcp123(3);
		%bcp(4) = atan(y/x)/pi*180;
    end
end