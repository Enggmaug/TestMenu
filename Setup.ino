void setup(void)
{
  pinMode(COD_CLK, INPUT);
  pinMode(COD_DT, INPUT);
  pinMode(COD_SW, INPUT);
  MenuChanged = true;
  RotDetect = false;
  delay(1000);

  /*Mise en place des interruptions pour les mouvements du codeur*/
  attachInterrupt(digitalPinToInterrupt(COD_DT), RotationDetectDT, CHANGE );
  attachInterrupt(digitalPinToInterrupt(COD_CLK), RotationDetectCLK, CHANGE );
  attachInterrupt(digitalPinToInterrupt(COD_SW), Selection, RISING );

  /*Start des services*/
  Serial.begin(9600);
  SdCardPresent = SD.begin(SDCARD_CS);
  tft.begin();

  tft.setRotation(3);

  GotoMainMenu();
  MenuChanged = true;
  Reglage = MI_SAISON;

  if (SdCardPresent)
  {
    ReadSeuilsFromFile();
  }
  else
  {
    DisableSD();
  }

  DisableRTC(); // A modifier lorsque le module RTC sera implémenté avec acces à la librarie du MAX3234
  //DateHeureCourante = ReadTime();
}
