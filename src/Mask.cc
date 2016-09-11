/*******************************************************************************
 * Name            : Mask.cc
 * Project         : csci3081
 * Module          : ??
 * Description     : Implementation of Mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Mask.h"
#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
using std::fill;
namespace csci3081 {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Mask::Mask() : m_radius(0.0),
               m_opacity(0.0),
               m_height(0),
               m_width(0),
               m_maskArray(nullptr) {}

Mask::Mask(float radius, float opacity)
    : m_radius(radius),
      m_opacity(opacity),
      m_height(ceil(radius)*2+1),
      m_width(ceil(radius)*2+1),
      m_maskArray(new float[m_width*m_height]) {
    fill(m_maskArray, m_maskArray+m_width*m_height, 1.f);
}

Mask::~Mask() {
    delete [] m_maskArray;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

float Mask::getValue(int x, int y) const {
        if (m_maskArray == nullptr || x < 0 || x > m_width ||
            y < 0 || y > m_width) {
            return 0.f;
        } else {
            return m_maskArray[y*m_width + x];
        }
}

void Mask::setValue(int x, int y, float v) {
    if (m_maskArray == NULL || x < 0 || x > m_width || y < 0 || y > m_width) {
        return;
    } else {
        m_maskArray[y*m_width + x] = v;
    }
}

void Mask::generateMask() {
    for (int j = 0; j < getHeight(); j++) {
        for (int i = 0; i < getWidth(); i++) {
            int x = i-getWidth()/2;
            int y = j-getHeight()/2;
            float intensity = m_opacity*getIntensity(x, y, m_radius);
            setValue(i, j, intensity);
        }
    }
}

}  // namespace csci3081
