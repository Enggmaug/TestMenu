void ReadSeuilsFromFile(void);
void WriteSeuilsToFile(void); // Ecriture des Seuils dans le fichier Seuils.par
void ReadHysterFromFile(void);
void WriteHysterToFile(void); // Ecriture des Seuils dans le fichier Seuils.par
void SaveHistoriques(void);
void Reset(void);
void SetState(void);
void None(void);
void ReadTime(void);
void SetAlarmMinutes(void);
void SetDateOnOff(void);
void SetDatePlus(void);
void SetDateMoins(void);
void SetDatePlusMoins(int Direction);
void SetHeuresOnOff(void);
void SetHeurePlus(void);
void SetHeureMoins(void);
void SetHeurePlusMoins(int Direction);
void GotoSetDate(void);
void GotoStartMenu(void);
void GotoDisplayTemp(void);
void GotoDisplayOutputs(void);
void GotoMainMenu(void);
void GotoDeclenche(void);
void GotoHysteresis(void);
void GotoSeuils(void);
void GotoHisto(void);
void GotoCourbes(void);
void ShowHistoExt(void);
void ShowHistoInt(void);
void ShowHistoPuit(void);
void ShowHistoChem(void);
void GotoMinMax(void);
void GotoResetScreen(void);
void GotoMaintenance(void);
void GotoSetDateHeure(void);
void GotoSetHeure(void);
void SaveYesNo(void);
void Suivant(void);
void ChangeItem(int Direction);
void SetMode(void);
char* AddValToLine(int idx);
char* AddModeToLine(int idx);
void ChangeHisto(int Direction);
void DisplayMenuScreen(void);
void DisplayTempScreen(void);
void DisplayCourbeScreen(void);
void DisableSD(void);
void DisableRTC(void);
void RotationDetectCLK(void);
void RotationDetectDT(void);
void Selection(void);
void ManageRotation(void);
void GetTemperatures(void);
float ReadTemperature(int AnalogPinNumber);
void CheckTemperatures (void);
int ConvertTemperature(float InputTemp, float Min, float Max, int HauteurMax);
float Moyenne (float *pt_tab, int NbOfElements);
void SetOnOff(void);
void SetSeuilPlus(void);
void SetSeuilMoins(void);
void SetSeuilPlusMoins(int Direction);
void SetHysteresisPlus(void);
void SetHysteresisMoins(void);
void SetHysteresisPlusMoins(int Direction);
void SetModePlus(void);
void SetModeMoins(void);
void SetMode(int Direction);
void SaveSeuils2File(void);
void RecallSeuils(void);
void SaveHyster2File(void);
void RecallHyster(void);
void SaveDate(void);
void RecallDate(void);
void SaveTime(void);
void RecallTime(void);
