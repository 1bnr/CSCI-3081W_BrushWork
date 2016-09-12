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
  float const *getFloatArray(void) const { return m_maskArray; }
  int width(void) const { return m_width;}
  int height(void) const {return m_height;}
  float value(int x, int y) const;

 protected:
  void value(int x, int y, float v);
  void generateMask(void);
  virtual float get_intensity(int x, int y, float radius) = 0;

 private:
  Mask(const Mask& rhs) = delete;
  Mask& operator=(const Mask& rhs) = delete;

  float m_radius;
  float m_opacity;
  int m_height;
  int m_width;
  float *m_maskArray;

};

}  // namespace csci3081

#endif  // INCLUDE_MASK_H_
