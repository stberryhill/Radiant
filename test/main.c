#include <stdio.h>
#include <stdlib.h>
#include <interactive/interactive.h>
#include <unistd.h>

int i, j;
IAttributeArray *quadVertices;
IAttributeArray *quadTextureCoordinates;
IAttributeArray *quadColors;
IAttributeArray *quadNormals;
IIndexArray *quadIndices;
IGeometry *geometry;

static const float QUAD_VERTEX_DATA[] = {
  -1.0f, 1.0f, 0.0f,
  1.0f, 1.0f, 0.0f,
  1.0f, -1.0f, 0.0f,
  -1.0f, -1.0f, 0.0f
};

static const float QUAD_TEXTURE_COORDINATE_DATA[] = {
  0.0f, 0.0f,
  1.0f, 0.0f,
  1.0f, 1.0f,
  0.0f, 1.0f
};

static const float QUAD_COLOR_DATA[] = {
  1.0f, 0.0f, 0.0f, 1.0f,
  1.0f, 1.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 0.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 1.0f
};

static const float QUAD_NORMAL_DATA[] = {
  0.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 0.0f
};

static const uint QUAD_INDEX_DATA[] = {
  0, 3, 2,
  2, 1, 0
};

void testButton(uint8 buttonState) {
  /* printf("value = %u, transition = %u\n", buttonState & I_BUTTON_STATE_MASK_VALUE, buttonState & I_BUTTON_STATE_MASK_TRANSITION); */
  if ((buttonState & I_BUTTON_STATE_MASK_VALUE)) {

    if (buttonState & I_BUTTON_STATE_MASK_TRANSITION) {
      printf("down %d\n", i + 1);
      i++;
    }

  } else {

    if (buttonState & I_BUTTON_STATE_MASK_TRANSITION) {
      printf("up %d\n", j + 1);
      j++;
    }

  }
}

void createGraphicsResources() {
  quadVertices = i_attribute_array_create(QUAD_VERTEX_DATA, sizeof(QUAD_VERTEX_DATA) / sizeof(QUAD_VERTEX_DATA[0]));
  quadTextureCoordinates = i_attribute_array_create(QUAD_TEXTURE_COORDINATE_DATA, sizeof(QUAD_TEXTURE_COORDINATE_DATA) / sizeof(QUAD_TEXTURE_COORDINATE_DATA[0]));
  quadColors = i_attribute_array_create(QUAD_COLOR_DATA, sizeof(QUAD_COLOR_DATA) / sizeof(QUAD_COLOR_DATA[0]));
  quadNormals = i_attribute_array_create(QUAD_NORMAL_DATA, sizeof(QUAD_NORMAL_DATA) / sizeof(QUAD_NORMAL_DATA[0]));

  quadIndices = i_index_array_create(QUAD_INDEX_DATA, sizeof(QUAD_INDEX_DATA) / sizeof(QUAD_INDEX_DATA[0]));

  geometry = i_geometry_create(6);
  i_geometry_loadColorArray(geometry, quadColors);
  i_geometry_loadVertexArray(geometry, quadVertices);
  i_geometry_loadTextureCoordinateArray(geometry, quadTextureCoordinates);
  i_geometry_loadNormalArray(geometry, quadNormals);
  i_geometry_loadIndexArray(geometry, quadIndices);
}

void destroyGraphicsResources() {
  i_attribute_array_destroy(quadVertices);
  i_attribute_array_destroy(quadTextureCoordinates);
  i_attribute_array_destroy(quadColors);
  i_attribute_array_destroy(quadNormals);
  i_index_array_destroy(quadIndices);
  i_geometry_destroy(geometry);
}

int main() {
  i = 0;
  j = 0;
  i_initialize(800, 600, false);
  createGraphicsResources();

  int testButtonId = -1;
  testButtonId = i_button_register(testButton);

  printf("buttonId = %d\n", testButtonId);

  i_button_sendPressEvent(testButtonId);
  i_button_sendPressEvent(testButtonId);
  i_button_sendPressEvent(testButtonId);
  i_button_sendReleaseEvent(testButtonId);
  i_button_sendReleaseEvent(testButtonId);
  i_button_sendReleaseEvent(testButtonId);

  printf("calling handleEventQueue...");
  i_handleEventQueue();
  printf("Ok\n");

  //i_button_delete(testButtonId);
  i_video_clearBuffer();

  i_geometry_bind(geometry);
  i_geometry_render(geometry);

  i_video_swapBuffer();
  i_pollEvents();

  sleep(1);
  destroyGraphicsResources();

  i_quit();
  return 0;
}
