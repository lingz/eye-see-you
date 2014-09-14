#include "opencv2/imgproc/imgproc.hpp"
#include "EventHandler.h"
#include "EventState.h"
#include "circularArray.h"
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
    else if(eyeCheck(15, false, true)){
        state = TURNED_LEFT;
    }

    // begin scanning for right turn
    else if(eyeCheck(15, true, false)){
        state = TURNED_RIGHT;
    }
    frames.getFrameAt(0).state = state;
}

void EventHandler::handleRedAlert(){
    if(eyeCheck(5, true, true)){
        std::cout << "1" << std::endl;
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
    if(eyeCheck(15, false, true)){
        std::cout << "3" << std::endl;
        state = ACTIVE;
    }
    else if(eyeCheck(5, false, false)){
        std::cout << "1" << std::endl;
        state = RED_ALERT;
    }
    else if(eyeCheck(5, true, true)){
        state = WAITING_FOR_RIGHT_TURN;
    }
}

void EventHandler::handleTurnedRight(){
    if(eyeCheck(15, true, false)){
        std::cout << "4" << std::endl;
        state = ACTIVE;
    }
    else if(eyeCheck(5, false, false)){
        std::cout << "1" << std::endl;
        state = RED_ALERT;
    }
    else if(eyeCheck(5, true, true)){
        state = WAITING_FOR_LEFT_TURN;
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
