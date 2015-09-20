void ManageRotation(void)
{
    if (MenuAction == GAUCHE)
  {
    MenuAction = NONE;
    EcranEnCours.Gauche();
  }
  else if (MenuAction == DROITE)
  {
    MenuAction = NONE;
    EcranEnCours.Droite();
  }
  else if (MenuAction == SELECT)
  {
    MenuAction = NONE;
    EcranEnCours.Select();
  }
}

void DisplayMenuScreen(void)
{
  int idx;
    noInterrupts()

    tft.setTextColor(ILI9340_BLACK);
    tft.fillRect(0, 0, tft.width(), (tft.height() / ct_NbItemMax)-1, ILI9340_WHITE);
    tft.setCursor(tft.width() / 2 - (strlen(EcranEnCours.pt_tab_menu) / 2) * (tft.width() / 17), 5);
    tft.setTextSize(3);
    tft.println(EcranEnCours.pt_tab_menu);
    tft.setTextSize(2);
    for (idx = 1; idx < EcranEnCours.NbItems; idx++)
    {
      if (idx == EcranEnCours.SelectedItem)
      {
        tft.setTextColor(ILI9340_BLACK);
        tft.fillRect(0, (tft.height() / ct_NbItemMax) * idx, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_WHITE);
      }
      else
      {
        tft.setTextColor(ILI9340_WHITE);
        tft.fillRect(0, (tft.height() / ct_NbItemMax) * idx, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
      }

      tft.setCursor(20, 10 + (tft.height() / ct_NbItemMax) * idx);
      tft.println( (char*)(EcranEnCours.pt_tab_menu + NB_CAR_LIGNE * idx));

    }
    for (idx = EcranEnCours.NbItems; idx < ct_NbItemMax; idx++)
    {
      tft.fillRect(0, (tft.height() / ct_NbItemMax) * idx, tft.width(), (tft.height() / ct_NbItemMax), ILI9340_BLACK);
    }
    interrupts()
}
