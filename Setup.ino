void setup(void)
{
  pinMode(RTCLK_CS, OUTPUT);       // chip select pin
  DS3234_init(RTCLK_CS, DS3234_INTCN);

  pinMode(COD_CLK, INPUT);
  pinMode(COD_DT, INPUT);
  pinMode(COD_SW, INPUT);
  pinMode(RTCLK_INT, INPUT);
  
  MenuChanged = true;
  RotDetect = false;
  delay(1000);

  /*Mise en place des interruptions pour les mouvements du codeur*/
  attachInterrupt(digitalPinToInterrupt(COD_DT),    RotationDetectDT,  CHANGE  );
  attachInterrupt(digitalPinToInterrupt(COD_CLK),   RotationDetectCLK, CHANGE  );
  attachInterrupt(digitalPinToInterrupt(COD_SW),    Selection,         RISING  );
  attachInterrupt(digitalPinToInterrupt(RTCLK_INT), RTClockInterrupt,  FALLING );

  /*Start des services*/
  Serial.begin(9600);
  SdCardPresent = SD.begin(SDCARD_CS);
  tft.begin();

  tft.setRotation(3);

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

  //DisableRTC(); // a implémenter si pas de RTC trouvé
  ReadTime();

  GotoStartMenu();
  DisplayMenuScreen();
  delay(1000);     // à remplacer par fin de phase d'init
  GotoMainMenu();  // à remplacer par écran principal
  RotDetect = false;

  SetAlarmMinutes();
}

