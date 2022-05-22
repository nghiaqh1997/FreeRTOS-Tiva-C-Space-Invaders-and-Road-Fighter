# SPACE-INVADERS-FREERTOS-TIVA-C
## Mục lục
[I.Description](#Description)

[II.Game-Instructions](#Game)

[III.Putting It Together](#PuttingItTogether)
- [1.Bill of Materials](#BillofMaterials)
- [2.Wiring](#Wiring)
- [3.Display](#Display)
- [4.Potentiometer and buttons](#4)

[IV.Programming](#Programming)
- [1.IDE](#IDE)
- [2.Libraries](#Lib)

===========================

<a name="Description"></a>
### I.Description
This is a my final project at course Embedded System Progamming at HCMUT. The project idea is to make Space Invaders game with my LaunchPad to apply all concepts that teached through this course like ADC,GPIO,Interrupts,SPI,Timer,FreeRTOS...etc. Only Demo, not Professional. 
<a name="Game"></a>
### II.Game-Instructions
The game consists one level. You have to kill 15 enemies. Enemy will try to kill you by their laser shoots so you need to dodge it and kill enemies before you are be killed or enemies reaches bottom line. You have Fire button, POT(to change resistor value) to move, LCD to visualize the game and a special button to clear all laser on screen (but need time to charge). 
<a name="PuttingItTogether"></a>
### III.Putting It Together
<a name="BillofMaterials"></a>
#### 1.Bill of Materials
