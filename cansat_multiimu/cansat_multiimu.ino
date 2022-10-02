const int CSPIN = 33;

#include <SPI.h>
#include <SD.h>
File myFile;

void setup() {
  Serial.begin(9600);    

  while (!Serial) {
  ; 
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(CSPIN)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("This is a test file :)");
    myFile.println("testing 1, 2, 3.");
    for (int i = 0; i < 20; i++) {
      myFile.println(i);
    }
  myFile.close();
  Serial.println("done.");
  } else {
  Serial.println("error opening test.txt");
  }
}
  

void loop() {
}
