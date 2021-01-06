
#include "f_config.h"
#include "f_misc.h"
#include "f_image.h"
#include "f_physics.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "f_config.h"

void fourvis_render_simulation(FourvisImage img, struct FourvisScene scene);
void fourvis_render_background(FourvisImage img, struct FourvisScene scene);
void fourvis_draw_pixels_by_circles(FourvisImage img, struct FourvisScene scene, double pr, double br);
void fourvis_determine_color(double bx, double by, uint *r, uint *g, uint *b);

int main(void){
     double aspect_ratio;
     FourvisImage img = fourvis_image_create(IMAGE_FILENAME, IMAGE_WIDTH, IMAGE_HEIGHT);
     FourvisImage bimg = fourvis_image_create("background_"IMAGE_FILENAME, IMAGE_WIDTH, IMAGE_HEIGHT);
     struct FourvisScene scene;

     aspect_ratio = (double)IMAGE_WIDTH / (double)IMAGE_HEIGHT;
     scene.camera_z = CAMERA_Z;
     scene.camera_height = CAMERA_HEIGHT;
     scene.camera_width = scene.camera_height * aspect_ratio;
     scene.barrier_z = BARRIER_Z;

     fourvis_render_simulation(img, scene);
     fourvis_render_background(bimg, scene);
     
     fourvis_image_save(img);
     fourvis_image_save(bimg);
     fourvis_image_destroy(img);
     fourvis_image_destroy(bimg);
     
     return 0;
}

void fourvis_render_simulation(FourvisImage img, struct FourvisScene scene)
{
     uint i;
     double x;
     double start_time, previous_time, current_time;
     struct FourvisRay wray = {0};

     current_time = previous_time = start_time = clock() / (double) CLOCKS_PER_SEC;

     for (x = THREE_SQRT_THREE + DELTA_R ; x <= scene.camera_width; x += DELTA_R) {
	  /* simulate light ray on equatorial plane */
	  wray.x = x;
	  wray.impact_parameter = x; /* when coming from infinity, this holds */
	  wray.y = 0;
	  wray.z = scene.camera_z;
	  wray.toggle = false;
	  
	  current_time = clock() / (double) CLOCKS_PER_SEC;
	  if (current_time - previous_time > PROGRESS_PRINT_INTERVAL) {
	       (void) printf("Progress: %d%%,  Time elapsed: %.2fs\n",
			     (int)(100*(x - THREE_SQRT_THREE)/(scene.camera_width - THREE_SQRT_THREE)),
			     current_time - start_time);
	       previous_time = current_time;
	  }
	  
	  for (i = 0; i < MAX_INTEGRATE_ITERATIONS; i++) {
	       fourvis_integrate(&wray);
	       if (wray.z <= scene.barrier_z) {
		    fourvis_draw_pixels_by_circles(img, scene, x, wray.x); /* NOTE: took fabs off x's */
		    break;
	       }
	  }
     }

     current_time = clock() / (double) CLOCKS_PER_SEC;
     (void) printf("Total time elapsed: %.2fs\n", current_time - start_time);
}

void fourvis_render_background(FourvisImage img, struct FourvisScene scene)
{
  uint const image_width = fourvis_image_get_width(img);
  uint const image_height = fourvis_image_get_height(img);
  uint x, y, r, g, b;
  double worldpx, worldpy;

  for (y = 0; y < image_height; ++y) {
    for (x = 0; x < image_width; ++x) {
      worldpx = fourvis_lerp(x, 0, image_width - 1,
			     -scene.camera_width/2, scene.camera_width/2);
      worldpy = fourvis_lerp(y, 0, image_height - 1,
			     -scene.camera_height/2, scene.camera_height/2);
      
      fourvis_determine_color(worldpx, worldpy, &r, &g, &b);
      fourvis_image_pixel_draw(img, x, y, r, g, b);
    }
  }
}

void fourvis_draw_pixels_by_circles(FourvisImage img, struct FourvisScene scene, double pr, double br)
{
     uint i, r, g, b;
     double const image_width = fourvis_image_get_width(img);
     double const image_height = fourvis_image_get_height(img);
     double sample_angle, worldpx, worldpy, imagepx, imagepy, px, py, bx, by;
     
     for (i = 0; i < CIRCLE_SAMPLES; i++) {
	  sample_angle = i * 2 * PI / CIRCLE_SAMPLES;
	  
	  worldpx = pr * cos(sample_angle);
	  worldpy = pr * sin(sample_angle);
	  imagepx = fourvis_lerp(worldpx, -scene.camera_width/2, scene.camera_width/2,
				 0, image_width - 1);
	  imagepy = fourvis_lerp(worldpy, -scene.camera_height/2, scene.camera_height/2,
				 0, image_height - 1);

	  if (imagepx < 0 || imagepx > image_width - 1 || imagepy < 0 || imagepy > image_height - 1)
	       continue;
	
	  if (modf(imagepx, &px) <= CIRCLE_TO_PIXEL_TOLERANCE &&
	      modf(imagepy, &py) <= CIRCLE_TO_PIXEL_TOLERANCE) {
	       bx = (br / pr) * worldpx;
	       by = (br / pr) * worldpy;
	       fourvis_determine_color(bx, by, &r, &g, &b);
	       fourvis_image_pixel_draw(img, px, py, r, g, b);
	  }
     }
}

#if CHECKER_COLORS_ON
void fourvis_determine_color(double bx, double by, uint *r, uint *g, uint *b)
{
#define xor(x,y) ((((x) && !(y))) || (((y) && !(x))))
     double x = fabs(fmod(bx / (CHECKER_WIDTH / 2.0), 2));
     double y = fabs(fmod(by / (CHECKER_HEIGHT / 2.0), 2));

     if (xor(x < 1, y < 1)) {
	  *r = CHECKER_COLOR_ON_R;
	  *g = CHECKER_COLOR_ON_G;
	  *b = CHECKER_COLOR_ON_B;
     }
     else {
	  *r = CHECKER_COLOR_OFF_R;
	  *g = CHECKER_COLOR_OFF_G;
	  *b = CHECKER_COLOR_OFF_B;
     } 
}
#elif QUADRANT_COLORS_ON
void fourvis_determine_color(double bx, double by, uint *r, uint *g, uint *b)
{
     if (bx >= 0 && by >= 0) {
	  *r = QUADRANT_COLOR_ONE_R;
	  *g = QUADRANT_COLOR_ONE_G;
	  *b = QUADRANT_COLOR_ONE_B;
     }
     else if (bx <= 0 && by >= 0) {
	  *r = QUADRANT_COLOR_TWO_R;
	  *g = QUADRANT_COLOR_TWO_G;
	  *b = QUADRANT_COLOR_TWO_B;
     }
     else if (bx <= 0 && by <= 0) {
	  *r = QUADRANT_COLOR_THREE_R;
	  *g = QUADRANT_COLOR_THREE_G;
	  *b = QUADRANT_COLOR_THREE_B;
     }
     else if (bx >= 0 && by <= 0) {
	  *r = QUADRANT_COLOR_FOUR_R;
	  *g = QUADRANT_COLOR_FOUR_G;
	  *b = QUADRANT_COLOR_FOUR_B;
     }
}
#else
void fourvis_determine_color(double bx, double by, uint *r, uint *g, uint *b)
{
     *r = DEFAULT_COLOR_R;
     *g = DEFAULT_COLOR_G;
     *b = DEFAULT_COLOR_B; 
}
#endif
