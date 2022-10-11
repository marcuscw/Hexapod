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
  | Amount | Part Type  | Part Name | Note |
  |:---:| ---------- | --------- | ------- |
  | x18| Servo  | MG996R  | Stall Torque: 11 kgf·cm (6 V) |
  | x1 | Microcontroller  | ESP32 |     |
  | x2 | Servo Controller | PCA9685 | used to control up to 16 servos <br> with $\text{I}^2\text{C}$.<br>Can also be chained together. |
  | x2 | Battery | "6V 2400mAh Ni-MH AA Rechargeable<br> Battery Pack with SM-2P 2Pin Plug" |two of these in parallel double the capacity but keep the voltage|


## Diagrams

in [Leg.ino](https://github.com/marcuscw/Hexapod/blob/main/HexapodESP32/Leg.ino) I have code for the inverse kinematics however all the variable names are very vague so here are some diagrams to help you identify which is which.

![IKdiagram3D](https://user-images.githubusercontent.com/59029701/194750931-4ebb3173-77f8-49c2-b223-9b08e427c842.jpg)
![IKdiagramTOP](https://user-images.githubusercontent.com/59029701/194750799-57d6da29-e047-4dfb-b61f-939cb031b969.jpg)
![IKdiagramSide](https://user-images.githubusercontent.com/59029701/194750801-5e077e23-9713-4215-8c6d-226e757891e5.jpg)
