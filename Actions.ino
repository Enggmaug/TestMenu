
void ToggleMaintenance(void)
{
}
void BacktoFunctional(void)
{

}
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
void SetSeuilOnOff(void)
{
  static bool ChangingSeuil = false;

  ChangingSeuil = not(ChangingSeuil);

  if (ChangingSeuil == true)
  {
    tft.setTextColor(ILI9340_RED);
    tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
    EcranEnCours.Droite = SetSeuilPlus;
    EcranEnCours.Gauche = SetSeuilMoins;
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

void SetSeuilPlus(void)
{
  Seuils[Reglage][EcranEnCours.SelectedItem - 1] += 0.5;
  MenuChanged = false;
  MenuAction = NONE;
  AddSeuilToLine(EcranEnCours.SelectedItem);
  tft.setTextColor(ILI9340_RED);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}
void SetSeuilMoins(void)
{

  Seuils [Reglage][EcranEnCours.SelectedItem - 1] -= 0.5;
  MenuChanged = false;
  MenuAction = NONE;
  AddSeuilToLine(EcranEnCours.SelectedItem);
  tft.setTextColor(ILI9340_RED);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}

void SaveToFile(void)
{
  WriteSeuilsToFile();
  GotoMainMenu();
}


void RecallSeuils(void)
{
  ReadSeuilsFromFile();
  GotoMainMenu();
}
void SetModePlus(void)
{
  switch (Reglage)
  {
    case ETE:
      Reglage = MI_SAISON;
      break;
    case MI_SAISON:
      Reglage = HIVERS;
      break;
    case HIVERS :
    default:
      Reglage = ETE;
  }
  AddModeToLine(EcranEnCours.SelectedItem);
  tft.setTextColor(ILI9340_RED);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}
void SetModeMoins(void)
{
  switch (Reglage)
  {
    case ETE:
      Reglage = HIVERS;
      break;
    case MI_SAISON:
      Reglage = ETE;
      break;
    case HIVERS :
      Reglage = MI_SAISON;
      break;
    default:
      Reglage = ETE;
  }
  AddModeToLine(EcranEnCours.SelectedItem);
  tft.setTextColor(ILI9340_RED);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}

void ReadSeuilsFromFile(void)
{
  unsigned int idx;
  char *pt_read;

  if (SD.exists("Seuils.par"))
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
  else
  {
    File dataFile = SD.open("Seuils.par", FILE_WRITE);
          pt_read = (char*) &Seuils[0][0];
    for (idx = 0; idx < sizeof(Seuils); idx ++)
    {
      dataFile.write(pt_read[idx]);
    }
    dataFile.close();
  }

}

void WriteSeuilsToFile(void)
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
