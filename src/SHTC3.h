#ifndef _SHTC3_H
#define _SHTC3_H

class SHTC3 {
  private:
    static float srh;
    static float st;
  public:
    static bool begin();

    static float getHumidity();
    static float getTemperature();
    static void readSample(bool clock_stretch = true, bool low_power = false, bool rh_first = false);

    static bool ready();
    static void reset();
    static void sleep();
    static void wakeup();
};

#endif /* _SHTC3_H */
