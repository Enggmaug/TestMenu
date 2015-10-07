/*---------------------------------------------------------------------------------------------*/
/*                           Navigation entre items d'un même menu                             */
/*---------------------------------------------------------------------------------------------*/
void Suivant(void)
{
  ChangeItem(1);
}

void Precedent(void)
{
  ChangeItem(-1);
}

void ChangeItem(int Direction)
{
  if (Direction > 0) Direction = 1;
  else Direction = -1;

  // Redessin de l'item précedemnet sélectionné, avec police blanche sur fond noir
  tft.setTextColor(BLANC);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), NOIR);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));

  do // Tant qu'on tombe sur un item desactivé, on passe au prochain
  {
    EcranEnCours.SelectedItem += Direction;
    if (EcranEnCours.SelectedItem >= EcranEnCours.NbItems)
    {
      EcranEnCours.SelectedItem = 1;
    }
    else if (EcranEnCours.SelectedItem < 1)
    {
      EcranEnCours.SelectedItem = EcranEnCours.NbItems - 1;
    }
  } while (EcranEnCours.pt_tab_EnabledItems[EcranEnCours.SelectedItem] == false);

  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem]; //Reaffectation du pointeur de fonction correspondant à l'item

  // Redessin de l'item  sélectionné, avec police noire sur fond blanc
  tft.setTextColor(NOIR);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), BLANC);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}

/*---------------------------------------------------------------------------------------------*/
/*                                         No Action                                           */
/*---------------------------------------------------------------------------------------------*/
void None(void)
{
}

/*---------------------------------------------------------------------------------------------*/
/*                         Changement de Mode ETE - MI_SAISON - HIVERS                         */
/*---------------------------------------------------------------------------------------------*/
void SetMode(void)
{
  static bool ChangingMode = false;

  ChangingMode = not(ChangingMode);

  if (ChangingMode == true)
  {
    tft.setTextColor(ROUGE);
    tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), NOIR);
    EcranEnCours.Droite = SetModePlus;
    EcranEnCours.Gauche = SetModeMoins;
    tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
    tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
    MenuChanged = false;
    MenuAction = NONE;
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
/*---------------------------------------------------------------------------------------------*/
/*                             Navigation vers écran démarrage                                 */
/*---------------------------------------------------------------------------------------------*/
void GotoStartMenu(void)
{
  int idx;
  const bool tab_enabled[ct_NbItemMax] = {true};
  const FctPtr tab_voidFonctions[ct_NbItemMax] = {None};

  MenuChanged = true;
  for (idx = 0; idx < ct_NbItemMax; idx ++)
  {
    strcpy(tab_MenuTemp[idx], "");
  }
  strcpy(&tab_MenuTemp[0][0], "INITIALISATION");
  sprintf(&tab_MenuTemp[3][0], "%02d/%02d/%04d %02d:%02d", DateHeureCourante.mday, DateHeureCourante.mon, DateHeureCourante.year, DateHeureCourante.hour, DateHeureCourante.min);

  EcranEnCours.pt_tab_menu = (char *)&tab_MenuTemp[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_enabled[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_voidFonctions;
  EcranEnCours.NbItems = ct_NbItemMax;
  EcranEnCours.SelectedItem = 0;
  EcranEnCours.Droite = None;
  EcranEnCours.Gauche = None;
  EcranEnCours.Select = None;
}
/*---------------------------------------------------------------------------------------------*/
/*                             Navigation vers écran menu principal                                 */
/*---------------------------------------------------------------------------------------------*/
void GotoMainMenu(void)
{
  int idx;
  MenuChanged = true;
  for (idx = 0; idx < ct_MenuMainNbItems; idx ++)
  {
    strcpy(tab_MenuTemp[idx], tab_MenuMain[idx]);
  }
  AddModeToLine(1);
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuTemp[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_MenuMainEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuMainFonct;
  EcranEnCours.NbItems = ct_MenuMainNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}
/*---------------------------------------------------------------------------------------------*/
/*                             Navigation vers les seuils                                      */
/*---------------------------------------------------------------------------------------------*/
void GotoSeuils(void)
{
  int idx;
  MenuChanged = true;
  strcpy(tab_MenuTemp[0], tab_MenuSeuils[0]);
  for (idx = 1; idx < ct_MenuSeuilsNbItems - 1; idx ++)
  {
    AddSeuilToLine(idx);
  }
  strcpy(tab_MenuTemp[ct_MenuSeuilsNbItems - 1], tab_MenuSeuils[ct_MenuSeuilsNbItems - 1]);
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuTemp[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_MenuSeuilsEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuSeuilsFonct;
  EcranEnCours.NbItems = ct_MenuSeuilsNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}

/*---------------------------------------------------------------------------------------------*/
/*                              Navigation vers l'ecran d'historiques                          */
/*---------------------------------------------------------------------------------------------*/
void GotoHisto(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuHist[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_MenuHistEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuHistFonct;
  EcranEnCours.NbItems = ct_MenuHistNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}

/*---------------------------------------------------------------------------------------------*/
/*                    Navigation vers l'ecran de Sauvegarde des Seuils                         */
/*---------------------------------------------------------------------------------------------*/

void SaveYesNo(void)
{
  MenuChanged = true;

  if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuSeuils[0][0]) == 0)
  {
    EcranEnCours.pt_MenuFonct = (FctPtr *)tab_SaveSeuilsFonct;
    EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_SauvegarderSDEnable[0];
  }
  else if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuDate[0][0]) == 0)
  {
    EcranEnCours.pt_MenuFonct = (FctPtr *)tab_SaveDateFonct;
    EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_SauvegarderRTCEnable[0];
  }
  else if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuHeure[0][0]) == 0)
  {
    EcranEnCours.pt_MenuFonct = (FctPtr *)tab_SaveHoursFonct;
    EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_SauvegarderRTCEnable[0];
  }
  EcranEnCours.pt_tab_menu = (char *)&tab_Sauvegarder[0][0];
  EcranEnCours.NbItems = ct_SauvegarderNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}

/*---------------------------------------------------------------------------------------------*/
/*                     Navigation vers l'ecran de réglage de la date                           */
/*---------------------------------------------------------------------------------------------*/
void GotoSetDateHeure(void)
{
  int idx;
  MenuChanged = true;
  for (idx = 0; idx <= ct_MenuDHNbItems - 1; idx ++)
  {

    if (strcmp(tab_MenuDateHeure[idx], "DATE ICI") == 0)
    {
      sprintf(tab_MenuTemp[idx], "     %02d/%02d/%04d", DateHeureCourante.mday, DateHeureCourante.mon, DateHeureCourante.year);
    }
    else if (strcmp(tab_MenuDateHeure[idx], "HEURE ICI") == 0)
    {

      sprintf(tab_MenuTemp[idx], "     %02d:%02d", DateHeureCourante.hour, DateHeureCourante.min);
    }
    else
    {
      strcpy(tab_MenuTemp[idx], tab_MenuDateHeure[idx]);
    }
  }
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuTemp[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_MenuDateHeureEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuDateHeureFonct;
  EcranEnCours.NbItems = ct_MenuDHNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}
void GotoSetDate(void)
{
  int idx;
  char str_blank[NB_CAR_LIGNE] = {0};
  int dateItem[ct_MenuDatebItems] = {0, DateHeureCourante.year, DateHeureCourante.mon, DateHeureCourante.mday};

  MenuChanged = true;
  strcpy(tab_MenuTemp[0], tab_MenuDate[0]);
  for (idx = 1; idx < ct_MenuDatebItems - 1; idx ++)
  {
    strncpy(str_blank, BlankLine, NB_CAR_LIGNE - strlen(tab_MenuDate[idx]) - 6);
    str_blank[NB_CAR_LIGNE - strlen(tab_MenuHeure[idx]) - 5] = 0;
    sprintf(tab_MenuTemp[idx], "%s%s%02d", tab_MenuDate[idx], str_blank, dateItem[idx]);
  }
  strcpy(tab_MenuTemp[ct_MenuDatebItems - 1], tab_MenuDate[ct_MenuDatebItems - 1]);

  EcranEnCours.pt_tab_menu = (char *)&tab_MenuTemp[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_MenuDateEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuDateFonct;
  EcranEnCours.NbItems = ct_MenuDatebItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}
void GotoSetHeure(void)
{
  int idx;
  char str_blank[NB_CAR_LIGNE] = {0};
  int heureItem[ct_MenuHeureNbItems] = {0, DateHeureCourante.hour, DateHeureCourante.min};

  strcpy(tab_MenuTemp[0], tab_MenuHeure[0]);
  for (idx = 1; idx < ct_MenuHeureNbItems - 1; idx ++)
  {
    strncpy(str_blank, BlankLine, NB_CAR_LIGNE - strlen(tab_MenuHeure[idx]) - 6);
    str_blank[NB_CAR_LIGNE - strlen(tab_MenuHeure[idx]) - 5] = 0;
    sprintf(tab_MenuTemp[idx], "%s%s%02d", tab_MenuHeure[idx], str_blank, heureItem[idx]);
  }
  strcpy(tab_MenuTemp[ct_MenuHeureNbItems - 1], tab_MenuHeure[ct_MenuHeureNbItems - 1]);

  EcranEnCours.pt_tab_menu = (char *)&tab_MenuTemp[0][0];
  MenuChanged = true;
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_MenuHeureEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuHeureFonct;
  EcranEnCours.NbItems = ct_MenuHeureNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}

/*---------------------------------------------------------------------------------------------*/
/*                  Modification des Items du menu seuil, pour ajouter la valeur               */
/*---------------------------------------------------------------------------------------------*/
char* AddSeuilToLine(int idx)
{
  char* str;
  char DisplayedTemp[8];
  float* Temp;
  Temp = &Seuils[Reglage][idx - 1];
  str = strcpy(tab_MenuTemp[idx], tab_MenuSeuils[idx]);
  str = strncat(str + strlen(str), BlankLine, NB_CAR_LIGNE - NB_CAR_T - strlen(str));
  sprintf(DisplayedTemp, " : %2.1f", *Temp);
  str = strcat(str, DisplayedTemp);

  return (str);
}


/*---------------------------------------------------------------------------------------------*/
/*                  Modification des Items du menu mode, pour ajouter la valeur                */
/*---------------------------------------------------------------------------------------------*/
char* AddModeToLine(int idx)
{
  char* str;
  str = strcpy(tab_MenuTemp[idx], tab_MenuMain[idx]);
  switch (Reglage)
  {
      Serial.println(str);
    case ETE:
      str = strncat(tab_MenuTemp[idx] + strlen(tab_MenuTemp[idx]), BlankLine, NB_CAR_LIGNE - strlen("ETE") - strlen(tab_MenuTemp[idx]) - 1);
      str = strcat(tab_MenuTemp[idx], "ETE");
      break;
    case MI_SAISON :
      str = strncat(tab_MenuTemp[idx] + strlen(tab_MenuTemp[idx]), BlankLine, NB_CAR_LIGNE - strlen("MI-SAISON") - strlen(tab_MenuTemp[idx]) - 1);
      str = strcat(tab_MenuTemp[idx], "MI-SAISON");
      break;
    case HIVERS:
      str = strncat(tab_MenuTemp[idx] + strlen(tab_MenuTemp[idx]), BlankLine, NB_CAR_LIGNE - strlen("HIVERS") - strlen(tab_MenuTemp[idx]) - 1);
      str = strcat(tab_MenuTemp[idx], "HIVERS");
      break;
    default:
      Reglage = MI_SAISON;
      str = strncat(tab_MenuTemp[idx] + strlen(tab_MenuTemp[idx]), BlankLine, NB_CAR_LIGNE - strlen("MI-SAISON") - strlen(tab_MenuTemp[idx]) - 1);
      str = strcat(tab_MenuTemp[idx], "MI-SAISON");
      Serial.println(str);
      return (str);
  }
  return (str);
}


