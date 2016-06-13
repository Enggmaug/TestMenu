/*---------------------------------------------------------------------------------------------*/
/*                         AFFICHAGE DU MENU SELECTIONNE - Entr�e sur ecran                    */
/*---------------------------------------------------------------------------------------------*/

void DisplayMenuScreen(void)
{
  int idx;
  int SDColor;
  
  noInterrupts();           // Desactivation des interruptions pendant le redessin de l'ecran

  // AFFICHAGE DE LA PREMIERE LIGNE
  tft.fillScreen(NOIR);
  tft.setTextColor(NOIR);
  tft.fillRect(0, 0, tft.width(), (tft.height() / ct_NbItemMax), BLANC);
  tft.drawFastHLine(0, (tft.height() / ct_NbItemMax) - 1, tft.width(), NOIR);
  tft.setCursor(tft.width() / 2 - (strlen(EcranEnCours.pt_tab_menu) / 2) * (tft.width() / 17), 5);       // On se positionne au centre, sur la base de 17 caracteres/ligne
  tft.setTextSize(3);
  tft.println(EcranEnCours.pt_tab_menu);

  
  // AFFICHAGE DES LIGNES SUIVANTES
  tft.setTextSize(2);
  for (idx = 1; idx < EcranEnCours.NbItems; idx++)              // Pour chaque Item du menu
  {
    if (EcranEnCours.pt_tab_EnabledItems[idx] == false)         // Si Item Desactiv�
    {
      if (idx == EcranEnCours.SelectedItem)                     //Et si item selectionn�, on change d'item selectionn�
      {
        Suivant();
      }
      tft.setTextColor(GRIS);                         // Police grise sur fond noir
      tft.fillRect(0, (tft.height() / ct_NbItemMax) * idx, tft.width(), (tft.height() / ct_NbItemMax), NOIR);
    }
    else if (idx == EcranEnCours.SelectedItem)                       // Item Selectionn�
    {
      tft.setTextColor(NOIR);                          // Police noire sur fond blanc
      tft.fillRect(0, (tft.height() / ct_NbItemMax) * idx, tft.width(), (tft.height() / ct_NbItemMax), BLANC);
    }
    else                                                       // Item D�selectionn�
    {
      tft.setTextColor(BLANC);                         // Police blanche sur fond noir
      tft.fillRect(0, (tft.height() / ct_NbItemMax) * idx, tft.width(), (tft.height() / ct_NbItemMax), NOIR);
    }

    tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * idx);
    tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * idx));
  }

  for (idx = EcranEnCours.NbItems; idx < ct_NbItemMax; idx++)   // Suppression des autres Items
  {
    tft.fillRect(0, (tft.height() / ct_NbItemMax) * idx, tft.width(), (tft.height() / ct_NbItemMax), NOIR);
  }

  //AFFICHAGE DE L'ETAT SD
  if (SdCardPresent)
   SDColor = VERT;
  else
   SDColor = ROUGE;
  tft.fillCircle(16,16,15,SDColor);
  tft.setTextColor(GRIS);
  tft.setTextSize(2);
  tft.setCursor(5, 10);
  tft.print("SD");

  //Reautorisation des interruptions
  interrupts();
}

/*---------------------------------------------------------------------------------------------*/
/*                                  AFFICHAGE DES TEMPERATURES                                 */
/*---------------------------------------------------------------------------------------------*/
void DisplayTempScreen(void)
{
  int idx;
  int color;
  int ConvertedTemp;
  float MinTemp;
  float MaxTemp;
  const int PixelMax = 190;
  const int PixelMin = 70;
  int PositionX;
  char DisplayedStr[8];
  int SDColor;

  
  noInterrupts();           // Desactivation des interruptions pendant le redessin de l'ecran
  
  // AFFICHAGE DE LA PREMIERE LIGNE
  tft.fillScreen(NOIR);
  tft.setTextColor(NOIR);
  tft.fillRect(0, 0, tft.width(), (tft.height() / ct_NbItemMax), BLANC);
  tft.drawFastHLine(0, (tft.height() / ct_NbItemMax) - 1, tft.width(), NOIR);
  tft.setCursor(tft.width() / 2 - (strlen(EcranEnCours.pt_tab_menu) / 2) * (tft.width() / 17), 5);       // On se positionne au centre, sur la base de 17 caracteres/ligne
  tft.setTextSize(3);
  tft.println(EcranEnCours.pt_tab_menu);
  tft.setTextSize(1);
  tft.setCursor(0, 200);    // Test du nombre de caract�res sur une ligne
  tft.setTextColor(ROUGE);

  for (idx = 1; idx < EcranEnCours.NbItems; idx++)              // Pour chaque Item du menu
  {
    if (idx == 1)
    {
      if ((TemperatureDepasseSeuil[idx - 1] == false) and (TemperatureDepasseSeuil[idx] == false))
      {
        color = BLEU;
      }
      else if ((TemperatureDepasseSeuil[idx - 1] == true) and (TemperatureDepasseSeuil[idx] == true))
      {
        color = ROUGE;
      }
      else if ((TemperatureDepasseSeuil[idx - 1] == true) and (TemperatureDepasseSeuil[idx] == false))
      {
        color = VERT;
      }
      else
      {
        //error
        color = NOIR;
      }
    }
    else {

      if (TemperatureDepasseSeuil[idx] == false)
      {
        color = BLEU;
      }
      else
      {
        color = ROUGE;
      }
    }
    if (idx == 1)
    {
      MinTemp = min(Seuils[Reglage][0] - Hysteresis[Reglage][0], MinMax[MIN][1]) - 1.0;
      MaxTemp = max (Seuils[Reglage][1] + Hysteresis[Reglage][1], MinMax[MAX][1]) + 1.0;
    }
    else
    {
      MinTemp = min(Seuils[Reglage][idx] - Hysteresis[Reglage][idx], MinMax[MIN][idx]) - 1.0;
      MaxTemp = max (Seuils[Reglage][idx] + Hysteresis[Reglage][idx], MinMax[MAX][idx]) + 1.0;
    }

    //Calcul de la hauteur de mercure
    ConvertedTemp = ConvertTemperature(Temperatures[idx], MinTemp, MaxTemp, PixelMax - PixelMin);

    //Dessin du thermom�tre
    PositionX = idx * (tft.width() / 4) - tft.width() / 8;
    tft.drawRect  (PositionX - 11, PixelMin,                 22, PixelMax - PixelMin, BLANC);
    tft.fillCircle(PositionX,      PixelMax,                 19,                     color);
    tft.drawCircle(PositionX,      PixelMax,                 19,                     BLANC);
    tft.drawCircle(PositionX,      PixelMin,                 10,                     BLANC);
    tft.fillRect  (PositionX - 10, PixelMin,                 20, PixelMax - PixelMin - 15, NOIR );
    //Dessin du mercure

    tft.fillRect  (PositionX - 10, PixelMax - ConvertedTemp, 20, ConvertedTemp - 15,       color);
    //Affichage de la valeur de temp�rature
    tft.setTextColor(NOIR);
    tft.setCursor (PositionX - 10, PixelMax - 2);
    sprintf(DisplayedStr, "%2.1f", Temperatures[idx]);
    tft.println(DisplayedStr);

    // Affichage des seuils
    tft.setTextColor(BLANC);
    if (TemperatureDepasseSeuil[idx] == true)
    {
      ConvertedTemp = ConvertTemperature(Seuils[Reglage][idx] - Hysteresis[Reglage][idx], MinTemp, MaxTemp, PixelMax - PixelMin);
      tft.drawLine (PositionX - 15, PixelMax - ConvertedTemp, PositionX + 10, PixelMax - ConvertedTemp, BLANC );
      tft.setCursor(PositionX + 12, PixelMax - ConvertedTemp - 4);
      sprintf(DisplayedStr, "%2.1f", Seuils[Reglage][idx] - Hysteresis[Reglage][idx]);
      tft.println(DisplayedStr);
    }
    else
    {
      ConvertedTemp = ConvertTemperature(Seuils[Reglage][idx] + Hysteresis[Reglage][idx], MinTemp, MaxTemp, PixelMax - PixelMin);
      tft.drawLine (PositionX - 15, PixelMax - ConvertedTemp, PositionX + 10, PixelMax - ConvertedTemp, BLANC );
      tft.setCursor(PositionX + 12, PixelMax - ConvertedTemp - 4);
      sprintf(DisplayedStr, "%2.1f", Seuils[Reglage][idx] + Hysteresis[Reglage][idx]);
      tft.println(DisplayedStr);
    }


    if (idx == 1) // Affichage du seuil Bas pour l'exterieur
    {
      if (TemperatureDepasseSeuil[0] == true)
      {
        ConvertedTemp = ConvertTemperature(Seuils[Reglage][0] - Hysteresis[Reglage][0], MinTemp, MaxTemp, PixelMax - PixelMin);
        tft.drawLine(PositionX - 15, PixelMax - ConvertedTemp, PositionX + 10, PixelMax - ConvertedTemp, BLANC );
        tft.setCursor(PositionX + 12, PixelMax - ConvertedTemp - 4);
        sprintf(DisplayedStr, "%2.1f", Seuils[Reglage][0] - Hysteresis[Reglage][0]);
        tft.println(DisplayedStr);
      }
      else
      {
        ConvertedTemp = ConvertTemperature(Seuils[Reglage][0] + Hysteresis[Reglage][0], MinTemp, MaxTemp, PixelMax - PixelMin);
        tft.drawLine(PositionX - 15, PixelMax - ConvertedTemp, PositionX + 10, PixelMax - ConvertedTemp, BLANC );
        tft.setCursor(PositionX + 12, PixelMax - ConvertedTemp - 4);
        sprintf(DisplayedStr, "%2.1f", Seuils[Reglage][0] + Hysteresis[Reglage][0]);
        tft.println(DisplayedStr);
      }
    }

    //Affichage du nom du thermom�tre
    tft.setCursor(PositionX - (strlen((char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * idx)) / 2) * (tft.width() / 52), 220);      // On se positionne au centre, sur la base de 34 caracteres/ligne
    tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * idx));

  }
  //AFFICHAGE DE L'ETAT SD
  if (SdCardPresent)
   SDColor = VERT;
  else
   SDColor = ROUGE;
  tft.fillCircle(16,16,15,SDColor);
  tft.setTextColor(GRIS);
  tft.setTextSize(2);
  tft.setCursor(5, 10);
  tft.print("SD");

  //Reautorisation des interruptions
  interrupts();
}


/*---------------------------------------------------------------------------------------------*/
/*                                 AFFICHAGE DES SORTIES                                       */
/*---------------------------------------------------------------------------------------------*/
void DisplayOutputs(void)
{
  int SDColor;

  noInterrupts();   

  //AFFICHAGE DE L'ETAT SD
  if (SdCardPresent)
   SDColor = VERT;
  else
   SDColor = ROUGE;
  tft.fillCircle(16,16,15,SDColor);
  tft.setTextColor(GRIS);
  tft.setTextSize(2);
  tft.setCursor(5, 10);
  tft.print("SD");

  //Reautorisation des interruptions
  interrupts();
}
   
/*---------------------------------------------------------------------------------------------*/
/*                                    AFFICHAGE DES COURBES                                    */
/*---------------------------------------------------------------------------------------------*/
void DisplayCourbeScreen(void)
{
  int idx;
  unsigned int TempToDisplay;
  unsigned int ConvertedTemp;
  unsigned int Grid;
  int color;
  const char TypeHisto[NB_TYP_HISTO][16] = {"24 Heures", "7 Jours", "30 Jours", "365 Jours"};
  int CourbeStart;
  int SDColor;
  float MinTemp, MaxTemp;

  
  noInterrupts();           // Desactivation des interruptions pendant le redessin de l'ecran
  
  tft.fillRect(0, (tft.height() / ct_NbItemMax), tft.width(),tft.height() , NOIR);

for (TempToDisplay = 1; TempToDisplay <= 4 ; TempToDisplay ++)
{
  if (strcmp(EcranEnCours.pt_tab_menu, (char*)&tab_MenuCourbes[TempToDisplay][0]) == 0)
  {
    break;
  }
}
  
switch(EcranEnCours.SelectedItem)
{
  case 1: 
      CourbeStart = CompteJours;
  break;
  case 2 :
      CourbeStart = CompteSemaines/7;
  break;
  case 3:
      CourbeStart = CompteMois/30;
  break;
  case 4 :
      CourbeStart = CompteAnnee/365;
  break;
  default:
    CourbeStart = CompteJours;
}

//Calcul des valeurs Min et Max sur l'interval
MinTemp = Historiques[TempToDisplay - 1][EcranEnCours.SelectedItem - 1][0];
MaxTemp = MinTemp;
  for (idx = 1; idx < tft.width(); idx ++)
  {
    float TabTemp;
    TabTemp = Historiques[TempToDisplay - 1][EcranEnCours.SelectedItem - 1][idx] ;
    if (TabTemp < MinTemp)
      MinTemp = TabTemp;
    if (TabTemp > MaxTemp)
      MaxTemp = TabTemp;    
  }

if (MaxTemp == MinTemp)
{
  MaxTemp =( MaxTemp + 2.0);
  MinTemp =( MinTemp - 2.0);
}

  
// AFFICHAGE de la grille (Lignes H)
  if (MaxTemp - MinTemp > 80)
    Grid = 20;
  else if (MaxTemp - MinTemp > 40)
    Grid = 10;
  else if (MaxTemp - MinTemp > 20)
    Grid = 5;
  else if (MaxTemp - MinTemp > 10)
    Grid = 2;
  else
    Grid = 1;

  for (idx = MinTemp; idx <= MaxTemp; idx ++)
  {
    if (idx % Grid == 0)
    {
      ConvertedTemp = ConvertTemperature(idx,
                                         MinTemp,
                                         MaxTemp,
                                         (tft.height() / ct_NbItemMax) * (ct_NbItemMax - 1));
      tft.drawFastHLine(0, tft.height() - ConvertedTemp -1, tft.width() - 31, GRIS);
      tft.setTextSize(1);
      tft.setCursor(tft.width() - 30, tft.height() - ConvertedTemp -1);
      tft.setTextColor(GRIS);
      tft.println((float)idx);
    }
  }
  // AFFICHAGE de la grille (Lignes V)
  switch (TempToDisplay)
  {
    case 1: // 24 H
      Grid = 4;
      break;
    case 2: // 7 J
      Grid = 7;
      break;
    case 3: // 30 J
      Grid = 4;
      break;
    case 4: //365 J
      Grid = 12;
      break;
    default:
      Grid = 1;
      break;
  }
  Grid = tft.width() / Grid;
  for (idx = 0; idx < tft.width(); idx = idx + Grid)
  {
    tft.drawFastVLine(idx, (tft.height() / ct_NbItemMax), tft.height(), GRIS);
  }

  // Affichage des Courbes
  color = BLEU;

  for (idx = 1; idx <= tft.width(); idx ++)
  {
    if ((idx + CourbeStart) > tft.width())
    {
      CourbeStart = CourbeStart-tft.width();
    }
    ConvertedTemp = ConvertTemperature(Historiques[TempToDisplay - 1][EcranEnCours.SelectedItem - 1][idx + CourbeStart],
                                       MinTemp,
                                       MaxTemp,
                                       (tft.height() / ct_NbItemMax) * (ct_NbItemMax - 1));
    if (Historiques[TempToDisplay - 1][EcranEnCours.SelectedItem - 1][idx + CourbeStart] > (Seuils[Reglage][TempToDisplay] + Hysteresis[Reglage][TempToDisplay]))
      color = ROUGE;
    if (Historiques[TempToDisplay - 1][EcranEnCours.SelectedItem - 1][idx + CourbeStart] < (Seuils[Reglage][TempToDisplay] - Hysteresis[Reglage][TempToDisplay]))
    {
      if (TempToDisplay == 1)
      {

        if (Historiques[TempToDisplay - 1][EcranEnCours.SelectedItem - 1][idx + CourbeStart] < (Seuils[Reglage][TempToDisplay - 1] - Hysteresis[Reglage][TempToDisplay - 1]))
          color =  BLEU;
        if (Historiques[TempToDisplay - 1][EcranEnCours.SelectedItem - 1][idx + CourbeStart] > (Seuils[Reglage][TempToDisplay - 1] + Hysteresis[Reglage][TempToDisplay - 1]))
          color = VERT;
      }
      else
        color =  BLEU;
    }

    tft.drawPixel(idx, tft.height() - ConvertedTemp -1, color);
  }

  tft.setCursor(10, (tft.height() / ct_NbItemMax) );
  tft.setTextColor(BLANC);
  tft.setTextSize(2);
  tft.println(TypeHisto[EcranEnCours.SelectedItem - 1]);

  // AFFICHAGE DE LA PREMIERE LIGNE
  tft.setTextColor(NOIR);
  tft.fillRect(0, 0, tft.width(), (tft.height() / ct_NbItemMax), BLANC);
  tft.drawFastHLine(0, (tft.height() / ct_NbItemMax) - 1, tft.width(), NOIR);
  tft.setCursor(tft.width() / 2 - (strlen(EcranEnCours.pt_tab_menu) / 2) * (tft.width() / 17), 5);       // On se positionne au centre, sur la base de 17 caracteres/ligne
  tft.setTextSize(3);
  tft.println(EcranEnCours.pt_tab_menu);

  //AFFICHAGE DE L'ETAT SD
  if (SdCardPresent)
   SDColor = VERT;
  else
   SDColor = ROUGE;
  tft.fillCircle(16,16,15,SDColor);
  tft.setTextColor(GRIS);
  tft.setTextSize(2);
  tft.setCursor(5, 10);
  tft.print("SD");

  //Reautorisation des interruptions
  interrupts();
}

/*---------------------------------------------------------------------------------------------*/
/*             Interdiction des Items qui ne sont pas accessibles si pas de SD                 */
/*---------------------------------------------------------------------------------------------*/
void DisableSD(void)
{
  int idx;
  const bool   tab_SauvegarderEnableTemp[ct_MenuHistNbItems]            =  {true, false, true , true};

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
  const bool   tab_MenuMainEnableTemp[ct_MenuMainNbItems]        =  {true, true , true , true , true , false, true};
  const bool   tab_MenuDateHeureEnableTemp[ct_MenuSeuilsNbItems] =  {true, false, false, true                     };
  const bool   tab_MenuDateEnableTemp[ct_MenuHistNbItems]        =  {true, false, false, false, true              };
  const bool   tab_MenuHeureEnableTemp[ct_MenuHistNbItems]       =  {true, false, false, true                     };
  const bool   tab_SauvegarderEnableTemp[ct_MenuHistNbItems]     =  {true, false, true , true                     };

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
