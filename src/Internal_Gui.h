/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef RADIANT_INTERNAL_GUI_H
#define RADIANT_INTERNAL_GUI_H

#include "RadiantGUI.h"

static const float DEFAULT_SPACING = 10.0;
static const float DEFAULT_VERTICAL_ALIGNMENT = VERTICAL_ALIGN_CENTER;
static const float DEFAULT_HORIZONTAL_ALIGNMENT = HORIZONTAL_ALIGN_CENTER;

typedef struct {
  GUILayoutType layoutType;
  GUIHorizontalAlignment horizontalAlignment;
  GUIVerticalAlignment verticalAlignment;
  float spacing;
  float width;
  float height;
} GUILayout;

static void beginLayout();
static void endLayout();

static GUILayout* layouts;
static int layoutCount = 0;

void GUI_BeginLayoutVertical() {
  GUILayout layout = { LAYOUT_TYPE_VBOX, DEFAULT_HORIZONTAL_ALIGNMENT, DEFAULT_VERTICAL_ALIGNMENT, DEFAULT_SPACING, 0, 0 };
  beginLayout();
}

void GUI_BeginLayoutHorizontal() {
  GUILayout layout = { LAYOUT_TYPE_HBOX, DEFAULT_HORIZONTAL_ALIGNMENT, DEFAULT_VERTICAL_ALIGNMENT, DEFAULT_SPACING, 0, 0 };
  beginLayout();
}

void beginLayout() {
  layoutCount++;
}

void endLayout() {
  layoutCount--;

  if (layoutCount < 0) {
  }
}
#endif
