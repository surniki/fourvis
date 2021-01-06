
#ifndef F_IMAGE_H
#define F_IMAGE_H

#include "f_misc.h"

typedef struct impl_FourvisImage *FourvisImage;

/* fourvis_image_create
 *
 * Instantiates a FourvisImage object.
 *
 * filename: The relative path where the file will be saved to.
 * width: The width of the image in pixels.
 * height: The height of the image in pixels.
 * 
 * return: A successfully created FourvisImage object, or NULL upon error.
 */
FourvisImage fourvis_image_create(const char *filename, uint width, uint height);

/* fourvis_image_destroy
 *
 * Frees a FourvisImage object. Note that this operation does not write the image
 * data out to the disk; in order to do that, see /fourvis_image_save/.
 *
 * img: The FourvisImage object to be freed.
 */
void fourvis_image_destroy(FourvisImage img);

/* fourvis_image_pixel_draw
 *
 * Sets the pixel color (in 8-bit RGB format) of a single pixel in the (x, y)
 * coordinate. This operation mutates a buffer of memory stored in the FourvisImage
 * object that can be overwritten by subsequent calls to this procedure. The top left
 * corner is the origin of the coordinate system for the pixels. The positive y axis
 * points downward, and the positive x axis points to the right.
 *
 * img: The FourvisImage that will be changed by this operation.
 * x: The x coordinate of the pixel to be drawn over.
 * y: The y coordinate of the pixel to be drawn over.
 * r: The red component of the color to use (0 - 255).
 * g: The green component of the color to use (0 - 255).
 * b: The blue component of the color to use (0 - 255).
 */
void fourvis_image_pixel_draw(FourvisImage img, uint x, uint y, byte r, byte g, byte b);

/* fourvis_image_get_width
 *
 * Returns the width of the image.
 *
 * img: The FourvisImage object to query.
 * return: The width of the image.
 */
uint fourvis_image_get_width(FourvisImage img);

/* fourvis_image_get_height
 *
 * Returns the height of the image.
 *
 * img: The FourvisImage object to query.
 * return: The height of the image.
 */
uint fourvis_image_get_height(FourvisImage img);

/* fourvis_image_save
 *
 * Saves the image data out to the file system using the PPM image file format.
 * The file name that was specified when the FourvisImage object was created will be
 * used as the path where the file will be either created or, if the file already exists,
 * overwritten. If the path given was a relative path, it will be relative to the
 * current working directory of the process.
 *
 * img: The image to save to the file system.
 * return: 0 on success, or 1 if an error occurred when writing data to the disk.
 */
int fourvis_image_save(FourvisImage img);

#endif
