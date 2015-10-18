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

  tft.setRotation(1);

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
  MinMax[0][EXTERIEUR_L] = -8.3;
  MinMax[0][EXTERIEUR_H] = -8.3;
  MinMax[0][INTERIEUR]   = 19.9;
  MinMax[0][CHEMINEE]    = 18.7;
  MinMax[0][PUIT_CANAD]  = 13.2;
  MinMax[1][EXTERIEUR_L] = 33.2;
  MinMax[1][EXTERIEUR_H] = 33.2;
  MinMax[1][INTERIEUR]   = 22.2;
  MinMax[1][CHEMINEE]    = 95.0;
  MinMax[1][PUIT_CANAD]  = 17.2;
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

