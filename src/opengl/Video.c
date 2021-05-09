#include "Radiant.h"
#include "Internal.h"
#include "Internal_Opengl.h"

#include <stdint.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

static uint videoResolution[2];

static void sendVideoResolutionChangeEvent(int width, int height) {
  rEventQueue.events[rEventQueue.numEvents].type = EVENT_TYPE_VIDEO_RESOLUTION_CHANGE;
  rEventQueue.numEvents++;
}

void Video_Initialize(uint16_t width, uint16_t height, bool fullscreen) {
  /*    glfwSetErrorCallback(onError);*/
  if ( !glfwInit() ) {
    printf("Error - couldn't initialize GLFW. Exiting...");
    exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  win = glfwCreateWindow(width, height, "Made with Interactive",
      (fullscreen ? glfwGetPrimaryMonitor() : NULL), NULL);
  if (!win)
  {
    printf("glfwCreateWindow error: opengl 2.0 may not be supported by your computer\n");
    exit(-1);
  }

  glfwMakeContextCurrent(win);
  glViewport(0, 0, width, height);

  videoResolution[0] = width;
  videoResolution[1] = height;
}

void Video_ChangeMode(uint16_t width, uint16_t height, bool fullscreen) {

  if (fullscreen) {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *nativeMode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(win, monitor, 0, 0, width, height, nativeMode->refreshRate);
  } else {
    const int UNUSED = 0;
    glfwSetWindowMonitor(win, NULL, 0, 0, width, height, UNUSED);
  }

  videoResolution[0] = width;
  videoResolution[1] = height;

  rEventQueue.events[rEventQueue.numEvents].type = EVENT_TYPE_VIDEO_RESOLUTION_CHANGE;
  rEventQueue.numEvents++;
}

void Video_GetResolution(uint *resolution) {
  resolution[0] = videoResolution[0];
  resolution[1] = videoResolution[1];
}

void Video_Deinitialize() {
  glfwDestroyWindow(win);
  glfwTerminate();
}

void Video_ClearBuffer() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Video_SwapBuffer() {
  glfwSwapBuffers(win);
}

/*void i_geometry_bind(IGeometry *geometry) {*/
  /*const IAttributeArray *vertexArray = geometry->vertexArray;*/
   /*const IAttributeArray *colorArray = geometry->colorArray;*/
   /*const IAttributeArray *normalArray = geometry->normalArray;*/
   /*const IAttributeArray *textureCoordinateArray = geometry->textureCoordinateArray;*/
   /*const IndexArray *indexArray = geometry->indexArray;*/

   /*glBindBuffer(GL_ARRAY_BUFFER, vertexArray->id);*/
   /*TODO: Maybe constant locations could be enforced and used to simplify and speed this up */
   /*glVertexAttribPointer(rBoundGpuProgram.vertexAttributeLocation, ATTRIBUTE_VERTEX_SIZE, GL_FLOAT, GL_FALSE, 0, NULL);*/

   /*glBindBuffer(GL_ARRAY_BUFFER, colorArray->id);*/
   /*glVertexAttribPointer(rBoundGpuProgram.colorAttributeLocation, I_ATTRIBUTE_COLOR_SIZE, GL_FLOAT, GL_FALSE,  0, NULL);*/

   /*glBindBuffer(GL_ARRAY_BUFFER, normalArray->id);*/
   /*glVertexAttribPointer(rBoundGpuProgram.normalAttributeLocation, ATTRIBUTE_NORMAL_SIZE, GL_FLOAT, GL_FALSE, 0, NULL);*/

   /*glBindBuffer(GL_ARRAY_BUFFER, textureCoordinateArray->id);*/
   /*glVertexAttribPointer(rBoundGpuProgram.textureCoordinateAttributeLocation, I_ATTRIBUTE_TEXTURE_COORDINATE_SIZE, GL_FLOAT, GL_FALSE, 0, NULL);*/

  /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArray->id);*/
 /*}*/

/* attribute arrays */
AttributeArray *AttributeArray_Create(const float *data, const uint32_t size) {
  AttributeArray *arr = malloc(sizeof *arr);
  
  glGenBuffers(1, &arr->id);
  glBindBuffer(GL_ARRAY_BUFFER, arr->id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(*data) * size, data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return arr;
}

void AttributeArray_Destroy(AttributeArray *input) {
  glDeleteBuffers(1, &input->id);
  free(input);
}

void AttributeArray_Bind(AttributeArray *attributeArray) {
  glBindBuffer(GL_ARRAY_BUFFER, attributeArray->id);
}

void AttributeArray_EnableAttributes(const uint *attributeLocations, const uint numAttributes) {
  uint i;
  for (i = 0; i < numAttributes; i++) {
    glEnableVertexAttribArray(attributeLocations[i]);
  }
}

void AttributeArray_DescribeAttribute(const uint gpuLocation, const uint width, const uint stride, const uint offset) {
  glVertexAttribPointer( gpuLocation, width, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (const GLvoid *)(offset * sizeof(GLfloat)) );
  glEnableVertexAttribArray(gpuLocation);

}

IndexArray *IndexArray_Create(const uint *data, const uint32_t size) {
  IndexArray *arr = malloc(sizeof *arr);
  arr->size = size;
  glGenBuffers(1, &arr->id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arr->id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*data) * size, data, GL_STATIC_DRAW);

  return arr;
}

void IndexArray_Destroy(IndexArray *indexArray) {
  glDeleteBuffers(1, &indexArray->id);
  free(indexArray);
}
void IndexArray_Bind(IndexArray *indexArray) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArray->id);
}
void IndexArray_Render(IndexArray *indexArray) {
  glDrawElements(GL_TRIANGLES, indexArray->size, GL_UNSIGNED_INT, (void*)0);
}

Texture *Texture_CreateRgb(const uint8_t *rgb, const uint16_t width, const uint16_t height) {
  Texture *tex = malloc(sizeof *tex);

  glGenTextures(1, &tex->id);
  glBindTexture(GL_TEXTURE_2D, tex->id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, rgb);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);

  tex->width = width;
  tex->height = height;

  return tex;
}

Texture *Texture_CreateRgba(const uint8_t *rgba, const uint16_t width, const uint16_t height) {
  Texture *tex = malloc(sizeof *tex);

  glGenTextures(1, &tex->id);
  glBindTexture(GL_TEXTURE_2D, tex->id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, rgba);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);

  tex->width = width;
  tex->height = height;

  return tex;
}

void Texture_Delete(Texture *texture) {
  glDeleteTextures(1, &texture->id);
  free(texture);
}

void Texture_Bind(Texture *texture) {
  glBindTexture(GL_TEXTURE_2D, texture->id);
}

void Texture_GetSize(Texture *texture, uint16_t *output) {
  output[0] = texture->width;
  output[1] = texture->height;
}
