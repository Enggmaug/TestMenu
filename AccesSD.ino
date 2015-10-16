
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

void SaveHistoriques(void) // A Ecrire
{
  Serial.println("Save Historique");
}


/*---------------------------------------------------------------------------------------------*/
/*                                AFFICHAGE DES HISTORIQUES                                    */
/*---------------------------------------------------------------------------------------------*/
void ShowHistoExt(void)
{
}
void ShowHistoInt(void)
{
}
void ShowHistoPuit(void)
{
}
void ShowHistoChem(void)
{
}

