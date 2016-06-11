void setup(void)
{
  pinMode(RTCLK_CS, OUTPUT);       // chip select pin
  pinMode(COD_CLK, INPUT);
  pinMode(COD_DT, INPUT);
  pinMode(COD_SW, INPUT);
  pinMode(RTCLK_INT, INPUT);

  DS3234_init(RTCLK_CS, DS3234_INTCN);

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
  GotoDisplayTemp();
  RotDetect = false;

  SetAlarmMinutes();

  //TESTS
  Seuils[0][EXTERIEUR_L] = 15.2;
  Seuils[0][EXTERIEUR_H] = 24.7;
  Seuils[0][INTERIEUR]   = 22.6;
  Seuils[0][CHEMINEE]    = 50.0;
  Seuils[0][PUIT_CANAD]  = 15.2;
  Hysteresis[0][EXTERIEUR_L] = 1.2;
  Hysteresis[0][EXTERIEUR_H] = 2.7;
  Hysteresis[0][INTERIEUR]   = 1.6;
  Hysteresis[0][CHEMINEE]    = 5.0;
  Hysteresis[0][PUIT_CANAD]  = 3.2;
  MinMax[MIN][EXTERIEUR_L] = -8.3;
  MinMax[MIN][EXTERIEUR_H] = -8.3;
  MinMax[MIN][INTERIEUR]   = 19.9;
  MinMax[MIN][CHEMINEE]    = 18.7;
  MinMax[MIN][PUIT_CANAD]  = 13.2;
  MinMax[MAX][EXTERIEUR_L] = 33.2;
  MinMax[MAX][EXTERIEUR_H] = 33.2;
  MinMax[MAX][INTERIEUR]   = 22.2;
  MinMax[MAX][CHEMINEE]    = 95.0;
  MinMax[MAX][PUIT_CANAD]  = 17.2;
  Temperatures[EXTERIEUR_L] = 19.9;
  Temperatures[EXTERIEUR_H] = 19.9;
  Temperatures[INTERIEUR]   = 21.8;
  Temperatures[CHEMINEE]    = 51.7;
  Temperatures[PUIT_CANAD]  = 15.4;
  TemperatureDepasseSeuil[EXTERIEUR_L] = true;
  TemperatureDepasseSeuil[EXTERIEUR_H] = false;
  TemperatureDepasseSeuil[INTERIEUR]   = false;
  TemperatureDepasseSeuil[CHEMINEE]    = true;
  TemperatureDepasseSeuil[PUIT_CANAD]  = false;

  Reglage = ETE;
}

