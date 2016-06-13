/*---------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------*/
/*                                NAVIGATION ENTRE MENUS                                       */
/*---------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------*/

/*-NIVEAU 0------------------------------------------------------------------------------------*/
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
  EcranEnCours.TypeEcran = MENU;
}
/*-NIVEAU 1------------------------------------------------------------------------------------*/
/*                     Navigation vers l'ecran d'affichage des Températures                    */
/*---------------------------------------------------------------------------------------------*/
void GotoDisplayTemp(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_DisplayT[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_DisplayTEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_DisplayTFonct;
  EcranEnCours.NbItems = ct_DisplayTNbItems;
  EcranEnCours.SelectedItem = 0;
  EcranEnCours.Droite = GotoDisplayOutputs;
  EcranEnCours.Gauche = GotoDisplayOutputs;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[0];
  EcranEnCours.TypeEcran = TEMPERATURES;
}

/*-NIVEAU 1------------------------------------------------------------------------------------*/
/*                     Navigation vers l'ecran d'affichage des sorties                         */
/*---------------------------------------------------------------------------------------------*/
void GotoDisplayOutputs(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_DispOutputs[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_DispOutputsEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_DispOutputsFonct;
  EcranEnCours.NbItems = ct_DispOutputsNbItems;
  EcranEnCours.SelectedItem = 0;
  EcranEnCours.Droite = GotoDisplayTemp;
  EcranEnCours.Gauche = GotoDisplayTemp;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[0];
  EcranEnCours.TypeEcran = SORTIES;
}

/*-NIVEAU 1------------------------------------------------------------------------------------*/
/*                             Navigation vers écran menu principal                            */
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
  EcranEnCours.TypeEcran = MENU;
}

/*-NIVEAU 2------------------------------------------------------------------------------------*/
/*     Navigation vers l'ecran de réglage des déclenchements (Seuils et Hysteresis)            */
/*---------------------------------------------------------------------------------------------*/
void GotoDeclenche(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuDeclenche[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_MenuDeclencheEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuDeclencheFonct;
  EcranEnCours.NbItems = ct_MenuDeclNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
  EcranEnCours.TypeEcran = MENU;
}
/*-NIVEAU 3------------------------------------------------------------------------------------*/
/*                     Navigation vers l'ecran de réglage des Hystéresis                       */
/*---------------------------------------------------------------------------------------------*/
void GotoHysteresis(void)
{
  int idx;

  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_Hysteresis[0][0];
  strcpy(tab_MenuTemp[0], tab_Hysteresis[0]);
  for (idx = 1; idx < ct_HysteresisNbItems - 1; idx ++)
  {
    AddValToLine(idx);
  }
  strcpy(tab_MenuTemp[ct_HysteresisNbItems - 1], tab_Hysteresis[ct_HysteresisNbItems - 1]);
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuTemp[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_HysteresisEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_HysteresisFonct;
  EcranEnCours.NbItems = ct_HysteresisNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
  EcranEnCours.TypeEcran = MENU;
}

/*-NIVEAU 3------------------------------------------------------------------------------------*/
/*                             Navigation vers les seuils                                      */
/*---------------------------------------------------------------------------------------------*/
void GotoSeuils(void)
{
  int idx;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuSeuils[0][0];
  MenuChanged = true;
  strcpy(tab_MenuTemp[0], tab_MenuSeuils[0]);
  for (idx = 1; idx < ct_MenuSeuilsNbItems - 1; idx ++)
  {
    AddValToLine(idx);
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
  EcranEnCours.TypeEcran = MENU;
}

/*-NIVEAU 2------------------------------------------------------------------------------------*/
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
  EcranEnCours.TypeEcran = MENU;
}

/*-NIVEAU 3------------------------------------------------------------------------------------*/
/*                      Navigation vers l'ecran d'affichage de courbe                          */
/*---------------------------------------------------------------------------------------------*/
void GotoCourbes(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuCourbes[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_MenuCourbesEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuCourbesFonct;
  EcranEnCours.NbItems = ct_MenuCourbesNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
  EcranEnCours.TypeEcran = MENU;
}
/*-NIVEAU 4------------------------------------------------------------------------------------*/
/*                      Navigation vers l'ecran d'affichage de courbe Exterieure               */
/*---------------------------------------------------------------------------------------------*/
void ShowHistoExt(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuCourbes[1][0];
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.NbItems = NB_TYP_HISTO;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = GotoCourbes;
  EcranEnCours.TypeEcran = HISTO;
}

/*-NIVEAU 4------------------------------------------------------------------------------------*/
/*                      Navigation vers l'ecran d'affichage de courbe Intérieure               */
/*---------------------------------------------------------------------------------------------*/
void ShowHistoInt(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuCourbes[2][0];
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.NbItems = NB_TYP_HISTO;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = GotoCourbes;
  EcranEnCours.TypeEcran = HISTO;
}

/*-NIVEAU 4------------------------------------------------------------------------------------*/
/*                      Navigation vers l'ecran d'affichage de courbe Puit Canadien            */
/*---------------------------------------------------------------------------------------------*/
void ShowHistoPuit(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuCourbes[3][0];
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.NbItems = NB_TYP_HISTO;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = GotoCourbes;
  EcranEnCours.TypeEcran = HISTO;
}

/*-NIVEAU 4------------------------------------------------------------------------------------*/
/*                      Navigation vers l'ecran d'affichage de courbe Cheminée                 */
/*---------------------------------------------------------------------------------------------*/
void ShowHistoChem(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuCourbes[4][0];
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.NbItems = NB_TYP_HISTO;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = GotoCourbes;
  EcranEnCours.TypeEcran = HISTO;
}

/*-NIVEAU 3------------------------------------------------------------------------------------*/
/*                              Navigation vers l'ecran des MIN/MAX                            */
/*---------------------------------------------------------------------------------------------*/
void GotoMinMax(void)
{

  int idx;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuMinMax[MIN][0];
  MenuChanged = true;
  strcpy(tab_MenuTemp[0], tab_MenuMinMax[MIN]);
  for (idx = 1; idx < ct_MenuMinMaxNbItems - 1; idx ++)
  {
    AddValToLine(idx);
  }
  strcpy(tab_MenuTemp[ct_MenuMinMaxNbItems - 1], tab_MenuMinMax[ct_MenuMinMaxNbItems - 1]);
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuTemp[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_MenuMinMaxEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuMinMaxFonct;
  EcranEnCours.NbItems = ct_MenuMinMaxNbItems;
  EcranEnCours.SelectedItem = 5;
  EcranEnCours.Droite = None;
  EcranEnCours.Gauche = None;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
  EcranEnCours.TypeEcran = MENU;
}
/*-NIVEAU 3------------------------------------------------------------------------------------*/
/*                     Navigation vers l'ecran de RESET des historiques                        */
/*---------------------------------------------------------------------------------------------*/
void GotoResetScreen(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_Reset[0][0];
  EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_ResetEnable[0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_ResetFonct;
  EcranEnCours.NbItems = ct_ResetNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
  EcranEnCours.TypeEcran = MENU;
}
/*-NIVEAU 2------------------------------------------------------------------------------------*/
/*                         Navigation vers l'ecran de Maintenance                              */
/*---------------------------------------------------------------------------------------------*/
void GotoMaintenance(void)
{

}

/*-NIVEAU 2------------------------------------------------------------------------------------*/
/*                     Navigation vers l'ecran de réglage Date/Heure                           */
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
  InhibRTCAlarms = false;
  EcranEnCours.TypeEcran = MENU;
}

/*-NIVEAU 3------------------------------------------------------------------------------------*/
/*                     Navigation vers l'ecran de réglage de la date                           */
/*---------------------------------------------------------------------------------------------*/
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
  InhibRTCAlarms = true;
  EcranEnCours.TypeEcran = MENU;
}

/*-NIVEAU 3------------------------------------------------------------------------------------*/
/*                     Navigation vers l'ecran de réglage de l'heure                           */
/*---------------------------------------------------------------------------------------------*/
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
  InhibRTCAlarms = true;
  EcranEnCours.TypeEcran = MENU;
}

/*-NIVEAU 4------------------------------------------------------------------------------------*/
/*                    Navigation vers l'ecran de Sauvegarde Paramètres                         */
/*---------------------------------------------------------------------------------------------*/

void SaveYesNo(void)
{
  MenuChanged = true;

  if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuSeuils[0][0]) == 0)
  { // SAUVEGARDE DES SEUILS
    EcranEnCours.pt_MenuFonct = (FctPtr *)tab_SaveSeuilsFonct;
    EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_SauvegarderSDEnable[0];
  }
  else if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_Hysteresis[0][0]) == 0)
  { // SAUVEGARDE DES HYSTERESIS
    EcranEnCours.pt_MenuFonct = (FctPtr *)tab_SaveHysteresisFonct;
    EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_SauvegarderSDEnable[0];
  }
  else if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuDate[0][0]) == 0)
  { // SAUVEGARDE DE LA DATE
    EcranEnCours.pt_MenuFonct = (FctPtr *)tab_SaveDateFonct;
    EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_SauvegarderRTCEnable[0];
  }
  else if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuHeure[0][0]) == 0)
  { // SAUVEGARDE DE L'HEURE
    EcranEnCours.pt_MenuFonct = (FctPtr *)tab_SaveHoursFonct;
    EcranEnCours.pt_tab_EnabledItems = (bool *)&tab_SauvegarderRTCEnable[0];
  }

  EcranEnCours.pt_tab_menu = (char *)&tab_Sauvegarder[0][0];
  EcranEnCours.NbItems = ct_SauvegarderNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
  EcranEnCours.TypeEcran = MENU;
}



/*---------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------*/
/*                                NAVIGATION SUR UN ECRAN                                      */
/*---------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------*/
void Suivant(void)
{
  if (EcranEnCours.TypeEcran == HISTO)
    ChangeHisto(1);
  else
    ChangeItem(1);
}

void Precedent(void)
{
  if (EcranEnCours.TypeEcran == HISTO)
    ChangeHisto(-1);
  else
    ChangeItem(-1);
}
/*---------------------------------------------------------------------------------------------*/
/*                             GENERIQUE : Changement d'item                                   */
/*---------------------------------------------------------------------------------------------*/
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
/*                  Modification des Items du menu seuil, pour ajouter la valeur               */
/*---------------------------------------------------------------------------------------------*/
char* AddValToLine(int idx)
{
  char* str;
  char DisplayedVal[16] = "";

  if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuSeuils[0][0]) == 0)
  {
    str = strcpy(tab_MenuTemp[idx], &tab_MenuSeuils[idx][0]);
    str = strncat(str + strlen(str), BlankLine, NB_CAR_LIGNE - NB_CAR_T - strlen(str));
    sprintf(DisplayedVal, " : %2.1f", Seuils[Reglage][idx - 1]);
  }
  else if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_Hysteresis[0][0]) == 0)
  {
    str = strcpy(tab_MenuTemp[idx], &tab_Hysteresis[idx][0]);
    str = strncat(str + strlen(str), BlankLine, NB_CAR_LIGNE - NB_CAR_T - strlen(str));
    sprintf(DisplayedVal, " : %2.1f", Hysteresis[Reglage][idx - 1]);
  }
  else if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuMinMax[MIN][0]) == 0)
  {
    str = strcpy(tab_MenuTemp[idx], &tab_MenuMinMax[idx][0]);
    str = strncat(str + strlen(str), BlankLine, NB_CAR_LIGNE - 13 - strlen(str));
    sprintf(DisplayedVal, " : %2.1f/%2.1f", MinMax[MIN][idx - 1], MinMax[MAX][idx - 1]);

  }
  else
  {
    str = strcpy(tab_MenuTemp[idx], "ERROR");
  }

  str = strcat(str, DisplayedVal);

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

/*---------------------------------------------------------------------------------------------*/
/*                                   Changement d'historique                                   */
/*---------------------------------------------------------------------------------------------*/
void ChangeHisto(int Direction)
{
  MenuChanged = true;
  if (Direction > 0) Direction = 1;
  else Direction = -1;

  EcranEnCours.SelectedItem += Direction;
  if (EcranEnCours.SelectedItem > EcranEnCours.NbItems)
  {
    EcranEnCours.SelectedItem = 1;
  }
  else if (EcranEnCours.SelectedItem < 1)
  {
    EcranEnCours.SelectedItem = EcranEnCours.NbItems;
  }
}
