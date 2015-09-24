/*---------------------------------------------------------------------------------------------*/
/*                         Ce que l'on fait de façon réccurente (boucle principale)            */
/*---------------------------------------------------------------------------------------------*/

void loop(void)
{
  if (RotDetect) ManageRotation();            // Si Action sur le bouton
  if (MenuChanged) DisplayMenuScreen();       // Si on change de Menu
  MenuChanged = false;

  //Lecture des températures
}
