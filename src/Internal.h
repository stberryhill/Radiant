/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _INTERACTIVE_INTERNAL_H
#define _INTERACTIVE_INTERNAL_H

#include "Radiant.h"

/* platform-dependent functions */
void pd_SetupEventQueueCallbacks();

struct RadiantEvent {
  EventType type;
  uint8_t buttonState;  /* button represents key or joystick button */
  uint16_t code;
  int movement;       /* represents mouse or joystick movement */
};

struct RadiantEventQueue {
  RadiantEvent events[RADIANT_MAX_EVENTS];
  uint8_t numEvents;
};

struct GpuProgram {
  uint programId;
  uint vertexShaderId;
  uint fragmentShaderId;
};

struct AttributeArray {
  uint id;
  uint32_t size;
  float *data;
};

struct IndexArray {
  uint id;
  uint32_t size;
  uint *data;
};

struct Texture {
  uint id; 
  uint16_t width;
  uint16_t height;
};


void EventQueue_AddEvent(const RadiantEvent *event);
void EventQueue_Initialize();

#endif
