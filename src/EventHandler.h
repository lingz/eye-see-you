#ifndef EVT_HANDLER
#define EVT_HANDLER

#include "circularArray.h"
#include "EventState.h"

class EventHandler{
    private:
        EventState pastSecondState;
        EventState state;
        CircularArray frames;

    public:
        EventHandler();
        void analyze(PupilsFrame&);

    private:
        void handleActive();
        void handleRedAlert();
        void handleTurnedLeft();
        void handleTurnedRight();
        void handleWaitingForLeftTurn();
        void handleWaitingForRightTurn();
        bool stateCheck(int, EventState);
        bool eyeCheck(int, bool, bool);
};

#endif
