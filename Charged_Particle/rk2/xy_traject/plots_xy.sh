#!/bin/bash

#Plot results
# Make two plots  one with polym\nomial order 6 approximation the other one with exponential order 6 approximation 
gnuplot -persist <<-EOFMarker
set title "RK2 - Charged Particle"
set xlabel "t"
set ylabel "x"
set zlabel "y"
set key left toset key left topp
splot "outputxyh1.dat" u 1:2:3 with lines title "h=100", "outputxyh2.dat" u 1:2:3 with lines title "h=200", "outputxyh3.dat" u 1:2:3 with lines title "h=25","outputxyh4.dat" u 1:2:3 with lines title "h=50"
EOFMarker



