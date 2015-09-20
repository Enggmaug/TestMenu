

void loop() {
  // put your main code here, to run repeatedly:
  if (RotDetect) ManageRotation();
  if (MenuChanged) DisplayMenuScreen();
  MenuChanged = false;
  RotDetect = false;
}
