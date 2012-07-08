#include "libmanyuc.h"
#include "i2c_accelerometer.h"
#include "car_commands.h"
#include <stdio.h>

void show_angle(Bus pins, float x) {

    int vel = (int)(x * 10);
    if (vel == 0)      pins = 6;
    else if (vel < -5) pins = 1;
    else if (vel < 0)  pins = 2;
    else if (vel < 6)  pins = 4;
    else               pins = 8;

}

// Gets the next command to the car
unsigned char get_command(float *vect, Pin left, Pin right)
{
    unsigned char r = 0;

    // Buttons are inverse enabled
    if (left == 0) {
         r = STOP;  // Stop
    } 
    if (right == 0) {
         r += START; // Start (line follower if Stop+Start)
    }

    // If buttons are enabled, return now.
    if (r != 0) return r;
    
    // Read current (Y, Z) position
    int velY = (int)(vect[1]*10);
    int velZ = (int)(vect[2]*10);

    // Capping
    if (velY >= 10)  velY = 9;
    if (velY <= -10) velY = -9;
    
    // Center position
    if ((-1 <= velY) && (velY <= 1)) {
        r = CENTER;
    } else if (velY > 1) {
        r = LEFT + velY;
    } else {
        r = RIGHT + ((-1) * velY);
    }
    
    // Backward
    if (velZ <= 0) {
        r += BACKWARD;
    }

    return r;
}

// Sends the next command to the car
void send_car_command(Serial cmdLink, float *vect, Pin left, Pin right) {
    unsigned char cmd = get_command(vect, left, right);
    cmdLink.putByte(cmd);
}

// Shows the current state of the accelerometer in the PC
void send_data_pc(Serial pc, float *vect) {
    fprintf(pc, "%d; %0d; %0d\r\n", 
            (int) (vect[0] * 10), (int) (vect[1] * 10), (int) (vect[2]* 10));
}

int main() {

    // Serial port through USB
    Serial pc(0, 9600);   

    // Zigbit connection
    Serial cmdLink(1, 38400);

    // Leds on the board
    Bus leds(4, LED1, LED2, LED3, LED4);
    leds.mode(Output);

    // Buttons on the board
    Pin left(P19, 2, Input, PullUp);
    Pin right(P20, 2, Input, PullUp);

    // Small pause before callibration
	Delay(1);
    // Create and initialize Accelerometer
    Accelerometer acer(2);
    
    float vect[3];
    
    while(1)
    {
        acer.get10BitVector(vect);
        show_angle(leds, vect[1]);
        //send_data_pc(pc, vect);
        send_car_command(cmdLink, vect, left, right);

        // Small pause between measurements
        Delay(0.1); 
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
