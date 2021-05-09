#include "Radiant.h"
#include "Internal.h"

#include <stdbool.h>
#include <stdio.h>

static uint8_t queuePosition = 0;

RadiantEvent *Input_ReadNextEventInQueueUntilEmpty() {
  RadiantEvent *event = 0;

  if (queuePosition < rEventQueue.numEvents) {
    event = &rEventQueue.events[queuePosition];
    queuePosition++;
  } else {
    queuePosition = 0;
    rEventQueue.numEvents = 0;
  }

  return event;
}

/* TODO: implement */
bool Event_MatchesButtonMapping(const RadiantEvent *event, const ButtonMapping *mapping) { return false; }

EventType Event_GetType(const RadiantEvent *event) {
  return event->type;
}

uint8_t Event_GetButtonState(const RadiantEvent *event) {
  return event->buttonState;
}

uint16_t Event_GetCode(const RadiantEvent *event) {
  return event->code;
}
