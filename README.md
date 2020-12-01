# waterSensor

This little project automatically waters your Christmas tree for you.

## Sensor

To detect the water level, I used one of these depth sensors.  +/- are VCC and ground, and `S` is the output level, in analog (10 bits, so 1024 max).

<img src="waterLevelSensor.jpg" alt="water level sensor" width="200"/>

I ordered 10 of these, and all 10 are very different from each other.  So I put placeholders in the code to read the Low and High settings from the exact sensor you're using.  

## Pump

For a simple pump, I bought a [kit](https://smile.amazon.com/gp/product/B07TMVNTDK) that's normally used for watering plants.  This kit includes submersible pumps, tubing, and relays to switch the pump on and off.  

Hooking this up is straightforward.  The pump wires get attached to the "normally closed" (NC) pair on the output of the relay, and one pin drives whether the switch is open or closed, so I hook that up to the digital PWM output of the microcontroller.

## Microcontroller

I chose the [Arduino Nano Every](https://store.arduino.cc/usa/nano-every), mostly because it's small, cheap and has an LED on it that can signal different colors.

For fun, I also added a 16x2 LCD display, but that's not necessary by any means as you can mostly go by the LED.

## Code

There are tons of ways you could write the code, as it's very simple.  I chose to turn on the pump when the water level dropped to below the midpoint between Low and High, but that's completely arbitrary - you could choose to turn on water any time it's below the Low point, or the High point, or whatever.

To minimize power usage, I put the microcontroller to sleep for 10 seconds if everything is fine, then have it refresh more frequently while the pump is on.

## Bill of Materials

| Part | Cost Total | Cost each |
| ---- | ---------- | --------- |
| [Arduino Nano Every](https://smile.amazon.com/gp/product/B07YQ56B6Q) | $33.00 for 3 | $11.00 |
| [Water Level Sensor](https://smile.amazon.com/gp/product/B07THDH7Y4) | $6.19 for 10 | $0.62 |
| [Pump, Relays, Tubing](https://smile.amazon.com/gp/product/B07TMVNTDK) | $28.99 for 4 | $7.25 | 
| Total | $68.18 | $18.87 | 

So the total cost per unit is $18.87.  That's a bit higher than I expected.  It looks like a cost reduced version of the Nano Every can be had for about $5 in bulk, so that would save $6, but I like to support Arduino so I buy the name brand ones.  You might even have extra ones sitting around from previous projects (like I do now since I bought three).  

The pump and relays could also likely be had for cheaper, but I intend to reuse the parts for a plant watering system after Christmas, so I opted for the bigger set.

Good luck!  Let me know if you have any tips on improvements.
