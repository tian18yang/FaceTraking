function xz = phi_to_xz(phi,l)
    L = 2*l*sin(phi(2)*pi/180);
    xz(1) = L*sin(phi(1)*pi/180);
    xz(2) = L*cos(phi(1)*pi/180);
end