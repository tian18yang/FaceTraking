ft = finaladjustment([phi_to_theta([20,45,0]),0]);
fwrite(arduino,['H','4',ft(4),30]);
fwrite(arduino,['H','3',ft(3),30]);
fwrite(arduino,['H','2',ft(2),30]);
fwrite(arduino,['H','1',ft(1),30]);