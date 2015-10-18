
/*---------------------------------------------------------------------------------------------*/
/*                              SEUILS : LECTURE / ECRITURE SUR SD                             */
/*---------------------------------------------------------------------------------------------*/
void ReadSeuilsFromFile(void)
{
  unsigned int idx;
  char *pt_read;

  if (SD.exists("Seuils.par")) // Si le fichier Seuils.par existe, on le lit
  {
    File dataFile = SD.open("Seuils.par", FILE_READ);
    if (dataFile)
    {
      pt_read = (char*) &Seuils[0];
      for (idx = 0; idx < sizeof(Seuils); idx ++)
      {
        pt_read[idx] = dataFile.read();
      }
    }
    dataFile.close();
  }
  else                        // Si le fichier Seuils.par n'existe pas, on le créé à partir des seuils courants
  {
    WriteSeuilsToFile();
  }
}

void WriteSeuilsToFile(void) // Ecriture des Seuils dans le fichier Seuils.par
{
  unsigned int idx;
  char *pt_read;
  File dataFile = SD.open("Seuils.par", FILE_WRITE);
  dataFile.seek(0);
  pt_read = (char*) &Seuils[0][0];
  for (idx = 0; idx < sizeof(Seuils); idx ++)
  {
    dataFile.write(pt_read[idx]);
  }
  dataFile.close();
}

/*---------------------------------------------------------------------------------------------*/
/*                            HYSTERESIS : LECTURE / ECRITURE SUR SD                           */
/*---------------------------------------------------------------------------------------------*/
void ReadHysterFromFile(void)
{
  unsigned int idx;
  char *pt_read;

  if (SD.exists("Hyst.par")) // Si le fichier Seuils.par existe, on le lit
  {
    File dataFile = SD.open("Hyst.par", FILE_READ);
    if (dataFile)
    {
      pt_read = (char*) &Hysteresis[0];
      for (idx = 0; idx < sizeof(Hysteresis); idx ++)
      {
        pt_read[idx] = dataFile.read();
      }
    }
    dataFile.close();
  }
  else                        // Si le fichier Seuils.par n'existe pas, on le créé à partir des seuils courants
  {
    WriteHysterToFile();
  }
}

void WriteHysterToFile(void) // Ecriture des Seuils dans le fichier Seuils.par
{
  unsigned int idx;
  char *pt_read;
  File dataFile = SD.open("Hyst.par", FILE_WRITE);
  dataFile.seek(0);
  pt_read = (char*) &Hysteresis[0][0];
  for (idx = 0; idx < sizeof(Hysteresis); idx ++)
  {
    dataFile.write(pt_read[idx]);
  }
  dataFile.close();
}

/*---------------------------------------------------------------------------------------------*/
/*                          SAUVEGARDE DES HISTORIQUES SUR SD ET RAM                           */
/*---------------------------------------------------------------------------------------------*/

void SaveHistoriques(void)
{
  int idx;
  static unsigned int CompteJours = 0;
  static unsigned int CompteSemaines = 0;
  static unsigned int CompteMois = 0;
  static unsigned int CompteAnnee = 0;

  CompteJours ++;
  CompteSemaines ++;
  CompteMois ++;
  CompteAnnee ++;

  for (idx = 0; idx < NB_TEMP - 1 ; idx ++)
  {
    Historiques[idx][0][CompteJours] = Temperatures[idx + 1];
    if ((CompteSemaines % 7) == 0)
      Historiques[idx][1][CompteSemaines / 7] = Temperatures[idx + 1];
    if ((CompteMois % 30) == 0)
      Historiques[idx][2][CompteMois / 30] = Temperatures[idx + 1];
    if ((CompteAnnee % 365) == 0)
      Historiques[idx][3][CompteAnnee / 365] = Temperatures[idx + 1];
  }
  if (CompteJours >= 320) CompteJours = 0;
  if (CompteSemaines >= 2240) CompteSemaines = 0;
  if (CompteMois >= 9600) CompteMois = 0;
  if (CompteAnnee >= 116800) CompteAnnee = 0;
}


/*---------------------------------------------------------------------------------------------*/
/*                                AFFICHAGE DES HISTORIQUES                                    */
/*---------------------------------------------------------------------------------------------*/

