extern Pin led3;

void handler_boton(void);

typedef enum {
    ADELANTE,
    ATRAS,
    DETENIDO,
} Sentido;

typedef enum {
    BLANCO,
    NEGRO,
    GRIS,
} Color;

class Motor {
private:
    Pin In1;
    Pin In2;

public:
    Sentido sentido;
    PWMPin  Velocidad;

    Motor (PinName in1, PinName in2, PinName Vel): In1(in1), In2(in2), Velocidad(Vel) {
        set_sentido(DETENIDO);
        Velocidad.set_period_ms(5);
        Velocidad = 0.0;
    };

    void set_sentido (Sentido Sens) {
// Pines para el puente H.
// In1=1 y In2=0 movimiento hacia adelante
// In1=0 y In2=1 movimiento hacia atras
// In1=0 y In2=0 frenado
// In1=1 y In2=1 frenado
        switch (Sens) {
            case ADELANTE:
                In1 = 1;
                In2 = 0;
                break;
            case ATRAS:
                In1 = 0;
                In2 = 1;
                break;
            case DETENIDO:
                In1 = 0;
                In2 = 0;
                break;
        }
        sentido = Sens;
    };

    Sentido get_sentido (void) {
        return sentido;
    };

};

class Sensor {
private:
    Pin led;
    AnalogIn transistor;
public:
    float negro_minimo;
    float blanco_maximo;

    Sensor (PinName l, PinName t): led(l), transistor(t) {
        led = 1;
        negro_minimo = 2000;
        blanco_maximo = 2000;
    };

    Color get_color (void) {
        Color c = GRIS;
		unsigned int color = transistor;
        if (color < negro_minimo && color > blanco_maximo) c = GRIS;
		else if (color > negro_minimo) c = NEGRO;
		else if (color < blanco_maximo) c= BLANCO;
        return c;
    };

    void sensor_on (bool a) {
        if (a) led = 1;
        else led = 0;
    };

    operator unsigned int() {
        return transistor;
    };
};
