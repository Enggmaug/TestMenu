
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
void SetSeuilOnOff(void)
{
  static bool ChangingSeuil = false;

  ChangingSeuil = not(ChangingSeuil);

  if (ChangingSeuil == true)
  {
    SetSeuilPlusMoins (0);
    EcranEnCours.Droite = SetSeuilPlus;
    EcranEnCours.Gauche = SetSeuilMoins;
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
  AddSeuilToLine(EcranEnCours.SelectedItem);
  tft.setTextColor(ILI9340_RED);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
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
  tft.setTextColor(ILI9340_RED);
  tft.fillRect(0, (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
  tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * EcranEnCours.SelectedItem);
  tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * EcranEnCours.SelectedItem));
}

/*---------------------------------------------------------------------------------------------*/
/*            Sauvegarde, ou pas des seuils, puis navigation vers ecran principal              */
/*---------------------------------------------------------------------------------------------*/
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
/*---------------------------------------------------------------------------------------------*/
/*                                        INTERRUPTIONS                                        */
/*---------------------------------------------------------------------------------------------*/
// Rotation à droite
void RotationDetectCLK(void)
{
  noInterrupts();
  if (RotDetect == false)
  {
    MenuAction = DROITE;
    RotDetect = true;
  }
  interrupts();
}

// Rotation à gauche
void RotationDetectDT(void)
{
  noInterrupts();
  if (RotDetect == false)
  {
    MenuAction = GAUCHE;
    RotDetect = true;
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
  
}

