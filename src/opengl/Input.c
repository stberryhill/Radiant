#include "Radiant.h"
#include "Internal.h"
#include "InternalOpengl.h"
#include <stdio.h>
#include <GLFW/glfw3.h>

void Input_Initialize() {
    INPUT_ACTION_PRESS = GLFW_PRESS;
    INPUT_ACTION_RELEASE = GLFW_RELEASE;
    INPUT_KEY_UP = GLFW_KEY_UP;
    INPUT_KEY_DOWN = GLFW_KEY_DOWN;
    INPUT_KEY_LEFT = GLFW_KEY_LEFT;
    INPUT_KEY_RIGHT = GLFW_KEY_RIGHT;
    INPUT_KEY_ESCAPE = GLFW_KEY_ESCAPE;
    INPUT_KEY_ENTER = GLFW_KEY_ENTER;
    INPUT_KEY_SPACE = GLFW_KEY_SPACE;
    INPUT_KEY_TAB = GLFW_KEY_TAB;
    INPUT_KEY_A = GLFW_KEY_A;
    INPUT_KEY_B = GLFW_KEY_B;
    INPUT_KEY_C = GLFW_KEY_C;
    INPUT_KEY_D = GLFW_KEY_D;
    INPUT_KEY_E = GLFW_KEY_E;
    INPUT_KEY_F = GLFW_KEY_F;
    INPUT_KEY_G = GLFW_KEY_G;
    INPUT_KEY_H = GLFW_KEY_H;
    INPUT_KEY_I = GLFW_KEY_I;
    INPUT_KEY_J = GLFW_KEY_J;
    INPUT_KEY_K = GLFW_KEY_K;
    INPUT_KEY_L = GLFW_KEY_L;
    INPUT_KEY_M = GLFW_KEY_M;
    INPUT_KEY_N = GLFW_KEY_N;
    INPUT_KEY_O = GLFW_KEY_O;
    INPUT_KEY_P = GLFW_KEY_P;
    INPUT_KEY_Q = GLFW_KEY_Q;
    INPUT_KEY_R = GLFW_KEY_R;
    INPUT_KEY_S = GLFW_KEY_S;
    INPUT_KEY_T = GLFW_KEY_T;
    INPUT_KEY_U = GLFW_KEY_U;
    INPUT_KEY_V = GLFW_KEY_V;
    INPUT_KEY_W = GLFW_KEY_W;
    INPUT_KEY_X = GLFW_KEY_X;
    INPUT_KEY_Y = GLFW_KEY_Y;
    INPUT_KEY_Z = GLFW_KEY_Z;
    INPUT_KEY_0 = GLFW_KEY_0;
    INPUT_KEY_1 = GLFW_KEY_1;
    INPUT_KEY_2 = GLFW_KEY_2;
    INPUT_KEY_3 = GLFW_KEY_3;
    INPUT_KEY_4 = GLFW_KEY_4;
    INPUT_KEY_5 = GLFW_KEY_5;
    INPUT_KEY_6 = GLFW_KEY_6;
    INPUT_KEY_7 = GLFW_KEY_7;
    INPUT_KEY_8 = GLFW_KEY_8;
    INPUT_KEY_9 = GLFW_KEY_9;
}

static void glfwKeyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (iEventQueue.numEvents < INPUT_MAX_EVENTS && action != GLFW_REPEAT) {
        iEventQueue.events[iEventQueue.numEvents].type = INPUT_EVENT_KEY;
        iEventQueue.events[iEventQueue.numEvents].code = key;
        iEventQueue.events[iEventQueue.numEvents].buttonState = action;
        iEventQueue.numEvents++;
    } else {
        printf("Error - too many events for queue. Dropping key event...");
    }
}

void pd_SetupEventQueueCallbacks() {
    glfwSetKeyCallback(win, glfwKeyCallbackWrapper);
}

bool Input_IsKeyDown(int keyCode) {
    return glfwGetKey(win, keyCode) != 0 ? true : false;
}

void Input_PollEvents() {
  glfwPollEvents();
}
