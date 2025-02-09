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
}

void loop() {
    if (digitalRead(buttonA) == LOW) {
        digitalWrite(buzzer, HIGH);
        digitalWrite(yellowLed, HIGH);
        Serial.println("Botón A presionado: LED amarillo y buzzer activados");
    } else {
        digitalWrite(buzzer, LOW);
        digitalWrite(yellowLed, LOW);
    }
    
    if (digitalRead(buttonB) == LOW) {
        digitalWrite(redLed, HIGH);
        Serial.println("Botón B presionado: LED rojo activado");
    } else {
        digitalWrite(redLed, LOW);
    }
    
    if (digitalRead(up) == LOW) {
        tone(buzzer, 1000);
        Serial.println("Arriba presionado: tono 1000 Hz");
    } else if (digitalRead(down) == LOW) {
        tone(buzzer, 500);
        Serial.println("Abajo presionado: tono 500 Hz");
    } else if (digitalRead(left) == LOW) {
        tone(buzzer, 750);
        Serial.println("Izquierda presionada: tono 750 Hz");
    } else if (digitalRead(right) == LOW) {
        tone(buzzer, 1250);
        Serial.println("Derecha presionada: tono 1250 Hz");
    } else {
        noTone(buzzer);
    }
}
