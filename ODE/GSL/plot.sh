#!/bin/bash

#Plot results
# Make two plots  one with polym\nomial order 6 approximation the other one with exponential order 6 approximation 
gnuplot -persist <<-EOFMarker
set title "GSL for y'=y"
f(x)=exp(x)
set xrange [0:1]
set xlabel "t"
set ylabel "y"
plot f(x) title "theory" w lines,'outputh1.dat' using 1:2 title "h1=0.1" w points,'outputh2.dat' using 1:2 title "h2=0.05" w points, 'outputh3.dat' using 1:2 title "h3=0.025" w points, 'outputh4.dat' using 1:2 title "h4=0.2" w points    
set output "plotODEGSL.png"
EOFMarker
