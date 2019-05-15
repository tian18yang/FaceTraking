function final_theta = finaladjustment(theta)
    final_theta(1)=theta(1)-15;
    if final_theta(1)>160
        final_theta(1)=160;
    end
    if final_theta(1)<0
        final_theta(1)=0;
    end
    final_theta(2)=theta(2)-40;
    if final_theta(2)<0
        final_theta(2)=0;
    end
    
    final_theta(3) = 90-theta(3);
    if final_theta(3)>180
        final_theta(3)=180;
    end
    if final_theta(3)<0
        final_theta(3)=0;
    end
    
    final_theta(4) = theta(4)+90;
    if final_theta(4)>180
        final_theta(4)=180;
    end
    if final_theta(4)<0
        final_theta(4)=0;
    end
end