/*******************************************************************************
 * Name            : io_manager.cc
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Implementation of IOManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/io_manager.h"
#include <iostream>
#include <string>
//#include "png.h"
#include "include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
IOManager::IOManager(void) :
    file_browser_(nullptr),
    load_canvas_btn_(nullptr),
    load_stamp_btn_(nullptr),
    save_canvas_btn_(nullptr),
    current_file_label_(nullptr),
    file_name_box_(nullptr),
    save_file_label_(nullptr),
    file_name_() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void IOManager::InitGlui(const GLUI *const glui,
                         void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *image_panel = new GLUI_Panel(const_cast<GLUI*>(glui),
                                           "Image I/O");
  file_browser_ = new GLUI_FileBrowser(image_panel,
                                      "Choose Image",
                                      false,
                                      UICtrl::UI_FILE_BROWSER,
                                      s_gluicallback);

  file_browser_->set_h(400);

  file_name_box_ = new GLUI_EditText(image_panel ,
                                    "Image:",
                                    file_name_,
                                    UICtrl::UI_FILE_NAME,
                                    s_gluicallback);
  file_name_box_->set_w(200);

  new GLUI_Separator(image_panel);

  current_file_label_ = new GLUI_StaticText(image_panel,
                                           "Will load image: none");
  load_canvas_btn_ = new GLUI_Button(image_panel,
                                    "Load Canvas",
                                    UICtrl::UI_LOAD_CANVAS_BUTTON,
                                    s_gluicallback);
  load_stamp_btn_ = new GLUI_Button(image_panel,
                                   "Load Stamp",
                                   UICtrl::UI_LOAD_STAMP_BUTTON,
                                   s_gluicallback);

  new GLUI_Separator(image_panel);

  save_file_label_ = new GLUI_StaticText(image_panel,
                                        "Will save image: none");

  save_canvas_btn_ = new GLUI_Button(image_panel,
                                    "Save Canvas",
                                    UICtrl::UI_SAVE_CANVAS_BUTTON,
                                    s_gluicallback);

  load_canvas_toggle(false);
  load_stamp_toggle(false);
  save_canvas_toggle(false);
}


bool IOManager::is_valid_image_file(const std::string & name) {
  FILE *f;
  bool is_valid = false;
  if (is_valid_image_file_name(name)) {
    if ((f = fopen(name.c_str(), "r"))) {
      is_valid = true;
      fclose(f);
    }
  }
  return is_valid;
}

void IOManager::set_image_file(const std::string & file_name) {
  // If a directory was selected
  // instead of a file, use the
  // latest file typed or selected.
  std::string image_file = file_name;
  if (!is_valid_image_file_name(image_file)) {
    image_file = file_name_;
  }

  // TOGGLE SAVE FEATURE
  // If no file is selected or typed,
  // don't allow file to be saved. If
  // there is a file name, then allow
  // file to be saved to that name.

  if (!is_valid_image_file_name(image_file)) {
    save_file_label_->set_text("Will save image: none");
    save_canvas_toggle(false);
  } else {
    save_file_label_->set_text((std::string("Will save image: ") +
                                image_file).c_str());
    save_canvas_toggle(true);
  }

  // TOGGLE LOAD FEATURE

  // If the file specified cannot be opened,
  // then disable stamp and canvas loading.
  if (is_valid_image_file(image_file)) {
    load_stamp_toggle(true);
    load_canvas_toggle(true);

    current_file_label_->set_text((std::string("Will load: ") +
                                   image_file).c_str());
    file_name_box_->set_text(image_file);
  } else {
    load_stamp_toggle(false);
    load_canvas_toggle(false);
    current_file_label_->set_text("Will load: none");
  }
}

PixelBuffer * IOManager::LoadImageToCanvas(void) {
  PixelBuffer * new_buffer;
//  std::cout << "Load Canvas has been clicked for file " <<
//      file_name_ << std::endl;
  // get suffix from incoming file name
  std::string file_suffix = file_name_.substr(file_name_.find_last_of(".") + 1);


  std::cout << file_suffix << std::endl;
  if (file_suffix.compare("png") == 0){
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
      if (!png_ptr)
        exit(4); // out of memory
    png_color_16p pBackground;
    unsigned int width, height, x, y;
    int bit_depth, color_type;
    png_bytep *row_pointers;
    // open file read only
    FILE *fp = fopen(file_name_.c_str(), "r");
    png_init_io(png_ptr, fp);
    png_read_info(png_ptr, info_ptr);
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

    ColorData bg_color;
    if (!png_get_valid(png_ptr, info_ptr, PNG_INFO_bKGD)) {
      png_get_bKGD(png_ptr, info_ptr, &pBackground);
      bg_color.red(pBackground->red);
      bg_color.green(pBackground->green);
      bg_color.blue(pBackground->blue);
    }
    else // no background color found; make it up...
    bg_color = ColorData(0,0,0,0);
    printf("bit_depth: %d\n", bit_depth);
    printf("color_type: %d\n", color_type);
  //  if (bit_depth == 16) //  if 16, change to 8 bits per channel...
  //      png_set_strip_16(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr); // change image data to rgb
    png_read_update_info(png_ptr, info_ptr); // update changes
    new_buffer = new PixelBuffer(width, height, bg_color);

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (y=0; y<height; y++){
      row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
    }
    png_read_image(png_ptr, row_pointers);
    int pxl_elems = (color_type < 6) ? 3 : 4; // 3 channels for rgb, 4 for rgba
    for(y = 0; y < height; y++) {
      png_bytep row = row_pointers[y];
      for(x = 0; x < width; x++) {
        png_bytep px = &(row[x * pxl_elems]);
        int b_divisor = bit_depth * 8; 
        new_buffer->set_pixel(x, height - y - 1, ColorData( // pxl is uch array; must be cast
            static_cast<float>(px[0])/b_divisor,    // red
            static_cast<float>(px[1])/b_divisor,    // green
            static_cast<float>(px[2])/b_divisor,    // blue
            (pxl_elems == 4)? static_cast<float>(px[3]/b_divisor) : 1 ));  // alpha
      }
    }
    fclose(fp); // close file
    free(row_pointers); // clear malloc'd memory
    return new_buffer;
  }
  else /** File loaded is a jpeg */
    if ((file_suffix.compare("jpg") == 0) || (file_suffix.compare("jpeg") == 0))


  return new PixelBuffer(1,1, ColorData());


}

void IOManager::LoadImageToStamp(void) {
  std::cout << "Load Stamp has been clicked for file " <<
      file_name_ << std::endl;
}

void IOManager::SaveCanvasToFile(void) {
  std::cout << "Save Canvas been clicked for file " <<
      file_name_ << std::endl;
}



}  /* namespace image_tools */
