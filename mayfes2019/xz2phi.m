function phi=xz2phi(x,z,l,ffc2)
	phi(4)=1;
    if x^2+z^2>l^2 || z<0
        phi(4)=0;
    else
        phi(1) = atan(x/z)*180/pi;
        phi(2) = asin(sqrt(x^2+z^2)/l)*180/pi;
        phi(3) = atan(ffc2(2)-z)/(ffc2(1)-x)*180/pi;
        theta = phi_to_theta;
        
    end
end