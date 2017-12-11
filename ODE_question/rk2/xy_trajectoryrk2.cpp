#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

double mode, t, t1, h, y[4];

void ReadInput()
{
        double r, R[7];
        int i=0;

        ifstream infile("input");

        while (infile >> r)
        {
                R[i]=r;
                i++;
        }

        mode=R[0];
        t=R[1];
        t1=R[2];
	h=R[3];

        for (i=0; i<=3; i++)
        {
                y[i]=R[i+4];
                //cout << "y" << i << " = " << y[i] << endl;
        }
//cout << "mode = " << mode << " t = " << t << " t1 = " << t1 << " h = " << h << " y0 = " << y[0] << " y1 = " << y[1] << " y2 = " << y[2] << " y3 = " << y[3] << endl;
}

int
func (double t, const double y[], double f[],
      void *params)
{
  f[0] = y[2];
  f[1] = y[3];
  f[2] = 5.0*y[3] - 0.2*y[2];
  f[3] = - 5.0*y[2] - 0.2*y[3];
  return GSL_SUCCESS;
}

int
jac (double t, const double y[], double *dfdy,
     double dfdt[], void *params)
{
  gsl_matrix_view dfdy_mat
    = gsl_matrix_view_array (dfdy, 4, 4);
  gsl_matrix * m = &dfdy_mat.matrix;
  // first line
  gsl_matrix_set (m, 0, 0, 0.0);
  gsl_matrix_set (m, 0, 1, 0.0);
  gsl_matrix_set (m, 0, 2, 1.0);
  gsl_matrix_set (m, 0, 3, 0.0);
  // Secomd line
  gsl_matrix_set (m, 1, 0, 0.0);
  gsl_matrix_set (m, 1, 1, 0.0);
  gsl_matrix_set (m, 1, 2, 0.0);
  gsl_matrix_set (m, 1, 3, 1.0);
  // Third line
  gsl_matrix_set (m, 2, 0, 0.0);
  gsl_matrix_set (m, 2, 1, 0.0);
  gsl_matrix_set (m, 2, 2, -0.2);
  gsl_matrix_set (m, 2, 3, 5.0);
  // Fourth line
  gsl_matrix_set (m, 3, 0, 0.0);
  gsl_matrix_set (m, 3, 1, 0.0);
  gsl_matrix_set (m, 3, 2, -5.0);
  gsl_matrix_set (m, 3, 3, -0.2);
 
  dfdt[0] = 0.0;
  dfdt[1] = 0.0;
  dfdt[2] = 0.0;
  dfdt[3] = 0.0;
  return GSL_SUCCESS;
}

int
main (void)
{
  gsl_odeiv2_system sys = {func, jac, 4, NULL};

  gsl_odeiv2_driver * d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk2,
                                  1e-6, 1e-6, 0.0);
  int i;
  //double t = 0.0, t1 = 10.0;
  //double y[4] = { 0.0, 0.0, 20.0, 0.0 };

	ofstream outputfile;
        outputfile.open("output");

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

      outputfile << t << y[0] << y[1] << y[2] << y[3] << endl;
      //printf ("%.5e %.5e %.5e %.5e %.5e\n", t, y[0], y[1], y[2], y[3]);
    }

  gsl_odeiv2_driver_free (d);
  return 0;
}

