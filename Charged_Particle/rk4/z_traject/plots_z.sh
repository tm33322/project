#!/bin/bash

#Plot results
# Make two plots  one with polym\nomial order 6 approximation the other one with exponential order 6 approximation 
gnuplot -persist <<-EOFMarker
set title "rk4 z trajectory"
set logscale xy
set xlabel "t"
set ylabel "z"
set key left top
plot 'outputzh1.dat' using 1:2 title "h1=100" w points,'outputzh2.dat' using 1:2 title "h2=200" w points, 'outputzh3.dat' using 1:2 title "h3=25" w points, 'outputzh4.dat' using 1:2 title "h4=50" w points
EOFMarker
