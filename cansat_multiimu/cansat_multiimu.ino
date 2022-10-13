#include <SPI.h>
#include <SD.h>
#include <Wire.h>

File myFile;
const int MPU2 = 0x69, MPU1=0x68;
const int MPU3 = 0x69, MPU4=0x68;
short accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;
short gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float gForceX2, gForceY2, gForceZ2;
unsigned long mytime;


void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  myFile = SD.open("ELE.txt", FILE_WRITE);
  
  Wire.begin();
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();  
  Wire.beginTransmission(MPU1);
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission(); 
  Wire.beginTransmission(MPU1);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission(); 

  Wire.begin();
  Wire.beginTransmission(MPU2);
  Wire.write(0x6B);
  Wire.write(0b00000000); 
  Wire.endTransmission();  
  Wire.beginTransmission(MPU2); 
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission(); 
  Wire.beginTransmission(MPU2);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission(); 

  Wire1.begin();
  Wire1.beginTransmission(MPU3);
  Wire1.write(0x6B);
  Wire1.write(0b00000000);
  Wire1.endTransmission();  
  Wire1.beginTransmission(MPU3);
  Wire1.write(0x1B);
  Wire1.write(0x00000000);
  Wire1.endTransmission(); 
  Wire1.beginTransmission(MPU3);
  Wire1.write(0x1C);
  Wire1.write(0b00000000);
  Wire1.endTransmission(); 

  Wire1.begin();
  Wire1.beginTransmission(MPU4);
  Wire1.write(0x6B);
  Wire1.write(0b00000000); 
  Wire1.endTransmission();  
  Wire1.beginTransmission(MPU4); 
  Wire1.write(0x1B);
  Wire1.write(0x00000000);
  Wire1.endTransmission(); 
  Wire1.beginTransmission(MPU4);
  Wire1.write(0x1C);
  Wire1.write(0b00000000);
  Wire1.endTransmission(); 

}
void loop() {
// nothing happens after setup
  
  
  Serial.print("IMU1 | ");
  //myFile.print("IMU1 | ");
  //Serial.print("T = ");
  //myFile.print("T = ");
  //Serial.print(millis()/1000.0, 4);
  //myFile.print(millis()/1000.0,4);
  //Serial.print(" ");
  //myFile.print(" ");

  GetMpuValue1(MPU1);
  Serial.println("");

  Serial.print("IMU2 | ");
  myFile.print("IMU2 | ");
  Serial.print("T = ");
  myFile.print("T = ");
  Serial.print(millis()/1000.0, 4);
  myFile.print(millis()/1000.0,4);
  Serial.print(" ");
  myFile.print(" ");
  
  GetMpuValue1(MPU2);
  Serial.println("");

  Serial.print("IMU3 | ");
  myFile.print("IMU3 | ");
  Serial.print("T = ");
  myFile.print("T = ");
  Serial.print(millis()/1000.0, 4);
  myFile.print(millis()/1000.0,4);
  Serial.print(" ");
  myFile.print(" ");
  
  GetMpuValue2(MPU3);
  Serial.println("");

  Serial.print("IMU4 | ");
  myFile.print("IMU4 | ");
  Serial.print("T = ");
  myFile.print("T = ");
  Serial.print(millis()/1000.0, 4);
  myFile.print(millis()/1000.0,4);
  Serial.print(" ");
  myFile.print(" ");
  
  GetMpuValue2(MPU4);
  Serial.println("");

  //if (mytime > 5000.0F)
  //{
    //myFile.close();
  //}*/
}

void GetMpuValue1(const int MPU){
  Wire.beginTransmission(MPU); 
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(MPU,6);
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); 
  accelY = Wire.read()<<8|Wire.read(); 
  accelZ = Wire.read()<<8|Wire.read();
  
  Wire.beginTransmission(MPU);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(MPU,6);
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read();
  gyroY = Wire.read()<<8|Wire.read();
  gyroZ = Wire.read()<<8|Wire.read(); 


  gForceX = (float)accelX / 16384.0;
  gForceY = (float)accelY / 16384.0; 
  gForceZ = (float)accelZ / 16384.0;
  rotX = (float)gyroX / 131.0;
  rotY = (float)gyroY / 131.0; 
  rotZ = (float)gyroZ / 131.0;

  if (myFile){
    Serial.print("ANG_VEL[deg/s]: ");
    myFile.print("ANG_VEL[deg/s]: ");
    Serial.print(rotX,5);
    myFile.print(rotX,5);
    Serial.print("; ");
    myFile.print("; ");
    Serial.print(rotY,5);
    myFile.print(rotY,5);
    Serial.print("; ");
    myFile.print("; ");
    Serial.print(rotZ,5);
    myFile.print(rotZ,5);
    Serial.print("; ");
    myFile.print("; ");
    Serial.print("\t ACC[g]: ");
    myFile.print("\t ACC[g]: ");
    Serial.print(gForceX,5);
    myFile.print(gForceX,5);
    Serial.print("; ");
    myFile.print("; ");
    Serial.print(gForceY,5);
    myFile.print(gForceY,5);
    Serial.print("; ");
    myFile.print("; ");
    Serial.print(gForceZ,5);
    myFile.print("; ");
  }
  
  delay(100);

}

void GetMpuValue2(const int MPU){
  Wire1.beginTransmission(MPU); 
  Wire1.write(0x3B);
  Wire1.endTransmission();
  Wire1.requestFrom(MPU,6);
  while(Wire1.available() < 6);
  accelX = Wire1.read()<<8|Wire1.read(); 
  accelY = Wire1.read()<<8|Wire1.read(); 
  accelZ = Wire1.read()<<8|Wire1.read();
  
  Wire1.beginTransmission(MPU);
  Wire1.write(0x43);
  Wire1.endTransmission();
  Wire1.requestFrom(MPU,6);
  while(Wire1.available() < 6);
  gyroX = Wire1.read()<<8|Wire1.read();
  gyroY = Wire1.read()<<8|Wire1.read();
  gyroZ = Wire1.read()<<8|Wire1.read(); 

  gForceX = (float)accelX / 16384.0;
  gForceY = (float)accelY / 16384.0; 
  gForceZ = (float)accelZ / 16384.0;
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;

  if (myFile){
    Serial.print("ANG_VEL[deg/s]: ");
    myFile.print("ANG_VEL[deg/s]: ");
    Serial.print(rotX,5);
    myFile.print(rotX,5);
    Serial.print("; ");
    myFile.print("; ");
    Serial.print(rotY,5);
    myFile.print(rotY,5);
    Serial.print("; ");
    myFile.print("; ");
    Serial.print(rotZ,5);
    myFile.print(rotZ,5);
    Serial.print("; ");
    myFile.print("; ");
    Serial.print("\t ACC[g]: ");
    myFile.print("\t ACC[g]: ");
    Serial.print(gForceX,5);
    myFile.print(gForceX,5);
    Serial.print("; ");
    myFile.print("; ");
    Serial.print(gForceY,5);
    myFile.print(gForceY,5);
    Serial.print("; ");
    myFile.print("; ");
    Serial.print(gForceZ,5);
    myFile.print("; ");
  }
  
  delay(100);

}
