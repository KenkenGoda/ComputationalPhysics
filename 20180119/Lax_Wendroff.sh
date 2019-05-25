set term x11 enhanced font "arial,20" 
set xlabel 'X'
set ylabel 'Amplitude'
unset key

if(t<10) label="0000".t; else if (t<100) label="000".t;

set title "snapshot ".label
plot[][-2:+2] "lax_wendroff_step_larger_".label.".dat" u 2:3 w l
#plot[][] "lax_wendroff_".label.".dat" u 2:3 w l
pause 0.5

t=t+1

reread

