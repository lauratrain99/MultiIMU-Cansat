const int ledPIN = 26;

#include <SPI.h>
#include <SD.h>
File myFile;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);    //iniciar puerto serie
  //pinMode(ledPIN , OUTPUT);  //definir pin como salida

  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(33)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  myFile = SD.open("test.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("This is a test file :)");
    myFile.println("testing 1, 2, 3.");
    for (int i = 0; i < 20; i++) {
      myFile.println(i);
    }
  // close the file:
  myFile.close();
  Serial.println("done.");
  } else {
  // if the file didn't open, print an error:
  Serial.println("error opening test.txt");
  }
}
  

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(ledPIN , HIGH);   // poner el Pin en HIGH
  //delay(1000);                   // esperar un segundo
  //digitalWrite(ledPIN , LOW);    // poner el Pin en LOW
  //delay(1000);                   // esperar un segundo
}
