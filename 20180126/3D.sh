set xlabel 'X'
set ylabel 'Y'
set ztics
set zlabel 'Z'
splot '3D_1.dat'u 2:3:4 t '3D' w l

pause -1

splot '3D_2.dat'u 2:3:4 t '3D' w l
