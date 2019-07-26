# DOOM Fire Effect
This code is based on 
http://fabiensanglard.net/doom_fire_psx/index.html

## Requirements
* Visual Studio 2017  
* SDL 2.0  

![Effect](./img/doomfire.gif)

# Notes
I do not think I can write this better than original Fabiens article, but only interesting thing I would like to note is this pice of code

``` cpp
int RandomeNumber = rand() % 3;
m_FrameBuffer[y - 1][x] = m_FrameBuffer[y][x] - (RandomeNumber & 1);
```

and in original Fabiens javascript

```
 function spreadFire(src) {
    var rand = Math.round(Math.random() * 3.0) & 3;
    firePixels[src - FIRE_WIDTH ] = firePixels[src] - (rand & 1);
 }
```
Why in the world would he chose a random number between 0 and 2  ``` Math.random() * 3.0 ``` then he forces it to be either 0 or 1 ``` 
(rand & 1) ``` ?

The answer is Probability! 
The code want to give the probability 1/3 to go and look and the below line.

If we have 0 to 2 as random number in binary (00, 01, 10), you can notice that 1 in the least significant bit is accruing 1/3 time. 
The ``` rand & 1 ``` is to mask it out.  
