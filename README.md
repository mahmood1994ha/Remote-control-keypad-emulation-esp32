# Remote-control-keypad-emulation-esp32
online controlled keypad emulation using esp32 for karting speed remote controls

This quick hack is a good way to emulate keypad presses of devices that you can't otherwise automatically control.


In order to use this hack properly, you should decode each button on your matrix keypad to it's corresponding row and column, and change the combLUT function correspondingly to reflect that. 
The rempte control i wrote this program for is a deHaardt Xtra remote control used to limit the speed of go karts see:
  http://www.de-haardt.com/en/products/1-go-karts/1-xtra.remote-control

Online control is realized by sending an HTTP GET request with the go kart number and speed limit level (1 to 4) 
For example: 192.192.192.1/901  sets speed level 1 to kart number 90

The code is self explanatory, Please feel free to commit your version for your own keypad emulation application :)
