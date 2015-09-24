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
  tft.setTextColor(ILI9340_WHITE);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
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
  tft.setTextColor(ILI9340_BLACK);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_WHITE);
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
    tft.setTextColor(ILI9340_RED);
    tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
    EcranEnCours.Droite = SetModePlus;
    EcranEnCours.Gauche = SetModeMoins;
    tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
    tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
    MenuChanged = false;
    MenuAction = NONE;
  }
  else
  {
    tft.setTextColor(ILI9340_BLACK);
    tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_WHITE);
    EcranEnCours.Droite = Suivant;
    EcranEnCours.Gauche = Precedent;
    tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
    tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
    MenuChanged = false;
    MenuAction = NONE;
  }
}
/*---------------------------------------------------------------------------------------------*/
/*                             Navigation vers écan principal                                  */
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
  }
  else if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuDate[0][0]) == 0)
  {
    EcranEnCours.pt_MenuFonct = (FctPtr *)tab_SaveDateFonct;
  }
  else if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuHeure[0][0]) == 0)
  {
    EcranEnCours.pt_MenuFonct = (FctPtr *)tab_SaveHoursFonct;
  }
  EcranEnCours.pt_tab_menu = (char *)&tab_Sauvegarder[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_SauvegarderEnable[0];
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
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuDateHeure[0][0];
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
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuDate[0][0];
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
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuHeure[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_MenuHeureEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuHeureFonct;
  EcranEnCours.NbItems = ct_MenuHeureNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}
void SetYear(void)
{
// Faire comme dans ChangingMode
}
void SetMonth(void)
{

}
void SetDay(void)
{

}
void SetHours(void)
{

}
void SetMinutes(void)
{

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


