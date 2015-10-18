
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
  const uint8_t flags[5] = {1, 1, 1, 1, 1};
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
