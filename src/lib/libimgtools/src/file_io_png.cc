/*******************************************************************************
 * Name        : file_io_png.cc
 * Project      : FlashPhoto
 * Module       : file_io_png
 * Description    : source for PngLoader class
 * Copyright     : Abner Holsinger All rights reserved.
 * Creation Date  : Wed Nov 11 2016
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <png.h>
#include <string>
#include <iostream>
#include "include/file_io.h"
#include "include/file_io_png.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FileIoPng::FileIoPng(void) {}
FileIoPng::~FileIoPng(void) {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
PixelBuffer FileIoPng::load_image(std::string file_name) {
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                  NULL, NULL, NULL);
  if (!png_ptr)
    return PixelBuffer(0, 0, ColorData(0, 0, 0, 0));  /* out of memory */
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    return PixelBuffer(0, 0, ColorData(0, 0, 0, 0));  /* out of memory */
  }
  // png_color_16p pBackground;  // unused; defaulting to black background
  unsigned int width, height, x, y;
  int bit_depth, color_type;
  png_bytep *row_pointers;
  // open file read only
  FILE *infile = fopen(file_name.c_str(), "rb");
  png_init_io(png_ptr, infile);
  // png_set_sig_bytes(png_ptr, 8); // unused unless reading signature bytes
  png_read_info(png_ptr, info_ptr);
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                                      NULL, NULL, NULL);
  if (color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_expand(png_ptr);
  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand(png_ptr);
  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    png_set_expand(png_ptr);
  if (bit_depth == 16)
    png_set_strip_16(png_ptr);
  if (color_type == PNG_COLOR_TYPE_GRAY ||
      color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png_ptr);  // change image data to rgb
  ColorData background_color = ColorData(0, 0, 0, 0);
  png_read_update_info(png_ptr, info_ptr);  // update changes
  // read image data line by line
  row_pointers = static_cast<png_bytep*>(malloc(sizeof(png_bytep*) * height));
  for (y = 0; y < height; y++) {
    row_pointers[y] = static_cast<png_byte*>(
                      malloc(png_get_rowbytes(png_ptr, info_ptr)));
  }
  png_read_image(png_ptr, row_pointers);
  int error = 0;
  // create a PixelBuffer to hold the pixel data;
  PixelBuffer new_buffer = PixelBuffer(width, height, background_color);
  // determine pixel data-block size; depends on number of channels
  int pxl_elems = (color_type < 6) ? 3 : 4;  // 3 channels for rgb, 4 for rgba
  for (y=0; y < height; y++) {
    png_bytep row = row_pointers[y];
    for (x=0; x < width; x++) {
      png_bytep px = &(row[x * pxl_elems]);
      int b_divisor = (1 << bit_depth) -1;
      if ((pxl_elems == 4) && (px[3] == 0))
        new_buffer.set_pixel(x, height - y - 1, background_color);
      else
        new_buffer.set_pixel(x, height - y - 1, ColorData(
                              static_cast<float>(px[0])/b_divisor,   // red
                              static_cast<float>(px[1])/b_divisor,   // green
                              static_cast<float>(px[2])/b_divisor,   // blue
      /* and the optional alpha channel */
      (pxl_elems == 4)? static_cast<float>(px[3]/b_divisor) : 1));
    }
  }
  fclose(infile);  // close file
  for (y=0; y < height; y++)
    free(row_pointers[y]);
  free(row_pointers);  // clear malloc'd memory
  if (png_ptr && info_ptr) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    png_ptr = NULL;
    info_ptr = NULL;
  }
return new_buffer;
}

int FileIoPng::save_image(const PixelBuffer & image,
                           const std::string & file_name) {
  png_byte color_type;
  png_byte bit_depth;
  png_structp png_ptr;
  png_infop info_ptr;
  int error = 0;
  int width = image.width();
  int height = image.height();
  png_bytep * row_pointers
                      = static_cast<png_bytep*>(malloc(sizeof(void*)*height));
  bit_depth = 8;
  color_type = 6;
  /* create file */
  FILE *outfile = fopen(file_name.c_str(), "wb");
  if (!outfile) {
    error = 1;
    printf("unable to save as %s\n", file_name.c_str() );
  }

  /* initialize stuff */
  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr) {
    error = 1;
    printf("png_create_write_struct failed");
  }
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    error = 1;
    printf("png_create_info_struct failed");
  }
  png_init_io(png_ptr, outfile);
  /* write header */
  if (setjmp(png_jmpbuf(png_ptr))) {
    error = 1;
    printf("error during writing header");
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type,
       PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
  png_write_info(png_ptr, info_ptr);

  /* write bytes */
  for (int y=0; y < height; y++) {
    row_pointers[y]  /* a buffer for each row of pixels */
           = static_cast<png_byte*>(malloc(sizeof(png_byte) * width * 4));
    for (int x=0; x < width; x++) {
     ColorData pxl = image.get_pixel(x, height - y - 1);
     /* copy the color data into the buffer */
     row_pointers[y][(x*4)] = static_cast<unsigned char>(pxl.red()*255);
     row_pointers[y][(x*4)+1] = static_cast<unsigned char>(pxl.green()*255);
     row_pointers[y][(x*4)+2] = static_cast<unsigned char>(pxl.blue()*255);
     row_pointers[y][(x*4)+3] = static_cast<unsigned char>(pxl.alpha()*255);
    }
  }
  if (setjmp(png_jmpbuf(png_ptr))) {
    error = 1;
    printf("error during writing bytes");
    }
  /* write buffered data to file */
  png_write_image(png_ptr, row_pointers);

  /* end write */
  if (setjmp(png_jmpbuf(png_ptr))) {
    error = 1;
    printf("error during end of write");
  }
  png_write_end(png_ptr, NULL);

  /* cleanup heap allocation */
  for (int y=0; y < height; y++)
        free(row_pointers[y]);
  free(row_pointers);

  fclose(outfile);
  return error;
}

}  /* namespace image_tools */
