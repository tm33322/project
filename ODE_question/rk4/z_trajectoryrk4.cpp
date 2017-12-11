#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

double mode, t, t1, h, y[2];

void ReadInput()
{
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


//cout << "mode = " << mode << " t = " << t << " t1 = " << t1 << " h = " << h << " y0 = " << y[0] << " y1 = " << y[1] << endl;
}


int
func (double t, const double y[], double f[],
      void *params)
{
  (void)(t); /* avoid unused parameter warning */
  double tau = *(double *)params;
  f[0] = y[1];
  f[1] = -y[1]/tau;
  return GSL_SUCCESS;
}

int
jac (double t, const double y[], double *dfdy,
     double dfdt[], void *params)
{
  (void)(t); /* avoid unused parameter warning */
  double tau = *(double *)params;
  gsl_matrix_view dfdy_mat
    = gsl_matrix_view_array (dfdy, 2, 2);
  gsl_matrix * m = &dfdy_mat.matrix;
  gsl_matrix_set (m, 0, 0, 0.0);
  gsl_matrix_set (m, 0, 1, 1.0);
  gsl_matrix_set (m, 1, 0, 0.0);
  gsl_matrix_set (m, 1, 1, -1/tau);
  dfdt[0] = 0.0;
  dfdt[1] = 0.0;
  return GSL_SUCCESS;
}


void Compute()
{
  double tau = 5;
  gsl_odeiv2_system sys = {func, jac, 2, &tau};

  gsl_odeiv2_driver * d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4,
                                  1e-6, 1e-6, 0.0);
  int i;
  //double t = 0.0, t1 = 10.0;
  //double y[2] = { 0.0, 2.0 };

	ofstream outputfile;
	outputfile.open("outputz");


  for (i = 1; i <= h; i++)
    {
      double ti = i * t1 / h;
      int status = gsl_odeiv2_driver_apply (d, &t, ti, y);

      if (status != GSL_SUCCESS)
        {
	  outputfile << "error, return value = " << status << endl;
          //printf ("error, return value=%d\n", status);
          break;
        }

      outputfile << t << " " << y[0] << " " << y[1] << endl;
      //printf ("%.5e %.5e %.5e\n", t, y[0], y[1]);
    }

  outputfile.close();

  gsl_odeiv2_driver_free (d);
 
}


int
main (void)
{
  ReadInput();
  Compute();
  
  return 0;
}
