# Wireless-Charging-Smart-Lamp-Project
This project is a Wireless Charging Smart Lamp.

## Purpose
This lamp is actually a gift I built for my friends and teachers before I came to US in 2016.
I was in charge of the hardware, embedded software and industrial design respectively. So this is also a good practice project for me to design a product totally by myself from hardware layer to software layer.

## Features
- Light: The lamp supports 65k color space. Users can change color with their smartphone.
- Multiple Charging Mode: The lamp supports wireless charing and cable charging. You can choose either way you want.
- Capacitive Touch Control: User can turn on/off the lamp by touch the capacitive sensing area, and dim the light by keep touching the area for long time.
- Wireless Control: Users can control the color of the light by writing a command to the lamp through BLE.
- Battery Management: The lamp has a built-in Lithium Ion battery inside. When charging, the battery management circuit will control & alter the charging phase accordingly. The lamp will indicate fully charged state and low battery state to the user. User can stop the indication by simply touch the lamp.

## Development
- Hardware: Both the schematic and PCB is designed with Altium Designer. To pursue a modular design, I prototyped a BQ51013B wireless charging module and used it on my project.
- Firmware: I use MSP430 as the controller in this project becasue of its low power consumption and cheap price. So the firmware is programmed with Code Composer Studio provided by Ti.
- Design: I used Rhino to design the case and exported to STL format for 3D printing.

## Usage
- Hardware: Use altium to open the PrjPcb file to see the whole project. After open the project, you need to import the Design Used Library. Bedside Lamp V3.0.pdf includes the schematic and the screenshot of the PCB design.
- Firmware: The firmware project is located under Firmware/ folder.
- Case: To print the case, you need to open the 3dm file under 3D Models/ folder and export everything into STL.

## Photos
![Circuits Photos](https://github.com/boningdong/Wireless-Charing-Smart-Lamp-Project/blob/master/Photos/All%20Circuits.jpg)
![Rhino Deisng](https://github.com/boningdong/Wireless-Charing-Smart-Lamp-Project/blob/master/Photos/Rhino%20Design.jpg)
![Real Photo](https://github.com/boningdong/Wireless-Charing-Smart-Lamp-Project/blob/master/Photos/Photo.JPG)

