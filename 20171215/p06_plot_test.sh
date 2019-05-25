# set font size 20
set term x11 font 'helvetica,20'


# set label of x-axis
set xlabel 'number of random number'

# set label of y-axis
set ylabel 'random number'

# plot data 'err.dat' with 2nd and 3rd columns
plot 'rand.dat' u 1:2 w d

pause -1

# set label of x-axis
set xlabel 'random number'

# set label of y-axis
set ylabel 'count'

plot 'count.dat' u 1:2  w linesp
