# RGB + ESP8266

## Wiring Guide

_In below tables, all pin references on the RGB side are referenced as excel cells, i.e. the top-left on input is A1 and bottom-right on output is D8_

### ESP to IN on RGB (1/8 Scan, 16x32 Resolution)
```
D0  > B7 # STB/LAT
D1  > A5 # A
D2  > B5 # B
D4  > A8 # P_OE
GND > B6 # Ground
D5  > A7 # CLK
D7  > A1 # R0 (or R1 where your board begins counting from 1)
D8  > A6 # C (for 1/8 scan rate and above)
GND > B4 # Additional ground / unused multiplex input
```

### ESP to IN on RGB (1/16 Scan, 32x64 Resolution)
```
D0  > B7 # STB/LAT
D1  > A5 # A
D2  > B5 # B
D4  > A8 # P_OE
D6  > B6 # D (for 1/16 scan rate and above) 
D5  > A7 # CLK
D7  > A1 # R0 (or R1 where your board begins counting from 1)
D8  > A6 # C (for 1/8 scan rate and above)
GND > B4 # Additional ground / unused multiplex input
```

### IN to OUT on RGB
```
A4 > C2
A3 > C1
A2 > D3
B1 > C3
B3 > D1
```

## Examples

### Pixeltime

[Pixeltime for 16x32 1/8 scan boards](examples/pixeltime-16x32/pixeltime-16x32.ino)

[Pixeltime for 32x64 1/16 scan boards](examples/pixeltime-32x64/pixeltime-32x64.ino)

### Hello World

[Hello Word for 16x32 1/8 scan boards](examples/helloworld-16x32/helloworld-16x32.ino)

[Hello Word for 32x64 1/16 scan boards](examples/helloworld-32x64/helloworld-32x64.ino)
