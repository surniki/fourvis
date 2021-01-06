
#include "f_config.h"
#include "f_misc.h"
#include "f_physics.h"
#include <stdbool.h>
#include <math.h>

double fourvis_lerp(double in, double min_in, double max_in, double min_out, double max_out)
{      
     return min_out + (in - min_in) * ((max_out - min_out) / (max_in - min_in));
}

static double delta_lambda(double r, double b)
{
     if (r > LAMBDA_STEP_MAX_IN)
	  return LAMBDA_STEP_MAX_OUT;
     else
	  if (r < LAMBDA_STEP_MIN_IN)
	       return LAMBDA_STEP_MIN_OUT;
     return (b / THREE_SQRT_THREE) * fourvis_lerp(r,
						  LAMBDA_STEP_MIN_IN,
						  LAMBDA_STEP_MAX_IN,
						  LAMBDA_STEP_MIN_OUT,
						  LAMBDA_STEP_MAX_OUT);
}

static double dr_wrt_dlambda(double r, double b, bool toggle)
{
     return (toggle ? 1 : -1) * sqrt(fabs(1 / pow(b, 2) - 1 / pow(r, 2) * (1 - 2 / r)));
}

static double dphi_wrt_dlambda(double r)
{
     return 1 / pow(r, 2);
}

void fourvis_integrate(struct FourvisRay *ray)
{ 
     double conv_x, conv_y, conv_z, r, phi, b;
     b = ray->impact_parameter;

     /* turn Cartesian coordinates so that "z" axis is perpendicular to equatorial plane */
     conv_x = ray->x;
     conv_y = ray->z;
     conv_z = ray->y;
     /* convert to Spherical coordinates, where theta is fixed to pi/2 */
     r = sqrt(pow(conv_x, 2) + pow(conv_y, 2) + pow(conv_z, 2));
     phi = atan2(conv_y, conv_x);
     if (!ray->toggle) /* set toggle to change behavior of dr_wrt_dlambda */
	  if (r <= 2)
	       ray->toggle = true;
     /* integrate using Euler method */
     phi += delta_lambda(r, b) * dphi_wrt_dlambda(r);
     r += delta_lambda(r, b) * dr_wrt_dlambda(r, b, ray->toggle);
     /* convert to Cartesian coordinates */
     conv_x = r * cos(phi); /* times sin(pi/2) -> 1 */
     conv_y = r * sin(phi); /* times sin(pi/2) -> 1 */
     conv_z = 0; /* since theta is fixed to pi/2 */
     /* return to original Cartesian coordinates */
     ray->x = conv_x;
     ray->y = conv_z;
     ray->z = conv_y;
}
