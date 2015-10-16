
/*---------------------------------------------------------------------------------------------*/
/*                     Reccuperation/Verification des Températures                             */
/*---------------------------------------------------------------------------------------------*/
void GetTemperatures(void)
{
  int idx;
  const int PinNumber[NB_TEMP] = {T_EXT, T_EXT, T_INT, T_CHEMINEE, T_PUIT};

  for (idx = 1; idx < NB_TEMP ; idx ++)
  {
    Temperatures[idx] = ReadTemperature(PinNumber[idx]);
  }
  Temperatures[0] = Temperatures[1];  // Les Deux premieres températures sont la même, car on a 2 seuils pour l'exterieur
}

float ReadTemperature(int AnalogPinNumber) // A ECRIRE
{
  if (AnalogPinNumber > 0)
  {
    return (0.0);
    //return (analogRead(AnalogPinNumber));
  }
  else
    return (0.0);
}


void CheckTemperatures (void)
{
  int idx;
  for (idx = 0; idx < NB_TEMP; idx++)
  {
    if (TemperatureDepasseSeuil[idx] == true)
    {
      if (Temperatures[idx] < ( Seuils[Reglage][idx] - Hysteresis[Reglage][idx]))
      {
        TemperatureDepasseSeuil[idx] = false;
      }
    }
    else
    {
      if (Temperatures[idx] > ( Seuils[Reglage][idx] + Hysteresis[Reglage][idx]))
      {
        TemperatureDepasseSeuil[idx] = true;
      }
    }
  }
}

/*---------------------------------------------------------------------------------------------*/
/*        Convertion d'une température de float vers int pour affichage dans thermomètre       */
/*---------------------------------------------------------------------------------------------*/
int ConvertTemperature(float InputTemp, float Min, float Max, int HauteurMax)
{
  float diff_MinMax;
  float RegleDeTroyes;

  diff_MinMax = Max - Min;

  RegleDeTroyes = (diff_MinMax * InputTemp) / (float) HauteurMax;
  return ((int) RegleDeTroyes);


}
