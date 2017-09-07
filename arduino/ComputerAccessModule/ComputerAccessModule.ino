const uint8_t buzzerPin = 15;
const uint8_t ledGrnPin = 16;
const uint8_t ledRedPin = 17;

char receivedArray[20];
uint8_t receivedArrayIndex;

void setup() {
  // put your setup code here, to run once:
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  Serial.begin(9600); 
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t readFlag = 0;
  uint8_t readByteFromReader;
  
  //Serial.println("Hello, world! :)");
  while(Serial1.available()){
    readByteFromReader = Serial1.read();
    //Serial.write(Serial1.read());
    readFlag = 1;
  }


//probably 12 bytes

  if(readFlag){
    if(readByteFromReader == 2){
      Serial.print("New Scan.\n\r");
      receivedArrayIndex = 0;
    }
    Serial.print("Read Byte. ");
    Serial.print("Byte available: ");
    Serial.print((char) readByteFromReader);
    Serial.print(" : ");
    Serial.print(readByteFromReader);
    Serial.print("\n\r");

    if(readByteFromReader > 30){ //We don't want any control codes in our ID
      receivedArray[receivedArrayIndex++] = readByteFromReader; 
    }

    if(readByteFromReader == 3){

      Serial.print("Read ID of : ");
      for(int i = 0; i < receivedArrayIndex; ++i){
        Serial.print((char) receivedArray[i]);
      }
      Serial.print("\n\r");
      Serial.print("-----\n\r");
      if(strcmp(receivedArray, "123456") == 0){ //Is the card we want (replace with target ID)
        tone(buzzerPin, 440, 250);
        digitalWrite(ledGrnPin, HIGH);
        delay(250);
        digitalWrite(ledGrnPin, LOW);
        Keyboard.set_key1(KEY_ENTER);
        Keyboard.send_now();
        Keyboard.set_key1(0);
        Keyboard.send_now();
        delay(750);
        Keyboard.print("password");
        Keyboard.set_key1(KEY_ENTER);
        Keyboard.send_now();
        Keyboard.set_key1(0);
        Keyboard.send_now();
        delay(250);
      }
      else { //Failed auth 
        for(int i = 0; i < 3; ++i){
          tone(buzzerPin, 230, 250);       
          digitalWrite(ledRedPin, HIGH);
          delay(100);
          digitalWrite(ledRedPin, LOW);
          delay(160);
        }
      }
    }
  }

}
