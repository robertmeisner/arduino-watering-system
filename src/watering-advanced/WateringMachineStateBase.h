
#ifndef W_M_STATE_BASE_H
#define W_M_STATE_BASE_H
class WateringMachine;
class WateringMachineStateBase
{
public:
    WateringMachineStateBase(WateringMachine& wm);
    // Class destructor for WateringMachineStateBase (Declared as virtual)
     ~WateringMachineStateBase() {}
    virtual bool handleWatering() ;
    virtual bool handleLighting() ;
    virtual bool handleMoistureReading() ;
    virtual bool init() ;
    virtual bool tick() ;
    virtual bool setContext() ;

protected:
  WateringMachine &context;
};
#endif