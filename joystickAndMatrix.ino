
// Pines del joystick (botones digitales)
const int up = 47;
const int left = 49;
const int down = 51;
const int right = 45;
const int buttonA = 40; // Rota la figura en sentido horario
const int buttonB = 42; // Rota la figura en sentido antihorario
const int buzzer = 53;  // Buzzer para emitir beep
const int yellowLed = 43; // LED amarillo (Botón B)
const int redLed = 41;   // LED rojo (Botón A)

// Pines de la matriz LED 16x16 (ÁNODO COMÚN)
const int filas[] = {A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A0};
const int columnas[] = {17, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

// Posición inicial de la figura
int offsetX = 0; // Posición X de la figura en la matriz
int offsetY = 0; // Posición Y de la figura en la matriz

// Figura actual (4x4)
bool figura[4][4] = {
  {1, 1, 0, 0},
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 0, 0, 0}
};

// Rota la figura en sentido horario
void rotarHorario() {
    bool temp[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[j][3 - i] = figura[i][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            figura[i][j] = temp[i][j];
        }
    }

    // Emitir beep y encender LED rojo
    digitalWrite(redLed, HIGH);
    tone(buzzer, 1000, 100);
    delay(100);
    digitalWrite(redLed, LOW);
}

// Rota la figura en sentido antihorario
void rotarAntihorario() {
    bool temp[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[3 - j][i] = figura[i][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            figura[i][j] = temp[i][j];
        }
    }

    // Emitir beep y encender LED amarillo
    digitalWrite(yellowLed, HIGH);
    tone(buzzer, 800, 100);
    delay(100);
    digitalWrite(yellowLed, LOW);
}

void setup() {
    Serial.begin(9600);

    // Configurar pines del joystick como entradas
    pinMode(up, INPUT_PULLUP);
    pinMode(down, INPUT_PULLUP);
    pinMode(left, INPUT_PULLUP);
    pinMode(right, INPUT_PULLUP);
    pinMode(buttonA, INPUT_PULLUP);
    pinMode(buttonB, INPUT_PULLUP);

    // Configurar buzzer y LEDs como salida
    pinMode(buzzer, OUTPUT);
    pinMode(yellowLed, OUTPUT);
    pinMode(redLed, OUTPUT);

    // Configurar pines de la matriz como salida
    for (int i = 0; i < 16; i++) {
        pinMode(filas[i], OUTPUT);
        digitalWrite(filas[i], LOW);
        pinMode(columnas[i], OUTPUT);
        digitalWrite(columnas[i], HIGH);
    }
}

// Muestra la figura en la matriz
void mostrarFigura() {
    static int filaAnterior = 15; // Variable para la fila anterior

    digitalWrite(filas[filaAnterior], LOW);
    for (int i = 0; i < 16; i++) {
        digitalWrite(columnas[i], HIGH);
    }

    int filaActual = (filaAnterior + 1) % 16;
    digitalWrite(filas[filaActual], HIGH);

    for (int j = 0; j < 16; j++) {
        bool encender = false;
        for (int fy = 0; fy < 4; fy++) {
            for (int fx = 0; fx < 4; fx++) {
                if (figura[fy][fx] == 1) {
                    if (filaActual == offsetY + fy && j == offsetX + fx) {
                        encender = true;
                    }
                }
            }
        }
        digitalWrite(columnas[j], encender ? LOW : HIGH);
    }

    filaAnterior = filaActual;
    delayMicroseconds(500);
}

// Mueve la figura en la matriz
void moverFigura() {
    static unsigned long ultimaEjecucion = 0;
    unsigned long tiempoActual = millis();

    if (tiempoActual - ultimaEjecucion > 150) {
        if (digitalRead(up) == LOW && offsetY > 0) {
            offsetY--;
        }
        if (digitalRead(down) == LOW && offsetY < 12) {
            offsetY++;
        }
        if (digitalRead(left) == LOW && offsetX > 0) {
            offsetX--;
        }
        if (digitalRead(right) == LOW && offsetX < 12) {
            offsetX++;
        }
        ultimaEjecucion = tiempoActual;
    }
}

// Verifica si se presionó A o B y rota la figura
void verificarRotacion() {
    static bool buttonAState = HIGH;
    static bool buttonBState = HIGH;

    if (digitalRead(buttonA) == LOW && buttonAState == HIGH) {
        rotarHorario();
        buttonAState = LOW;
    }
    if (digitalRead(buttonA) == HIGH) {
        buttonAState = HIGH;
    }

    if (digitalRead(buttonB) == LOW && buttonBState == HIGH) {
        rotarAntihorario();
        buttonBState = LOW;
    }
    if (digitalRead(buttonB) == HIGH) {
        buttonBState = HIGH;
    }
}

void loop() {
    moverFigura();
    verificarRotacion();
    mostrarFigura();
}
