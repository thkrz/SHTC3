# SHTC3 Library

## Methods

### `begin()`

Resets the sensor in a well-defined state, verifies the presence of the
sensor and proper communication, and puts it to sleep. begin() should be called before
readSample().

#### Syntax

``` arduino
SHTC3.begin()
```

### `readSample(bool clock_stretch = true, bool low_power = false, bool rh_first = false)`


#### Syntax

``` arduino
SHTC3.readSample(low_power = true)
```

### `getTemperature()`

Resets the sensor in a well-defined state, verifies the presence of the
sensor and proper communication, and puts it to sleep. begin() should be called before
readSample().

#### Syntax

``` arduino
float temp = SHTC3.getTemperature()
```

### `getHumidity()`

Resets the sensor in a well-defined state, verifies the presence of the
sensor and proper communication, and puts it to sleep. begin() should be called before
readSample().

#### Syntax

``` arduino
float hum = SHTC3.getHumidity()
```

