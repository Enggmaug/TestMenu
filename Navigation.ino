

void Suivant(void)
{
  tft.setTextColor(ILI9340_WHITE);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
  EcranEnCours.SelectedItem += 1;
  if (EcranEnCours.SelectedItem >= EcranEnCours.NbItems)
  {
    EcranEnCours.SelectedItem = 1;
  }
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
  tft.setTextColor(ILI9340_BLACK);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_WHITE);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}

void Precedent(void)
{
  tft.setTextColor(ILI9340_WHITE);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
  EcranEnCours.SelectedItem -= 1;
  if (EcranEnCours.SelectedItem < 1)
  {
    EcranEnCours.SelectedItem = EcranEnCours.NbItems - 1;
  }
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
  tft.setTextColor(ILI9340_BLACK);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_WHITE);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}

void None(void)
{
}

void GotoMode(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuMode[0][0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuModeFonct;
  EcranEnCours.NbItems = ct_MenuModeNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}

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
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuSeuilsFonct;
  EcranEnCours.NbItems = ct_MenuSeuilsNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}
void GotoHisto(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuHist[0][0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuHistFonct;
  EcranEnCours.NbItems = ct_MenuHistNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}

void GotoMainMenu(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_MenuMain[0][0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_MenuMainFonct;
  EcranEnCours.NbItems = ct_MenuMainNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}

char* AddSeuilToLine(int idx)
{
  char* str;
  char DisplayedTemp[8];
  float* Temp;
  Temp = &Seuils[idx - 1];
  str = strcpy(tab_MenuTemp[idx], tab_MenuSeuils[idx]);
  str = strncat(str + strlen(str), BlankLine, NB_CAR_LIGNE - NB_CAR_T - strlen(str));
  sprintf(DisplayedTemp, " : %2.1f", *Temp);
  str = strcat(str, DisplayedTemp);

  return (str);
}

void SaveYesNo(void)
{
  MenuChanged = true;
  EcranEnCours.pt_tab_menu = (char *)&tab_Sauvegarder[0][0];
  EcranEnCours.pt_MenuFonct = (FctPtr *)tab_SauvegarderFonct;
  EcranEnCours.NbItems = ct_SauvegarderNbItems;
  EcranEnCours.SelectedItem = 1;
  EcranEnCours.Droite = Suivant;
  EcranEnCours.Gauche = Precedent;
  EcranEnCours.Select = EcranEnCours.pt_MenuFonct[EcranEnCours.SelectedItem];
}
