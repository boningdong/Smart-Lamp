# Wireless-Charing-Smart-Lamp-Project
This project is a Wireless Charging Smart Lamp.

##Purpose
This lamp is actually a gift I built for my friends and teachers before I left China.
I was in charge of the hardware, embedded software and industrial design respectively.

##Features
- Light: The lamp supports 65k color space. Users can change color with their smartphone.
- Multiple Charging Mode: The lamp supports wireless charing and cable charging. You can choose either way you want.
- Capacitive Touch Control: User can turn on/off the lamp by touch the capacitive sensing area, and dim the light by keep touching the area for long time.
- Wireless Control: Users can control the color of the light by writing a command to the lamp through BLE.
- Battery Management: The lamp has a built-in Lithium Ion battery inside. When charging, the battery management circuit will control & alter the charging phase accordingly. The lamp will indicate fully charged state and low battery state to the user. User can stop the indication by simply touch the lamp.

##Development
- Hardware: Both the schematic and PCB is designed with Altium Designer.
- Firmware: I use MSP430 as the controller in this project becasue of its low power consumption and cheap price. So the firmware is programmed with Code Composer Studio provided by Ti.
- Design: I used Rhino to design the case and exported to STL format for 3D printing.


