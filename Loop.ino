/*---------------------------------------------------------------------------------------------*/
/*                         Ce que l'on fait de façon réccurente (boucle principale)            */
/*---------------------------------------------------------------------------------------------*/

void loop(void)
{
  static int counter;
  if (RotDetect) ManageRotation();            // Si Action sur le bouton
  if (MenuChanged) DisplayMenuScreen();       // Si on change de Menu
  MenuChanged = false;

  //Lecture des températures
  if (counter++ >= 10000000) // => A changer par flag sur OneMinutePassed (interruption RTClock)
  {
    counter = 0;
    GetTemperatures();
    CheckTemperatures();
  }
}
