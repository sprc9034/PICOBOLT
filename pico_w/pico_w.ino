
#include <Keyboard.h>                           
#include <KeyboardBLE.h>

#define modekey 22

int longPressDelay = 100;                   //customizable encoderValues
int spamSpeed = 15;
int rowval=5;
int colval=15;
char KEY_SPACE = ' ';
byte inputs[] = {7, 8, 9, 10, 11, 12, 13,14,15,16,17,18,19,20,21};          //declaring inputs and outputs
const int inCount = sizeof(inputs)/sizeof(inputs[0]);
byte outputs[] = {2,3,4,5,6};
const int outCount = sizeof(outputs)/sizeof(outputs[0]);

char layout[5][15] = {               //layout grid for characters
    {KEY_ESC,   '1',   '2',   '3',   '4',   '5',   '6',   '7',   '8',   '9',   '0', '-',  '=',  KEY_BACKSPACE,'`' },
    {KEY_TAB,    'q',    'w',    'e',    'r',    't',    'y',    'u',    'i',    'o',    'p', '[', ']', '\\',KEY_PRINT_SCREEN},
    {KEY_CAPS_LOCK,    'a',    's',    'd',    'f',    'g',    'h',    'j',    'k',    'l', ';', '\'', ' ',    KEY_RETURN, KEY_F11},
    {KEY_LEFT_SHIFT,    'z',    'x',    'c',    'v',    'b',    'n',    'm', ',',  '.', '/', '_', ' ',    KEY_UP_ARROW , KEY_F12},
    {KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT,' ',  ' ',' ', ' ', ' ', ' ',  ' ', KEY_RIGHT_ALT, KEY_DELETE, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW }
};



int keyDown[5][15];
int modestate=0;
void setup(){
  pinMode(modekey, INPUT_PULLDOWN);

  for(int i=0; i<outCount; i++){    //declaring all the outputs and setting them high
    pinMode(outputs[i],OUTPUT);
    digitalWrite(outputs[i],HIGH);
  }
  for(int i=0; i<inCount; i++){     //declaring all the inputs and activating the internal pullup resistor
    pinMode(inputs[i],INPUT_PULLUP);
  }
  Serial.begin(115200);
  Serial1.begin();
  KeyboardBLE.begin();
  Keyboard.begin();
  delay(500);

  if(digitalRead(modekey)==HIGH)
  {

    modestate=1;

  }
  
  else
  {
      modestate=0;
  }

}



//Main loop going through all the keys, then waiting 0.5ms
void loop() {

  
  for (int i=0; i<rowval; i++)
  {    
    digitalWrite(outputs[i],LOW);   //setting one row low
    delayMicroseconds(5);           //giving electronics time to settle down
    
    for(int j=0; j<colval; j++)
    {
      if(digitalRead(inputs[j]) == LOW)
      {
        keyPressed(i,j);            //calling keyPressed function if one of the inputs reads low
      }
      else if(keyDown[i][j] != 0)   //resetting the key if it is not pressed any more
      {  
        resetKey(i,j);
      }
    }
    
    digitalWrite(outputs[i],HIGH);
    delayMicroseconds(500);         //setting the row high and waiting 0.5ms until next cycle
  }

  while (Serial1.available()) {
      delay(1);
    if (Serial1.available() >0) {
      char c = Serial1.read();

      if(c=='1')
      {
        if(modestate==HIGH)
        {
        KeyboardBLE.pressm(VOLUME_UP);
        KeyboardBLE.releasem();
        }

         else
         {

          Keyboard.writeRaw(0x80);
          
         }

        }

        if(c=='2')
       {
        if(modestate==1)
        {
        KeyboardBLE.pressm(VOLUME_DOWN);
        KeyboardBLE.releasem();
        }

         else
         {

          Keyboard.writeRaw(0x81);

         }

        }

        if(c=='3')
        {
          if(modestate==1)
        {
        KeyboardBLE.pressm(MEDIA_NEXT);
        KeyboardBLE.releasem();
        }

         else
         {

          Keyboard.writeRaw(0xeb);

         }

        }

        if(c=='4')
        {
          if(modestate==1)
        {
        KeyboardBLE.pressm(MEDIA_PREV);
        KeyboardBLE.releasem();
        }

        else
         {

          Keyboard.writeRaw(0xea);

         }

        }

        if(c=='5')
        {
          if(modestate==1)
        {
        KeyboardBLE.pressm(MEDIA_PLAY_PAUSE);
        KeyboardBLE.releasem();
        }

        else
         {

          Keyboard.writeRaw(0xe8);

         }

        }

        
    }
}

 if(digitalRead(modekey)==HIGH && modestate!=1)
  {

    modestate=1;

  }

   if(digitalRead(modekey)==LOW && modestate!=0)
  {

    modestate=0;

  }

  }






//if a key is pressed, this Funtion is called and outputs to serial the key location, it also sends the keystroke if not already done so
void keyPressed(int row, int col){
      
   if(keyDown[row][col]==0)  
   {

    if(layout[row][col]==KEY_F11)
    {
      if(modestate==1)
        {
      KeyboardBLE.pressm(VOLUME_MUTE);
      KeyboardBLE.releasem();
        }

        else
        {
          Keyboard.writeRaw(0x7F);

        }
      
      }

     
        else
        {
         if(modestate==1)
        {
          KeyboardBLE.press(layout[row][col]);
        }

        else
        {
         Keyboard.press(layout[row][col]);
        }
      }
   }
 
  keyDown[row][col]++;
}





void resetKey(int row, int col){ //resetting the variables after key is released        
  keyDown[row][col] = 0;
  KeyboardBLE.release(layout[row][col]);
  Keyboard.release(layout[row][col]);
}

