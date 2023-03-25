# PumpFirmware

This project simply turns on/off relays based on 2 buttons and to prevent PID overshoot. The temp controls act as a lowpass filter for tempurature adjustments made by the PID controller. 

Currently there is old code that was intended to monitor the state of the relays and shut down the system due to an electrical overtemp situation. Due to a faulty termocouple (experiencing sporatic temp readings) the code was commented out for short term stability. 
