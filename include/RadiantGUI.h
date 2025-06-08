#ifndef _RADIANT_GUI_H
#define _RADIANT_GUI_H

#include "Radiant.h"
#include "RadiantAPIMacro.h"

#include <stdbool.h>

typedef struct {
  void (*setGpuParametersBeforeRendering)(GpuProgram *program);
  GpuProgram *program;
} GUIRenderInstructions;

typedef struct {
  GUIRenderInstructions *textRenderInstructions;
  GUIRenderInstructions *buttonRenderInstructions;
} GUIRenderSettings;

typedef enum {
  HORIZONTAL_ALIGN_LEFT,
  HORIZONTAL_ALIGN_RIGHT,
  HORIZONTAL_ALIGN_CENTER,
  HORIZONTAL_ALIGN_COUNT,
} GUIHorizontalAlignment;

typedef enum {
  VERTICAL_ALIGN_TOP,
  VERTICAL_ALIGN_BOTTOM,
  VERTICAL_ALIGN_CENTER,
  VERTICAL_ALIGN_COUNT,
} GUIVerticalAlignment;

typedef enum {
  LAYOUT_TYPE_HBOX,
  LAYOUT_TYPE_VBOX,
  LAYOUT_TYPE_COUNT,
} GUILayoutType;

RADIANT_API void GUI_BeginLayoutVertical();
RADIANT_API void GUI_BeginLayoutHorizontal();
RADIANT_API void GUI_EndLayout();
RADIANT_API void GUI_UseRenderSettings(GUIRenderSettings *renderSettings);
RADIANT_API void GUI_Text(const char *text);
RADIANT_API bool GUI_Button(const char *text);

#endif
