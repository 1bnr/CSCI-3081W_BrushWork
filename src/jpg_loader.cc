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
    unsigned char * pxl;
    unsigned char *read_buffer;

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
  read_buffer = static_cast<unsigned char*>(malloc(row_stride * height));

  while (cinfo.output_scanline < cinfo.output_height) {
    unsigned char *buffer_array[1];
    buffer_array[0] = read_buffer + (cinfo.output_scanline) * row_stride;
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
      pxl = &read_buffer[(y*row_stride)+(x*c_ch)];  // 1 pixel
       new_buffer.set_pixel(x, height - y -1, ColorData(
       static_cast<float>(pxl[0])/b_divisor,  /* red channel */
       static_cast<float>(pxl[1])/b_divisor,  /* green channel */
       static_cast<float>(pxl[2])/b_divisor,  /* blue channel */
       1));  // jpeg has no alpha channel
    }
  }
  free(read_buffer);
  read_buffer = NULL;
printf("in jpg_loader size is %d x %d\n", new_buffer.width(), new_buffer.height() );
  return new_buffer;
}
/** save the given PixelBuffer image as the given FILE file_name */
void JpgLoader::save_image(const PixelBuffer & image, const std::string & file_name) {

  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  /* More stuff */
  FILE * outfile;		/* target file */
  JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
  int row_stride;		/* byte width per row in image buffer */
  int width = image.width();
  int height = image.height();
  printf("in JpgLoader::save_image size is %d x %d\n", width, height );
  int quality = 70;
  cinfo.err = jpeg_std_error(&jerr);
  /* Now we can initialize the JPEG compression object. */
  jpeg_create_compress(&cinfo);

  /* Step 2: specify data destination (eg, a file) */
  /* Note: steps 2 and 3 can be done in either order. */

  /* Here we use the library-supplied code to send compressed data to a
   * stdio stream.  You can also write your own code to do something else.
   * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
   * requires it in order to write binary files.
   */
  if ((outfile = fopen(file_name.c_str(), "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", file_name.c_str());
    exit(1);
  }
  jpeg_stdio_dest(&cinfo, outfile);

  /* Step 3: set parameters for compression */

  /* First we supply a description of the input image.
   * Four fields of the cinfo struct must be filled in:
   */
  cinfo.image_width = width; 	/* image width and height, in pixels */
  cinfo.image_height = height;
  cinfo.input_components = 3;		/* # of color components per pixel */
  cinfo.dct_method = JDCT_FLOAT;
  cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
  /* Now use the library's routine to set default compression parameters.
   * (You must set at least cinfo.in_color_space before calling this,
   * since the defaults depend on the source color space.)
   */
  jpeg_set_defaults(&cinfo);
  /* Now you can set any non-default parameters you wish to.
   * Here we just illustrate the use of quality (quantization table) scaling:
   */
  jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

  /* Step 4: Start compressor */

  /* TRUE ensures that we will write a complete interchange-JPEG file.
   * Pass TRUE unless you are very sure of what you're doing.
   */
  jpeg_start_compress(&cinfo, TRUE);
  row_stride = image.width() * 3;	/* JSAMPLEs per pixel in image_buffer */

  unsigned char * image_buffer;
//  unsigned char* pxl;
  int c_ch = 3; // number of color channels
  image_buffer = static_cast<unsigned char*>(malloc(height*row_stride));

  for (int y=0; y < height; y++) {
    for (int x=0; x < width; x++) {
  //    pxl = &image_buffer[(y * row_stride) + (x*c_ch)];
      image_buffer[(y * row_stride) + (x*c_ch)] = 255 * image.get_pixel(x,height-y-1).red();
      image_buffer[(y * row_stride) + (x*c_ch) + 1] = 255 * image.get_pixel(x,height-y-1).green();
      image_buffer[(y * row_stride) + (x*c_ch) + 2] = 255 * image.get_pixel(x,height-y-1).blue();
    }

  }

  while (cinfo.next_scanline < height) {
    row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  /* Step 6: Finish compression */

  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
  free(image_buffer);
  fclose(outfile);

  /* And we're done! */
}

}  /* namespace image_tools */
