# SmartPoolController
In this project I made a smart pool controller system. The entry door to the pool room is automated. If the IR sensor detects a person standing at the door, the door is opened 73°, then automatically closes 23 seconds later. 2 temperature sensors are used inside the pool water and in the outside environment to constantly monitor the temperature. Individual LCD displays are used to display corresponding temperatures. The water level is constantly monitored, once every 15 minutes. 5 LED lights indicate the water level detected by the sensor. Assume, the sensor is placed in such a manner that it is perpendicular to the water surface.
    a. If the distance is within 0-20cm, all 5 lights are on, indicating the pool is filled 100%
    b. If the distance is within 21-40cm, 4 lights are on, indicating the pool is filled 80%
    c. If the distance is within 41-60cm, 3 lights are on, indicating the pool is filled 60%
    d. If the distance is within 61-80cm, 2 lights are on, indicating the pool is filled 40%
    e. If the distance is greater than 81cm, 1 light is on, indicating the pool is filled 20%
       In this case, a buzzer goes off as a warning and a motor is turned on for refilling the pool.
