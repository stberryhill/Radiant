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
    if (rEventQueue.numEvents < RADIANT_MAX_EVENTS && action != GLFW_REPEAT) {
        rEventQueue.events[rEventQueue.numEvents].type = EVENT_TYPE_KEY;
        rEventQueue.events[rEventQueue.numEvents].code = key;
        rEventQueue.events[rEventQueue.numEvents].buttonState = action;
        rEventQueue.numEvents++;
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
