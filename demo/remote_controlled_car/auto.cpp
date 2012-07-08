
#include    "libmanyuc.h"
#include    "auto.h"
#include    "car_commands.h"

#define MARCHA_IZQ    0.4f
#define MARCHA_DER    0.4f
//MotorA en el auto 17, es el izquierdo
//MotorB en el auto 17, es el derecho

//Faroles delanteros
Pin FarolA(P20);
Pin FarolB(P30);

// Config sensores
Sensor sensorA (P9, P19);
Sensor sensorB (P10, P18);

void estado_sensores (void) {
    //if (sensorA.get_color() == BLANCO) led2 = 1; else led2 = 0;
    //if (sensorB.get_color() == BLANCO) led3 = 1; else led3 = 0;
}

void line_follower(Motor motorA, Motor motorB) {
    if (sensorA.get_color() == BLANCO && sensorB.get_color() == BLANCO) {
        motorA.set_sentido(ADELANTE);
        motorB.set_sentido(ADELANTE);
    } else if (sensorA.get_color() == BLANCO && sensorB.get_color() != BLANCO) {
        motorA.set_sentido(ATRAS);
        motorB.set_sentido(ADELANTE);
    } else if (sensorA.get_color() != BLANCO && sensorB.get_color() == BLANCO) {
        motorA.set_sentido(ADELANTE);
        motorB.set_sentido(ATRAS);
    }
} 

unsigned char get_command(Serial cmdLink) {
    while (! cmdLink.readable());  
    return cmdLink.getByte();
}

void wait_for_start(Serial cmdLink) {
	while (get_command(cmdLink) != START);
}

int main()
{
	// PC connection
	Serial pc(0, 9600);
	
	// Turn all leds on while waiting
	Bus leds(4, LED4, LED3, LED2, LED1);
	leds.mode(Output);
	leds.write_all(1);
    
    // Config motors
    Motor motorB (P22, P21, P23);
    Motor motorA (P25, P24, P26);

	// Turn lights on
    FarolA = 1;
    FarolB = 1;

	// The interface with the remote control
	Serial cmdLink(1, 38400);

	// Read until the control says START
	wait_for_start(cmdLink);
	
    // Seteo velocidad y direccion del motor A
    motorA.set_sentido(ADELANTE);
    motorA.Velocidad = MARCHA_IZQ;

    // Seteo velocidad y direccion del motor B
    motorB.set_sentido(ADELANTE);
    motorB.Velocidad = MARCHA_DER;

    while (1)
    {
        // encendemos los leds de acuerdo con los sensores
        //estado_sensores();

		unsigned char cmd = get_command(cmdLink);
		leds.write(cmd);

		// Stop makes the car stop until the next start
		if (cmd == STOP) {
            motorA.set_sentido(DETENIDO);
            motorB.set_sentido(DETENIDO);
			wait_for_start(cmdLink);
		} 
		
		// Go faster
		else if (cmd == START) {
			motorA.Velocidad = 0.9;
			motorB.Velocidad = 0.9;
		}

		// Enter line_follower mode
		else if (cmd == LINE_FOLLOWER) {
			line_follower(motorA, motorB);
		} 
		
		// Go forward
		else if (cmd == (CENTER+FORWARD)) {
            motorA.set_sentido(ADELANTE);
            motorA.Velocidad = MARCHA_IZQ;
            motorB.set_sentido(ADELANTE);
            motorB.Velocidad = MARCHA_DER;
		} 
		
		// Go backward
		else if (cmd == (CENTER+BACKWARD)) {
            motorA.set_sentido(ATRAS);
            motorA.Velocidad = MARCHA_IZQ;
            motorB.set_sentido(ATRAS);
            motorB.Velocidad = MARCHA_DER;
		} 
		
		// Go left
		else if (cmd > LEFT && cmd < RIGHT) {
            motorB.set_sentido(ADELANTE);
			float f = (cmd - LEFT) / 10.;
			if (f > 0.7) {
                motorA.set_sentido(ATRAS);
                motorA.Velocidad = MARCHA_IZQ*(f-0.2);
                motorB.Velocidad = MARCHA_DER*(f-0.2);
			} else {
				motorA.set_sentido(ADELANTE);
				motorA.Velocidad = MARCHA_IZQ*(0.7-f);
				motorB.Velocidad = MARCHA_DER*(1+f);
			}
		} 
		
		// Go right
		else if (cmd > RIGHT && cmd < BACKWARD) {
            motorA.set_sentido(ADELANTE);
			float f = (cmd - RIGHT) / 10.;
			if (f > 0.7) {
	            motorB.set_sentido(ATRAS);
				motorA.Velocidad = MARCHA_IZQ*(f-0.2);
		        motorB.Velocidad = MARCHA_DER*(f-0.2);
			} else {
	            motorB.set_sentido(ADELANTE);
				motorA.Velocidad = MARCHA_IZQ*(1+f);
		        motorB.Velocidad = MARCHA_DER*(0.7-f);
			}
		} else {
			cmd -= BACKWARD;
			if (cmd > LEFT && cmd < RIGHT) {
				float f = (cmd - LEFT) / 10.;
			    motorB.set_sentido(ATRAS);
				if (f > 0.7) {
	                motorA.set_sentido(ADELANTE);
		            motorA.Velocidad = MARCHA_IZQ*(f-0.2);
				    motorB.Velocidad = MARCHA_DER*(f-0.2);
				} else {
	                motorA.set_sentido(ATRAS);
		            motorA.Velocidad = MARCHA_IZQ*(0.9-f);
				    motorB.Velocidad = MARCHA_DER*(1+f);
				}
			} else {
				float f = (cmd - RIGHT) / 10.;
				motorA.set_sentido(ATRAS);
				if (f > 0.7) {
		            motorB.set_sentido(ADELANTE);
	                motorA.Velocidad = MARCHA_IZQ*(f-0.2);
			        motorB.Velocidad = MARCHA_DER*(f-0.2);
				} else {
		            motorB.set_sentido(ATRAS);
	                motorA.Velocidad = MARCHA_IZQ*(1+f);
			        motorB.Velocidad = MARCHA_DER*(0.9-f);
				}
			}
		}
    }
}
