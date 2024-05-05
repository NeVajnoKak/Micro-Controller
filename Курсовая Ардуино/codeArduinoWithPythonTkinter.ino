#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>

SoftwareSerial mySoftwareSerial(2, 3); // RX, TX для плеера DFPlayer Mini 
DFRobotDFPlayerMini myDFPlayer;
int buttonNext = 8;   // кнопка следующий трек
int buttonPause = 9;  // кнопка пауза/пуск
int buttonPrevious = 10; // кнопка предыдущий трек 
int buttonVolumeUp = 11; // кнопка увеличение громкости
int buttonVolumeDown = 12; // кнопка уменьшение громкости
boolean isPlaying = false; // статус воспроизведения/пауза

void setup() {
  pinMode(buttonPause, INPUT_PULLUP); 
  pinMode(buttonNext, INPUT_PULLUP);
  pinMode(buttonPrevious, INPUT_PULLUP);
  pinMode(buttonVolumeUp, INPUT_PULLUP);
  pinMode(buttonVolumeDown, INPUT_PULLUP);
  mySoftwareSerial.begin(9600); 
  Serial.begin(9600);
  delay(1000);
  Serial.println();
  Serial.println("DFPlayer Mini Demo");
  Serial.println("Initializing DFPlayer...");
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("Unable to begin:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(300);
  //----Set volume----
  myDFPlayer.volume(5); //Set volume value (0~30).
  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  myDFPlayer.play(2); //Воспроизведение первого mp3
  isPlaying = true; // воспроизводим
  Serial.println("Playing..");
  //----Читать информацию----
  Serial.println(myDFPlayer.readState()); //читать состояние mp3
  Serial.println(myDFPlayer.readVolume()); //Текущая громкость 
  Serial.println(myDFPlayer.readEQ()); // читаем настройку эквалайзера
  Serial.println(myDFPlayer.readFileCounts()); // читать все файлы на SD-карте
  Serial.println(myDFPlayer.readCurrentFileNumber()); // текущий номер файла воспроизведения
}

void loop() {
  if (Serial.available() > 0) {
  char command = Serial.read();
  switch (command) {
    case 'p':
      if (isPlaying) {
        myDFPlayer.pause();
        isPlaying = false;
        Serial.println("Paused..");
      } else {
        isPlaying = true;
        myDFPlayer.start();
      }
      break;
    case 'n':
      if (isPlaying) {
        myDFPlayer.next();
        Serial.println("Next Song..");
      }
      break;
    case 'b':
      if (isPlaying) {
        myDFPlayer.previous();
        Serial.println("Previous Song..");
      }
      break;
    case 'u':
      if (isPlaying) {
        myDFPlayer.volumeUp();
        Serial.println("Volume Up..");
      }
      break;
    case 'd':
      if (isPlaying) {
        myDFPlayer.volumeDown();
        Serial.println("Volume Down..");
      }
      break;
  }
}

  if (digitalRead(buttonPause) == LOW) {
    if (isPlaying) { // если было воспроизведение трека
      myDFPlayer.pause(); // пауза
      isPlaying = false; // пауза
      Serial.println("Paused..");
    } else {        // иначе
      isPlaying = true; // воспроизводим
      myDFPlayer.start(); //запускаем mp3 с паузы
    }
    delay(500);
  }
  if (digitalRead(buttonNext) == LOW) {
    if (isPlaying) {
      myDFPlayer.next(); //Next Song
      Serial.println("Next Song..");
    }
    delay(500);
  }
  if (digitalRead(buttonPrevious) == LOW) {
    if (isPlaying) {
      myDFPlayer.previous(); //Previous Song
      Serial.println("Previous Song..");
    }
    delay(500);
  }
  if (digitalRead(buttonVolumeUp) == LOW) {
    if (isPlaying) {
      myDFPlayer.volumeUp(); //Volume Up
      Serial.println("Volume Up..");
    }
    delay(500);
  }
  if (digitalRead(buttonVolumeDown) == LOW) {
    if (isPlaying) {
      myDFPlayer.volumeDown(); //Volume Down
      Serial.println("Volume Down..");
    }
    delay(500);
  }
}
