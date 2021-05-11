/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "Radiant.h"
#include "Internal.h"
#include "Internal_KeyDefines.h"
#include "Internal_Opengl.h"
#include <stdio.h>
#include <GLFW/glfw3.h>

/* Todo: Remove, or keep for possible future use? */
void Input_Initialize() {
    /* Do nothing */
}

static void glfwKeyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != GLFW_REPEAT) {
        RadiantEvent event;
        event.type = EVENT_TYPE_KEY;
        event.code = key;
        event.buttonState = action;
        EventQueue_AddEvent(&event);
    }
}

void pd_SetupEventQueueCallbacks() {
    glfwSetKeyCallback(Video_GetWin(), glfwKeyCallbackWrapper);
}

bool Input_IsKeyDown(int keyCode) {
    return glfwGetKey(Video_GetWin(), keyCode) != 0 ? true : false;
}

void Input_PollEvents() {
  glfwPollEvents();
}
