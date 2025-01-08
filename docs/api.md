# SHTC3 Library

## Methods

### `begin()`

Resets the sensor in a well-defined state, verifies the presence of the
sensor and proper communication, and puts it to sleep. begin() should be called once before
readSample().

#### Syntax

``` arduino
SHTC3.begin()
```

### `readSample()`

Reads humidity and temperature values.

#### Syntax

``` arduino
SHTC3.readSample(bool clock_stretch = true, bool low_power = false, bool rh_first = false)
```

#### Parameters

- clock_stretch: set colck stretch.
- low_power: set low power mode.
- rh_first: sample relative humidity first.

### `getTemperature()`

Get the temperature value. This is only a valid value if called after readSample().

#### Syntax

``` arduino
SHTC3.getTemperature()
```

#### Return
the temperature value.

### `getHumidity()`

Get the humidity value. This is only a valid value if called after readSample().

#### Syntax

``` arduino
float hum = SHTC3.getHumidity()
```

#### Return
the humidity value.

