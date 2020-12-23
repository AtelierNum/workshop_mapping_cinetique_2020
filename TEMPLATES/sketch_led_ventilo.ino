//
// Parse incoming messages consisting of three decimal values followed by a carriage return
//  Example  "12 34 56\n"
//  In TouchDesigner:     op('serial1').send("12 34 56", terminator="\n")
//

#include <Adafruit_NeoPixel.h> // Charge la librairie Neo Pixel d'Adafruit utilisé pour piloter le ruban de LED

#define PIXEL_PIN 10 // On définit le pin où est connecté la patte DATA du bandeau
#define PIXEL_COUNT 4 // On définit le nombre de LED compris sur le Ruban de LED soit 150 pour le ruban de 5m50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800); // Paramètre l'objet strip qui correspond à toute les LED du ruban


char buffer[15];   //maximum expected length 
int len = 0;

void setup()
{
  strip.begin(); // Lance la connection
  strip.show(); // Initialise toute les led à 'off'
  Serial.begin(9600); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
}
void loop()
{
    if (Serial.available() > 0) 
    {
        int incomingByte = Serial.read();
        buffer[len++] = incomingByte;
        //
        // check for overflow
        //
        if (len >= 15)
        {
            // overflow, resetting
            len = 0;
        }
        //
        // check for newline (end of message)
        //
        if (incomingByte == '\n')
        {
            int red, green, blue, vent1, vent2;
            int n = sscanf(buffer, "%d %d %d %d %d", &red, &green, &blue, &vent1, &vent2);
            Serial.println(vent1);
            if (vent1 == 1) 
            {
              digitalWrite(13, HIGH);
            }
            else
            {
              digitalWrite(13, LOW);
              
            }
            if (n == 5)
            {
                all(red, green, blue);
              
                digitalWrite(6, vent1);
                digitalWrite(5, vent2);
         
            }
            else
            {
                 // parsing error, reject
            }
            len = 0; // reset buffer counter
        }
    }
}


void all(int r, int v, int b)
{
   for(int i = 0 ; i < 4 ; i++)
  {
     strip.setPixelColor(i, r, v, b);
  }
  strip.show();
   delay(10); 
}
