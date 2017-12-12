#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

double mode, t, t1, h, y[2];
ofstream outdebugfile;

void ReadInput()
{
        if (mode=1)
        {   
        outdebugfile.open ("outdebugz");
        outdebugfile << "entering ReadInput" << endl;
        }   


        double r, R[8];
        int i=0;

        ifstream infile("inputz");

        while (infile >> r)
        {
                R[i]=r;
                i++;
                //cout << r << endl;
        }

        mode=R[0];
        t=R[1];
        t1=R[2];
        h=R[3];
	y[0]=R[4];
	y[1]=R[5];


outdebugfile << "mode = " << mode << " t = " << t << " t1 = " << t1 << " h = " << h << " y0 = " << y[0] << " y1 = " << y[1] << endl;
}


int
func (double t, const double y[], double f[],
      void *params)
{
  if (mode=1)
  {
        outdebugfile << "entering func" << endl;
  }

  (void)(t); /* avoid unused parameter warning */
  double tau = *(double *)params;
  f[0] = y[1];
  f[1] = -y[1]/tau;

  if (mode=1)
  {
        outdebugfile << "func success is " << GSL_SUCCESS << endl;
  }

  return GSL_SUCCESS;
}


int * jac;


void Compute()
{
   if (mode=1)
  {
        outdebugfile << "entering Compute" << endl;
  }

  double tau = 5;
  gsl_odeiv2_system sys = {func, NULL, 2, &tau};

  gsl_odeiv2_driver * d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk8pd,
                                  1e-6, 1e-6, 0.0);
  int i;

	ofstream outputfile;
	outputfile.open("outputz");


  for (i = 1; i <= h; i++)
    {
      double ti = i * t1 / h;
      int status = gsl_odeiv2_driver_apply (d, &t, ti, y);

      if (status != GSL_SUCCESS)
        {
	  outputfile << "error, return value = " << status << endl;
          if (mode=1)
          {
                outdebugfile << "error, return value = " << status << endl;
          }
          break;
        }

      outputfile << t << " " << y[0] << " " << y[1] << endl;
    }

  outputfile.close();

  gsl_odeiv2_driver_free (d);

  if (mode=1)
  {
        outdebugfile << "closing" <<endl;
        outdebugfile.close();
  }
 
}


int
main (void)
{
        clock_t c1=clock();

  ReadInput();
  Compute();
  
        c1 = clock() - c1;
        cout << "execution time is " << c1/(double)CLOCKS_PER_SEC << " seconds" << endl;

  return 0;
}
