/*---------------------------------------------------------------------------------------------*/
/*                         Ce que l'on fait de façon réccurente (boucle principale)            */
/*---------------------------------------------------------------------------------------------*/

void loop(void)
{
  static int counter = 0;
  if (RotDetect) ManageRotation();            // Si Action sur le bouton
  if (MenuChanged) DisplayMenuScreen();       // Si on change de Menu
  MenuChanged = false;

  //Lecture des températures
  if (RTClockAlarm == true)
  {
    RTClockAlarm = false;    
    DS3234_clear_a1f(RTCLK_CS);
    counter++;
    GetTemperatures();

    if ((counter % 10)==0)
    {
      SaveHistoriques();
    }
  }
}
