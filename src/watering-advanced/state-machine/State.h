#ifndef STATE_H
#define STATE_H
//abstract class Sensor
class State
{
  public:
    //initialize the sensor
    inline virtual void begin(){/*nothing*/};
    //read function must be implemented
    //this is called a pure virtual function
    virtual int read() = 0;

  private:

};
#endif