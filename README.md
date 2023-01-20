# Wemos_PubSub_ControlBlinds_cloudmqtt.com


Some photos and videos of the unit connected to the window.

This log is about how to control the window blinds from a smartphone or a tablet/PC.

In this case, I have used my Mac to send instructions to the curtain to lower or raise. This uses the Publish / Subscribe model of MQTT protocol, where the smartPhone is publishing instructions and the microcontroller attached to the curtain is acting as a subscriber.

At the curtain end, I have a wemos D1 R1 looking at the cloud broker cloudmqtt.com waiting to receive instructions and act accordingly.

The Publisher code is in Node.js and is running on the Mac OS and user can click on "raise" or "Lower" buttons and they will publish appropriate commants to the cloud mqtt broker.

![image](https://user-images.githubusercontent.com/14288989/198988796-cb7a2a44-930f-4490-aadd-0139c7f73e89.png)


The curtain hardware were purchased from Amazon. Likewise the 12v geared DC motor, wemos D1 R1 microcontroller, L298 motor driver were purchased from online stores.

The microcontroller on receiving appropriate instructions will send a High/Low signal to the (L298) motor driver.

The motor driver has 3 pins to control the motor, The EN ( Enable) pin to turn on and off the motor, The IN1 and IN2 to control the direction of the motor.

If EN1 is High, then signals at the IN1 and IN2 pins will be looked at.

If IN1 is High, and IN2 is low, then the motor turns clockwise. ( or lower the curtains )

If IN1 is Low and IN2 is High, then the motor turns anticlockwise ( or raise the curtains )

This part of the logic was introduced in the Microcontroller code, which lowered or raised the curtains.




![image](https://user-images.githubusercontent.com/14288989/197375512-54fa4a56-7c3e-4ed2-8de5-338d9a53760f.png)

The motor was from Amazon. It's a 12v Geared 60rpm motor.

![image](https://user-images.githubusercontent.com/14288989/197375525-773d7947-6b05-497e-827b-8c2811d6e6cd.png)

![image](https://user-images.githubusercontent.com/14288989/197375438-a3f7ed05-8aa2-45f3-ba0c-624b5006695c.png)


![WhatsApp Image 2022-10-19 at 10 59 57 AM](https://user-images.githubusercontent.com/14288989/197375492-eff83b56-f45d-47e9-bb76-759e2bdbf8e8.jpeg)


https://user-images.githubusercontent.com/14288989/197375449-256053a7-d420-4114-9309-4538118e3ac3.mp4



https://user-images.githubusercontent.com/14288989/197375468-79450ee9-684d-4a4e-82fa-fcd8570db5e6.mp4



https://user-images.githubusercontent.com/14288989/197375480-9a89303e-4038-4bae-8a47-2bfb9e362e82.mp4



Using the DPDT switch


https://www.elprocus.com/dpdt-switch/

![image](https://user-images.githubusercontent.com/14288989/197392619-38c5ed97-b7a9-441d-9005-3f2684413aa5.png)

The Arduino IDE -> Board options for Wemos D1 R1 is

![image](https://user-images.githubusercontent.com/14288989/213639227-fadcfde1-e0a5-40cd-8256-20d155a689bb.png)


--

The motor driver uses 3.3v onwards for IN pins to activate and deactivate.


// Pin Diagram

![image](https://user-images.githubusercontent.com/14288989/213679672-678aa715-2d61-4860-bed7-89fb6c4474fd.png)


