/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _RADIANT_H
#define _RADIANT_H

#include "RadiantAPIMacro.h"
#include "RadiantMath.h"
#include "RadiantPhysics.h"
#include "RadiantTime.h"
#include "RadiantString.h"
#include <stdint.h>
#include <stdbool.h>

extern const uint8_t DEFAULT_NUM_BUTTONS;
typedef unsigned int uint;

#define MAX_ATTRIBUTE_NAME_SIZE 64

#define BUTTON_STATE_MASK_VALUE 0x7F      /* 0b01111111 */
#define BUTTON_STATE_MASK_TRANSITION 0x80 /* 0b10000000 */
#define BUTTON_STATE_BIT_TRANSITION 7     /* The transition bit is bit 7 */
#define RADIANT_MAX_EVENTS 64

/* Each button is associated with a single function which takes the button's state as input */
typedef void (*ButtonFunctionPointer)(uint8_t);

typedef enum {
  EVENT_TYPE_KEY,
  EVENT_TYPE_MOUSE,
  EVENT_TYPE_VIDEO_RESOLUTION_CHANGE,
  EVENT_TYPE_COUNT
} EventType;

/* input-related */
typedef struct RadiantEvent RadiantEvent;
typedef struct Buttons Buttons;
typedef struct RadiantEventQueue RadiantEventQueue;
typedef void (*KeyCallbackFunction)(int keyCode, int action);

/* Gpu/shader-related */
typedef struct GpuProgram GpuProgram;

typedef struct {
  char name[MAX_ATTRIBUTE_NAME_SIZE];
  uint gpuLocation;
} GpuAttributeBinding;


typedef struct {
  uint16_t buttonCode;
  uint16_t eventCode;
  EventType eventType;
} ButtonMapping;

/* 3d-mesh representation */
typedef struct AttributeArray AttributeArray;
typedef struct AttributeDescription AttributeDescription;
typedef struct IndexArray IndexArray;

#define I_ATTRIBUTE_VERTEX_SIZE 3
#define I_ATTRIBUTE_NORMAL_SIZE 3
#define I_ATTRIBUTE_COLOR_SIZE 4
#define I_ATTRIBUTE_TEXTURE_COORDINATE_SIZE 2

typedef enum TextureFilterType {
  TEXTURE_FILTER_NEAREST,
  TEXTURE_FILTER_LINEAR
} TextureFilterType;

typedef enum PixelFormatType {
  PIXEL_FORMAT_RGB8,
  PIXEL_FORMAT_RGBA8
} PixelFormatType;

typedef struct Texture Texture;

/* Input actions */
#define INPUT_ACTION_PRESS
#define INPUT_ACTION_RELEASE

/* Key codes */
#define INPUT_KEY_UP
#define INPUT_KEY_DOWN
#define INPUT_KEY_LEFT
#define INPUT_KEY_RIGHT
#define INPUT_KEY_ESCAPE
#define INPUT_KEY_ENTER
#define INPUT_KEY_SPACE
#define INPUT_KEY_TAB
#define INPUT_KEY_A
#define INPUT_KEY_B
#define INPUT_KEY_C
#define INPUT_KEY_D
#define INPUT_KEY_E
#define INPUT_KEY_F
#define INPUT_KEY_G
#define INPUT_KEY_H
#define INPUT_KEY_I
#define INPUT_KEY_J
#define INPUT_KEY_K
#define INPUT_KEY_L
#define INPUT_KEY_M
#define INPUT_KEY_N
#define INPUT_KEY_O
#define INPUT_KEY_P
#define INPUT_KEY_Q
#define INPUT_KEY_R
#define INPUT_KEY_S
#define INPUT_KEY_T
#define INPUT_KEY_U
#define INPUT_KEY_V
#define INPUT_KEY_W
#define INPUT_KEY_X
#define INPUT_KEY_Y
#define INPUT_KEY_Z
#define INPUT_KEY_0
#define INPUT_KEY_1
#define INPUT_KEY_2
#define INPUT_KEY_3
#define INPUT_KEY_4
#define INPUT_KEY_5
#define INPUT_KEY_6
#define INPUT_KEY_7
#define INPUT_KEY_8
#define INPUT_KEY_9

extern const uint8_t BUTTON_QUIT;

RADIANT_API void Radiant_Initialize(uint16_t windowWidth, uint16_t windowHeight, bool fullscreen);
RADIANT_API void Radiant_Quit();

/* User input functions */
RADIANT_API void Input_Initialize();
RADIANT_API void Input_SetMouseCallback();
RADIANT_API void Input_SetKeyCallback(KeyCallbackFunction callback);
RADIANT_API void Input_SetButtonMappings(ButtonMapping *mappings, int numMappings);
RADIANT_API RadiantEvent *Input_ReadNextEventInQueueUntilEmpty();
RADIANT_API bool Input_IsKeyDown(int keyCode);
RADIANT_API void Input_PollEvents();

/* Event functions */
RADIANT_API bool Event_MatchesButtonMapping(const RadiantEvent *event, const ButtonMapping *mapping);
RADIANT_API EventType Event_GetType(const RadiantEvent *event);
RADIANT_API uint8_t Event_GetButtonState(const RadiantEvent *event);
RADIANT_API uint16_t Event_GetCode(const RadiantEvent *event);

/* Video functions */
RADIANT_API void Video_Initialize(uint16_t width, uint16_t height, bool fullscreen);
RADIANT_API void Video_ChangeMode(uint16_t width, uint16_t height, bool fullscreen);
RADIANT_API void Video_GetResolution(uint *resolution);
RADIANT_API void Video_Deinitialize();
RADIANT_API void Video_ClearBuffer();
RADIANT_API void Video_SwapBuffer();
RADIANT_API void Video_LoadModelMatrix(float *mat4);
RADIANT_API void Video_LoadViewProjectionMatrix(float *mat4);

/* Gpu programs */
RADIANT_API GpuProgram *GpuProgram_Create(const char *vertexShaderSource, const char *fragmentShaderSource, const GpuAttributeBinding *attributeBindings, const uint numBindings);
RADIANT_API void GpuProgram_Destroy(GpuProgram *gpuProgram);
RADIANT_API void GpuProgram_Bind(GpuProgram *gpuProgram);
RADIANT_API void GpuProgram_BindAttributeArray(GpuProgram *gpuProgram, const uint gpuLocation, const char *nameInShader);
RADIANT_API void GpuProgram_SetMatrix4f(const uint matrixLocation, float *inputMatrix);
RADIANT_API void GpuProgram_SetVector2f(const uint vectorLocation, float *inputVector);
RADIANT_API void GpuProgram_SetVector3f(const uint vectorLocation, float *inputVector);
RADIANT_API void GpuProgram_SetVector4f(const uint vectorLocation, float *inputVector);
RADIANT_API void GpuProgram_SetVector2i(const uint intLocation, int *inputVector);
RADIANT_API void GpuProgram_SetInt(const uint intLocation, int inputInt);
RADIANT_API uint GpuProgram_GetParameterLocation(GpuProgram *program, const char *name);

/* Attribute arrays */
RADIANT_API AttributeArray *AttributeArray_Create(const float *data, const uint32_t size);
RADIANT_API void AttributeArray_Destroy(AttributeArray *input);
RADIANT_API void AttributeArray_Bind(AttributeArray *attributeArray);
RADIANT_API void AttributeArray_EnableAttributes(const uint *attributeLocations, const uint numAttributes);
RADIANT_API void AttributeArray_DescribeAttribute(const uint gpuLocation, const uint width, const uint stride, const uint offset);

/* Index arrays */
RADIANT_API IndexArray *IndexArray_Create(const uint *data, const uint32_t size);
RADIANT_API void IndexArray_Destroy(IndexArray *indexArray);
RADIANT_API void IndexArray_Bind(IndexArray *indexArray);
RADIANT_API void IndexArray_Render(IndexArray *indexArray);

/* Textures */
RADIANT_API Texture *Texture_CreateRgb(const uint8_t *rgb, const uint16_t width, const uint16_t height);
RADIANT_API Texture *Texture_CreateRgba(const uint8_t *rgba, const uint16_t width, const uint16_t height);
RADIANT_API void Texture_Delete(Texture *texture);
RADIANT_API void Texture_Bind(Texture *texture);
RADIANT_API void Texture_GetSize(Texture *texture, uint16_t *output);

/* Button functions */
RADIANT_API bool ButtonState_IsDown(uint8_t buttonState);

#endif
