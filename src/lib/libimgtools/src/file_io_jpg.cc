/*******************************************************************************
 * Name        : file_io_jpg.cc
 * Project      : FlashPhoto
 * Module       : file_io_jpg
 * Description    : source for FileIoJpg class
 * Copyright     : Abner Holsinger All rights reserved.
 * Creation Date  : Wed Nov 11 2016
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

 /*******************************************************************************
  * Includes
  ******************************************************************************/
#include <jerror.h>
#include <setjmp.h>
#include <string>
#include <cstring>
#include <iostream>
#include "include/file_io.h"
#include "include/file_io_jpg.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {
/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FileIoJpg::FileIoJpg(void) {}
FileIoJpg::~FileIoJpg(void) {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
PixelBuffer FileIoJpg::load_image(std::string file_name) {
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

  cinfo.err = jpeg_std_error(&jerr.pub);
  // assuming all files are good, as per TAs' instruction.
  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);

  (void) jpeg_read_header(&cinfo, TRUE);
  /* start decompressor */
  (void) jpeg_start_decompress(&cinfo);

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

  /* finish decompression */
  (void) jpeg_finish_decompress(&cinfo);
  /* release JPEG decompression object */
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
       1));  /* jpeg has no alpha channel */
    }
  }
  free(read_buffer);  /* free the malloc'd buffer memory */
  read_buffer = NULL;
  return new_buffer;
}
/** save the given PixelBuffer image as the given FILE file_name */
int FileIoJpg::save_image(
                    const PixelBuffer & image, const std::string & file_name) {
  int error = 0;
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  /* More stuff */
  FILE * outfile;  /* target file */
  JSAMPROW row_pointer[1];  /* pointer to JSAMPLE row[s] */
  int row_stride;  /* byte width per row in image buffer */
  int width = image.width();  /* pixel width of image */
  int height = image.height();  /* pixel height of image */
  int quality = 70;  /* compression quality; [1-100] */
  int bit_depth = 8;  /* each color channel is 8-bits */
  cinfo.err = jpeg_std_error(&jerr);  /* error handler */
  /* initialize the JPEG compression object. */
  jpeg_create_compress(&cinfo);

  /* specify data destination file */
  if ((outfile = fopen(file_name.c_str(), "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", file_name.c_str());
    error = 1;
    exit(error);
  }
  jpeg_stdio_dest(&cinfo, outfile);

  /* parameters for compression */
  cinfo.image_width = width;   /* image width in pixels */
  cinfo.image_height = height;  /* image height in pixels */
  cinfo.input_components = 3;    /* # of color components per pixel */
  cinfo.dct_method = JDCT_FLOAT;
  cinfo.in_color_space = JCS_RGB;   /* colorspace of input image */

  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

  /* start the compressor */

  jpeg_start_compress(&cinfo, TRUE);
  row_stride = image.width() * 3;  /* JSAMPLEs per pixel in image_buffer */

  unsigned char * image_buffer;  /* the buffer for the image data */
  int c_ch = 3;  // number of color channels
  int bd_factor = (1 << bit_depth) -1;
  image_buffer = static_cast<unsigned char*>(malloc(height*row_stride));
  /* put the image data into the buffer */
  for (int y=0; y < height; y++) {
    for (int x=0; x < width; x++) {
      ColorData pxl = image.get_pixel(x, height-y-1);  /* this pixel */
      int p_offset = (y * row_stride) + (x*c_ch);  /* pixel offset in buffer */
      image_buffer[p_offset] = bd_factor * pxl.red();
      image_buffer[p_offset + 1] = bd_factor * pxl.green();
      image_buffer[p_offset + 2] = bd_factor * pxl.blue();
    }
  }
  /* write the buffered data into the output file */
  while (cinfo.next_scanline < height) {
    row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  /* finish compression */
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
  free(image_buffer);
  fclose(outfile);
  return error;
}

}  /* namespace image_tools */
