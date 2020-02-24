#include "interactive.h"
#include <lang/types.h>
#include <stdio.h>
#include <stdlib.h>

const uint8 DEFAULT_NUM_BUTTONS = 16;
const uint8 I_BUTTON_QUIT = 0;

uint64 frameStartTime;

void i_initialize(uint16 windowWidth, uint16 windowHeight, bool fullscreen) {
  printf("initializing interactive...\n");

  iEventQueue.numEvents = 0;

  iButtons.states = malloc((sizeof *iButtons.states) * DEFAULT_NUM_BUTTONS);

  uint8 i;
  for(i = 0; i < DEFAULT_NUM_BUTTONS; i++) {
    iButtons.states[i] = 0; /* No butons down or transitioning to start */
  }

  iButtons.functionPointers = malloc(sizeof (IButtonFunctionPointer) * DEFAULT_NUM_BUTTONS);
  iButtons.numButtons = DEFAULT_NUM_BUTTONS;

  iButtons.functionPointers[0] = i_button_quit;
  iButtons.nextAvailableButton++;

  i_video_initialize(windowWidth, windowHeight, fullscreen);
}

void i_quit() {
  free(iButtons.states);
  /* This assumes malloc will never be used to allocate a function pointer itself, only the array as a whole. */
  free(iButtons.functionPointers);
  i_video_deinitialize();
}
