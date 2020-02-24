#include "interactive.h"
#include <lang/types.h>
#include <GLFW/glfw3.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <stdio.h>

static GLFWwindow *win;

static void sendVideoResolutionChangeEvent(int width, int height) {
  iEventQueue.events[iEventQueue.numEvents].type = I_EVENT_VIDEO_RESOLUTION_CHANGE;
  iEventQueue.numEvents++;
}

void i_video_initialize(uint16 width, uint16 height, bool fullscreen) {
  /*    glfwSetErrorCallback(onError);*/
  if ( !glfwInit() ) {
    /*        Services::getLogger()->fatal("glfwInit error: failed to initialize glfw library\n"); */
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
}

void i_video_changeMode(uint16 width, uint16 height, bool fullscreen) {

  if (fullscreen) {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *nativeMode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(win, monitor, 0, 0, width, height, nativeMode->refreshRate);
  } else {
    const int UNUSED = 0;
    glfwSetWindowMonitor(win, NULL, 0, 0, width, height, UNUSED);
  }

  iEventQueue.events[iEventQueue.numEvents].type = I_EVENT_VIDEO_RESOLUTION_CHANGE;
  iEventQueue.numEvents++;
}

void i_video_deinitialize() {
  glfwDestroyWindow(win);
  glfwTerminate();
}

void i_video_clearBuffer() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void i_video_swapBuffer() {
  glfwSwapBuffers(win);
}

/*void i_geometry_bind(IGeometry *geometry) {*/
  /*const IAttributeArray *vertexArray = geometry->vertexArray;*/
   /*const IAttributeArray *colorArray = geometry->colorArray;*/
   /*const IAttributeArray *normalArray = geometry->normalArray;*/
   /*const IAttributeArray *textureCoordinateArray = geometry->textureCoordinateArray;*/
   /*const IIndexArray *indexArray = geometry->indexArray;*/

   /*glBindBuffer(GL_ARRAY_BUFFER, vertexArray->id);*/
   /*TODO: Maybe constant locations could be enforced and used to simplify and speed this up */
   /*glVertexAttribPointer(iBoundGpuProgram.vertexAttributeLocation, I_ATTRIBUTE_VERTEX_SIZE, GL_FLOAT, GL_FALSE, 0, NULL);*/

   /*glBindBuffer(GL_ARRAY_BUFFER, colorArray->id);*/
   /*glVertexAttribPointer(iBoundGpuProgram.colorAttributeLocation, I_ATTRIBUTE_COLOR_SIZE, GL_FLOAT, GL_FALSE,  0, NULL);*/

   /*glBindBuffer(GL_ARRAY_BUFFER, normalArray->id);*/
   /*glVertexAttribPointer(iBoundGpuProgram.normalAttributeLocation, I_ATTRIBUTE_NORMAL_SIZE, GL_FLOAT, GL_FALSE, 0, NULL);*/

   /*glBindBuffer(GL_ARRAY_BUFFER, textureCoordinateArray->id);*/
   /*glVertexAttribPointer(iBoundGpuProgram.textureCoordinateAttributeLocation, I_ATTRIBUTE_TEXTURE_COORDINATE_SIZE, GL_FLOAT, GL_FALSE, 0, NULL);*/

  /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArray->id);*/
 /*}*/

/* attribute arrays */
IAttributeArray *i_attribute_array_create(const float *data, const uint32 size) {
  IAttributeArray *arr = malloc(sizeof *arr);
  
  glGenBuffers(1, &arr->id);
  glBindBuffer(GL_ARRAY_BUFFER, arr->id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(*data) * size, data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return arr;
}

void i_attribute_array_destroy(IAttributeArray *input) {
  glDeleteBuffers(1, &input->id);
  free(input);
}

void i_attribute_array_bind(IAttributeArray *attributeArray) {
  glBindBuffer(GL_ARRAY_BUFFER, attributeArray->id);
}

void i_attribute_array_enableAttributes(const uint *attributeLocations, const uint numAttributes) {
  uint i;
  for (i = 0; i < numAttributes; i++) {
    glEnableVertexAttribArray(attributeLocations[i]);
  }
}

void i_attribute_array_describeAttribute(const uint gpuLocation, const uint width, const uint stride, const uint offset) {
  glVertexAttribPointer( gpuLocation, width, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (const GLvoid *)(offset * sizeof(GLfloat)) );
  glEnableVertexAttribArray(gpuLocation);

}

IIndexArray *i_index_array_create(const uint *data, const uint32 size) {
  IIndexArray *arr = malloc(sizeof *arr);
  arr->size = size;
  glGenBuffers(1, &arr->id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arr->id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*data) * size, data, GL_STATIC_DRAW);

  return arr;
}

void i_index_array_destroy(IIndexArray *indexArray) {
  glDeleteBuffers(1, &indexArray->id);
  free(indexArray);
}
void i_index_array_bind(IIndexArray *indexArray) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArray->id);
}
void i_index_array_render(IIndexArray *indexArray) {
  glDrawElements(GL_TRIANGLES, indexArray->size, GL_UNSIGNED_INT, (void*)0);
}

ITexture *i_texture_createRgb(const uint8 *rgb, const uint16 width, const uint16 height) {
  ITexture *tex = malloc(sizeof *tex);

  glGenTextures(1, &tex->id);
  glBindTexture(GL_TEXTURE_2D, tex->id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, rgb);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);

  return tex;
}

ITexture *i_texture_createRgba(const uint8 *rgba, const uint16 width, const uint16 height) {
  ITexture *tex = malloc(sizeof *tex);

  glGenTextures(1, &tex->id);
  glBindTexture(GL_TEXTURE_2D, tex->id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, rgba);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);

  return tex;
}

void i_texture_delete(ITexture *texture) {
  glDeleteTextures(1, &texture->id);
  free(texture);
}

void i_texture_bind(ITexture *texture) {
  glBindTexture(GL_TEXTURE_2D, texture->id);
}
