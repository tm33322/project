#include <iomanip>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
 
typedef double F(double,double);	//Definition of the F type as an array of 2 double

double mode, y0, a, b, h, x[5], r;	//If mode=1, we are in normal mode
					//if mode=2, we are in debug mode
int i;

void inputdata()	//Treatment of input data
{

	i=0;
	ifstream infile("input.dat");

	while (infile >> r)
	{
		x[i]=r;
		i++;
	}

	mode=x[0];
	y0=x[1];
	a=x[2];
	b=x[3];
	h=x[4];

}
 
/*
Approximates y(t) in y'(t)=f(t,y) with y(a)=y0 and
t=a..b and the step size h.
*/
void euler(F f, double y0, double a, double b, double h)
{
	ofstream outputfile;
	outputfile.open("output.dat");

    double y = y0;
    for (double t = a; t < b; t += h)
    {
        std::cout << std::fixed << std::setprecision(3) << t << " " << y << "\n";
	outputfile << t << " " << y << endl;
        y += h * f(t, y);
    }
    std::cout << "done\n";
	outputfile.close();
}
 
// Example: dy/dt=y
double func(double t, double y)		//The function receives 2 arguments of type double
					//This is a general form, we only use 1 argument here
{
    return y;
}
 
int main()
{
  	clock_t c1=clock();
	
	inputdata();
	euler(func, y0, a, b, h);

	c1 = clock() - c1; 
  	cout << "execution time is " << c1/(double)CLOCKS_PER_SEC << " seconds" << endl;

}
