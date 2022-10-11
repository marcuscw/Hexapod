# Hexapod

The ultimate purpose for the hexapod is to be able to walk in multiple terrains.
I've been working on this for 2 years now and everything has been done from scratch apart from the servo control library and the IDEs used.
The hexapod is controlled using an `ESP32` and a `PCA9685` on both sides to control all 18 servos.

For a video introduction and guide watch the videos below:
  - [episode 1](https://www.youtube.com/watch?v=Y2SkA0lwIdg)
    Here I am tackling the legs

  - [episode 2](https://www.youtube.com/watch?v=KBEews2-PPQ)
    Here I am issuing some problems
    
  - [episode 3](https://www.youtube.com/watch?v=KYlweOxck5U)
    Here I explain how it creates a smooth arc when stepping and share some footage of it walking

## Hardware
### Requirements
  - `An FDM 3D Printer` (I use an ender3v2)
  - `CAD experience` incase you wish to modify parts to your liking
  - `A soldering iron`
  - `Experience with the arduino IDE`
### Parts
  | Amount | Part Type  | Part Name | Note | Price For All Units / Link |
  |:---:| ---------- | --------- | ------- | :-------------:|
  | x18| Servo  | MG996R  | Stall Torque: 11 kgf·cm (6 V) | [£93](https://www.amazon.co.uk/diymore-Digital-Helicopter-Airplane-controls/dp/B09KZRPJ41/ref=sr_1_5?crid=1FIV9EMT1TRCD&keywords=mg996r&qid=1665498784&qu=eyJxc2MiOiIzLjg3IiwicXNhIjoiMy44MyIsInFzcCI6IjMuNDAifQ%3D%3D&sprefix=mg996r%2Caps%2C218&sr=8-5)|
  | x1 | Microcontroller  | ESP32 |     |[£10](https://www.amazon.co.uk/AZDelivery-NodeMcu-CP2102-Development-including/dp/B071P98VTG/ref=sr_1_4?crid=27JBP48B85OKK&keywords=esp32&qid=1665498996&qu=eyJxc2MiOiI1LjgyIiwicXNhIjoiNC43OSIsInFzcCI6IjQuNDQifQ%3D%3D&refinements=p_89%3AAZDelivery&rnid=1632651031&s=computers&sprefix=esp32+%2Caps%2C97&sr=1-4) |
  | x2 | Servo Controller | PCA9685 | <ul><li>used to control up to 16 servos with $\text{I}^2\text{C}$</li><li>In both of my boards the reverse polarity diode blew up so it is recommended to buy the newer model with the beefier diode however there is an easy fix</li></ul>|[£26](https://www.amazon.co.uk/SunFounder-PCA9685-Channel-Arduino-Raspberry/dp/B014KTSMLA/ref=sr_1_6?crid=1Z2B2VAWX7VAH&keywords=pca9685&qid=1665499045&qu=eyJxc2MiOiIzLjcyIiwicXNhIjoiMy4xNCIsInFzcCI6IjIuODEifQ%3D%3D&s=computers&sprefix=pca9685%2Ccomputers%2C82&sr=1-6) |
  | x2 | Battery | "6V 2400mAh Ni-MH AA Rechargeable<br> Battery Pack with SM-2P 2Pin Plug" |two of these in parallel double the capacity but keep the voltage|[£30](https://www.amazon.co.uk/Hootracker-2400mAh-Rechargeable-Battery-Vehicles/dp/B085WVBYXK/ref=sr_1_6?keywords=6v+battery+pack&qid=1665499186&qu=eyJxc2MiOiIzLjc3IiwicXNhIjoiMy40MCIsInFzcCI6IjMuMTkifQ%3D%3D&sr=8-6)|


## Diagrams

in [Leg.ino](https://github.com/marcuscw/Hexapod/blob/main/HexapodESP32/Leg.ino) I have code for the inverse kinematics however all the variable names are very vague so here are some diagrams to help you identify which is which.

![IKdiagram3D](https://user-images.githubusercontent.com/59029701/194750931-4ebb3173-77f8-49c2-b223-9b08e427c842.jpg)
![IKdiagramTOP](https://user-images.githubusercontent.com/59029701/194750799-57d6da29-e047-4dfb-b61f-939cb031b969.jpg)
![IKdiagramSide](https://user-images.githubusercontent.com/59029701/194750801-5e077e23-9713-4215-8c6d-226e757891e5.jpg)
