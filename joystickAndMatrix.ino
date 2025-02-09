const int up = 47;
const int left = 49;
const int down = 51;
const int right = 45;
const int buzzer = 53;
const int yellowLed = 43;
const int redLed = 41;
const int buttonA = 40;
const int buttonB = 42;

// Pines que deben actuar como GND
const int gndPins[] = {46, 48, 50, 52};

// Pines de la matriz LED 16x16
const int filas[] = {A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A0};
const int columnas[] = {17, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

void setup() {
    Serial.begin(9600);
    pinMode(up, INPUT_PULLUP);
    pinMode(left, INPUT_PULLUP);
    pinMode(down, INPUT_PULLUP);
    pinMode(right, INPUT_PULLUP);
    pinMode(buttonA, INPUT_PULLUP);
    pinMode(buttonB, INPUT_PULLUP);
    
    pinMode(buzzer, OUTPUT);
    pinMode(yellowLed, OUTPUT);
    pinMode(redLed, OUTPUT);
    
    // Configurar los pines no usados como "GND"
    for (int i = 0; i < sizeof(gndPins) / sizeof(gndPins[0]); i++) {
        pinMode(gndPins[i], OUTPUT);
        digitalWrite(gndPins[i], LOW);
    }
    
    // Configurar pines de la matriz como salida
    for (int i = 0; i < 16; i++) {
        pinMode(filas[i], OUTPUT);
        digitalWrite(filas[i], LOW);
        pinMode(columnas[i], OUTPUT);
        digitalWrite(columnas[i], HIGH);
    }
}

void encenderPixel(int fila, int columna) {
    if (fila >= 1 && fila <= 16 && columna >= 1 && columna <= 16) {
        int filaIndex = fila - 1;
        int columnaIndex = columna - 1;
        Serial.print("Encendiendo LED en fila: ");
        Serial.print(fila);
        Serial.print(", columna: ");
        Serial.println(columna);
        digitalWrite(filas[filaIndex], HIGH);
        digitalWrite(columnas[columnaIndex], LOW);
        delay(50);
        digitalWrite(filas[filaIndex], LOW);
        digitalWrite(columnas[columnaIndex], HIGH);
    }
}

void loop() {
    if (digitalRead(buttonA) == LOW) {
        digitalWrite(buzzer, HIGH);
        digitalWrite(yellowLed, HIGH);
        Serial.println("Botón A presionado: LED amarillo y buzzer activados");
        encenderPixel(1, 1);
        encenderPixel(2, 2);
        encenderPixel(3, 3);
    } else {
        digitalWrite(buzzer, LOW);
        digitalWrite(yellowLed, LOW);
    }
    
    if (digitalRead(buttonB) == LOW) {
        digitalWrite(redLed, HIGH);
        Serial.println("Botón B presionado: LED rojo activado");
        encenderPixel(16, 16);
        encenderPixel(15, 15);
        encenderPixel(14, 14);
    } else {
        digitalWrite(redLed, LOW);
    }
    
    if (digitalRead(up) == LOW) {
        tone(buzzer, 1000);
        Serial.println("Arriba presionado: tono 1000 Hz");
        encenderPixel(8, 8);
        encenderPixel(7, 8);
    } else if (digitalRead(down) == LOW) {
        tone(buzzer, 500);
        Serial.println("Abajo presionado: tono 500 Hz");
        encenderPixel(9, 9);
        encenderPixel(10, 9);
    } else if (digitalRead(left) == LOW) {
        tone(buzzer, 750);
        Serial.println("Izquierda presionada: tono 750 Hz");
        encenderPixel(8, 4);
        encenderPixel(8, 3);
    } else if (digitalRead(right) == LOW) {
        tone(buzzer, 1250);
        Serial.println("Derecha presionada: tono 1250 Hz");
        encenderPixel(8, 12);
        encenderPixel(8, 13);
    } else {
        noTone(buzzer);
    }
}
