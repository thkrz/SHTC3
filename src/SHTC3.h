#ifndef _SHTC3_H
#define _SHTC3_H

class _SHTC3 {
  private:
    float _srh;
    float _st;
  public:
    bool begin();

    float getHumidity();
    float getTemperature();
    void readSample(bool clock_stretch = true, bool low_power = false, bool rh_first = false);

    bool ready();
    void reset();
    void sleep();
    void wakeup();
};

extern _SHTC3 SHTC3;

#endif /* _SHTC3_H */
