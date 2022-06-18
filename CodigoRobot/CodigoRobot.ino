#include <BluetoothSerial.h>
#include <Tone.h>
#include <analogWrite.h>
#include<vector> //to include vector container in code
using namespace std; 

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define FRENTE 45
#define TRAS 65
#define DIREITA 95
#define ESQUERDA 96
#define PISCA 100
#define BUZINA 120
#define ASAB 130
#define PARAB 140
#define STARW 150
#define LIGAR 200
#define APAGAR 300

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// Valores aleatórios para as portas onde ligaremos os motores das rodas, só modificar na hora que montarmos o robô, já coloquei o sentido de giro de cada variável
int S_A = 30;  //speed motor a
int M_A1 = 26; //motor a = +
int M_A2 = 25; //motor a = -
int M_B1 = 32; //motor b = -
int M_B2 = 33; //motor b = +
int S_B = 30;  //speed motor b
int LED1 = 13;
int LED2 = 14;
int buzzer = 12;
const int potPin = 34;


int potValue = 0;
int control = 0;


int t_90 = 565; // tempo (delay) que ele demora pra girar 90°
int d = t_90 / 4;
BluetoothSerial SerialBT;


// change this to make the song slower or faster
int tempo = 125;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melodyAsa[] = {

  // Asa branca - Luiz Gonzaga
  // Score available at https://musescore.com/user/190926/scores/181370

  NOTE_G4, 8, NOTE_A4, 8, NOTE_B4, 4, NOTE_D5, 4, NOTE_D5, 4, NOTE_B4, 4,
  NOTE_C5, 4, NOTE_C5, 2, NOTE_G4, 8, NOTE_A4, 8,
  NOTE_B4, 4, NOTE_D5, 4, NOTE_D5, 4, NOTE_C5, 4,

  NOTE_B4, 2, REST, 8, NOTE_G4, 8, NOTE_G4, 8, NOTE_A4, 8,
  NOTE_B4, 4, NOTE_D5, 4, REST, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_B4, 8,
  NOTE_G4, 4, NOTE_C5, 4, REST, 8, NOTE_C5, 8, NOTE_B4, 8, NOTE_A4, 8,

  NOTE_A4, 4, NOTE_B4, 4, REST, 8, NOTE_B4, 8, NOTE_A4, 8, NOTE_G4, 8,
  NOTE_G4, 2, REST, 8, NOTE_G4, 8, NOTE_G4, 8, NOTE_A4, 8,
  NOTE_B4, 4, NOTE_D5, 4, REST, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_B4, 8,

  NOTE_G4, 4, NOTE_C5, 4, REST, 8, NOTE_C5, 8, NOTE_B4, 8, NOTE_A4, 8,
  NOTE_A4, 4, NOTE_B4, 4, REST, 8, NOTE_B4, 8, NOTE_A4, 8, NOTE_G4, 8,
  NOTE_G4, 4, NOTE_F5, 8, NOTE_D5, 8, NOTE_E5, 8, NOTE_C5, 8, NOTE_D5, 8, NOTE_B4, 8,

  NOTE_C5, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_G4, 8, NOTE_A4, 8, NOTE_G4, 8, NOTE_E4, 8, NOTE_G4, 8,
  NOTE_G4, 4, NOTE_F5, 8, NOTE_D5, 8, NOTE_E5, 8, NOTE_C5, 8, NOTE_D5, 8, NOTE_B4, 8,
  NOTE_C5, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_G4, 8, NOTE_A4, 8, NOTE_G4, 8, NOTE_E4, 8, NOTE_G4, 8,
  NOTE_G4, -2, REST, 4

};

int melodyPara[] = {

  // Happy Birthday
  // Score available at https://musescore.com/user/8221/scores/26906

  NOTE_C4, 4, NOTE_C4, 8,
  NOTE_D4, -4, NOTE_C4, -4, NOTE_F4, -4,
  NOTE_E4, -2, NOTE_C4, 4, NOTE_C4, 8,
  NOTE_D4, -4, NOTE_C4, -4, NOTE_G4, -4,
  NOTE_F4, -2, NOTE_C4, 4, NOTE_C4, 8,

  NOTE_C5, -4, NOTE_A4, -4, NOTE_F4, -4,
  NOTE_E4, -4, NOTE_D4, -4, NOTE_AS4, 4, NOTE_AS4, 8,
  NOTE_A4, -4, NOTE_F4, -4, NOTE_G4, -4,
  NOTE_F4, -2,

};

int melodyStar[] = {

  // Dart Vader theme (Imperial March) - Star wars
  // Score available at https://musescore.com/user/202909/scores/1141521
  // The tenor saxophone part was used

  NOTE_AS4, 8, NOTE_AS4, 8, NOTE_AS4, 8, //1
  NOTE_F5, 2, NOTE_C6, 2,
  NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F6, 2, NOTE_C6, 4,
  NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F6, 2, NOTE_C6, 4,
  NOTE_AS5, 8, NOTE_A5, 8, NOTE_AS5, 8, NOTE_G5, 2, NOTE_C5, 8, NOTE_C5, 8, NOTE_C5, 8,
  NOTE_F5, 2, NOTE_C6, 2,
  NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F6, 2, NOTE_C6, 4,

  NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F6, 2, NOTE_C6, 4, //8
  NOTE_AS5, 8, NOTE_A5, 8, NOTE_AS5, 8, NOTE_G5, 2, NOTE_C5, -8, NOTE_C5, 16,
  NOTE_D5, -4, NOTE_D5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
  NOTE_F5, 8, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 4, NOTE_D5, 8, NOTE_E5, 4, NOTE_C5, -8, NOTE_C5, 16,
  NOTE_D5, -4, NOTE_D5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,

  NOTE_C6, -8, NOTE_G5, 16, NOTE_G5, 2, REST, 8, NOTE_C5, 8, //13
  NOTE_D5, -4, NOTE_D5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
  NOTE_F5, 8, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 4, NOTE_D5, 8, NOTE_E5, 4, NOTE_C6, -8, NOTE_C6, 16,
  NOTE_F6, 4, NOTE_DS6, 8, NOTE_CS6, 4, NOTE_C6, 8, NOTE_AS5, 4, NOTE_GS5, 8, NOTE_G5, 4, NOTE_F5, 8,
  NOTE_C6, 1

};

void tocar(int melody[], int tamanho) {
  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = tamanho / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}




void robot_frente()
{
  Serial.println("Frente\n");
  analogWrite(M_A1, 0);
  analogWrite(M_A2, 0);
  analogWrite(M_B1, 255);
  analogWrite(M_B2, 0);
}

void robot_tras()
{
  Serial.println("Tras\n");
  digitalWrite(M_A1, HIGH);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, HIGH);
}

void turn_right()
{
  Serial.println("Direita\n");
  digitalWrite(M_A1, HIGH);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);
}

void turn_left()
{
  Serial.println("Esquerda\n");
  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, HIGH);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, HIGH);
}

void robot_parar()
{
  Serial.println("Para\n");
  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, LOW);
}

void buzina()
{
  tone(buzzer, 660, 200);

  delay(200);

  noTone(buzzer);

  tone(buzzer, 660, 200);

  delay(200);

  noTone(buzzer);
}

void liga_led()
{
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  control = 1;
}

void apaga_led()
{
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  control = 0;
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32Robot"); //Nome do dispositivo
  Serial.println("O dispositivo foi iniciado!");
  pinMode(M_B1, OUTPUT);
  pinMode(M_B2, OUTPUT);
  pinMode(M_A1, OUTPUT);
  pinMode(M_A2, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  potValue = analogRead(potPin);
  
  if(potValue < 30){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }

  if(potValue > 80 and control == 0){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
  if (SerialBT.available()) {
    int action = SerialBT.parseInt();
    switch (action)
    {
      case FRENTE:
        robot_frente();
        delay(200);
        robot_parar();
        break;

      case TRAS:
        robot_tras();
        delay(200);
        robot_parar();
        break;

      case DIREITA:
        turn_right();
        delay(d);
        robot_parar();
        break;

      case ESQUERDA:
        turn_left();
        delay(d);
        robot_parar();
        break;

      case PISCA:
        Serial.println("Pisca");
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        delay(100);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        delay(100);
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        delay(100);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        break;

      case BUZINA:
        Serial.println("Buzina");
        buzina();
        Serial.println("Acabou");
        break;

      case ASAB:
        Serial.println("Asa");
        tocar(melodyAsa, sizeof(melodyAsa));
        Serial.println("Acabou");
        break;

      case PARAB:
        Serial.println("Parabens");
        tocar(melodyPara, sizeof(melodyPara));
        Serial.println("Acabou");
        break;

      case STARW:
        Serial.println("Star Wars");
        tocar(melodyStar, sizeof(melodyStar));
        Serial.println("Acabou");
        break;

      case LIGAR:
        liga_led();
        break;
        
      case APAGAR:
        apaga_led();
        break;
        
      default:
        break;
    }
  }
  delay(20);
}
