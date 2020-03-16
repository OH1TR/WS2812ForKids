#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    30
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];


CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
    delay( 1000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    Serial.begin(115200);

}

void loop()
{
  if( Serial.available())
  {
    char ch = Serial.read();
    if(ch=='S')
    {
      unsigned int led,r,g,b;
      if(ReadValue(&led,2) && ReadValue(&r,2) && ReadValue(&g,2) && ReadValue(&b,2) && led>=0 && led<NUM_LEDS)
      {
        leds[led].red=r;     
        leds[led].green=g;
        leds[led].blue=b;
      }
    }
    if(ch=='D')
      FastLED.show();

    while(true)
    {
        while(!Serial.available());
        if(Serial.read()==10)
          break;
    }
  }
}

bool ReadValue(unsigned int *retval,byte chars)
{
  *retval=0;
  
  for(int i=0;i<chars;i++)
  {
    while(!Serial.available());  
    char ch = Serial.read();
    int val=HexToVal(ch);
    if(val==-1)
      return(false);
    *retval=(*retval) << 4;
    *retval=(*retval) | val;      
  }
  return(true);  
}

int HexToVal(char ch)
{
  if(ch>='0' && ch <='9')
    return((int)ch-'0');

  if(ch>='A' && ch <='F')
    return((int)ch-'A'+10);

  return(-1);    
}
