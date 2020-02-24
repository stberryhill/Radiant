#include "interactive.h"
#include <lang/types.h>
#include <stdio.h>

/* Should probably be called every frame but maybe could go 
 * a few frames to spread out the handling */
void i_handleEventQueue() {
  IEvent *event;
  for (event = iEventQueue.events; event < &iEventQueue.events[iEventQueue.numEvents]; event++) {
    switch (event->type) {
      case I_EVENT_BUTTON:
        iButtons.functionPointers[event->code](event->buttonState);
        break;
      case I_EVENT_MOUSE:
        printf("Error - mouse events not yet supported.\n");
        break;
      case I_EVENT_VIDEO_RESOLUTION_CHANGE:
        printf("Error - video resolution change event not yet supported.\n");
        break;
      default:
        printf("Error - faulty event type.\n");
        break;
    }
  }
  iEventQueue.numEvents = 0;
}
