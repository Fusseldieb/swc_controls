#include "ADS1X15.h"

ADS1115 ADS(0x48); // Default address

void setup()
{
  Serial.begin(115200);

  ADS.begin();
  ADS.setGain(1); // Up to 4V approx.
}

byte pressed_key = 0;                             // Stores the button pressed, 1-8
uint16_t key_occur[9] = {0, 0, 0, 0, 0, 0, 0, 0}; // Stores occurences key 1-8
byte valid_loop = 0;                              // When button is pressed, increases until the button is valid

// Used for debouncing. Counts the occurrences of all 8 keys as long as they are pressed down
// The key which appears the MOST in the array will get selected
// Should be pretty reliable
byte getBiggestKey()
{

  uint16_t max_v = 0;
  uint16_t max_i = 0;

  for (int i = 0; i < 9; i++)
  {
    if (key_occur[i] > max_v)
    {
      max_v = key_occur[i];
      max_i = i;
    }
  }

  return max_i;
}

byte ReadSWC()
{
  int16_t val = ADS.readADC(0); // Read channel A0

  if (val > 13200 && val < 13300)
  {
    // Serial.println("VOL +");
    pressed_key = 1;
  }
  else if (val > 15730 && val < 15850)
  {
    // Serial.println("VOL -");
    pressed_key = 2;
  }
  else if (val > 10600 && val < 10700)
  {
    // Serial.println("MUTE");
    pressed_key = 3;
  }
  else if (val > 2200 && val < 2300)
  {
    // Serial.println("UP /\\");
    pressed_key = 4;
  }
  else if (val > 5100 && val < 6800)
  {
    // Serial.println("DOWN \\/");
    pressed_key = 5;
  }
  else if (val > 8200 && val < 8600)
  {
    // Serial.println("MODE");
    pressed_key = 6;
  }
  else if (val > 23750 && val < 23900)
  {
    // Serial.println("ACCEPT");
    pressed_key = 7;
  }
  else if (val > 21200 && val < 21350)
  {
    // Serial.println("DECLINE");
    pressed_key = 8;
  }

  else
  {
    if (val > 26000)
    {

      // Loops required to make the pressed button valid - Debouncing
      // > and < are there to only fire it once without requiring a new (bool) variable
      byte temp_return = 0;
      if (valid_loop > 6 && valid_loop < 60)
      {
        //Serial.println(getBiggestKey());
        temp_return = getBiggestKey();
      }

      pressed_key = 0;
      valid_loop = 0;
      for (byte i = 0; i < 9; i++)
      {
        key_occur[i] = 0;
      }
      return temp_return;
    }
  }

  if (pressed_key > 0)
  {
    key_occur[pressed_key]++;
    valid_loop++;

    if (valid_loop >= 60 && valid_loop < 61)
    {
      // Holding
      //Serial.println(getBiggestKey() + 8);
      return getBiggestKey() + 8;
    }
  }
  return 0;
}

void loop()
{
  byte key = ReadSWC();
  if (key)
  {
    Serial.println(key);
  }
}