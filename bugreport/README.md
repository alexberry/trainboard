# Display corruption on P4 (16S 32x64) Display - pixeltime

Hi there. I've been having somewhat of an issue with using PxMatrix with a P4 display. I have got the point where I can reliably cause the code to work on a 1/8 Scan 16x32 display, but if I move the cables to the larger display and just reconfigure the code for 32x64 it simply doesn't work properly.

## Videos

### Pixeltime

I have recorded the resultant issue and have [uploaded it to youtube here](https://www.youtube.com/watch?v=kKVjqLSDeao).In the video I reset the esp immediately and then wait until it scrolls to the icon / colour-block test.

### Pattern_test

I have also recorded the patter_test and uploaded it [here](https://www.youtube.com/watch?v=oXgAmYN9Rmg). From the video, things look ok, however I have noticed that it is not symmetrical - there are 7 rows below the bottom line and 8 rows above the top line, suggesting an alignment issue perhaps?

## Code differences

Below are the diffs of the two files I used when switching from 8S to 16S:

```C++
50,51c50,51
< #define matrix_width 32
< #define matrix_height 16
---
> #define matrix_width 64
> #define matrix_height 32
57,58c57,58
< PxMATRIX display(32,16,P_LAT, P_OE,P_A,P_B,P_C);
< //PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);
---
> //PxMATRIX display(32,16,P_LAT, P_OE,P_A,P_B,P_C);
> PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);
135c135
<   display.begin(8);
---
>   display.begin(16);
```

## Source

And here they are on github:

### Pixeltime
[1/8 Scan 16x32 pixeltime](https://github.com/alexberry/trainboard/blob/master/examples/pixeltime-32x64/pixeltime-32x64.ino)

[1/16 Scan 32x64 pixeltime](https://github.com/alexberry/trainboard/blob/master/examples/pixeltime-32x64/pixeltime-32x64.ino)

### Pattern_test
[1/16 Scan 16x32 pattern_test](https://github.com/alexberry/trainboard/blob/master/examples/pattern_test-16x32/pattern_test-16x32.ino)

[1/16 Scan 32x64 pattern_test](https://github.com/alexberry/trainboard/blob/master/examples/pattern_test-32x64/pattern_test-32x64.ino)

## Library Versions

Here's a list of all libraries & software I've been using:

Library | Version
--- | ---
PXMatrix (2nd attempt)| [No tag - f1fa1bf](https://github.com/2dom/PxMatrix/commit/f1fa1bfce4ccf04c6a086f48208e602e0d4a01e4)
PXMatrix (1st attempt) | [v1.7.0](https://github.com/2dom/PxMatrix/tree/v1.7.0)
Ticker | Built-in / 1.0.0
ESP8266 Board Manager | [2.6.3](https://github.com/esp8266/Arduino/releases/tag/2.6.3)
Arduino IDE | 1.8.5

## Wiring

I made sure wiring was identical, with the addition of connecting D for 1/16 Scan rate. I also attempted to connect not-in-use E to ground on arduino, to no good effect. The display has been powered by both a USB -> Barrel power supply and a dedicated 10A 5v power supply, neither solution made a difference.

I have made my own wiring table for this, viewable [here](https://github.com/alexberry/trainboard#wiring-guide)

Also, here's a photo:

![wiring](https://github.com/alexberry/trainboard/bugreport/image/wiring.jpg).

## Hardware

This has been tested with 3 different ESP8266 chips and 2 identical RGB panels, all present the same issue.

## Troubleshooting

I have made efforts to follow [your troubleshooting guide](https://github.com/2dom/PxMatrix#troubleshooting) and have double-checked:

* Grounding unused A,B,C,D,E pins (namely E in this instance)
* Testing different multiplex patterns (LINE, ZIGZAG,ZZAGG, ZAGGIZ, WZAGZIG, VZAG, ZAGZIG)
* Disabling setFastUpdate
* Attempting to slow it down with setMuxDelay
* Testing alternative drivers with setDriverChip
* Continuity tested all cabling
* Tested using patterntest.ino - _this actually appears to work as expected_.
* Pared-down to a simple [helloworld](https://github.com/alexberry/trainboard/blob/master/examples/helloworld-32x64/helloworld-32x64.ino) version of the code, confirmed as working at 8S and still not at 16S

All to no avail. Any assistance would be greatly appreciated, I'm at a loss as to where to go next to resolve this.

Thanks,

Alex
