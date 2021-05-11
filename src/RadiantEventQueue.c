
#include "Radiant.h"
#include "Internal.h"

#include <stdio.h>

static RadiantEventQueue eventQueue;
static uint8_t queuePosition = 0;

RadiantEvent *Input_ReadNextEventInQueueUntilEmpty() {
  RadiantEvent *event = 0;

  if (queuePosition < eventQueue.numEvents) {
    event = &eventQueue.events[queuePosition];
    queuePosition++;
  } else {
    queuePosition = 0;
    eventQueue.numEvents = 0;
  }

  return event;
}

void EventQueue_Initialize() {
  eventQueue.numEvents = 0;
}

void EventQueue_AddEvent(const RadiantEvent *event) {
  if (eventQueue.numEvents < RADIANT_MAX_EVENTS) {
    eventQueue.events[eventQueue.numEvents] = *event;
    eventQueue.numEvents++;
  } else {
    printf("EventQueue error - can't add any more events, reached max size.\n");
  }
}