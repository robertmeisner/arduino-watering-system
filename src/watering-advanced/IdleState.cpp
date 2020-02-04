#include "IdleState.h"
#include "CustomLog.h"
char* IdleState::getName(){
    return "IdleState";
}
bool IdleState::handleWatering() {}
bool IdleState::handleLighting() {}
bool IdleState::handleMoistureReading() {}
bool IdleState::handleIdle() {}
bool IdleState::init() {}
bool IdleState::tick() {}
bool IdleState::setContext() {}