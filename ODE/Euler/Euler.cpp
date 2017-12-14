#include <iomanip>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

double mode, y0, a, b, dis, x[5], r;      //If mode=1, we are in normal mode
                                        //if mode=2, we are in debug mode
int i;

void inputdata()        //Treatment of input data
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
        dis=x[4];

}

/*
Approximates y(t) in y'(t)=y(t) with y(a)=y0 and
t=a..b and the step size h.
*/
void euler(double y0, double a, double b, double dis)
{
        ofstream outputfile;
        outputfile.open("output.dat");

    double y = y0;
    double h = 1/dis;
    for (double t = a+h; t < b+h; t += h)
    {
        outputfile << t << " " << y << endl;
        y = 1/(1-h) *y ;
    }
        outputfile.close();
}
int main()
{
        clock_t c1=clock();

        inputdata();
        euler(y0, a, b, dis);

        c1 = clock() - c1;
        cout << "execution time is " << c1/(double)CLOCKS_PER_SEC << " seconds" << endl;

        return 0;
}
