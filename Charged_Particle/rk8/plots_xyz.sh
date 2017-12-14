#!/bin/bash

paste outputxyh1.dat outputzh1.dat > xyzh1_data.dat
paste outputxyh2.dat outputzh2.dat > xyzh2_data.dat
paste outputxyh3.dat outputzh3.dat > xyzh3_data.dat
paste outputxyh4.dat outputzh4.dat > xyzh4_data.dat

#Plot results
# Make two plots  one with polym\nomial order 6 approximation the other one with exponential order 6 approximation 
gnuplot -persist <<-EOFMarker
set title "RK8 - Charged Particle"
set xlabel "x"
set ylabel "y"
set zlabel "z"
splot "xyzh1_data.dat" u col=2:3:7 with lines title "h=100","xyzh2_data.dat" u col=2:3:7 with lines title "h=200","xyzh3_data.dat" u col=2:3:7 with lines title "h=25","xyzh4_data.dat" u col=2:3:7 with lines title "h=50"
EOFMarker



