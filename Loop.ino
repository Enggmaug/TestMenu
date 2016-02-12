/*---------------------------------------------------------------------------------------------*/
/*                         Ce que l'on fait de façon réccurente (boucle principale)            */
/*---------------------------------------------------------------------------------------------*/

void loop(void)
{
  static int counter = 0;
  if (RotDetect) ManageRotation(); // Si Action sur le bouton
  if (MenuChanged) {
    switch (EcranEnCours.TypeEcran)
    {
      case MENU :
        DisplayMenuScreen();       // Si on change de Menu
        break;
      case TEMPERATURES :
        DisplayTempScreen();
      case SORTIES :
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
  if ((RTClockAlarm == true) and (InhibRTCAlarms == false))
  {
    RTClockAlarm = false;
    DS3234_clear_a1f(RTCLK_CS);
    counter++;
    //GetTemperatures();
    CheckTemperatures();
    if (counter % 60 == 0)
    {
      ReadTime();
    }
    if (counter == 270)
    {
      SaveHistoriques();
    }
    else if (counter >= 1)//540) Pour voir en vitesse accelérée les courbes
    {
      counter = 0;
      SaveHistoriques();
    }
  }
}
