
#include "f_image.h"
#include "f_misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct impl_FourvisImage {
     const char *filename;
     uint width;
     uint height;
     byte buffer[1];
};

FourvisImage fourvis_image_create(const char *filename, uint width, uint height)
{
     FourvisImage result = malloc((sizeof *result) + 3*width*height - 1);
     if (!result)
	  return NULL;

     result->filename = filename;
     result->width = width;
     result->height = height;
     memset(result->buffer, 0, width * height);
     return result;
}

void fourvis_image_destroy(FourvisImage img)
{
     free(img);
}

uint fourvis_image_get_width(FourvisImage img)
{
     return img->width;
}

uint fourvis_image_get_height(FourvisImage img)
{
     return img->height;
}

void fourvis_image_pixel_draw(FourvisImage img, uint x, uint y, byte r, byte g, byte b)
{
     *(img->buffer + 3*(x + y * img->width) + 0) = r;
     *(img->buffer + 3*(x + y * img->width) + 1) = g;
     *(img->buffer + 3*(x + y * img->width) + 2) = b;
}

int fourvis_image_save(FourvisImage img)
{
#define error_file_write 1

     FILE *file = fopen(img->filename, "wb");
     uint digits = log10(img->width * img->height);
     uint buffer_size = 3 * img->width * img->height;
     
     if (!file)
	  return error_file_write;

     /* The file header for the ppm format. */
     if (fprintf(file, "P6 %d %d 255\n", img->width, img->height) < 9 + digits)
	  return error_file_write;
     
     if (fwrite(img->buffer, 1, buffer_size, file) < buffer_size)
	  return error_file_write;

     if (fclose(file))
	  return error_file_write;

     return 0;

#undef error_file_write
}
