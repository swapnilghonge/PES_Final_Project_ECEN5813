# PES_Final_Project_ECEN5813
# Smart Health Monitoring System
# Using Triple Axis Acceleromter

# Objective 
1. The proposed System tracks the fitness of a person by measuring the distance
  travelled by that person.
2. This system also measures the amount of calories while monitoring the distance.
3. All the results example calories and distance are displayed on LCD.

# Implementation
1. FRDM-KL25Z measures the acceleration using the onboard sensor MMA8451.
2. This interfacing is done over the I2C communication protocol.
3. An LCD HD44780 is interfaced in the system so display the value of the distance travelled and the calorie burnt.
4. Initialization of LCD is done by going through the datasheets.
5. Systick is used to get the delay
6. A demo video is also uploaded for your reference, to demonstrate the proof of concept.

# System FlowChart
![PES_Project](https://user-images.githubusercontent.com/36632481/166404134-353fa4ab-320a-4942-9d6e-c376d672d33d.jpg)

# Implementation Flowchart
![PES_Project (1)](https://user-images.githubusercontent.com/36632481/166404578-433f029a-5cbb-4fcc-9d2b-df498bcb5046.jpg)

# Hardware
1. FRDM-Kl25z
2. LCD HD44780
3. Potentiometer
4. MMA8451 Accelerometer

# Testing
Follow the below mentioned connections on the FRDM-KL25Z board to interface other peripheral hardware.

* 16x2 LCD Connections

| FRDM Board       | 16x2 LCD Display |
|------------------|------------------|
| PTC7(J1-Pin 1)   | LCD_DB7 (Pin 14) |  
| PTC0(J1-Pin 3)   | LCD_DB6 (Pin13)  |  
| PTC3(J1-Pin 5)   | LCD_DB5 (Pin12)  |
| PTC4(J1-Pin 7)   | LCD_DB4 (Pin11)  |
| PTC5(J1-Pin 9)   | LCD_E (Pin6)     |
| PTC6(J1-Pin 11)  | LCD_RW (Pin5)    |  
| PTC10(J1-Pin 13) | LCD_RS (Pin4)    |

5V VCC(J9-Pin 10) -> LCD_VCC (Pin 2), LCD_L+(Pin 15)  
GND(J9-Pin 12) -> LCD_VSS (Pin 1), LCD_L-(Pin 16)  
GND(J9-Pin 12) -> Potentiometer(Pin 3)  
5V VCC(J9-Pin 10) -> Potentiometer(Pin 1) 

# IMAGES OF WORKING CODE
![Working](https://user-images.githubusercontent.com/36632481/166407407-18a0672c-1f22-4cc9-8f63-d5a7c6e9ace4.jpg)
Test_1
![LCD_Test_1](https://user-images.githubusercontent.com/36632481/166407437-3d7c5031-f203-4a52-be55-8709ac9c771d.jpg)

Test_2
![LCD_Test_1](https://user-images.githubusercontent.com/36632481/166407442-0ba128fe-1bf6-42e0-98cc-47594493789d.jpg)

Test_3
![LCD_Test_3](https://user-images.githubusercontent.com/36632481/166407450-57b51dfd-2b20-42ea-b418-69b5fbe0c4f0.jpg)

# Project Demo Video
Please click the below of the Demo
https://www.youtube.com/watch?v=k7JECP1Zu1U&ab_channel=SwapnilGhonge


