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
