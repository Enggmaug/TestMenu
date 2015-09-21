void setup() {

  pinMode(COD_CLK, INPUT);
  pinMode(COD_DT, INPUT);
  pinMode(COD_SW, INPUT);
  MenuChanged = true;
  RotDetect = false;
  delay(1000);
  
  attachInterrupt(digitalPinToInterrupt(COD_DT), RotationDetectDT, CHANGE );
  attachInterrupt(digitalPinToInterrupt(COD_CLK), RotationDetectCLK, CHANGE );
  attachInterrupt(digitalPinToInterrupt(COD_SW), Selection, RISING );
  
  Serial.begin(9600);
  SdCardPresent = SD.begin(SDCARD_CS);
  tft.begin();

  tft.setRotation(3);
  tft.fillScreen(ILI9340_BLACK);

  GotoMainMenu();
  MenuChanged = true;
  Reglage = MI_SAISON;



  if (SdCardPresent)
  {
  ReadSeuilsFromFile();
  }
}
