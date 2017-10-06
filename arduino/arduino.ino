
void breakline()
{
 static int counts = 0;
 counts++;
 
 if (counts%20 == 0)
 {
   Serial.print("\n");
 }
}

class TempPin {
  private:
    int counter;
    float analogFilter;
    uint8_t pin;
  public:
     TempPin(uint8_t _pin);
     void loop();
};

TempPin::TempPin(uint8_t _pin) {
  counter=0;
  pin=_pin;
  analogFilter=0;
}

void TempPin::loop() {
 int analogValue;

 float temperatureC;
 float temperatureF;
 
 analogValue = analogRead (pin);
 delay(10);
 analogValue = analogRead (pin);
 
 if (analogFilter == 0)
   analogFilter = float(analogValue);
 else
   analogFilter = (analogFilter*99 + float(analogValue)) / 100;
   
    analogFilter = float(analogValue);
   
 temperatureC = (analogFilter / 1024.0 * 500.0) - 273.15;
 
 temperatureF = temperatureC * 9.0 / 5.0 + 32.0;
 
 counter++;
 
 if (counter%20 == 0)
 {
   Serial.print("Temp @");
   Serial.print(pin);
   Serial.print("="); 
   Serial.print(temperatureF);
   Serial.print(","); 
   Serial.print(analogValue);
   
   Serial.print("\n");
 }
}

TempPin p0(A0);
TempPin p1(A1);
TempPin p2(A2);
TempPin p3(A3);
TempPin p4(A4);
TempPin p5(A5);

void setup()
{
  Serial.begin(9600);
  Serial.print("RESET\n");
}
  
void loop()
{
 breakline();
 p0.loop();
 p1.loop();
 p2.loop();
 p3.loop();
 p4.loop();
 p5.loop();
}
