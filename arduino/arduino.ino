
static int counts = 0;
static int sn = 0;

class TempPin {
  private:
    int counter;
    float analogFilter;
    uint8_t pin;
  public:
     TempPin(uint8_t _pin);
     int loop();
};

TempPin::TempPin(uint8_t _pin) {
  counter=0;
  pin=_pin;
  analogFilter=0;
}

float toC(int v) {
  return (v / 1024.0 * 500.0) - 273.15;
}

int TempPin::loop() {
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
 if (false) {
  if (counter%200 == 0)
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
 return analogValue;
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
 int a0 = p0.loop();
 int a1 = p1.loop();
 int a2 = p2.loop();
 int a3 = p3.loop();
 int a4 = p4.loop();
 int a5 = p5.loop();

 if (counts%200 == 0)
 {
   Serial.print(sn);
   Serial.print(" ");
   Serial.print(millis()/1000);
   Serial.print(" ");
   Serial.print(a0);
   Serial.print(" ");
   Serial.print(a1);
   Serial.print(" ");
   Serial.print(a2);
   Serial.print(" ");
   Serial.print(a3);
   Serial.print(" ");
   Serial.print(a4);
   Serial.print(" ");
   Serial.print(a5);
   Serial.print(" ");
   Serial.print(toC(a0));
   Serial.print(" ");
   Serial.print(toC(a1));
   Serial.print(" ");
   Serial.print(toC(a2));
   Serial.print(" ");
   Serial.print(toC(a3));
   Serial.print(" ");
   Serial.print(toC(a4));
   Serial.print(" ");
   Serial.print(toC(a5));
   Serial.print("\n");
   sn++;

 }
 
  counts++;
}

