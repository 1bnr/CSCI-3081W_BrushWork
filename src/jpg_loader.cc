/*******************************************************************************
 * Name        : jpg_loader.cc
 * Project      : FlashPhoto
 * Module       : jpg_loader
 * Description    : source for JpgLoader class
 * Copyright     : Abner Holsinger All rights reserved.
 * Creation Date  : Wed Nov 11 2016
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

 /*******************************************************************************
  * Includes
  ******************************************************************************/
#include <iostream>
#include <jerror.h>
#include <setjmp.h>
#include <cstring>
#include <jpeglib.h>
#include <string>
#include "include/jpg_loader.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {
/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
 
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
PixelBuffer JpgLoader::load_image(std::string file_name) {
  /* This struct contains the JPEG decompression parameters and pointers to
  * working space (which is allocated as needed by the JPEG library).
  */
  struct jpeg_decompress_struct cinfo;
  struct my_error_mgr jerr;
  /* More stuff */
  int bit_depth = 8;
  FILE * infile;  /* source file */
  int row_stride; /* physical row width in output buffer */
  int height, width, c_ch;

  // printf("%s\n", "opening file\n");
  if ((infile = fopen(file_name.c_str(), "r")) == NULL) {
    fprintf(stderr, "can't open %s\n", file_name.c_str());
    return PixelBuffer(0, 0, ColorData(0, 0, 0, 0));  // error condition
  }

  /* Step 1: allocate and initialize JPEG decompression object */

  /* We set up the normal JPEG error routines, then override error_exit. */
  cinfo.err = jpeg_std_error(&jerr.pub);
  // assuming all files are good, as per TAs' instruction.
  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);

  printf("%s\n", "read header");
  (void) jpeg_read_header(&cinfo, TRUE);
  /* Step 5: Start decompressor */
  printf("%s\n", "start decompression");
  (void) jpeg_start_decompress(&cinfo);
  /* We can ignore the return value since suspension is not possible
   * with the stdio data source.
   */
  height = cinfo.output_height;  // pixels per height
  width = cinfo.output_width;  // pixels per row
  c_ch = cinfo.output_components;  // number of channels per pixel; typically 3
  row_stride = width * c_ch;  // number of bytes wide; each channel is 1 byte
  int b_divisor = (1 << bit_depth) -1;
  unsigned char *bmp_buffer;
  bmp_buffer = static_cast<unsigned char*>(malloc(row_stride * height));

  while (cinfo.output_scanline < cinfo.output_height) {
    unsigned char *buffer_array[1];
    buffer_array[0] = bmp_buffer + (cinfo.output_scanline) * row_stride;
    /* read the data into a the buffer */
    jpeg_read_scanlines(&cinfo, buffer_array, 1);
  }

  /* Step 7: Finish decompression */
  printf("%s\n", "finish compression.");
  (void) jpeg_finish_decompress(&cinfo);
  /* Step 8: Release JPEG decompression object */
  jpeg_destroy_decompress(&cinfo);
  fclose(infile);
  PixelBuffer new_buffer = PixelBuffer(width, height, ColorData(0, 0, 0));
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
     new_buffer.set_pixel(x, height - y -1, ColorData(
       static_cast<float>(bmp_buffer[(y*row_stride)+(x*c_ch)])/b_divisor,
       static_cast<float>(bmp_buffer[(y*row_stride)+(x*c_ch)+1])/b_divisor,
       static_cast<float>(bmp_buffer[(y*row_stride)+(x*c_ch)+2])/b_divisor,
       1));  // jpeg has no alpha channel
    }
  }
  free(bmp_buffer);
  bmp_buffer = NULL;
  return new_buffer;
}

}  /* namespace image_tools */
