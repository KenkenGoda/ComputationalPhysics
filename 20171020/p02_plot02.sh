# set font size 20
set term x11 font 'helvetica,20'
set size square

# set label of x-axis
set xlabel 'Time [yr]'

# set label of y-axis set ylabel 'Energy'

# plot data with 2nd and 3rd columns
plot 'orbit_euler.dat'u 1:6 title 'kinetic' with lines,'orbit_euler.dat'u 1:7 title 'potential' with lines,'orbit_euler.dat'u 1:8 title 'total' with lines
