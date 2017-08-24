//*************LCD*************************
#include <LiquidCrystal.h>//for lcd

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// Setup the LiquidCrystal library with the pin numbers we have
                                      // physically connected the module to.
int lastUpdate = 0;
int currentIndex = 0;
char* lyrics[] = { 
  "*****WELCOME*****", 
  "   RETION SHOP   ",
  "     plees       ",
  "swipe your card..."
}; 
//**************IFID reader**************************
#include <SoftwareSerial.h>//for if reder
SoftwareSerial mySerial(9, 10);                // Setup the RFID reader with the pin numbers we have
                                               // physically connected the module to.
void setup() {
//*******************set up for lcd*****************************
  lcd.begin(16, 2);                            // Setup the number of columns and rows that are available on the LCD. 
  lcd.clear();
//*******************set up for RFID reader*****************************
  mySerial.begin(9600);                        // rf-Setting the baud rate of Software Serial Library  
  Serial.begin(9600);                          //rf-Setting the baud rate of Serial Monitor 
}
void loop() {
  int time;
  int s = 0;
  
  while(1) {
    time = millis();
    if(mySerial.available()> 0 ){       
      readrfid();
      delay(100);
      s=1;        
    } else if(s ==0 && (time  - lastUpdate) >= 800) {
      welcome();
      lastUpdate = time;                      
    }
  }
}

void welcome()  {
  // Move the cursor back to the first column of the first row.
  lcd.setCursor(0, 0);
  
  if (currentIndex == 0 || currentIndex == 2){
    // clear the screen and print the appropriate line.  
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print(lyrics[currentIndex]);
  }
  else{
    lcd.setCursor(0, 1);
    lcd.print(lyrics[currentIndex]);
  }
  if (currentIndex == 3){                 // Increment or reset the current index.
    currentIndex = 0;
  }
  else{
    currentIndex += 1;
  }
}

void readrfid() {
  String n="1234567890";
  for(int i=0;i<10;i++) {  
    // SYMCHRONIZE WITH DEVICE  
    delay(10);
    //read 10 digit id no: 
    n.setCharAt(i, (char)mySerial.read());
  }
  // checksum read
  mySerial.read();
  mySerial.read();
  
  lcd.clear(); 
  lcd.setCursor(0, 0);
    
  if(n == "0006268497"){
    lcd.print("vineeth"); 
  } else if(n == "0009132617"){
    lcd.print("suhaib");
  }  
  
  lcd.setCursor(0, 1);
  lcd.print("ID :"+n);

}

