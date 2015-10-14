/*---------------------------------------------------------------------------------------------*/
/*                          GESTION DE MODIFICATION DES VALEURS                                */
/*---------------------------------------------------------------------------------------------*/
void SetOnOff(void) // Actionnement et inhibition du changement d'une valeur dans un menu
{
  static bool Changing = false; // Variable qui indique si on est en cours de changement d'une valeur ou pas

  Changing = not(Changing);

  if (Changing == true) // Autorisation du changement
  {
    if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuSeuils[0][0]) == 0)
    { // Pour le menu des Seuils
      SetSeuilPlusMoins (0);
      EcranEnCours.Droite = SetSeuilPlus;
      EcranEnCours.Gauche = SetSeuilMoins;
    }
    if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_Hysteresis[0][0]) == 0)
    { // Pour le menu des hysteresis
      SetHysteresisPlusMoins (0);
      EcranEnCours.Droite = SetHysteresisPlus;
      EcranEnCours.Gauche = SetHysteresisMoins;
    }
  }
  else // Inhibition du changement
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
/*                          GESTION DE MODIFICATION DES SEUILS                                 */
/*---------------------------------------------------------------------------------------------*/
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

/*---------------------------------------------------------------------------------------------*/
/*                          GESTION DE MODIFICATION DES HYSTERESIS                             */
/*---------------------------------------------------------------------------------------------*/
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

