#include "MCP3221.h"

const byte DEV_ADDR = 0x4D;                       // I2C address of the MCP3221 (Change as needed)

MCP3221 mcp3221(DEV_ADDR);

void setup() {
    Serial.begin(115200);
    Wire.begin();
    while(!Serial);
    printDivider();
    Serial.print(F("\nWater Level Sense V1.0\n"));
    printDivider();
    Serial.print(F("\nINITIATING SERIAL COMMUNICATION\n"));  
    Serial.print(F("\nSerial Port is "));
    Serial.print(Serial ? "Open\n" : "Could not be opened\n"); 
    printDivider();
    Serial.print(F("\nINITIALIZING TESTS\n"));
    testPingDevice();
}

void loop() {
  getPressureKPa();
  delay(2000);
}

void getPressureKPa(){
  //Pressure equation:
  //Vout = 5*(0.09*pressure + 0.04) ± (Pressure Error x Temp. Factor x 0.09 x VS)
  //pressure = (4/9)*(5*x-1)
  unsigned int reading = mcp3221.getVoltage();
  
  double pressure = (4.0/9)*(5*reading/1000.0-1);



  Serial.print(F("\n\nVoltage:  "));
  Serial.print(reading);
  Serial.print(F("mV\n"));
  Serial.print(F("Pressure:  "));
  Serial.print(pressure, 3);
  Serial.print(F("KPa\n"));  
}

void testPingDevice() {
    Serial.print(F("\nSearching for device...Device "));
    Serial.print(mcp3221.ping() ? (F("Not Found\n")) : (F("Found!\n")));
    printDivider(); 
}

void testGetReading() {
    unsigned int reading = mcp3221.getVoltage();
    Serial.print(F("\n\nVoltage:  "));
    Serial.print(reading);
    Serial.print(F("mV\n\n"));
}

void printDivider() {
    Serial.print(F("\n-----------------------------------------\n"));
}
