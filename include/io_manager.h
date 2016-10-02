/*******************************************************************************
 * Name            : io_manager.h
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Header for IoManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef INCLUDE_IO_MANAGER_H_
#define INCLUDE_IO_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "GL/glui.h"
#include "include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A collection of io parameters for manipulating photos
 * TODO: Add more detail, and add comments/doc for the members below
 */
class IOManager {
 public:
  IOManager();
  ~IOManager() {}

  /**
   * @brief Initialize GLUI control elements for IO management
   *
   * @param glui GLUI handle
   * @param s_gluicallback Callback to install
   */
  void InitGlui(const GLUI *const glui,
                void (*s_gluicallback)(int));

  /**
   * @brief Set the image file. If the file is valid, enable loading/saving
   *
   * @param filepath Pathname of the file
   */
  void set_image_file(const std::string & filepath);

  /**
   * @brief Get the current image file name
   *
   * @return The current image file name
   */
  const std::string& file_name(void) { return file_name_;}

  /**
   * @brief Get a handle on the GLUI file browser
   *
   * @return The handle
   */
  GLUI_FileBrowser* file_browser(void) { return file_browser_;}


  /**
   * @brief Load the selected image file to the canvas
   *
   */
  void LoadImageToCanvas(void);

  /**
   * @brief Load the selected image file to the stamp
   *
   */
  void LoadImageToStamp(void);

  /**
   * @brief Save the current state of the canvas to a file
   *
   */
  void SaveCanvasToFile(void);

 private:
  /* Copy/move assignment/construction disallowed */
  IOManager(const IOManager &rhs) = delete;
  IOManager& operator=(const IOManager &rhs) = delete;

  void save_canvas_toggle(bool enabled) {
    UICtrl::button_toggle(save_canvas_btn_, enabled);
  }

  void load_stamp_toggle(bool enabled) {
    UICtrl::button_toggle(load_stamp_btn_, enabled);
  }

  void load_canvas_toggle(bool enabled) {
    UICtrl::button_toggle(load_canvas_btn_, enabled);
  }
  bool is_valid_image_file_name(const std::string & name);
  bool is_valid_image_file(const std::string & name);
  bool has_suffix(const std::string & str, const std::string & suffix);

  /* data members */
  GLUI_FileBrowser *file_browser_;
  GLUI_Button *load_canvas_btn_;
  GLUI_Button *load_stamp_btn_;
  GLUI_Button *save_canvas_btn_;
  GLUI_StaticText *current_file_label_;
  GLUI_EditText *file_name_box_;
  GLUI_StaticText *save_file_label_;
  std::string file_name_;
};

}  // namespace image_tools
#endif  // INCLUDE_IO_MANAGER_H_
