#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"
#include <SD.h>

#define NB_CAR_LIGNE   24
#define NB_CAR_T       9
#define TFT_DC         9
#define TFT_CS         10
#define TFT_RST        -1
#define COD_CLK        6
#define COD_DT         7
#define COD_SW         8
#define SDCARD_CS      15

typedef void(*FctPtr)(void);
const int ct_NbItemMax = 7;
const int ct_MenuMainNbItems = 6;
const int ct_MenuModeNbItems = 3;
const int ct_MenuSeuilsNbItems = 7;
const int ct_MenuHistNbItems = 6;
const int ct_SauvegarderNbItems = 4;
const char tab_MenuMain[ct_MenuMainNbItems][NB_CAR_LIGNE] = {{"MENU"}, {"MODE"}, { "SEUILS"}, { "HISTORIQUE"}, { "MAINTENANCE"}, { "RETOUR"}};
const FctPtr tab_MenuMainFonct[ct_MenuMainNbItems] = {None, SetMode, GotoSeuils, GotoHisto, ToggleMaintenance, BacktoFunctional};
const char tab_MenuMode[ct_MenuModeNbItems][NB_CAR_LIGNE] = {"ETE", "MI-SAISON", "HIVERS"};
const char tab_MenuSeuils[ct_MenuSeuilsNbItems][NB_CAR_LIGNE] = {"REGLAGE SEUILS", "T. EXT. BASSE", "T. EXT. HAUTE", "T. INTERIEURE", "T. CHEMINEE", "T. PUIT C.", "RETOUR"};
const FctPtr tab_MenuSeuilsFonct[ct_MenuSeuilsNbItems] = {None, SetSeuilOnOff, SetSeuilOnOff, SetSeuilOnOff, SetSeuilOnOff, SetSeuilOnOff, SaveYesNo};
const char tab_MenuHist[ct_MenuHistNbItems][NB_CAR_LIGNE] = {"HISTORIQUE", "EXTERIEUR", "INTERIEUR", "PUIT CAN.", "CHEMINEE", "RETOUR"};
const FctPtr tab_MenuHistFonct[ct_MenuHistNbItems] = {None, ShowHistoExt, ShowHistoInt, ShowHistoPuit, ShowHistoChem, GotoMainMenu};
const char tab_Sauvegarder[ct_SauvegarderNbItems][NB_CAR_LIGNE] = {"SAUVEGARDER", "OUI", "NON", "ANNULER"};
const FctPtr tab_SauvegarderFonct[ct_MenuHistNbItems] = {None, SaveToFile, RecallSeuils, GotoSeuils};
const char* BlankLine = "                       ";

float Seuils[3][5] = {{15.0, 24.0, 22.0, 40.0, 16.0},{15.0, 24.0, 22.0, 40.0, 16.0},{15.0, 24.0, 22.0, 40.0, 16.0}};
float Temperatures[5] = {20.3, 20.3, 21.6, 21.8, 12.7};

char tab_MenuTemp[ct_NbItemMax][NB_CAR_LIGNE];
bool SdCardPresent;

Adafruit_ILI9340 tft = Adafruit_ILI9340(TFT_CS, TFT_DC, TFT_RST);

typedef struct
{
  int NbItem;
  char *pt_tab_menu;
  FctPtr *pt_MenuFonct;
  int SelectedItem;
  char NbItems;
  void (*Droite)(void);
  void (*Gauche)(void);
  void (*Select)(void);
} ScreenDef;

ScreenDef EcranEnCours;
bool MenuChanged = true;
bool RotDetect = false;
enum CodeurActions
{
  NONE,
  GAUCHE,
  DROITE,
  SELECT
} MenuAction;

enum Reglages {
  ETE = 0,
  MI_SAISON = 1,
  HIVERS = 2
} Reglage;


void RotationDetectCLK(void)
{
  if (RotDetect == false)
  {
    MenuAction = DROITE;

    RotDetect = true;
  }
}
void RotationDetectDT(void)
{
  if (RotDetect == false)
  {
    MenuAction = GAUCHE;

    RotDetect = true;
  }
}

void Selection(void)
{
  Serial.println("click");
  noInterrupts();
  if (RotDetect == false)
  {
    delay(100);
    RotDetect = true;
    MenuAction = SELECT;
  }
  interrupts();
}

