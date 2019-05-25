# set font size 20
set term x11 font 'helvetica,20'


# set label of x-axis
set xlabel 'number of trial'

# set label of y-axis
set ylabel 'Integral number'

# plot data 'err.dat' with 2nd and 3rd columns
plot 'hit-miss.dat' u 1:2 w l

pause -1

# set label of x-axis
set xlabel 'number of trial'

# set label of y-axis
set ylabel 'error'

plot 'hit-miss.dat' u 1:3  w l
