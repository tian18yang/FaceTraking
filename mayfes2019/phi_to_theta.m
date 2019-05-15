function theta = phi_to_theta(phi)
	theta(1) = phi(1)+phi(2);
	theta(2) = phi(2)*2;
	theta(3) = phi(1)-phi(2)+phi(3)+90;
end