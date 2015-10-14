
/*---------------------------------------------------------------------------------------------*/
/*                            SORTIE DE L'ECRAN DE SAUVEGARDE SEUILS                           */
/*---------------------------------------------------------------------------------------------*/
void SaveSeuils2File(void)
{
  WriteSeuilsToFile();
  GotoDeclenche();
}

void RecallSeuils(void)
{
  ReadSeuilsFromFile();
  GotoDeclenche();
}

/*---------------------------------------------------------------------------------------------*/
/*                            SORTIE DE L'ECRAN DE SAUVEGARDE HYSTERESIS                       */
/*---------------------------------------------------------------------------------------------*/
void SaveHyster2File(void)
{
  WriteHysterToFile();
  GotoDeclenche();
}

void RecallHyster(void)
{
  ReadHysterFromFile();
  GotoDeclenche();
}

/*---------------------------------------------------------------------------------------------*/
/*                              SORTIE DE L'ECRAN DE SAUVEGARDE DATE                           */
/*---------------------------------------------------------------------------------------------*/
void SaveDate(void)
{
  WriteTime();
  GotoSetDateHeure();
}

void RecallDate(void)
{
  Serial.println("Recall");
  ReadTime();
  GotoSetDateHeure();
}

/*---------------------------------------------------------------------------------------------*/
/*                              SORTIE DE L'ECRAN DE SAUVEGARDE HEURE                          */
/*---------------------------------------------------------------------------------------------*/
void SaveTime(void)
{
  WriteTime();
  GotoSetDateHeure();
}

void RecallTime(void)
{
  Serial.println("Recall");
  ReadTime();
  GotoSetDateHeure();
}


