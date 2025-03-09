This is the readme for the PICOCHET keyboard.
This is a handwired keyboard based on the raspberry pi pico w 

Prerequisites after installing the arduino-pico framework:

On linux:
Go to /home/user/Arduino/hardware/pico/rp2040/libraries/KeyboardBLE/src 

On windows:
Go to C:\Users\{username}\Documents\Arduino\hardware\pico\rp2040\libraries\KeyboardBLE\src

Inide the src directory replace the KeyboardBLE.h and KeyboardBLE.cpp file with the files provided in this repository.

Note: This keyboard uses two pi pico's of which one is a pico w and the other one is a pico,
both the picos communicate with each other via uart0.

After making the connections as per the connection diagram provided upload the code to the respective pico.
I have also provided the STL files for 3d printing the case.







The final result:
![image](https://github.com/user-attachments/assets/92931de9-7ac9-4159-8324-6d1c24fff801)



![image](https://github.com/user-attachments/assets/456a1965-9e3e-4902-b5c6-9f06cd4b1161)
