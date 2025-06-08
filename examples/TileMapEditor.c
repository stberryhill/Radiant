#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <Radiant.h>

static const char *vertSource = "#version 120\n"
"attribute vec3 vertXyz;\n"
"attribute vec4 colorRgba;\n"
"attribute vec3 normalIjk;\n"
"attribute vec2 textureCoordUv;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"
"varying vec4 fragColor;\n"
"void main()\n"
"{\n"
"  fragColor = colorRgba;\n"
"  gl_Position = (projection*view*model) * vec4(vertXyz, 1.0);\n"
"}\n";

static const char *fragSource = "#version 120\n"
"varying vec4 fragColor;\n"
"void main()\n"
"{\n"
" gl_FragColor = fragColor;\n"
"}\n";

static const uint16_t WIDTH = 800;
static const uint16_t HEIGHT = 600;
static const bool FULLSCREEN = false;
static bool running;
int i, j;
int modelMatLoc, viewMatLoc, projMatLoc;
AttributeArray *quadAttributes;
IndexArray *quadIndices;
GpuProgram *gpuProgram;
Texture *texture;

void quitButton(uint8_t buttonState) {
  if (ButtonState_IsDown(buttonState)) {
    running = false;
  }
}

/*

void ui() {
  GUI_BeginLayoutVertical();
  GUI_Text("Hello, world!");
  if (GUI_Button("Quit")) {
    running = false;
  }
  GUI_EndLayout();
}
*/

int main() {
/* t_Start(); */
  i = 0;
  j = 0;
  Radiant_Initialize(WIDTH, HEIGHT, FULLSCREEN);

  float view[16];
  Matrix4f_Identity(view);

  float projection[16] = {0};
  Matrix4f_PerspectiveProjection(90.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f, projection);
  printf("Projection mat:\n%s\n", Matrix4f_ToString(projection));

/*   t_Tick(); */
  /*printf("Initialization time: %f\n", t_SecondsSinceLastTick());*/

  running = true;
  
  unsigned int enableAttributes[] = {1, 2, 3, 4};
  
  double currentTime = System_TimeSeconds();
  double accumulator = 0.0;
  double dt = 0.01;
  double t = 0.0;
  float alpha;
  float centerA[2], centerB[2];

  while (running) {
    double newTime = System_TimeSeconds();
    double frameTime = newTime - currentTime;
    if (frameTime > 0.25) {
      frameTime = 0.25;
    }

    currentTime = newTime;
    accumulator += frameTime;

    while (accumulator >= dt) {
      t += dt;
      accumulator -= dt;
    }
    
    alpha = accumulator / dt;

    Video_ClearBuffer();

    GpuProgram_Bind(gpuProgram);
    GpuProgram_SetMatrix4f(viewMatLoc, view);
    GpuProgram_SetMatrix4f(projMatLoc, projection);

    AttributeArray_Bind(quadAttributes);
    AttributeArray_EnableAttributes(enableAttributes, 4);
    IndexArray_Bind(quadIndices);
  
    Matrix4f_Translation(vec, translation);
    Matrix4f_Multiply(translation, rotation, tr);
    Matrix4f_Multiply(tr, scale, model);
    GpuProgram_SetMatrix4f(modelMatLoc, model);
    IndexArray_Render(quadIndices);

    Video_SwapBuffer();
    Input_PollEvents();

    printf("t: %f\n", t);
    fflush(stdout);
    if (t >= 5.0) {
      running = false;
    }

/*     i_HandleEventQueue() */;
    while ((System_TimeSeconds() - newTime) < 1.0/60.0) {

    }
/*     printf("FPS: %d\n", t_Fps());
    printf("milli: %li\n", t_MillisecondsSinceLastTick());
    t_Tick(); */
  }

  destroyGraphicsResources();
  Radiant_Quit();

  return 0;
}
