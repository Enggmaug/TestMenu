/*---------------------------------------------------------------------------------------------*/
/*                         AFFICHAGE DU MENU SELECTIONNE - Entrée sur ecran                    */
/*---------------------------------------------------------------------------------------------*/

void DisplayMenuScreen(void)
{
  int idx;
  noInterrupts();           // Desactivation des interruptions pendant le redessin de l'ecran

  // AFFICHAGE DE LA PREMIERE LIGNE
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
    if (EcranEnCours.pt_tab_EnabledItems[idx] == false)         // Si Item Desactivé
    {
      if (idx == EcranEnCours.SelectedItem)                     //Et si item selectionné, on change d'item selectionné
      {
        Suivant();
      }
      tft.setTextColor(GRIS);                         // Police grise sur fond noir
      tft.fillRect(0, (tft.height() / ct_NbItemMax) * idx, tft.width(), (tft.height() / ct_NbItemMax), NOIR);
    }
    else if (idx == EcranEnCours.SelectedItem)                       // Item Selectionné
    {
      tft.setTextColor(NOIR);                          // Police noire sur fond blanc
      tft.fillRect(0, (tft.height() / ct_NbItemMax) * idx, tft.width(), (tft.height() / ct_NbItemMax), BLANC);
    }
    else                                                       // Item Déselectionné
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
  float Min;
  float Max;
  noInterrupts();           // Desactivation des interruptions pendant le redessin de l'ecran
  const int PixelMax = 190;
  const int PixelMin = 70;

  // AFFICHAGE DE LA PREMIERE LIGNE
  tft.fillScreen(NOIR);
  tft.setTextColor(NOIR);
  tft.fillRect(0, 0, tft.width(), (tft.height() / ct_NbItemMax), BLANC);
  tft.drawFastHLine(0, (tft.height() / ct_NbItemMax) - 1, tft.width(), NOIR);
  tft.setCursor(tft.width() / 2 - (strlen(EcranEnCours.pt_tab_menu) / 2) * (tft.width() / 17), 5);       // On se positionne au centre, sur la base de 17 caracteres/ligne
  tft.setTextSize(3);
  tft.println(EcranEnCours.pt_tab_menu);
  tft.setTextSize(1);
  tft.setCursor(0, 200);    // Test du nombre de caractères sur une ligne
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
      }
    }
    else {

      if (TemperatureDepasseSeuil[idx] == false)
      {
        color = BLEU;
      }
      else if (TemperatureDepasseSeuil[idx] == true)
      {
        color = ROUGE;
      }
    }
    if (idx == 1)
    {
      Min = min(Seuils[Reglage][0] - Hysteresis[Reglage][0], MinMax[1][0]) - 1.0;
      Max = max (Seuils[Reglage][1] + Hysteresis[Reglage][1], MinMax[1][1]) + 1.0;
    }
    else
    {
      Min = min(Seuils[Reglage][idx] - Hysteresis[Reglage][idx], MinMax[idx][0]) - 1.0;
      Max = max (Seuils[Reglage][idx] + Hysteresis[Reglage][idx], MinMax[idx][1]) + 1.0;
    }
    //Clacul de la hauteur de mercure
    ConvertedTemp = ConvertTemperature(Temperatures[idx], Min, Max, PixelMax - PixelMin);

    //Dessin du thermomètre
    tft.drawCircle(idx * (tft.width() / 4) - tft.width() / 8, PixelMax, 19, BLANC);
    tft.drawCircle(idx * (tft.width() / 4) - tft.width() / 8, PixelMin, 10, BLANC);
    tft.drawRect(idx * (tft.width() / 4) - tft.width() / 8 - 11, PixelMin, 22, PixelMax - PixelMin, BLANC);
    tft.fillRect(idx * (tft.width() / 4) - tft.width() / 8 - 10, PixelMin, 20, PixelMax - PixelMin, NOIR);
    //Dessin du mercure
    tft.fillCircle(idx * (tft.width() / 4) - tft.width() / 8, PixelMax, 18, color);
    tft.fillRect(idx * (tft.width() / 4) - tft.width() / 8 - 10, PixelMax - ConvertedTemp, 20, ConvertedTemp, color);
    //Affichage de la valeur de température
    tft.setCursor(idx * (tft.width() / 4) - 30, PixelMax - ConvertedTemp);
    tft.println(Temperatures[idx]);

    // Affichage des seuils
    if (TemperatureDepasseSeuil[idx] == true)
    {
      ConvertedTemp = ConvertTemperature(Seuils[Reglage][idx] - Hysteresis[Reglage][idx], Min, Max, PixelMax - PixelMin);
      tft.drawLine(idx * (tft.width() / 4) - tft.width() / 8 - 20, PixelMax - ConvertedTemp, 40, PixelMax - ConvertedTemp, BLANC );
      tft.setCursor(idx * (tft.width() / 4) + 30, PixelMax - ConvertedTemp);
      tft.println(Seuils[Reglage][idx] - Hysteresis[Reglage][0]);
    }
    else
    {
      ConvertedTemp = ConvertTemperature(Seuils[Reglage][idx] + Hysteresis[Reglage][idx], Min, Max, PixelMax - PixelMin);
      tft.drawLine(idx * (tft.width() / 4) - tft.width() / 8 - 20, PixelMax - ConvertedTemp, 40, PixelMax - ConvertedTemp, BLANC );
      tft.setCursor(idx * (tft.width() / 4) + 30, PixelMax - ConvertedTemp);
      tft.println(Seuils[Reglage][idx] + Hysteresis[Reglage][0]);
    }

    if (idx == 1) // Affichage du seuil Bas pour l'exterieur
    {
      if (TemperatureDepasseSeuil[0] == true)
      {
        ConvertedTemp = ConvertTemperature(Seuils[Reglage][0] - Hysteresis[Reglage][0], Min, Max, PixelMax - PixelMin);
        tft.drawLine(idx * (tft.width() / 4) - tft.width() / 8 - 20, PixelMax - ConvertedTemp, 40, PixelMax - ConvertedTemp, BLANC );
        tft.setCursor(idx * (tft.width() / 4) + 30, PixelMax - ConvertedTemp);
        tft.println(Seuils[1][idx] - Hysteresis[Reglage][0]);
      }
      else
      {
        ConvertedTemp = ConvertTemperature(Seuils[Reglage][0] + Hysteresis[Reglage][0], Min, Max, PixelMax - PixelMin);
        tft.drawLine(idx * (tft.width() / 4) - tft.width() / 8 - 20, PixelMax - ConvertedTemp, 40, PixelMax - ConvertedTemp, BLANC );
        tft.setCursor(idx * (tft.width() / 4) + 30, PixelMax - ConvertedTemp);
        tft.println(Seuils[Reglage][1] + Hysteresis[Reglage][0]);
      }
    }

    //Affichage du nom du thermomètre
    tft.setCursor(idx * (tft.width() / 4) - tft.width() / 8 - (strlen((char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * idx)) / 2) * (tft.width() / 52), 220);      // On se positionne au centre, sur la base de 34 caracteres/ligne
    tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * idx));

  }
  interrupts();
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
