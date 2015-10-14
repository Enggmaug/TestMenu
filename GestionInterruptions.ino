
/*---------------------------------------------------------------------------------------------*/
/*                                        INTERRUPTIONS                                        */
/*---------------------------------------------------------------------------------------------*/
// Rotation à droite
void RotationDetectCLK(void)
{
  noInterrupts();
  if (digitalRead(COD_CLK) != digitalRead(COD_DT))
  {
    if (RotDetect == false)
    {
      MenuAction = DROITE;
      RotDetect = true;
    }
  }
  interrupts();
}

// Rotation à gauche
void RotationDetectDT(void)
{
  noInterrupts();
  if (digitalRead(COD_CLK) != digitalRead(COD_DT))
  {
    if (RotDetect == false)
    {
      MenuAction = GAUCHE;
      RotDetect = true;
    }
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

void RTClockInterrupt(void)
{
  RTClockAlarm = true;
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

