#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

//declaration of the initial and final X values, initial Y value and step
double X0, Xf, Y0, H;

//Reads the input values from a file
void ReadInput()
{
	double r, R[4];
	int i=0;

	ifstream infile("input");

	while (infile >> r)
	{
		//cout << i << endl;
		R[i]=r;
		//cout << "R=" << R[i] << ", r=" << r << endl;
		i++;
	}

	X0=R[0];
	Xf=R[1];
	Y0=R[2];
	H=R[3];

//cout << "X0 = " << X0 << ", Xf = " << Xf << ", Y0 = " << Y0 << ", H = " << H << endl;

}

int odefunc (double x, const double y[], double f[], void *params)
{
    f[0] = y[0];
    return GSL_SUCCESS;
}


int * jac;

void OdeSolve(double x0, double xf, double y0, double h)
{
    int dim =1;
    gsl_odeiv2_system sys = {odefunc, NULL, dim, NULL};

    gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkf45, 1e-6, 1e-6, 0.0);
    int i;
    double x = x0;
    double y[1] = { y0 };  /* initial value */

    ofstream outputfile;
    outputfile.open("output");

    for (i = 1; i <= h; i++)
    {
        double xi = x0 + i * (xf-x0) / h;
        int status = gsl_odeiv2_driver_apply (d, &x, xi, y);

        if (status != GSL_SUCCESS)
        {
	    outputfile << "error, return value = " << status << endl;
            //printf ("error, return value=%d\n", status);
            break;
        }

	outputfile << x << " " << y[0] << endl;
        //printf ("%.8e %.8e\n", x, y[0]);
    }

    outputfile.close();

    gsl_odeiv2_driver_free (d);
 
}


int main ()
{
  	clock_t c1=clock();
	
	ReadInput();
	OdeSolve(X0, Xf, Y0, H);

	c1 = clock() - c1; 
	cout << "execution time is " << c1/(double)CLOCKS_PER_SEC << " seconds" << endl;

   return 0;
}
