#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

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
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk8pd,
                                  1e-6, 1e-6, 0.0);
  int i;
  double t = 0.0, t1 = 10.0;
  double y[4] = { 0.0, 0.0, 20.0, 0.0 };

  for (i = 1; i <= 100; i++)
    {
      double ti = i * t1 / 100.0;
      int status = gsl_odeiv2_driver_apply (d, &t, ti, y);

      if (status != GSL_SUCCESS)
        {
          printf ("error, return value=%d\n", status);
          break;
        }

      printf ("%.5e %.5e %.5e\n", t, y[0], y[1], y[2], y[3]);
    }

  gsl_odeiv2_driver_free (d);
  return 0;
}
