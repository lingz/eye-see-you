#include "opencv2/imgproc/imgproc.hpp"
#include "EventHandler.h"
#include "EventState.h"
#include "circularArray.h"
#include "PupilsFrame.h"
#include <iostream>

EventHandler::EventHandler(){
    frames = CircularArray();
}

void EventHandler::analyze(PupilsFrame& frame){
    frames.addData(frame);
    switch(state){
        case RED_ALERT:
            handleRedAlert();
            break;
        case WAITING_FOR_LEFT_TURN:
            handleWaitingForLeftTurn();
            break;
        case WAITING_FOR_RIGHT_TURN:
            handleWaitingForRightTurn();
            break;
        case TURNED_LEFT:
            handleTurnedLeft();
            break;
        case TURNED_RIGHT:
            handleTurnedRight();
            break;
        case WINK_LEFT:
            handleWinkLeft();
            break;
        case WINK_RIGHT:
            handleWinkRight();
            break;
        case DEACTIVATE:
            handleDeactivate();
            break;
        case IDLE:
            handleIdle();
            break;
        default:
            handleActive();
    }
    frames.getFrameAt(0).state = state;
}

void EventHandler::handleActive(){
    if(eyeCheck(5, false, false)){
        std::cout << "1" << std::endl;
        state = RED_ALERT;
    }

    // begin scanning for left turn
    else if(!frames.getFrameAt(0).hasLeftPupil && frames.getFrameAt(0).rightPupilAbsX > 10){
        state = TURNED_LEFT;
    }
    else if(!frames.getFrameAt(0).hasLeftPupil && (frames.getFrameAt(0).rightPupilAbsX > 15 || frames.getFrameAt(0).rightPupilAbsY > 15)){
        state = WINK_LEFT;
    }

    // begin scanning for right turn
    else if(!frames.getFrameAt(0).hasRightPupil && frames.getFrameAt(0).leftPupilAbsX > 10){
        state = TURNED_RIGHT;
    }
    else if(!frames.getFrameAt(0).hasRightPupil && (frames.getFrameAt(0).leftPupilAbsX > 15 || frames.getFrameAt(0).leftPupilAbsY > 15)){
        state = WINK_RIGHT;
    }  
    frames.getFrameAt(0).state = state;
}

void EventHandler::handleRedAlert(){
    if(eyeCheck(5, true, true)){
        std::cout << "2" << std::endl;
        state = ACTIVE;
    }
}

void EventHandler::handleWaitingForLeftTurn(){
    if(eyeCheck(5, false, true)){
        std::cout << "7" << std::endl;
        state = ACTIVE;
    }

    else if(eyeCheck(15, true, true)){
        //reset
        state = ACTIVE;    
    }
}

void EventHandler::handleWaitingForRightTurn(){
    if(eyeCheck(5, true, false)){
        std::cout << "7" << std::endl;
        state = ACTIVE;
    }

    else if(eyeCheck(15, true, true)){
        //reset
        state = ACTIVE;
    }
}

void EventHandler::handleTurnedLeft(){
    if(eyeCheck(10, true, true)){
        state = WAITING_FOR_RIGHT_TURN;
    }
    else if(eyeCheck(10, false, true)){
        std::cout << "3" << std::endl;
        state = DEACTIVATE;
    }
    else if(eyeCheck(5, false, false)){
        std::cout << "1" << std::endl;
        state = RED_ALERT;
    }
}

void EventHandler::handleTurnedRight(){

    if(eyeCheck(10, true, true)){
        state = WAITING_FOR_LEFT_TURN;
    }    
    else if(eyeCheck(10, true, false)){
        std::cout << "4" << std::endl;
        state = DEACTIVATE;
    }
    else if(eyeCheck(5, false, false)){
        std::cout << "1" << std::endl;
        state = RED_ALERT;
    }
}

void EventHandler::handleWinkLeft(){
    std::cout << "6" << std::endl;
    state = DEACTIVATE;
}

void EventHandler::handleWinkRight(){
    std::cout << "6" << std::endl;
    state = DEACTIVATE;
}

void EventHandler::handleDeactivate(){
    state = IDLE;
}

void EventHandler::handleIdle(){
    if(frames.getFrameAt(15).state == DEACTIVATE){
        state = ACTIVE;
    }
}

// Scans the previous n frames. Return true if the majority were queryState, false otherwise.
bool EventHandler::stateCheck(int n, EventState queryState){
    int stateCount = 0;
    for(int i = 0; i < n; i++){
        if(frames.getFrameAt(i).state == queryState){
            stateCount++;
        }
    }
    return (stateCount/(double)n > 0.6);
}

// Scans the previous n frames. Return true if the majority were queryState, false otherwise.
bool EventHandler::eyeCheck(int n, bool leftEye, bool rightEye){
    int count = 0;
    for(int i = 0; i < n; i++){
        if(frames.getFrameAt(i).hasLeftPupil == leftEye && frames.getFrameAt(i).hasRightPupil == rightEye){
            count++;
        }
    }
    return (count/(double)n > 0.6);
}
