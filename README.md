🚗 Hyundai HB20 (2018) SWC Controls
---
Interfacing the SWC on the HB20 (2018 model) with an ADS1115 breakout board. 
Circuit powered at 3.3V in my case.
Using A0 and default I2C address (pull ADDR to GND).

Can detect all 8 steering wheel controls (SWC) and is programmed to also recognize *holding* these buttons.
With that you should have 16 freely programmable buttons.

Due the nature of the HOLD detection, the short press only fires at *key-up* (the long press fires after 1 second still pressing it).

I used the ADS1115 with an 4.7K pullup resistor from A0 to 3.3V. This is the best resistor value for these particular SWCs. 
This was thoughtfully calculated using an Excel spreadsheet with these exact SWC resistor values (attached).
Other resistor values might increase the chances of false detection.
The "distance" between ADC values when measuring the SWC are the furthest apart with a 4.7K resistor.

Also, if you can, try to power the ADS1115 from the 3.3V supply from your ESP or Arduino, since this rail should have less noise than the 5V coming directly from your step-down or 5V supply. 
16-Bit is extremely succeptible to noise, so let's try our best.

****Setup****
> 4.7k resistor between 3.3V and A0
>
> ADDR goes to GND
>
> SWC white goes to A0
>
> SWC black goes to GND
>
> I2C goes to ESP or Arduino

Be noted that this code isn't beautiful by any means, but it does the job more than fine. 

I also tried to use as little ressources as possible. 
If you find a bug and your cat 🐈 catches fire due to this, blame me on the Issues page.