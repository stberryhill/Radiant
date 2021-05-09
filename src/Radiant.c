#include "Radiant.h"
#include "Internal.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t frameStartTime;

void Radiant_Initialize(uint16_t windowWidth, uint16_t windowHeight, bool fullscreen) {
  printf("initializing interactive...\n");

  Video_Initialize(windowWidth, windowHeight, fullscreen);
  Input_Initialize();
  pd_SetupEventQueueCallbacks();
  rEventQueue.numEvents = 0;
}

void Radiant_Quit() {
  Video_Deinitialize();
}
