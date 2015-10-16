#include "SPI.h"
#include "Adafruit_GFX.h"
#include "ILI9341_t3.h"
#include <SD.h>
#include "ds3234.h"

// DEFINE
#define NB_CAR_LIGNE   24
#define NB_CAR_T       9
#define DEFAULT_SEUILS {15.0, 24.0, 22.0, 40.0, 16.0}
#define DEFAULT_HYSTERESIS {0.0, 0.0, 0.0, 0.0, 0.0}
#define NB_TEMP 5

//DEFINE des Numeros de Pins à remplacer par les bonnes valeurs
#define TFT_DC         9
#define TFT_CS         10
#define TFT_RST        -1
#define COD_CLK        6
#define COD_DT         7
#define COD_SW         8
#define SDCARD_CS      15
#define T_EXT          23
#define T_INT          22
#define T_CHEMINEE     19
#define T_PUIT         20
#define RTCLK_CS       21
#define RTCLK_INT      18

//test
#define BUFF_MAX 256

//Couleurs
//                       R     V      B
#define BLANC 0xFFFF //11111 111111 11111
#define NOIR  0x0000 //00000 000000 00000
#define GRIS  0x3186 //00110 001100 00110
#define ROUGE 0xF800 //11111 000000 00000
#define BLEU  0x001F //00000 000000 11111
#define VERT  0x07E0 //00000 111111 00000

//Definitions des Ecrans Menu
typedef void(*FctPtr)(void);
const int ct_NbItemMax          = 7;
const int ct_DisplayTNbItems    = 5;
const int ct_DispOutputsNbItems = 7;
const int ct_MenuMainNbItems    = 7;
const int ct_MenuModeNbItems    = 3;
const int ct_MenuDeclNbItems    = 4;
const int ct_MenuSeuilsNbItems  = 7;
const int ct_HysteresisNbItems  = 7;
const int ct_MenuHistNbItems    = 7;
const int ct_MenuCourbesNbItems = 6;
const int ct_MenuMinMaxNbItems  = 6;
const int ct_ResetNbItems       = 3;
const int ct_MaintenanceNbItems = 7;
const int ct_MenuDHNbItems      = 6;
const int ct_MenuDatebItems     = 5;
const int ct_MenuHeureNbItems   = 4;
const int ct_SauvegarderNbItems = 4;


//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
//                   ITEMS sur Ecran :                               |TITRE,            |Item 1          |Item 2           |Item 3          |Item 4            |Item 6              |Item 7           |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_DisplayT[ct_DisplayTNbItems][NB_CAR_LIGNE]       =  {"TEMPERATURES"    , "EXTERIEUR"    ,                   "INTERIEUR"    , "PUIT CAN."      , "CHEMINEE"         }; //             |
const FctPtr tab_DisplayTFonct[ct_DisplayTNbItems]                =  {GotoMainMenu      } ; //           |                 |                |                  |                    |                 |
/*-*/ bool   tab_DisplayTEnable[ct_DisplayTNbItems]               =  {true              , true           ,                   true           , true             , true               }; //             |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_DispOutputs[ct_DispOutputsNbItems][NB_CAR_LIGNE] =  {"SORTIES"         , "BYPASS1 :"    , "     "         , "BYPASS2 :"    , "     "          , "CHEMINEE :"       , "     "         };
const FctPtr tab_DispOutputsFonct[ct_DispOutputsNbItems]          =  {GotoMainMenu      } ; //           |                 |                |                  |                    |                 |
/*-*/ bool   tab_DispOutputsEnable[ct_DispOutputsNbItems]         =  {true              , true           , true            , true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuMain[ct_MenuMainNbItems][NB_CAR_LIGNE]       =  {"MENU"            , "MODE"         , "DECLENCHEMENTS", "HISTORIQUE"   , "MAINTENANCE"    , "REGLER DATE/HEURE", "RETOUR"        };
const FctPtr tab_MenuMainFonct[ct_MenuMainNbItems]                =  {None              , SetMode        , GotoDeclenche   , GotoHisto      , GotoMaintenance  , GotoSetDateHeure   , GotoDisplayTemp };
/*-*/ bool   tab_MenuMainEnable[ct_MenuMainNbItems]               =  {true              , true           , true            , true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuMode[ct_MenuModeNbItems][NB_CAR_LIGNE]       =  {"ETE"             , "MI-SAISON"    , "HIVERS"        }; //            |                  |                    |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuDeclenche[ct_MenuDeclNbItems][NB_CAR_LIGNE]  =  {"DECLENCHEMENTS"  , "SEUILS"       , "SENSIBILITE"   , "RETOUR"       }; //              |                    |                 |
const FctPtr tab_MenuDeclencheFonct[ct_MenuDeclNbItems]           =  {None              , GotoSeuils     , GotoHysteresis  , GotoMainMenu   }; //              |                    |                 |
/*-*/ bool   tab_MenuDeclencheEnable[ct_MenuDeclNbItems]          =  {true              , true           , true            , true           }; //              |                    |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuSeuils[ct_MenuSeuilsNbItems][NB_CAR_LIGNE]   =  {"REGLAGE SEUILS"  , "T. EXT. BASSE", "T. EXT. HAUTE" , "T. INTERIEURE", "T. CHEMINEE"    , "T. PUIT C."       , "RETOUR"        };
const FctPtr tab_MenuSeuilsFonct[ct_MenuSeuilsNbItems]            =  {None              , SetOnOff       , SetOnOff        , SetOnOff       , SetOnOff         , SetOnOff           , SaveYesNo       };
/*-*/ bool   tab_MenuSeuilsEnable[ct_MenuSeuilsNbItems]           =  {true              , true           , true            , true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_Hysteresis[ct_HysteresisNbItems][NB_CAR_LIGNE]   =  {"SENSIBILITE"     , "T. EXT. BASSE", "T. EXT. HAUTE" , "T. INTERIEURE", "T. CHEMINEE"    , "T. PUIT C."       , "RETOUR"        };
const FctPtr tab_HysteresisFonct[ct_HysteresisNbItems]            =  {None              , SetOnOff       , SetOnOff        , SetOnOff       , SetOnOff         , SetOnOff           , SaveYesNo       };
/*-*/ bool   tab_HysteresisEnable[ct_HysteresisNbItems]           =  {true              , true           , true            , true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuHist[ct_MenuHistNbItems][NB_CAR_LIGNE]       =  {"HISTORIQUE"      , "COURBES HISTO", "MIN/MAX"       , "RESET COURBES", "RESET MIN/MAX"  , "RESET TOUT"       , "RETOUR"        };
const FctPtr tab_MenuHistFonct[ct_MenuHistNbItems]                =  {None              , GotoCourbes    , GotoMinMax      , GotoResetScreen, GotoResetScreen  , GotoResetScreen    , GotoMainMenu    };
/*-*/ bool   tab_MenuHistEnable[ct_MenuHistNbItems]               =  {true              , true           , true            , true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuCourbes[ct_MenuHistNbItems][NB_CAR_LIGNE]    =  {"COURBES"         , "EXTERIEUR"    ,                   "INTERIEUR"    , "PUIT CAN."      , "CHEMINEE"         , "RETOUR"        };
const FctPtr tab_MenuCourbesFonct[ct_MenuCourbesNbItems]          =  {None              , ShowHistoExt   ,                   ShowHistoInt   , ShowHistoPuit    , ShowHistoChem      , GotoHisto       };
/*-*/ bool   tab_MenuCourbesEnable[ct_MenuCourbesNbItems]         =  {true              , true           ,                   true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuMinMax[ct_MenuHistNbItems][NB_CAR_LIGNE]     =  {"MIN/MAX"         , "EXTERIEUR"    ,                   "INTERIEUR"    , "PUIT CAN."      , "CHEMINEE"         , "RETOUR"        };
const FctPtr tab_MenuMinMaxFonct[ct_MenuMinMaxNbItems]            =  {None              , None           ,                   None           , None             , None               , GotoHisto       };
/*-*/ bool   tab_MenuMinMaxEnable[ct_MenuMinMaxNbItems]           =  {true              , true           ,                   true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_Reset[ct_ResetNbItems][NB_CAR_LIGNE]             =  {"RESET"           , "OUI"          , "ANNULER"       }; //            |                  |                    |                 |
const FctPtr tab_ResetFonct[ct_ResetNbItems]                      =  {None              , Reset          , GotoHisto       }; //            |                  |                    |                 |
/*-*/ bool   tab_ResetEnable[ct_ResetNbItems]                     =  {true              , true           , true            }; //            |                  |                    |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuMaint[ct_MaintenanceNbItems][NB_CAR_LIGNE]   =  {"MAINTENANCE"     , "ETAT :"       , "RELAIS"        , "     "        , "FINS DE COURSE" , "     "            , "RETOUR"         };
const FctPtr tab_MenuMaintFonct[ct_MaintenanceNbItems]            =  {None              , SetState       , None            , None           , None             , None               , GotoMainMenu    };
/*-*/ bool   tab_MenuMaintEnable[ct_MaintenanceNbItems]           =  {true              , true           , true            , false          , true             , false              , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuDateHeure[ct_MenuDHNbItems][NB_CAR_LIGNE]    =  {"DATE / HEURE"    , "REGLER DATE"  , "DATE ICI"      , "REGLER HEURE" , "HEURE ICI"      , "RETOUR"           }; //             |
const FctPtr tab_MenuDateHeureFonct[ct_MenuDHNbItems]             =  {None              , GotoSetDate    , None            , GotoSetHeure   , None             , GotoMainMenu       }; //             |
/*-*/ bool   tab_MenuDateHeureEnable[ct_MenuDHNbItems]            =  {true              , true           , false           , true           , false            , true               }; //             |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuDate[ct_MenuDatebItems][NB_CAR_LIGNE]        =  {"REGLER DATE"     , "ANNEE"        , "MOIS"          , "JOUR"         , "RETOUR"         }; //                |                 |
const FctPtr tab_MenuDateFonct[ct_MenuDatebItems]                 =  {None              , SetDateOnOff   , SetDateOnOff    , SetDateOnOff   , SaveYesNo        }; //                |                 |
/*-*/ bool   tab_MenuDateEnable[ct_MenuDatebItems]                =  {true              , true           , true            , true           , true             }; //                |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuHeure[ct_MenuHeureNbItems][NB_CAR_LIGNE]     =  {"REGLER HEURE"    , "HEURES"       , "MINUTES"       , "RETOUR"       }; //              |                    |                 |
const FctPtr tab_MenuHeureFonct[ct_MenuHeureNbItems]              =  {None              , SetHeuresOnOff , SetHeuresOnOff  , SaveYesNo      }; //              |                    |                 |
/*-*/ bool   tab_MenuHeureEnable[ct_MenuHeureNbItems]             =  {true              , true           , true            , true           }; //              |                    |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_Sauvegarder[ct_SauvegarderNbItems][NB_CAR_LIGNE] =  {"SAUVEGARDER"     , "OUI"          , "NON"           , "ANNULER"      }; //              |                    |                 |
const FctPtr tab_SaveSeuilsFonct[ct_SauvegarderNbItems]           =  {None              , SaveSeuils2File, RecallSeuils    , GotoSeuils     }; //              |                    |                 |
const FctPtr tab_SaveHysteresisFonct[ct_SauvegarderNbItems]       =  {None              , SaveHyster2File, RecallHyster    , GotoHysteresis }; //              |                    |                 |
const FctPtr tab_SaveDateFonct[ct_SauvegarderNbItems]             =  {None              , SaveDate       , RecallDate      , GotoSetDate    }; //              |                    |                 |
const FctPtr tab_SaveHoursFonct[ct_SauvegarderNbItems]            =  {None              , SaveTime       , RecallTime      , GotoSetHeure   }; //              |                    |                 |
/*-*/ bool   tab_SauvegarderSDEnable[ct_SauvegarderNbItems]       =  {true              , true           , true            , true           }; //              |                    |                 |
/*-*/ bool   tab_SauvegarderRTCEnable[ct_SauvegarderNbItems]      =  {true              , true           , true            , true           }; //              |                    |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+

const char* BlankLine = "                       ";
char tab_MenuTemp[ct_NbItemMax][NB_CAR_LIGNE];

//Seuils et Température par défaut
float Seuils[3][NB_TEMP] = {DEFAULT_SEUILS, DEFAULT_SEUILS, DEFAULT_SEUILS};
float Hysteresis[3][NB_TEMP] = {DEFAULT_HYSTERESIS, DEFAULT_HYSTERESIS, DEFAULT_HYSTERESIS};
float MinMax[2][NB_TEMP] = {DEFAULT_SEUILS, DEFAULT_SEUILS};
float Temperatures[NB_TEMP];
bool TemperatureDepasseSeuil[NB_TEMP];


// Si carte SD présente
bool SdCardPresent;

// TFT Screen
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST);

//Gestion de navigation - écrans menu
typedef enum
{
  MENU,
  TEMPERATURES,
  SORTIES,
  MAINTENANCE
} ScreenType;

typedef struct
{
  int NbItem;
  char *pt_tab_menu;
  bool *pt_tab_EnabledItems;
  FctPtr *pt_MenuFonct;
  int SelectedItem;
  char NbItems;
  void (*Droite)(void);
  void (*Gauche)(void);
  void (*Select)(void);
  ScreenType TypeEcran;
} ScreenDef;

ScreenDef EcranEnCours;
bool MenuChanged = true;

//Gestion de l'encodeur rotatif
bool RotDetect = false;
enum CodeurActions
{
  NONE,
  GAUCHE,
  DROITE,
  SELECT
} MenuAction;


// Definition des Réglages
enum Reglages {
  ETE = 0,
  MI_SAISON = 1,
  HIVERS = 2
} Reglage;

//Definition de la date/heure courante
struct ts DateHeureCourante;
const struct ts BlankDateHeure = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool RTClockAlarm = false;
bool InhibRTCAlarms = false;
