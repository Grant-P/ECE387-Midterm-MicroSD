/*Author: Grant Picker
*ECE 387 - Midterm
*Interfaces a 16x2 LCD and a MicroSD adaptor with an Arduino Uno microcontroller
*
*16 March 2017
*/

//Include libraries
#include <LiquidCrystal.h>
#include <SD.h>
#include <SPI.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //Initialize the LiquidCrystal object with the pins in use
int confirmPin = 9; //Digital pin for button to confirm each letter being selected
int selectPin = A0; //Analog pin for potentiometer.  Value determines letter being selected and then displayed
int csPin = 10; //Chip Select pin for the MicroSD adaptor

File file;
String text = "";

void setup() {
  Serial.begin(9600);//Serial communication for debugging when connected to computer with USB

  pinMode(confirmPin, INPUT);
  lcd.begin(16, 2);//Initialize lcd display, 2 lines of 16 characters
  lcd.print("Ready");
  initializeSD();
  
}

void loop() {
  //Initialize values
  bool done = false;//Indicates whether or not text gathering has completed
  text = "";
  
  //Set up the LCD to display in the correct position
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("File name:");
  lcd.setCursor(0, 1);//Character 0, row 1
  
  //Get file name
  while(!done){
    done = getLetter();
  }
  
  //Make the text into a file name, copy it to a char array, and create the file with that name
  text += ".txt";
  char filename[(text.length()+1)];
  text.toCharArray(filename,(text.length()+1));
  createFile(filename);
  
  //Write to the file.  Any actions can be done with the file at this point
  writeToFile("Test successful\n");
  
  //Close file and indicate display success message
  closeFile();
  lcd.clear();
  lcd.print("File saved.");
  delay(1000);
  
}

//Function for displaying the letter being selected, and adding it to the string of text
//once it has been confirmed.  Returns TRUE if text gathering is complete, and FALSE otherwise
bool getLetter(){
  //Initialize local variables
  String letter, stuff = "";
  int value;
  
  //Until the button is pressed, display the character being selected at the
  //end of the text already being displayed
  while(digitalRead(confirmPin) == LOW){
    value = analogRead(selectPin);
    if(value < 32) letter = "a";
    else if(value >= 32 && value < 64) letter = "b";
    else if(value >= 64 && value < 96) letter = "c";
    else if(value >= 96 && value < 128) letter = "d";
    else if(value >= 128 && value < 160) letter = "e";
    else if(value >= 160 && value < 192) letter = "f";
    else if(value >= 192 && value < 224) letter = "g";
    else if(value >= 224 && value < 256) letter = "h";
    else if(value >= 256 && value < 288) letter = "i";
    else if(value >= 288 && value < 320) letter = "j";
    else if(value >= 320 && value < 352) letter = "k";
    else if(value >= 352 && value < 384) letter = "l";
    else if(value >= 384 && value < 416) letter = "m";
    else if(value >= 416 && value < 448) letter = "n";
    else if(value >= 448 && value < 480) letter = "o";
    else if(value >= 480 && value < 512) letter = "p";
    else if(value >= 512 && value < 544) letter = "q";
    else if(value >= 544 && value < 576) letter = "r";
    else if(value >= 576 && value < 608) letter = "s";
    else if(value >= 608 && value < 640) letter = "t";
    else if(value >= 640 && value < 672) letter = "u";
    else if(value >= 672 && value < 704) letter = "v";
    else if(value >= 704 && value < 736) letter = "w";
    else if(value >= 736 && value < 768) letter = "x";
    else if(value >= 768 && value < 800) letter = "y";
    else if(value >= 800 && value < 832) letter = "z";
    else if(value >= 832 && value < 864) letter = "0";
    else if(value >= 864 && value < 896) letter = "1";
    else if(value >= 896 && value < 928) letter = "_";
    else if(value >= 928 && value < 960) letter = "-";
    else if(value >= 960 && value < 992) letter = "<";//Backspace. Delete the previous character
    else letter = "E"; //Enter. The text is done
    
    stuff = text + letter;//Temporary string for displaying the previous characters plus the one currently being selected
    lcd.setCursor(0,1);//Set the cursor at the beginning of the second row of characters to start printing in the correct position
    lcd.print(stuff);
  }
  
  //When the button is pressed, add the currently selected letter to the end
  //of the text
  
  //Wait until the button is low again to proceed.
  while(digitalRead(confirmPin) == HIGH){}
  
  //If the character is "Enter", the text is done, ending the text gathering
  //even if the string is less than 16 characters long.  Note that it does not
  //add the E onto the string being stored
  if(letter.equals("E"))
    return true;
    
  //If the character is "Backspace", remove the last character from the string
  if(letter.equals("<")){
    text.remove(text.length()-1);
    lcd.clear();
    return false;
  }
  
  //Otherwise, it's a normal character.  Add to the string and return
  text += letter;
  //If the text has reached the limit of 16 characters, return
  if(text.length() >= 16)
    return true;
    
  return false;
}

//Call the begin() function from the SD library to initialize the SD, or print an error if it fails.
void initializeSD() {
  Serial.println("Initializing SD card...");
  pinMode(csPin, OUTPUT);

  if (SD.begin()) {
    Serial.println("SD card ready to use.");
  }else {
    Serial.println("Initialization failed");
    return;
  }
}

//Create a new file on the SD, or print an error if it fails
int createFile(char filename[]) {
  file = SD.open(filename, FILE_WRITE);

  if (file) {
    Serial.println("File created successfully.");
    return 1;
  }else {
    Serial.println("Error while creating file.");
    return 0;
  }
}

//Write text to the file, or print an error if it fails
int writeToFile(char text[]) {
  if (file) {
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  }else {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

//Close the file when done using
void closeFile() {
  if (file) {
    file.close();
    Serial.println("File closed");
  }
}
