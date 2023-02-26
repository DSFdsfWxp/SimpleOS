
#include "Arduino.h"
#include "keyScanD.h"

void keyScanD::start(){
    Serial.println("hello keyScanD !");
}

keyScanD::~keyScanD(){
    Serial.println("goodbye keyScanD !");
}