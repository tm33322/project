#!/bin/bash

#Plot results
# Make two plots  one with polym\nomial order 6 approximation the other one with exponential order 6 approximation 
gnuplot -persist <<-EOFMarker
set title "Convergence at t=0.4"
set xlabel "h"
set ylabel "relative error"
plot 'cvg.dat' using col=1:4 w linespoints title "Backward Euler", 'cvg.dat' using col=1:6 w linespoints title "GSL Backward Euler"

EOFMarker