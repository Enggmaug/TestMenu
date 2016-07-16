/*---------------------------------------------------------------------------------------------*/
/*                         Ce que l'on fait de façon réccurente (boucle principale)            */
/*---------------------------------------------------------------------------------------------*/

void loop(void)
{
    static unsigned int counter = 0;                        // +1 toutes les secondes
    const int NBEl_Moyenne[NB_TYP_HISTO] = {1,7,4,12};      // Nb de points à moyenner
    const int NBJ_HistoTyp[NB_TYP_HISTO] = {1,7,30,365};    // Nb de jours pour trigger l'enregistrement d'histo
    int IndexTemp;
    int idx;
    static unsigned long int comptejours = 0;

  if (RotDetect) ManageRotation(); // Si Action sur le bouton
  if (MenuChanged) {
    switch (EcranEnCours.TypeEcran)
    {
      case MENU :
        DisplayMenuScreen();       // Si on change de Menu
        break;
      case TEMPERATURES :
        DisplayTempScreen();
        break;
      case SORTIES :
        DisplayMenuScreen();
        DisplayOutputs();
        break;
      case MAINTENANCE :
        break;
      case HISTO :
        DisplayCourbeScreen();
        break;
      default :
        break;
    }
  }
  MenuChanged = false;

  //Lecture des températures
  if ((RTClockAlarm == true) and (InhibRTCAlarms == false))//or RTC dans les choux et timeout.
  {

    RTClockAlarm = false;
    DS3234_clear_a1f(RTCLK_CS);
    counter++;
    
    if (counter % 30 == 0 ) // Resynchro toutes les 30 secondes
    {      
      ReadTime();
    }

    if (counter % 270 == 0 ) // 270 seconds = 4.5 minutes = 320 points sur 24h
    {      
      GetTemperatures();
      CheckTemperatures();
    
      //Remplissage des Historiques
      for (idx = 0; idx < NB_TYP_HISTO ; idx ++)
      {
        for (IndexTemp = 0; IndexTemp < NB_TEMP - 1; IndexTemp ++)
        {
          if (idx == 0)
            Historiques[IndexTemp][idx][IndexHistoriques[idx]] = Temperatures[IndexTemp];
          else if (IndexHistoriques[idx - 1] % NBJ_HistoTyp[idx] == 0)
            Historiques[IndexTemp][idx][IndexHistoriques[idx]] = Moyenne(&Historiques[IndexTemp][idx - 1][0], IndexHistoriques[idx - 1], NBEl_Moyenne[idx]);
        }

        if (idx == 0)
        {
          IndexHistoriques[idx] ++ ;
          comptejours ++ ;
          if (comptejours >= 365 * 30 * 7)
            comptejours = 0;
        }
        else if (comptejours % NBJ_HistoTyp[idx] == 0)
          IndexHistoriques[idx] ++ ;

        if (IndexHistoriques[idx] >= SCREEN_WIDTH)
        {
          IndexHistoriques[idx] = 0;
        }
      }

      counter = 0;
    }

  }
}
