#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR   0x3C
#define LED_PIN    2
#define LED_COUNT 68
#define CLK 12
#define  DT 11
#define SW 10
#define CLK1 8
#define  DT1 7
#define SW1 6

int currentStateCLK;
int lastStateCLK;
unsigned  long lastButtonPress = 0;
int currentStateCLK1;
int lastStateCLK1;
unsigned  long lastButtonPress1 = 0;
char colname[10];
int a=20;
int color=1;
int aprev=a;
int colorprev=color;
int b=30;
char colread[10]="MAGENTA";
int modelast;
int modecurr;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t magenta = strip.Color(255, 0, 255);
uint32_t cyan = strip.Color(0, 255, 255);
uint32_t yellow = strip.Color(180, 255, 0);
uint32_t orange = strip.Color(255, 30, 0);
uint32_t white = strip.Color(150, 150, 150);
uint32_t silver_blue = strip.Color(100, 100, 200);
uint32_t neon_green = strip.Color(120, 255, 0);
uint32_t gold = strip.Color(255, 255, 0);
uint32_t sky = strip.Color(0, 140, 255);
uint32_t off = strip.Color(0,0,0);
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);


void setup() {

  
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW,  INPUT_PULLUP);
  pinMode(CLK1,INPUT);
  pinMode(DT1,INPUT);
  pinMode(SW1,  INPUT_PULLUP);
  Serial.begin();
  Serial1.begin();
  strip.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  strcpy(colread, colname);
  checkcolor();
}

void loop()
{
  checkencoder();
  checkencoder1();

  
    if(color>10)
    {
      color=1;
    }

    if(color<1)
    {
      color=10;
    }

    if(a<10)
    {
      a=10;
    }

    if(a>100)
    {
      a=100;
    }

     if(colorprev != color)

      {
        checkcolor();
      }

     if(aprev != a)
     {
      displayssd();
      aprev=a;
     }
      strip.setBrightness(a);
      strip.show();
    
  }




  
  
void checkencoder()
{

  currentStateCLK = digitalRead(CLK); //CLK current value
  int btnState = digitalRead(SW);  // ButurrentStateCLK) 
 if (currentStateCLK != lastStateCLK  && currentStateCLK == 1)
   
       {  

        if(btnState == LOW){

    if (digitalRead(DT) != currentStateCLK) 
    
     { 
      color+=1;
      delay(2);

     } 
    
    else
     
     {  
        color-=1;
        delay(2);
    }

  }

  else
  {
    
    if (digitalRead(DT) != currentStateCLK) 
    
     { 
      a+=10;
      delay(2);

     } 
    
    else
     
     {  
        a-=10;
        delay(2);
    }
    
    
    }

       } 
 
lastStateCLK  = currentStateCLK; // Last CLK Value
}

   

    
  
   


  void checkencoder1()
{

  currentStateCLK1 = digitalRead(CLK1); //CLK current value
   int btnState1 = digitalRead(SW1);  // Button Value
 
  if (currentStateCLK1 != lastStateCLK1  && currentStateCLK1 == 1)
   
       {  

        if(btnState1 == LOW){

    if (digitalRead(DT1) != currentStateCLK1) 
    
     { 
      Serial1.write('3');
      delay(2);

     } 
    
    else
     
     {  
        Serial1.write('4');
        delay(2);
    }

  }

  else
  {
    
    if (digitalRead(DT1) != currentStateCLK1) 
    
     { 
      Serial1.write('1');
      delay(2);

     } 
    
    else
     
     {  
        Serial1.write('2');
        delay(2);
    }
    
    
    }

       }



  lastStateCLK1  = currentStateCLK1; // Last CLK Value

   

    if (btnState1 == LOW) { // Switch pushed
    
    
    
    

    if  (millis() - lastButtonPress1 > 50) 
    { 
    
       Serial1.write('5');
    }

   
    lastButtonPress1 = millis();
  }

  delay(1); // Push swithc delay


  
  
  }

  void displayssd()
  {
      display.clearDisplay();  
      display.setCursor(0, 0);
      display.print("CR:");
      display.println(colname);
      display.print("BR:");
      display.println(a);
      display.println();
      display.print("BATT:");
      display.print(b);
      display.display();
      delay(2);
  }



  void checkcolor()
  {
    
   switch(color) 
   
        {
          case 1:     
                      strcpy(colname, "MAGENTA");
                      for(int i=0;i<LED_COUNT;i++)
                      {
                      strip.setPixelColor(i, magenta);
                      }
                      strip.show();
                      displayssd();
                      colorprev = color;
                      break;

          case 2:     
                      strcpy(colname, "CYAN");
                      for(int i=0;i<LED_COUNT;i++)
                      {
                      strip.setPixelColor(i, cyan);
                      }
                      strip.show();
                      displayssd();
                      colorprev = color;
                      break;

          case 3:     
                      strcpy(colname, "YELLOW");
                      for(int i=0;i<LED_COUNT;i++)
                      {
                      strip.setPixelColor(i, yellow);
                      }
                      strip.show();
                      displayssd();
                      colorprev = color;
                      break;

          case 4:     
                      strcpy(colname, "ORANGE");
                      for(int i=0;i<LED_COUNT;i++)
                      {
                      strip.setPixelColor(i, orange);
                      }
                      strip.show();
                      displayssd();
                      colorprev = color;
                      break;

          case 5:     
                      strcpy(colname, "WHITE");
                      for(int i=0;i<LED_COUNT;i++)
                      {
                      strip.setPixelColor(i, white);
                      }
                      strip.show();
                      displayssd();
                      colorprev = color;
                      break;

          case 6:     
                      strcpy(colname, "SILBLUE");
                      for(int i=0;i<LED_COUNT;i++)
                      {
                      strip.setPixelColor(i, silver_blue);
                      }
                      strip.show();
                      displayssd();
                      colorprev = color;
                      break;

          case 7:     
                      strcpy(colname, "N_GREEN");
                      for(int i=0;i<LED_COUNT;i++)
                      {
                      strip.setPixelColor(i, neon_green);
                      }
                      strip.show();
                      displayssd();
                      colorprev = color;
                      break;

          case 8:     
                      strcpy(colname, "GOLD");
                      for(int i=0;i<LED_COUNT;i++)
                      {
                      strip.setPixelColor(i, gold);
                      }
                      strip.show();
                      displayssd();
                      colorprev = color;
                      break;      

          case 9:     
                      strcpy(colname, "SKY");
                      for(int i=0;i<LED_COUNT;i++)
                      {
                      strip.setPixelColor(i, sky);
                      }
                      strip.show();
                      displayssd();
                      colorprev = color;
                      break;     

          case 10:     
                      strcpy(colname, "OFF");
                      for(int i=0;i<LED_COUNT;i++)
                      {
                      strip.setPixelColor(i, off);
                      }
                      strip.show();
                      displayssd();
                      colorprev = color;
                      break;                                   
        }




  }



