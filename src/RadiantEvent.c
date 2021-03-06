/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "Radiant.h"
#include "Internal.h"

#include <stdbool.h>
#include <stdio.h>

/* TODO: implement */
bool Event_MatchesButtonMapping(const RadiantEvent *event, const ButtonMapping *mapping) { return false; }

EventType Event_GetType(const RadiantEvent *event) {
  return event->type;
}

uint8_t Event_GetButtonState(const RadiantEvent *event) {
  return event->buttonState;
}

uint16_t Event_GetCode(const RadiantEvent *event) {
  return event->code;
}
