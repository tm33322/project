#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

double mode, t, t1, h, y[4], order;
ofstream outdebugfile;

//reads the input file
void ReadInput()
{
	if (mode=1)
	{
	outdebugfile.open ("outdebugxy");
	outdebugfile << "entering ReadInput" << endl;
	}


	double r, R[8];
	int i=0;

	ifstream infile("inputxy");

	while (infile >> r)
	{
		R[i]=r;
		i++;
		//cout << r << endl;
	}

	mode=R[0];	//mode = 0 for normal mode and 1 for debug mode
	t=R[1];		//initial time
	t1=R[2];	//final time
	h=R[3];		//step


	for (i=0; i<=3; i++)
	{
		y[i]=R[i+4];	//solution

		if (mode=1)
		{
			outdebugfile << "y" << i << " = " << y[i] << endl;
		}
	}

		outdebugfile << "mode = " << mode << " t = " << t << " t1 = " << t1 << " h = " << h << " y0 = " << y[0] << " y1 = " << y[1] << " y2 = " << y[2] << " y3 = " << y[3] << endl;
}


int
func (double t, const double y[], double f[],
      void *params)
{

  if (mode=1)
  {
	outdebugfile << "entering func" << endl;
  }

  f[0] = y[2];
  f[1] = y[3];
  f[2] = 5.0*y[3] - 0.2*y[2];
  f[3] = - 5.0*y[2] - 0.2*y[3];

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

 gsl_odeiv2_system sys = {func, NULL, 4, NULL};

  gsl_odeiv2_driver * d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk2,
                                  1e-6, 1e-6, 0.0);

  int i;

	ofstream outputfile;
	outputfile.open("outputxy");

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

      outputfile << t << " " << y[0] << " " << y[1] << " " << y[2] << " " << y[3] << endl;
 
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
main ()
{

  clock_t c1=clock();

  ReadInput();
  Compute();

  c1 = clock() - c1;
  cout << "execution time is " << c1/(double)CLOCKS_PER_SEC << " seconds" << endl;

  return 0;
}

