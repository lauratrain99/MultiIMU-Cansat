#include <SPI.h>
#include <SD.h>
#include <Wire.h>

File myFile;
const int SDA_2 = 26;
const int SCL_2 = 25;

const int MPU2 = 0x69, MPU1=0x68;
const int MPU3 = 0x69, MPU4=0x68;
short accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;
short gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float gForceX2, gForceY2, gForceZ2;
unsigned long mytime;

char buf[40];

void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  /*if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  myFile = SD.open("ELE.txt", FILE_WRITE);*/
  
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

  Wire1.begin(SDA_2, SCL_2, 100000);
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

  Wire1.begin(SDA_2, SCL_2, 100000);
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

  if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
  }

  
  writeFile(SD, "/log.txt", "Init file imu log: \n");
  

}
void loop() {
// nothing happens after setup
  
  
  Serial.print("IMU1 | ");
  appendFile(SD, "/log.txt", "IMU1 | ");
  appendFile(SD, "/log.txt", "T = ");
  sprintf(buf, "%.4f", millis()/1000.0);
  appendFile(SD, "/log.txt", buf );

  GetMpuValue1(MPU1);
  appendFile(SD, "/log.txt", "\n");

  appendFile(SD, "/log.txt", "IMU2 | ");
  appendFile(SD, "/log.txt", "T = ");
  sprintf(buf, "%.4f", millis()/1000.0);
  appendFile(SD, "/log.txt", buf );
  
  GetMpuValue1(MPU2);
  appendFile(SD, "/log.txt", "\n");

  appendFile(SD, "/log.txt", "IMU3 | ");
  appendFile(SD, "/log.txt", "T = ");
  sprintf(buf, "%.4f", millis()/1000.0);
  appendFile(SD, "/log.txt", buf );

  GetMpuValue2(MPU3);
  appendFile(SD, "/log.txt", "\n");
  
  appendFile(SD, "/log.txt", "IMU4 | ");
  appendFile(SD, "/log.txt", "T = ");
  sprintf(buf, "%.4f", millis()/1000.0);
  appendFile(SD, "/log.txt", buf );
  
  GetMpuValue2(MPU4);
  appendFile(SD, "/log.txt", "\n");
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

    Serial.print(" ANG_VEL[deg/s]: ");
    appendFile(SD, "/log.txt", " ANG_VEL[deg/s]: ");
  
    Serial.print(rotX,5);
    sprintf(buf, "%.4f", rotX);
    appendFile(SD, "/log.txt", buf );
    appendFile(SD, "/log.txt", "; ");
    
    Serial.print(rotY,5);
    sprintf(buf, "%.4f", rotY);
    appendFile(SD, "/log.txt", buf );
    appendFile(SD, "/log.txt", "; ");
    
    Serial.print(rotZ,5);
    sprintf(buf, "%.4f", rotZ);
    appendFile(SD, "/log.txt", buf );
    appendFile(SD, "/log.txt", "; ");

    Serial.print("ACC[g]: ");
    appendFile(SD, "/log.txt", "ACC[g]: ");

    Serial.print(gForceX,5);
    sprintf(buf, "%.4f", gForceX);
    appendFile(SD, "/log.txt", buf );
    appendFile(SD, "/log.txt", "; ");
    
    Serial.print(gForceY,5);
    sprintf(buf, "%.4f", gForceY);
    appendFile(SD, "/log.txt", buf );
    appendFile(SD, "/log.txt", "; ");

    Serial.print(gForceZ,5);
    sprintf(buf, "%.4f", gForceZ);
    appendFile(SD, "/log.txt", buf );
    appendFile(SD, "/log.txt", "; ");
    
    appendFile(SD, "/log.txt", "\n");
    
  delay(25);

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
  
    Serial.print(" ANG_VEL[deg/s]: ");
    appendFile(SD, "/log.txt", " ANG_VEL[deg/s]: ");
  
    Serial.print(rotX,5);
    sprintf(buf, "%.4f", rotX);
    appendFile(SD, "/log.txt", buf );
    appendFile(SD, "/log.txt", "; ");
    
    Serial.print(rotY,5);
    sprintf(buf, "%.4f", rotY);
    appendFile(SD, "/log.txt", buf );
    appendFile(SD, "/log.txt", "; ");
    
    Serial.print(rotZ,5);
    sprintf(buf, "%.4f", rotZ);
    appendFile(SD, "/log.txt", buf );
    appendFile(SD, "/log.txt", "; ");

    Serial.print("ACC[g]: ");
    appendFile(SD, "/log.txt", "ACC[g]: ");

    Serial.print(gForceX,5);
    sprintf(buf, "%.4f", gForceX);
    appendFile(SD, "/log.txt", buf );
    appendFile(SD, "/log.txt", "; ");
    
    Serial.print(gForceY,5);
    sprintf(buf, "%.4f", gForceY);
    appendFile(SD, "/log.txt", buf );
    appendFile(SD, "/log.txt", "; ");

    Serial.print(gForceZ,5);
    sprintf(buf, "%.4f", gForceZ);
    appendFile(SD, "/log.txt", buf );
    appendFile(SD, "/log.txt", "; ");
    
    appendFile(SD, "/log.txt", "\n");
    
  
  delay(100);

}


void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}
