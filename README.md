![Arduino Car](/Images/tc-car-1.jpg)

The purpose of this arduino project is to explore through trial and error how to implement a rudimentary traction control system on an arduino car. I used 4x LM393 IR optocouplers on each of the four wheels to measure wheel speed, and a L298N DC motor controller to take in PWM signals from my arduino...

![Control Loop](/Images/tc-control-loop.png)

I initially tried to use a 9V battery to provide power to my motors, only to realize its voltage would drop to less than 5V under load and barely spin the motors at all. I then sought out a 11.1V 3S LiPo to do the heavy lifting. Despite the 2V drop across the L298N outputs I was still able to deliver up to 10.6V to each motor (LiPo is 12.6V under full charge, 4.2V per cell). This provided ample voltage and current and was able to spin the wheels up to ~450rpm...

I still had an issue with the rear wheels gripping despite the cheap plasticky rubber tires. Doing a little research I found out about UHMW (Ultra High Molecular Weight) tape which greatly reduces the coefficient of friction on the tires. With them wrapped around the rear tires they now slip easily...

Halfway through the build I realized due to my lack of experience with arduinos that my UNO R3 board with its 14 digital I/O wouldn't be enough for a project of my scale. Therefore I replaced it with the MEGA 2560 which also represented a challenge in terms of its larger footprint. I used 25mm standoffs to lift the Mega above the breadboard, conveniently creating a perfect slot in which to insert the LiPo battery...

With the input and output signals I was able to slowly work out an algorithm to detect when the rear wheels rotated at a greater angular velocity than that of the front wheels...
<br><br>

List of parts used for this build:  
4 wheel car base: http://amzn.com/B06VTP8XBQ  
Willwin 5pcs LM393: http://amzn.com/B0776RHKB1  
Qunqi 2Packs L298N http://amzn.com/B01M29YK5U  
Elegoo Dupont Wires: http://amzn.com/B01EV70C78  
Elegoo UNO R3 Kit: http://amzn.com/B01D8KOZF4  
Soldering Kit: http://amzn.com/B07GTGGLXN  
Heatshrink Kit: http://amzn.com/B01MFA3OFA  
Ovonic 11.1V 2200mAh Lipo: http://amzn.com/B077P73SDS  
2pc Deans connector: http://amzn.com/B00PC13IYC  
Tenergy Balance Charger: http://amzn.com/B004FGWY54  
Elegoo 6pc 170 Breadboard: http://amzn.com/B01EV6SBXQ  
Elegoo Arduino Mega 2560 R3: http://amzn.com/B01H4ZDYCE  
iFlight 20x M3 Titanium Bolts: http://amzn.com/B073TRKRRX  
iFlight 10x 25mm Aluminum Standoffs: http://amzn.com/B06XCQDZ9V  
eBoot 100x Adhesive Cable Clips: http://amzn.com/B01HR9VS4I  
TapeCase UHMW Tape: http://amzn.com/B00823JF0S
Pre-Formed 140pc Jumper Wire Kit: http://amzn.com/B014JOV4TI

Total cost of all parts: $178.94 USD
