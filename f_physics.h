
#ifndef F_PHYSICS_H
#define F_PHYSICS_H

#include <stdbool.h>

struct FourvisScene {
     double camera_z;
     double camera_width;
     double camera_height;
     double barrier_z;
};

struct FourvisRay {
     double x, y, z, impact_parameter;
     bool toggle;
};

/* fourvis_lerp
 *
 * Linear interpolation routine.
 *
 * in: The input that is to be interpolated.
 * min_in: The input value for the first point.
 * min_out: The output value for the first point.
 * max_in: The input value for the second point.
 * max_out: The output value for the second point.
 *
 * return: The corresponding output of the given input.
 */
double fourvis_lerp(double in, double min_in, double min_out, double max_in, double max_out);

/* fourvis_integrate
 *
 * Marches the given ray forward by a small step in lambda.
 *
 * ray: The ray to be marched forward. NOTE: ray is mutated in place!
 */
void fourvis_integrate(struct FourvisRay *ray);

#endif
