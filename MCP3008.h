#include "esphome.h"
#include "MCP3XXX.h"

class MyTempSensor : public PollingComponent, public Sensor {
 public:
  // constructor
  MyTempSensor() : PollingComponent(1000) {}
  
  MCP3008 adc;
  int R1 = 10000;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

  void setup() override {
    // This will be called by App.setup()
    adc.begin();
  }
  void update() override {
    // This will be called every "update_interval" milliseconds.
    float Vo = adc.analogRead(0);
    float R2 = R1 * (1023.0 / (float)Vo - 1.0);
    float logR2 = log(R2);
    float T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)) - 273.15;

    publish_state(T);
  }
};
