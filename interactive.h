#ifndef _TYLER_INTERACTIVE_H
#define _TYLER_INTERACTIVE_H

#include <lang/types.h>

extern const uint8 DEFAULT_NUM_BUTTONS;

#define I_MAX_ATTRIBUTE_NAME_SIZE 64

#define I_BUTTON_STATE_MASK_VALUE 0x7F      /* 0b01111111 */
#define I_BUTTON_STATE_MASK_TRANSITION 0x80 /* 0b10000000 */
#define I_BUTTON_STATE_BIT_TRANSITION 7     /* The transition bit is bit 7 */
#define I_MAX_EVENTS 64

typedef enum {
  I_EVENT_BUTTON,
  I_EVENT_MOUSE,
  I_EVENT_VIDEO_RESOLUTION_CHANGE,
  I_EVENT_COUNT
} IEventType;

typedef struct {
  IEventType type;
  uint8 buttonState;
  uint16 code;
  int mouseMovement;
} IEvent;

/* Each button is associated with a single function which takes the button's state as input */
typedef void (*IButtonFunctionPointer)(uint8);

/* TODO: implement mapping between key and button - simple 1d array (will need to make key codes indices to the array) */
typedef struct {
  uint8 *states;
  IButtonFunctionPointer *functionPointers;
  uint16 numButtons;
  uint16 nextAvailableButton;
} IButtons;

typedef struct {
  IEvent events[I_MAX_EVENTS];
  uint8 numEvents;
} IEventQueue;

typedef struct IGpuProgram {
  uint programId;
  uint vertexShaderId;
  uint fragmentShaderId;
} IGpuProgram;

typedef struct IGpuAttributeBinding {
  char name[I_MAX_ATTRIBUTE_NAME_SIZE];
  uint gpuLocation;
} IGpuAttributeBinding;

typedef struct {
  uint id;
  uint32 size;
  float *data;
} IAttributeArray;

typedef struct IAttributeDescription {
  uint gpuLocation;
  uint width;
  uint offset;
} IAttributeDescription;

typedef struct {
  uint id;
  uint32 size;
  uint *data;
} IIndexArray;

#define I_ATTRIBUTE_VERTEX_SIZE 3
#define I_ATTRIBUTE_NORMAL_SIZE 3
#define I_ATTRIBUTE_COLOR_SIZE 4
#define I_ATTRIBUTE_TEXTURE_COORDINATE_SIZE 2

typedef enum {
  I_TEXTURE_FILTER_NEAREST,
  I_TEXTURE_FILTER_LINEAR
} ITextureFilterType;

typedef enum {
  RGB8,
  RGBA8
} IPixelFormatType;

typedef struct {
  uint id; 
} ITexture;

IButtons iButtons;
IEventQueue iEventQueue;
IGpuProgram iBoundGpuProgram;

/* Key codes */
extern char I_KEY_UP;
extern char I_KEY_DOWN;
extern char I_KEY_LEFT;
extern char I_KEY_RIGHT;
extern char I_KEY_ENTER;
extern char I_KEY_SPACE;
extern char I_KEY_TAB;

/* Mouse codes */
extern char I_MOUSE_BUTTON_LEFT;
extern char I_MOUSE_BUTTON_RIGHT;
extern char I_MOUSE_WHEEL;

extern const uint8 I_BUTTON_QUIT;

void i_initialize(uint16 windowWidth, uint16 windowHeight, bool fullscreen);
void i_quit();

/* User input functions */
void i_setMouseCallback();
void i_handleEventQueue();
void i_pollEvents();

/* Video functions */
void i_video_initialize(uint16 width, uint16 height, bool fullscreen);
void i_video_changeMode(uint16 width, uint16 height, bool fullscreen);
void i_video_deinitialize();
void i_video_clearBuffer();
void i_video_swapBuffer();
void i_video_loadModelMatrix(float *input);
void i_video_loadViewProjectionMatrix(float *input);

/* Gpu programs */
IGpuProgram *i_gpu_program_create(const char *vertexShaderSource, const char *fragmentShaderSource, const IGpuAttributeBinding *attributeBindings, const uint numBindings);
void i_gpu_program_destroy(IGpuProgram *gpuProgram);
void i_gpu_program_bind(IGpuProgram *gpuProgram);
void i_gpu_program_bindAttributeArray(IGpuProgram *gpuProgram, const uint gpuLocation, const char *nameInShader);
void i_gpu_program_setMatrix4f(const uint matrixLocation, float *inputMatrix);
void i_gpu_program_setVector2f(const uint vectorLocation, float *inputVector);
void i_gpu_program_setVector3f(const uint vectorLocation, float *inputVector);
void i_gpu_program_setVector4f(const uint vectorLocation, float *inputVector);
uint i_gpu_program_getParameterLocation(IGpuProgram *program, const char *name);

/* Attribute arrays */
IAttributeArray *i_attribute_array_create(const float *data, const uint32 size);
void i_attribute_array_destroy(IAttributeArray *input);
void i_attribute_array_bind(IAttributeArray *attributeArray);
void i_attribute_array_enableAttributes(const uint *attributeLocations, const uint numAttributes);
void i_attribute_array_describeAttribute(const uint gpuLocation, const uint width, const uint stride, const uint offset);

/* Index arrays */
IIndexArray *i_index_array_create(const uint *data, const uint32 size);
void i_index_array_destroy(IIndexArray *indexArray);
void i_index_array_bind(IIndexArray *indexArray);
void i_index_array_render(IIndexArray *indexArray);

/* Textures */
ITexture *i_texture_createRgb(const uint8 *rgb, const uint16 width, const uint16 height);
ITexture *i_texture_createRgba(const uint8 *rgba, const uint16 width, const uint16 height);
void i_texture_delete(ITexture *texture);
void i_texture_bind(ITexture *texture);

/* Button functions */
int  i_button_register(IButtonFunctionPointer functionPointer);
void i_button_delete(uint16 buttonId);
void i_button_sendPressEvent(uint16 buttonId);
void i_button_sendReleaseEvent(uint16 buttonId);
void i_button_quit(uint8 buttonState);

#endif
