/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "Radiant.h"
#include "Internal.h"

#include <stdint.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

static GpuProgram rBoundGpuProgram;

static uint sizeOfShaderSource(const char *shaderSource) {
  int count = 0;

  while (shaderSource[count] != EOF && shaderSource[count] != '\0') {
    count++;
  }

  return count;
}

static void printShaderLog(const uint shaderId) {
  GLint maxLength = 0;
  glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

  if(maxLength > 0) {
    GLchar log[maxLength];
    glGetShaderInfoLog(shaderId, maxLength, &maxLength, &log[0]);
    printf("%s", log);
  }
}

static void createShader(uint *shaderId, const char *shaderSource, const uint shaderGlType) {
  *shaderId = glCreateShader(shaderGlType);
  if(*shaderId == 0) {
    printf("Error - shader with source... \"\n%s\n\" ... could not be created.\n", shaderSource);
    exit(-1);
  }

  /* Parameters: shader id, num shader sources, sources, size of sources */
  const GLchar *source[1] = {shaderSource};
  const GLint size[1] = {sizeOfShaderSource(shaderSource)};
  glShaderSource(*shaderId, 1, source, size);
  glCompileShader(*shaderId);

  GLint isCompiled = 0;
  glGetShaderiv(*shaderId, GL_COMPILE_STATUS, &isCompiled);
  if(isCompiled == GL_FALSE) {
    printf("Error - shader with source... \"\n%s\n\" ... could not be created.\n", shaderSource);
    printShaderLog(*shaderId);
    exit(-1);
  }
}

static void destroyShader(const uint shaderId) {
  glDeleteShader(shaderId);
}


GpuProgram *GpuProgram_Create(const char *vertexShaderSource, const char *fragmentShaderSource, const GpuAttributeBinding *attributeBindings, const uint numBindings) {
  GpuProgram *gpuProgram = malloc(sizeof *gpuProgram);
  gpuProgram->programId = glCreateProgram();
  if (!gpuProgram->programId) {
    printf("Error - couldn't create opengl gpu program.");
    exit(-1);
  }

  createShader(&gpuProgram->vertexShaderId, vertexShaderSource, GL_VERTEX_SHADER);
  createShader(&gpuProgram->fragmentShaderId, fragmentShaderSource, GL_FRAGMENT_SHADER);

  glAttachShader(gpuProgram->programId, gpuProgram->vertexShaderId);
  glAttachShader(gpuProgram->programId, gpuProgram->fragmentShaderId);

  GLint programIsLinked = 0;
  glLinkProgram(gpuProgram->programId);
  glGetProgramiv(gpuProgram->programId, GL_LINK_STATUS, &programIsLinked);

  if (programIsLinked == GL_FALSE) {
    printf("Error - opengl gpu program failed to link... \nvertex source:\n\"%s\"\nfragment source:\n\"%s\"\n", vertexShaderSource, fragmentShaderSource);
    exit(-1);
  }
  
  /* Explicitly bind attribute locations */
  uint i;
  for (i = 0; i < numBindings; i++) {
    glBindAttribLocation(gpuProgram->programId, attributeBindings[i].gpuLocation, attributeBindings[i].name);
    printf("binding %d: %s\n", attributeBindings[i].gpuLocation, attributeBindings[i].name);
  }
  
  glLinkProgram(gpuProgram->programId); /* Attribute bindings do not go into effect until glLinkProgram is called */

  return gpuProgram;
}

void GpuProgram_Destroy(GpuProgram *gpuProgram) {
  glDetachShader(gpuProgram->programId, gpuProgram->vertexShaderId);
  glDetachShader(gpuProgram->programId, gpuProgram->fragmentShaderId);
  destroyShader(gpuProgram->vertexShaderId);
  destroyShader(gpuProgram->fragmentShaderId);
  glDeleteProgram(gpuProgram->programId);
  /* TODO: do you have to unlink? */
  free(gpuProgram);
}

void GpuProgram_Bind(GpuProgram *gpuProgram) {
  glUseProgram(gpuProgram->programId);
  rBoundGpuProgram = *gpuProgram;
}

void GpuProgram_SetMatrix4f(const uint matrixLocation, float *inputMatrix) {
  glUniformMatrix4fv(matrixLocation, 1, GL_TRUE, inputMatrix);
}

void GpuProgram_SetVector2f(const uint vectorLocation, float *inputVector) {
  glUniform2fv(vectorLocation, 1, inputVector);
}

void GpuProgram_SetVector3f(const uint vectorLocation, float *inputVector) {
  glUniform3fv(vectorLocation, 1, inputVector);
}

void GpuProgram_SetVector4f(const uint vectorLocation, float *inputVector) {
  glUniform4fv(vectorLocation, 1, inputVector);
}

void GpuProgram_SetVector2i(const uint intLocation, int *inputVector) {
  glUniform2iv(intLocation, 1, inputVector);
}

void GpuProgram_SetInt(const uint intLocation, int inputInt) {
  glUniform1i(intLocation, inputInt);
}

uint GpuProgram_GetParameterLocation(GpuProgram *program, const char *name) {
  return glGetUniformLocation(program->programId, name);
}
