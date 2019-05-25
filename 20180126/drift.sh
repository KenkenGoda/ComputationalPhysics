set xlabel 'X'
set ylabel 'Y'
set ztics
set zlabel 'Z'
splot 'drift.dat'u 2:3:4 t 'drift' w l
