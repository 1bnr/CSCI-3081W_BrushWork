/*******************************************************************************
 * Name            : Mask.h
 * Project         : csci3081
 * Module          : ??
 * Description     : Header file for Mask base class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_MASK_H_
#define INCLUDE_MASK_H_

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
//  Mask is a wrapper for the array of floats representing the shape of
//  a tool. It is pure virtual, because a mask does not inherently have
//  a shape. Shapes are defined implicitly with getIntensity().
class Mask {
 public:
  Mask(float radius, float opacity);
  Mask(void);
  virtual ~Mask(void);
  float const *getFloatArray(void) const { return mask_array_; }
  int width(void) const { return width_;}
  int height(void) const {return height_;}
  float value(int x, int y) const;

 protected:
  void value(int x, int y, float v);
  void generateMask(void);
  virtual float get_intensity(int x, int y, float radius) = 0;

 private:
  Mask(const Mask& rhs) = delete;
  Mask& operator=(const Mask& rhs) = delete;

  float radius_;
  float opacity_;
  int height_;
  int width_;
  float *mask_array_;

};

}  // namespace csci3081

#endif  // INCLUDE_MASK_H_
