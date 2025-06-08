#include <stdio.h>
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
int modelMatLoc, viewMatLoc, projMatLoc;
PhysicsMaterial *physicsMaterial1;
PhysicsMaterial *physicsMaterial2;

int i, j;
AttributeArray *quadAttributes;
IndexArray *quadIndices;

GpuProgram *gpuProgram;

const GpuAttributeBinding attributeBindings[] = {{"vertXyz", 0}, {"textureCoordUv", 1}, {"colorRgba", 2}, {"normalIjk", 3}};

static const float QUAD_ATTRIBUTE_DATA[] = {
  /*vertices*/
  -1.0f, 1.0f, 0.0f,
  1.0f, 1.0f, 0.0f,
  1.0f, -1.0f, 0.0f,
  -1.0f, -1.0f, 0.0f,

  /*uv*/
  0.0f, 0.0f,
  1.0f, 0.0f,
  1.0f, 1.0f,
  0.0f, 1.0f,

  /*colors*/
  1.0f, 0.0f, 0.0f, 1.0f,
  1.0f, 1.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 0.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 1.0f,

  /*normals*/
  0.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 0.0f
};

static const unsigned int QUAD_INDEX_DATA[] = {
  0, 3, 2,
  2, 1, 0
};

void quitButton(uint8_t buttonState) {
  if (ButtonState_IsDown(buttonState)) {
    running = false;
  }
}

void createGraphicsResources() {
  const char *vertexSource = vertSource;
  const char *fragmentSource = fragSource;

  gpuProgram = GpuProgram_Create(vertexSource, fragmentSource, attributeBindings, sizeof(attributeBindings) / sizeof(attributeBindings[0]));

  modelMatLoc = GpuProgram_GetParameterLocation(gpuProgram, "model");
  viewMatLoc = GpuProgram_GetParameterLocation(gpuProgram, "view");
  projMatLoc = GpuProgram_GetParameterLocation(gpuProgram, "projection");

  quadAttributes = AttributeArray_Create(QUAD_ATTRIBUTE_DATA, sizeof(QUAD_ATTRIBUTE_DATA) / sizeof(QUAD_ATTRIBUTE_DATA[0]));
  /* Warnning: May need to do this again when switching to different attribute array */
  AttributeArray_Bind(quadAttributes);
  AttributeArray_DescribeAttribute(0, 3, 0, 0);
  AttributeArray_DescribeAttribute(1, 2, 0, 12);
  AttributeArray_DescribeAttribute(2, 4, 0, 20);
  AttributeArray_DescribeAttribute(3, 3, 0, 36);

  printf("numIndices calc: %lu\n", sizeof(QUAD_INDEX_DATA) / sizeof(QUAD_INDEX_DATA[0]));
  quadIndices = IndexArray_Create(QUAD_INDEX_DATA, sizeof(QUAD_INDEX_DATA) / sizeof(QUAD_INDEX_DATA[0]));
}

void destroyGraphicsResources() {
  GpuProgram_Destroy(gpuProgram);

  AttributeArray_Destroy(quadAttributes);
  IndexArray_Destroy(quadIndices);
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
  Physics_Initialize();

  createGraphicsResources();

  physicsMaterial1 = PhysicsMaterial_Create("light", 0.1, 0.9);
  physicsMaterial2 = PhysicsMaterial_Create("immovable", 10.0, 0.5);

  float vel[2] = {1.5, 0.05};
  float center[2] = {1.25, -0.5};
  float size[2] = {0.1, 0.1};
  float theta = 0.0;
  float accel[2] = {0.0, -0.98};
  center[0] = -0.5;
  center[1] = 0.75;
  BBox2D *boxA = Physics_AddBBox2D(BBOX_TYPE_AXIS_ALIGNED, physicsMaterial1, center, size, theta);
  BBox2D_setVelocity(boxA, vel);
  BBox2D_setAcceleration(boxA, accel);
  center[0] = 0.8;
  center[1] = 0.35;
  BBox2D *boxB = Physics_AddBBox2D(BBOX_TYPE_AXIS_ALIGNED, physicsMaterial2, center, size, theta);
  vel[0] = -0.0;
  vel[1] = -0.03;

  float rotation[16], translation[16], scale[16];
  float vec[3] = {0.0, 0.0, 0.0};

  Matrix4f_Rotation(vec, rotation);
  printf("Rotation mat:\n%s", Matrix4f_ToString(rotation));

  BBox2D_getSize(boxA, vec);
  vec[2] = 1.0;
  Matrix4f_Scale(vec, scale);
  printf("Scale mat:\n%s", Matrix4f_ToString(scale));

  vec[0] = 0.0;
  vec[1] = 0.0;
  vec[2] = -1.0;
  Matrix4f_Translation(vec, translation);
  printf("Translation mat:\n%s", Matrix4f_ToString(translation));

  float model[16];
  float tr[16];

  Matrix4f_Multiply(translation, rotation, tr);
  Matrix4f_Multiply(tr, scale, model);

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
  BBox2D_getCenter(boxA, centerA);
  BBox2D_getCenter(boxB, centerB);

  while (running) {
    double newTime = System_TimeSeconds();
    double frameTime = newTime - currentTime;
    if (frameTime > 0.25) {
      frameTime = 0.25;
    }

    currentTime = newTime;
    accumulator += frameTime;

    while (accumulator >= dt) {
      Physics_Update(t, dt);
      t += dt;
      accumulator -= dt;
      /* printf("sim time: %f\n", t); */
    }
    
    alpha = accumulator / dt;

    Video_ClearBuffer();

    GpuProgram_Bind(gpuProgram);
    GpuProgram_SetMatrix4f(viewMatLoc, view);
    GpuProgram_SetMatrix4f(projMatLoc, projection);

    AttributeArray_Bind(quadAttributes);
    AttributeArray_EnableAttributes(enableAttributes, 4);
    IndexArray_Bind(quadIndices);
  
    BBox2D_getCenter(boxA, vec);
    Vector2f_Scale(vec, alpha, vec);
    Vector2f_Scale(centerA, (1.0 - alpha), centerA);
    Vector2f_Add(vec, centerA, vec);
  
    BBox2D_getCenter(boxA, centerA);
    Matrix4f_Translation(vec, translation);
    Matrix4f_Multiply(translation, rotation, tr);
    Matrix4f_Multiply(tr, scale, model);
    GpuProgram_SetMatrix4f(modelMatLoc, model);
    IndexArray_Render(quadIndices);

    BBox2D_getCenter(boxB, vec);
    Vector2f_Scale(vec, alpha, vec);
    Vector2f_Scale(centerB, (1.0-alpha), centerB);
    Vector2f_Add(vec, centerB, vec);
    BBox2D_getCenter(boxB, centerB);
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

    /* printf("boxA address: %d", boxA); */

  destroyGraphicsResources();
  Physics_Quit();
  Radiant_Quit();

  return 0;
}
