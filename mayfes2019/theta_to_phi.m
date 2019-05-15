function phi=theta_to_phi(theta)
	phi(1) = theta(1)-theta(2)/2;
	phi(2) = theta(2)/2;
	phi(3) = theta(3)-theta(1)+theta(2)-90;
end