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
  tft.setCursor(0, 200);    // Test du nombre de caractères sur une ligne
  tft.setTextColor(ROUGE);

  for (idx = 1; idx < EcranEnCours.NbItems; idx++)              // Pour chaque Item du menu
  {
    // Charge le BMP qui va bien au bon endroit
    // Place les curseurs de seuil
    // Trace le rectangle bleu ou rouge de température selon si le seuil est passé ou pas
    if (TemperatureDepasseSeuil[idx] == false)
    {
        color = BLEU;
    }
    else if (TemperatureDepasseSeuil[idx] == false)
    {
        color = ROUGE;
    }
    ConvertedTemp = ConvertTemperature(Temperatures[idx], MinMax[idx][0] -1,MinMax[idx][1] +1,idx/*Hauteur max*/);
    tft.drawCircle(idx *(tft.width() / 4) - tft.width() / 8,190,19,BLANC);
    tft.drawCircle(idx *(tft.width() / 4) - tft.width() / 8,70,10,BLANC);
    tft.drawRect(idx *(tft.width() / 4) - tft.width() / 8 - 11,70,22, 120,BLANC);
    tft.fillRect(idx *(tft.width() / 4) - tft.width() / 8 - 10,70,20, 120,NOIR);
    tft.fillCircle(idx *(tft.width() / 4) - tft.width() / 8,190,18,color);
    tft.fillRect(idx *(tft.width() / 4) - tft.width() / 8 - 10,190-ConvertedTemp,20, ConvertedTemp,color);
    tft.setCursor(idx *(tft.width() / 4) - tft.width() / 8 - (strlen((char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * idx)) / 2) * (tft.width() / 52), 220);       // On se positionne au centre, sur la base de 34 caracteres/ligne
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
