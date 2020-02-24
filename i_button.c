#include "interactive.h"
#include <lang/types.h>
#include <stdio.h>

int  i_button_register(IButtonFunctionPointer functionPointer) {
  printf("slotting into %u\n", iButtons.nextAvailableButton);
  iButtons.functionPointers[iButtons.nextAvailableButton] = functionPointer;
  return iButtons.nextAvailableButton++;
}

void i_button_delete(uint16 buttonId) {
 /* TODO: clean up after button, release id back into the wild */
}

void i_button_sendPressEvent(uint16 buttonId) {
  /* WARNING - will cause bug if too many buttons assigned to same thing all pressed at the same time (128) */
  uint8 transition = (iButtons.states[buttonId] & I_BUTTON_STATE_MASK_VALUE) == 0;

  iButtons.states[buttonId] = (iButtons.states[buttonId] & I_BUTTON_STATE_MASK_VALUE) + 1; /* Increase button value by 1 and clear transition bit*/
  iButtons.states[buttonId] |= transition << I_BUTTON_STATE_BIT_TRANSITION;

  iEventQueue.events[iEventQueue.numEvents].type = I_EVENT_BUTTON;
  iEventQueue.events[iEventQueue.numEvents].buttonState = iButtons.states[buttonId];
  iEventQueue.events[iEventQueue.numEvents].code = buttonId; 
  iEventQueue.numEvents++;
}

void i_button_sendReleaseEvent(uint16 buttonId) {
  /* Only a transition if this release causes value to go to 0 (so when value = 1) */
  uint8 transition = (iButtons.states[buttonId] & I_BUTTON_STATE_MASK_VALUE) == 1;

  iButtons.states[buttonId] = (iButtons.states[buttonId] & I_BUTTON_STATE_MASK_VALUE) - 1; /* Increase button value by 1 and clear transition bit*/
  iButtons.states[buttonId] |= transition << I_BUTTON_STATE_BIT_TRANSITION;

  iEventQueue.events[iEventQueue.numEvents].type = I_EVENT_BUTTON;
  iEventQueue.events[iEventQueue.numEvents].buttonState = iButtons.states[buttonId];
  iEventQueue.events[iEventQueue.numEvents].code = buttonId; 
  iEventQueue.numEvents++;
}

void i_button_quit(uint8 buttonState) {
  if ( (buttonState & I_BUTTON_STATE_MASK_VALUE) && (buttonState & I_BUTTON_STATE_MASK_TRANSITION) ) {
    i_quit();
  }
}
