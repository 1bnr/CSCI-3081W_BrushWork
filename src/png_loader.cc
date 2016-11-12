/*******************************************************************************
 * Name            : png_loader.cc
 * Project         : FlashPhoto
 * Module          : png_loader
 * Description     : source for PngLoader class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Nov 11 2016
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

 /*******************************************************************************
  * Includes
  ******************************************************************************/
#include <string>
#include <iostream>
#include <png.h>
#include "include/png_loader.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

  /*******************************************************************************
   * Constructors/Destructor
   ******************************************************************************/
   // use defaults
   /*******************************************************************************
    * Member Functions
    ******************************************************************************/
PixelBuffer PngLoader::load_image(std::string file_name) {
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr)
        return PixelBuffer(0,0,ColorData(0,0,0,0));   /* out of memory */
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return PixelBuffer(0,0,ColorData(0,0,0,0));   /* out of memory */
    }
  //png_color_16p pBackground; // unused; default to black background
  unsigned int width, height, x, y;
  int bit_depth, color_type;
  png_bytep *row_pointers;
  // open file read only
  FILE *infile = fopen(file_name.c_str(), "r");
  png_init_io(png_ptr, infile);
  //png_set_sig_bytes(png_ptr, 8); // unused unless reading signature bytes
  png_read_info(png_ptr, info_ptr);
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);
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
    png_set_gray_to_rgb(png_ptr); // change image data to rgb

  png_read_update_info(png_ptr, info_ptr); // update changes
  // read image data line by line
  row_pointers = static_cast<png_bytep*>(malloc(sizeof(png_bytep*) * height));
  for (y=0; y<height; y++){
    row_pointers[y] = static_cast<png_byte*>(malloc(png_get_rowbytes(png_ptr,info_ptr)));
  }
  png_read_image(png_ptr, row_pointers);
  // create a PixelBuffer to hold the pixel data;
  PixelBuffer new_buffer = PixelBuffer(width, height, ColorData(0,0,0,1));
  // determine pixel data-block size; depends on number of channels
  int pxl_elems = (color_type < 6) ? 3 : 4; // 3 channels for rgb, 4 for rgba
  printf("pxl_elems: %d\n", pxl_elems);
  for(y = 0; y < height; y++) {
    png_bytep row = row_pointers[y];
    for(x = 0; x < width; x++) {
      png_bytep px = &(row[x * pxl_elems]);
      int b_divisor = (1 << bit_depth) -1;
      new_buffer.set_pixel(x, height - y - 1, ColorData( // pxl is uch array; must be cast
          static_cast<float>(px[0])/b_divisor,    // red
          static_cast<float>(px[1])/b_divisor,    // green
          static_cast<float>(px[2])/b_divisor,    // blue
          (pxl_elems == 4)? static_cast<float>(px[3]/b_divisor) : 1 ));  // alpha
    }
  }
  fclose(infile); // close file
  for (y=0; y<height; y++)
    free(row_pointers[y]);
  free(row_pointers); // clear malloc'd memory
  if (png_ptr && info_ptr) {
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      png_ptr = NULL;
      info_ptr = NULL;
  }
return new_buffer;
}

}  /* namespace image_tools */
