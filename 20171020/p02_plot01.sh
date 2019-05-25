# set font size 20
set term x11 font 'helvetica,20'
set size square

# set label of x-axis
set xlabel 'X[Au]'

# set label of y-axis
set ylabel 'Y[Au]'

# plot data with 2nd and 3rd columns
plot 'orbit_euler.dat'u 2:3 title 'euler' with l
