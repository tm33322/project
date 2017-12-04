#include <iomanip>
#include <iostream>
 
typedef double F(double,double);	//Definition of the F type as an array of 2 double
 
/*
Approximates y(t) in y'(t)=f(t,y) with y(a)=y0 and
t=a..b and the step size h.
*/
void euler(F f, double y0, double a, double b, double h)
{
    double y = y0;
    for (double t = a; t < b; t += h)
    {
        std::cout << std::fixed << std::setprecision(3) << t << " " << y << "\n";
        y += h * f(t, y);
    }
    std::cout << "done\n";
}
 
// Example: Newton's cooling law
double newtonCoolingLaw(double, double t)	//The function receives 2 arguments of type double
						//This is a general form, we only use 1 argument here
{
    return -0.07 * (t - 20);
}
 
int main()
{
    euler(newtonCoolingLaw, 100, 0, 100,  2);
    euler(newtonCoolingLaw, 100, 0, 100,  5);
    euler(newtonCoolingLaw, 100, 0, 100, 10);
}
