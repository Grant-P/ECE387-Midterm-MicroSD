# ECE387-Midterm-MicroSD
# Author: Grant P
# 16 March 2017

Interfaces a liquid crystal display and MicroSD adaptor with an Arduino Uno.
Characters are selected with a knob and entered with a button, and displayed on the LCD as
they are typed in.  When the user finishes or the character limit of 16 is reached, a text
file is created on the MicroSD card with that name, opened, text is written to the file,
and the file is closed.

Requires libraries built into Arduino IDE: LiquidCrystal, SD, SPI

In this configuration, the Arduino Uno relies on a USB connection to power itself and the circuit.

Pin Connections:
  MicroSD Adaptor <-> Uno
      CS - D10
     SCK - D13
    MOSI - D11
    MISO - D12
     VCC - 5V
     GND - GND

  Liquid Crystal Display <-> Uno
           1 - GND
           2 - 5V
           3 - Potentiometer_1 signal pin
           4 - D7
           5 - GND
           6 - D6
    7,8,9,10 - FLOATING
          11 - D5
          12 - D4
          13 - D3
          14 - D2
          15 - 220 Ohm Resistor - 5V
          16 - GND
          
  Potentiometer_1 <-> Uno
    (+) pin - 5V
    (-) pin - GND
  
  Potentiometer_2 <-> Uno
       (+) pin - 5V
       (-) pin - GND
    signal pin - A0
       (+) pin - 100 uF Capacitor - (-) pin (OPTIONAL)
    
  Push Button <-> Uno
    1 - 5V
    2 - 10 kOhm Resistor - GND
    2 - D9
    
