#ifndef _SHTC3_H
#define _SHTC3_H

class SHTC3 {
  private:
    int clock_stretch;
    int rh_first;
    int low_power;
    float srh;
    float st;
  public:
    static const uint16_t INVALID = 0xFFFF;

    bool begin();

    float getHumidity();
    float getTemperature();
    void readSample();

    bool ready();
    void reset();
    void sleep();
    void wakeup();
};

#endif /* _SHTC3_H */
