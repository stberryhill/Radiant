#include "Radiant.h"
#include "Internal.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

bool ButtonState_IsDown(uint8_t buttonState) {
  return buttonState & BUTTON_STATE_MASK_VALUE;
}
