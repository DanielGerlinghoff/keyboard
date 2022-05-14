#pragma once

#include "quantum.h"

#define LAYOUT( \
  k00, k01, \
  k10       \
) \
{ \
  { k00, k01 }, \
  { k10, KC_NO } \
}
