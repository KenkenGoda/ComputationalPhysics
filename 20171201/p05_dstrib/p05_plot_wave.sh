set term x11 font 'helvetica,12'
set xlabel 'time'
set ylabel 'X'
set ztics
set zlabel '|Phi|^2'
set view 40,50
set surface
unset contour
splot 't_x_phi_ftcs.dat'u 1:2:3 w l

pause -1

unset ztics
unset zlabel
unset surface
set contour
set cntrparam levels incremental  0,0.005,0.1
set key at -200,-130
set view 0,90
splot 't_x_phi_ftcs.dat'u 1:2:3 w l


pause -1

#unset ztics
#unset zlabel

set xlabel 'X'
set ylabel '|Phi|^2'
set key at 75,0.055
plot 'x_phi_start_ftcs.dat'u 1:2 w l lw 2,'x_phi_end_ftcs.dat'u 1:2 w l lt 3 lw 2
