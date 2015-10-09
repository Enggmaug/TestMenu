
void ToggleMaintenance(void)
{
}
void BacktoFunctional(void)
{

}

/*---------------------------------------------------------------------------------------------*/
/*                          GESTION DU CHANGEMENT DE REGLAGE                                   */
/*---------------------------------------------------------------------------------------------*/
void SetEte(void)
{
  Reglage = ETE;
}

void SetMiSaison(void)
{
  Reglage = MI_SAISON;
}

void SetHivers(void)
{
  Reglage = HIVERS;
}

/*---------------------------------------------------------------------------------------------*/
/*                          GESTION DE MODIFICATION DES SEUILS                                 */
/*---------------------------------------------------------------------------------------------*/
void SetOnOff(void)
{
  static bool Changing = false;

  Changing = not(Changing);

  if (Changing == true)
  {
    if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuSeuils[0][0]) == 0)
    {
      SetSeuilPlusMoins (0);
      EcranEnCours.Droite = SetSeuilPlus;
      EcranEnCours.Gauche = SetSeuilMoins;
    }
    if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_Hysteresis[0][0]) == 0)
    {
      SetHysteresisPlusMoins (0);
      EcranEnCours.Droite = SetHysteresisPlus;
      EcranEnCours.Gauche = SetHysteresisMoins;
    }
  }
  else
  {
    tft.setTextColor(NOIR);
    tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), BLANC);
    EcranEnCours.Droite = Suivant;
    EcranEnCours.Gauche = Precedent;
    tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
    tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
    MenuChanged = false;
    MenuAction = NONE;
  }
}

void SetSeuilPlus(void)
{
  SetSeuilPlusMoins(1);
}
void SetSeuilMoins(void)
{
  SetSeuilPlusMoins(-1);
}
void SetSeuilPlusMoins(int Direction)
{
  if (Direction > 0) Direction = 1;
  else if (Direction < 0) Direction = -1;

  Seuils[Reglage][EcranEnCours.SelectedItem - 1] += (Direction * 0.5);
  MenuChanged = false;
  MenuAction = NONE;
  AddValToLine(EcranEnCours.SelectedItem);
  tft.setTextColor(ROUGE);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), NOIR);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}

void SetHysteresisPlus(void)
{
  SetHysteresisPlusMoins(1);
}
void SetHysteresisMoins(void)
{
  SetHysteresisPlusMoins(-1);
}
void SetHysteresisPlusMoins(int Direction)
{
  if (Direction > 0) Direction = 1;
  else if (Direction < 0) Direction = -1;

  Hysteresis[Reglage][EcranEnCours.SelectedItem - 1] += (Direction * 0.1);
  MenuChanged = false;
  MenuAction = NONE;
  AddValToLine(EcranEnCours.SelectedItem);
  tft.setTextColor(ROUGE);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), NOIR);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}

/*---------------------------------------------------------------------------------------------*/
/*                              SEUILS : LECTURE / ECRITURE /                                  */
/*---------------------------------------------------------------------------------------------*/
void ReadSeuilsFromFile(void)
{
  unsigned int idx;
  char *pt_read;

  if (SD.exists("Seuils.par")) // Si le fichier Seuils.par existe, on le lit
  {
    File dataFile = SD.open("Seuils.par", FILE_READ);
    if (dataFile)
    {
      pt_read = (char*) &Seuils[0];
      for (idx = 0; idx < sizeof(Seuils); idx ++)
      {
        pt_read[idx] = dataFile.read();
      }
    }
    dataFile.close();
  }
  else                        // Si le fichier Seuils.par n'existe pas, on le créé à partir des seuils courants
  {
    WriteSeuilsToFile();
  }
}

void WriteSeuilsToFile(void) // Ecriture des Seuils dans le fichier Seuils.par
{
  unsigned int idx;
  char *pt_read;
  File dataFile = SD.open("Seuils.par", FILE_WRITE);
  dataFile.seek(0);
  pt_read = (char*) &Seuils[0][0];
  for (idx = 0; idx < sizeof(Seuils); idx ++)
  {
    dataFile.write(pt_read[idx]);
  }
  dataFile.close();
}

void ReadHysterFromFile(void)
{
  unsigned int idx;
  char *pt_read;

  if (SD.exists("Hyst.par")) // Si le fichier Seuils.par existe, on le lit
  {
    File dataFile = SD.open("Hyst.par", FILE_READ);
    if (dataFile)
    {
      pt_read = (char*) &Hysteresis[0];
      for (idx = 0; idx < sizeof(Hysteresis); idx ++)
      {
        pt_read[idx] = dataFile.read();
      }
    }
    dataFile.close();
  }
  else                        // Si le fichier Seuils.par n'existe pas, on le créé à partir des seuils courants
  {
    WriteHysterToFile();
  }
}

void WriteHysterToFile(void) // Ecriture des Seuils dans le fichier Seuils.par
{
  unsigned int idx;
  char *pt_read;
  File dataFile = SD.open("Hyst.par", FILE_WRITE);
  dataFile.seek(0);
  pt_read = (char*) &Hysteresis[0][0];
  for (idx = 0; idx < sizeof(Hysteresis); idx ++)
  {
    dataFile.write(pt_read[idx]);
  }
  dataFile.close();
}

/*---------------------------------------------------------------------------------------------*/
/*                                AFFICHAGE DES HISTORIQUES                                    */
/*---------------------------------------------------------------------------------------------*/
void ShowHistoExt(void)
{
}
void ShowHistoInt(void)
{
}
void ShowHistoPuit(void)
{
}
void ShowHistoChem(void)
{
}


/*---------------------------------------------------------------------------------------------*/
/*                                CHANGEMENT DE MODE                                           */
/*---------------------------------------------------------------------------------------------*/
void SetModePlus(void)
{
  SetMode(1);
}

void SetModeMoins(void)
{
  SetMode(-1);
}

void SetMode(int Direction)
{
  switch (Reglage)
  {
    case ETE:
      Reglage = Direction > 0 ? MI_SAISON : HIVERS;
      break;
    case MI_SAISON:
      Reglage = Direction > 0 ? HIVERS : ETE;
      break;
    case HIVERS :
      Reglage = Direction > 0 ? ETE : MI_SAISON;
      break;
    default:
      Reglage = ETE;
  }
  AddModeToLine(EcranEnCours.SelectedItem);
  tft.setTextColor(ROUGE);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), NOIR);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}

/*---------------------------------------------------------------------------------------------*/
/*            Sauvegarde, ou pas des seuils, puis navigation vers ecran principal              */
/*---------------------------------------------------------------------------------------------*/
void SaveSeuils2File(void)
{
  WriteSeuilsToFile();
  GotoMainMenu();
}

void RecallSeuils(void)
{
  ReadSeuilsFromFile();
  GotoMainMenu();
}

void SaveHyster2File(void)
{
  WriteHysterToFile();
  GotoMainMenu();
}

void RecallHyster(void)
{
  ReadHysterFromFile();
  GotoMainMenu();
}
/*---------------------------------------------------------------------------------------------*/
/*                              Sauvegarde de la date ou de l'heure                            */
/*---------------------------------------------------------------------------------------------*/
void SaveDate(void)
{
  WriteTime();
  GotoSetDateHeure();
}

void SaveTime(void)
{
  WriteTime();
  GotoSetDateHeure();
}

void RecallDate(void)
{
  Serial.println("Recall");
  ReadTime();
  GotoSetDateHeure();
}

void RecallTime(void)
{
  Serial.println("Recall");
  ReadTime();
  GotoSetDateHeure();
}
/*---------------------------------------------------------------------------------------------*/
/*                                        INTERRUPTIONS                                        */
/*---------------------------------------------------------------------------------------------*/
// Rotation à droite
void RotationDetectCLK(void)
{
  noInterrupts();
  if (digitalRead(COD_CLK) != digitalRead(COD_DT))
  {
    if (RotDetect == false)
    {
      MenuAction = DROITE;
      RotDetect = true;
    }
  }
  interrupts();
}

// Rotation à gauche
void RotationDetectDT(void)
{
  noInterrupts();
  if (digitalRead(COD_CLK) != digitalRead(COD_DT))
  {
    if (RotDetect == false)
    {
      MenuAction = GAUCHE;
      RotDetect = true;
    }
  }
  interrupts();
}

// Click
void Selection(void)
{
  noInterrupts();
  if (RotDetect == false)
  {
    delay(100);
    RotDetect = true;
    MenuAction = SELECT;
  }
  interrupts();
}

void RTClockInterrupt(void)
{
  RTClockAlarm = true;
}

/*---------------------------------------------------------------------------------------------*/
/*                         Actionnement des commandes suite aux interruptions                  */
/*---------------------------------------------------------------------------------------------*/
void ManageRotation(void)
{
  switch (MenuAction)                        // En fonction de l'action bouton, on appele la fonction pointée par le menu
  {
    case GAUCHE :
      EcranEnCours.Gauche();
      break;
    case DROITE :
      EcranEnCours.Droite();
      break;
    case SELECT :
      EcranEnCours.Select();
      break;
    case NONE :
    default :
      break;
  }
  RotDetect = false;                          // L'action ayant été traitée, on la désactive
  MenuAction = NONE;
}

/*---------------------------------------------------------------------------------------------*/
/*             Interdiction des Items qui ne sont pas accessibles si pas de SD                 */
/*---------------------------------------------------------------------------------------------*/
void DisableSD(void)
{
  int idx;
  bool   tab_SauvegarderEnableTemp[ct_MenuHistNbItems]            =  {true, false, true , true                    };
  for (idx = 0; idx < ct_SauvegarderNbItems; idx ++)
  {
    tab_SauvegarderSDEnable[idx] = tab_SauvegarderEnableTemp[idx];
  }
  MenuChanged = true;
}

/*---------------------------------------------------------------------------------------------*/
/*       Interdiction des Items qui ne sont pas accessibles si pas de Real Time Clock          */
/*---------------------------------------------------------------------------------------------*/
void DisableRTC(void)
{
  int idx;
  bool   tab_MenuMainEnableTemp[ct_MenuMainNbItems]        =  {true, true , true , true , true , false, true};
  bool   tab_MenuDateHeureEnableTemp[ct_MenuSeuilsNbItems] =  {true, false, false, true                     };
  bool   tab_MenuDateEnableTemp[ct_MenuHistNbItems]        =  {true, false, false, false, true              };
  bool   tab_MenuHeureEnableTemp[ct_MenuHistNbItems]       =  {true, false, false, true                     };
  bool   tab_SauvegarderEnableTemp[ct_MenuHistNbItems]            =  {true, false, true , true                    };

  for (idx = 0; idx < ct_MenuMainNbItems; idx ++)
  {
    tab_MenuMainEnable[idx] = tab_MenuMainEnableTemp[idx];
  }
  for (idx = 0; idx < ct_MenuDHNbItems; idx ++)
  {
    tab_MenuDateHeureEnable[idx] = tab_MenuDateHeureEnableTemp[idx];
  }
  for (idx = 0; idx < ct_MenuDatebItems; idx ++)
  {
    tab_MenuDateEnable[idx] = tab_MenuDateEnableTemp[idx];
  }
  for (idx = 0; idx < ct_MenuHeureNbItems; idx ++)
  {
    tab_MenuHeureEnable[idx] = tab_MenuHeureEnableTemp[idx];
  }
  for (idx = 0; idx < ct_SauvegarderNbItems; idx ++)
  {
    tab_SauvegarderRTCEnable[idx] = tab_SauvegarderEnableTemp[idx];
  }
  MenuChanged = true;
}

/*---------------------------------------------------------------------------------------------*/
/*                                Reccuperation des Températures                               */
/*---------------------------------------------------------------------------------------------*/
void GetTemperatures(void)
{
  int idx;
  const int PinNumber[NB_TEMP] = {T_EXT, T_EXT, T_INT, T_CHEMINEE, T_PUIT};

  for (idx = 1; idx < NB_TEMP ; idx ++)
  {
    Temperatures[idx] = ReadTemperature(PinNumber[idx]);
  }
  Temperatures[0] = Temperatures[1];  // Les Deux premieres températures sont la même, car on a 2 seuils pour l'exterieur
}

float ReadTemperature(int AnalogPinNumber) // A ECRIRE
{
  if (AnalogPinNumber > 0)
    return (analogRead(AnalogPinNumber));
  else
    return (0.0);
}


void Reset(void)
{

}


void CheckTemperatures (void)
{
  int idx;
  for (idx = 0; idx < NB_TEMP; idx++)
  {
    if (TemperatureDepasseSeuil[idx] == true)
    {
      if (Temperatures[idx] < ( Seuils[Reglage][idx] - Hysteresis[Reglage][idx]))
      {
        TemperatureDepasseSeuil[idx] = false;
      }
    }
    else
    {
      if (Temperatures[idx] > ( Seuils[Reglage][idx] + Hysteresis[Reglage][idx]))
      {
        TemperatureDepasseSeuil[idx] = true;
      }
    }
  }
}

/*---------------------------------------------------------------------------------------------*/
/*                                        Gestion RTC                                          */
/*---------------------------------------------------------------------------------------------*/
void ReadTime(void)
{
  DS3234_get(RTCLK_CS, &DateHeureCourante);
}
void WriteTime(void)
{
  DS3234_set(RTCLK_CS, DateHeureCourante);
  delay(500);
  DateHeureCourante = BlankDateHeure;
  ReadTime();
}

void SetAlarmMinutes(void)
{
  // flags are: A1M1 (seconds), A1M2 (minutes), A1M3 (hour), A1M4 (day) 0 to enable, 1 to disable, DY/DT (dayofweek == 1/dayofmonth == 0)
  const uint8_t flags[5] = {0, 1, 1, 1, 1};
  DS3234_set_a1(RTCLK_CS, 0, 0, 0, 0, &flags[0]);

      // activate Alarm1
    DS3234_set_creg(RTCLK_CS, DS3234_INTCN | DS3234_A1IE);
  
}

/*---------------------------------------------------------------------------------------------*/
/*                          GESTION DE MODIFICATION DE DATE                                    */
/*---------------------------------------------------------------------------------------------*/
void SetDateOnOff(void)
{
  static bool ChangingDate = false;

  ChangingDate = not(ChangingDate);

  if (ChangingDate == true)
  {
    SetDatePlusMoins (0);
    EcranEnCours.Droite = SetDatePlus;
    EcranEnCours.Gauche = SetDateMoins;
  }
  else
  {
    tft.setTextColor(NOIR);
    tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), BLANC);
    EcranEnCours.Droite = Suivant;
    EcranEnCours.Gauche = Precedent;
    tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
    tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
    MenuChanged = false;
    MenuAction = NONE;
  }
}
void SetDatePlus(void)
{
  SetDatePlusMoins(1);
}
void SetDateMoins(void)
{
  SetDatePlusMoins(-1);
}
void SetDatePlusMoins(int Direction)
{
  char str_blank[NB_CAR_LIGNE] = {0};

  if (Direction > 0) Direction = 1;
  else if (Direction < 0) Direction = -1;

  switch (EcranEnCours.SelectedItem)
  {
    case 1:
      DateHeureCourante.year += (Direction);
      if (DateHeureCourante.year < 2015)
        DateHeureCourante.year = 2015;
      break;
    case 2:
      DateHeureCourante.mon += (Direction);
      if (DateHeureCourante.mon < 1)
        DateHeureCourante.mon = 12;
      else if (DateHeureCourante.mon > 12)
        DateHeureCourante.mon = 1;
      break;
    case 3:
      DateHeureCourante.mday += (Direction);
      if (DateHeureCourante.mday < 1)
        DateHeureCourante.mday = 31;
      else if (DateHeureCourante.mday > 31)
        DateHeureCourante.mday = 1;
      break;
    default:
      break;
  }
  MenuChanged = false;
  MenuAction = NONE;
  int dateItem[ct_MenuDatebItems] = {0, DateHeureCourante.year, DateHeureCourante.mon, DateHeureCourante.mday};

  strncpy(str_blank, BlankLine, NB_CAR_LIGNE - strlen(tab_MenuDate[EcranEnCours.SelectedItem]) - 6);
  str_blank[NB_CAR_LIGNE - strlen(tab_MenuDate[EcranEnCours.SelectedItem]) - 5] = 0;
  sprintf(tab_MenuTemp[EcranEnCours.SelectedItem], "%s%s%02d", tab_MenuDate[EcranEnCours.SelectedItem], str_blank, dateItem[EcranEnCours.SelectedItem]);
  tft.setTextColor(ROUGE);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), NOIR);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}
/*---------------------------------------------------------------------------------------------*/
/*                          GESTION DE MODIFICATION DE l'HEURE                                 */
/*---------------------------------------------------------------------------------------------*/
void SetHeuresOnOff(void)
{
  static bool ChangingHeure = false;

  ChangingHeure = not(ChangingHeure);

  if (ChangingHeure == true)
  {
    SetHeurePlusMoins (0);
    EcranEnCours.Droite = SetHeurePlus;
    EcranEnCours.Gauche = SetHeureMoins;
  }
  else
  {
    tft.setTextColor(NOIR);
    tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), BLANC);
    EcranEnCours.Droite = Suivant;
    EcranEnCours.Gauche = Precedent;
    tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
    tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
    MenuChanged = false;
    MenuAction = NONE;
  }
}
void SetHeurePlus(void)
{
  SetHeurePlusMoins(1);
}
void SetHeureMoins(void)
{
  SetHeurePlusMoins(-1);
}
void SetHeurePlusMoins(int Direction)
{
  char str_blank[NB_CAR_LIGNE] = {0};

  if (Direction > 0) Direction = 1;
  else if (Direction < 0) Direction = -1;

  switch (EcranEnCours.SelectedItem)
  {
    case 1:
      DateHeureCourante.hour += (Direction);
      if (DateHeureCourante.hour == 255)
        DateHeureCourante.hour = 23;
      else if (DateHeureCourante.hour > 23)
        DateHeureCourante.hour = 0;
      break;
    case 2:
      DateHeureCourante.min += (Direction);
      if (DateHeureCourante.min == 255)
        DateHeureCourante.min = 59;
      else if (DateHeureCourante.min > 59)
        DateHeureCourante.min = 0;
      break;
    default:
      break;
  }
  MenuChanged = false;
  MenuAction = NONE;
  int heureItem[ct_MenuHeureNbItems] = {0, DateHeureCourante.hour, DateHeureCourante.min};

  strncpy(str_blank, BlankLine, NB_CAR_LIGNE - strlen(tab_MenuHeure[EcranEnCours.SelectedItem]) - 6);
  str_blank[NB_CAR_LIGNE - strlen(tab_MenuHeure[EcranEnCours.SelectedItem]) - 5] = 0;
  sprintf(tab_MenuTemp[EcranEnCours.SelectedItem], "%s%s%02d", tab_MenuHeure[EcranEnCours.SelectedItem], str_blank, heureItem[EcranEnCours.SelectedItem]);
  tft.setTextColor(ROUGE);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), NOIR);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}

void SaveHistoriques(void)
{
  
  Serial.println("Save Historique");
}

