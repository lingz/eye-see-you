#ifndef EVT_STATE
#define EVT_STATE
enum EventState{
    ACTIVE,
    RED_ALERT,
    TURNED_LEFT,
    TURNED_RIGHT,
    WINK_LEFT,
    WINK_RIGHT,
    WAITING_FOR_LEFT_TURN,
    WAITING_FOR_RIGHT_TURN,
    DEACTIVATE,
    IDLE
};
#endif
