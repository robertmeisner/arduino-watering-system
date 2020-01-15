
#ifndef W_M_STATE_BASE_H
#define W_M_STATE_BASE_H
class WateringMachineStateBase
{
public:
    // Class destructor for WateringMachineStateBase (Declared as virtual)

    ~WateringMachineStateBase() {}
    bool handleWatering() {}
    bool handleLighting() {}
    bool handleMoistureReading() {}
    bool init(){}
    bool tick(){}
    bool setContext(){}
private:
};
#endif