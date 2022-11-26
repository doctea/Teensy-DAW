void Plugin_5_Settings() {


  pl5filter1.frequency(pl5[pl5presetNr].Filter1_Frequency);
  pl5filter1.resonance(pl5[pl5presetNr].Filter1_Resonance);
  pl5filter1.octaveControl(pl5[pl5presetNr].Filter1_Sweep);

  pl5envelope1.delay(0);
  pl5envelope1.attack(pl5[pl5presetNr].Env1_Attack);
  pl5envelope1.hold(0);
  pl5envelope1.decay(500);
  pl5envelope1.sustain(0.8);
  pl5envelope1.release(pl5[pl5presetNr].Env1_Release);

  pl5dc1.amplitude(1);

  pl5envelope2.delay(0);
  pl5envelope2.attack(pl5[pl5presetNr].Env1_Attack);
  pl5envelope2.hold(0);
  pl5envelope2.decay(500);
  pl5envelope2.sustain(0.8);
  pl5envelope2.release(pl5[pl5presetNr].Env1_Release);
  pl5amp.gain(1);
}


void Plugin5_Page_Static(byte Pagenumber) {
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawNrInRect(18, 1, pl5presetNr, ILI9341_PURPLE);
  drawPot(CTRL_COL_0, CTRL_ROW_0, pl5[pl5presetNr].selected_file_graph, pl5[pl5presetNr].selected_file, "WAV", trackColor[desired_instrument]);
  drawPot(CTRL_COL_3, CTRL_ROW_0, plugin[5].Volume_graph, plugin[5].Volume_graph, "MIX", trackColor[desired_instrument]);

  drawPot(CTRL_COL_0, CTRL_ROW_1, pl5[pl5presetNr].Filter1_Frequency_graph, pl5[pl5presetNr].Filter1_Frequency, "Frq", trackColor[desired_instrument]);
  drawPot(CTRL_COL_1, CTRL_ROW_1, pl5[pl5presetNr].Filter1_Resonance_graph, pl5[pl5presetNr].Filter1_Resonance_graph, "Res", trackColor[desired_instrument]);
  drawPot(CTRL_COL_2, CTRL_ROW_1, pl5[pl5presetNr].Filter1_Sweep_graph, pl5[pl5presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_instrument]);
  drawPot(CTRL_COL_3, CTRL_ROW_1, pl5[pl5presetNr].Filter1_Type_graph, pl5[pl5presetNr].Filter1_Type, "", trackColor[desired_track]);
  drawChar(CTRL_COL_3, 7, filterType[pl5[pl5presetNr].Filter1_Type], ILI9341_WHITE);

  drawPot(CTRL_COL_0, CTRL_ROW_2, pl5[pl5presetNr].Env1_Attack_graph, pl5[pl5presetNr].Env1_Attack, "Att", trackColor[desired_instrument]);
  drawPot(CTRL_COL_1, CTRL_ROW_2, pl5[pl5presetNr].Env1_Decay_graph, pl5[pl5presetNr].Env1_Decay, "Dec", trackColor[desired_instrument]);
  drawPot(CTRL_COL_2, CTRL_ROW_2, pl5[pl5presetNr].Env1_Sustain_graph, pl5[pl5presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_instrument]);
  drawPot(CTRL_COL_3, CTRL_ROW_2, pl5[pl5presetNr].Env1_Release_graph, pl5[pl5presetNr].Env1_Release, "Rel", trackColor[desired_instrument]);
}
void Plugin5_Page1_Dynamic() {

  switch (lastPotRow) {
    case 0:
      if (msecs % 11 == 0) {

        if (abs(Potentiometer[0] - pl5[pl5presetNr].selected_file_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl5[pl5presetNr].selected_file_graph != Potentiometer[0]) {
            pl5[pl5presetNr].selected_file_graph = Potentiometer[0];
            pl5[pl5presetNr].selected_file = map(pl5[pl5presetNr].selected_file_graph, 0, 127, 0, MAX_WAV_FILES);
            drawPot(CTRL_COL_0, CTRL_ROW_0, pl5[pl5presetNr].selected_file_graph, pl5[pl5presetNr].selected_file, "WAV", trackColor[desired_instrument]);
          }
        }
        if (enter_button) {
          newdigate::flashloader loader;
          pl5sample = loader.loadSample(WAV_files[pl5[pl5presetNr].selected_file]);
        }
      }
      break;
    case 1:
      if (msecs % 11 == 0) {
        if (abs(Potentiometer[0] - pl5[pl5presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Filter1_Frequency = map(Potentiometer[0], 0, 127, 40, 5900.00);
          pl5[pl5presetNr].Filter1_Frequency_graph = Potentiometer[0];
          pl5filter1.frequency(pl5[pl5presetNr].Filter1_Frequency);
          drawPot(CTRL_COL_0, CTRL_ROW_1, pl5[pl5presetNr].Filter1_Frequency_graph, pl5[pl5presetNr].Filter1_Frequency, "Frq", trackColor[desired_instrument]);
        }
        if (abs(Potentiometer[1] - pl5[pl5presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Filter1_Resonance_graph = Potentiometer[1];
          pl5[pl5presetNr].Filter1_Resonance = pl5[pl5presetNr].Filter1_Resonance_graph / 25.40;
          pl5filter1.resonance(pl5[pl5presetNr].Filter1_Resonance);
          drawPot(CTRL_COL_1, CTRL_ROW_1, pl5[pl5presetNr].Filter1_Resonance_graph, pl5[pl5presetNr].Filter1_Resonance_graph, "Res", trackColor[desired_instrument]);
        }
        if (abs(Potentiometer[2] - pl5[pl5presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Filter1_Sweep_graph = Potentiometer[2];
          pl5[pl5presetNr].Filter1_Sweep = pl5[pl5presetNr].Filter1_Sweep_graph / 18.14;
          pl5filter1.octaveControl(pl5[pl5presetNr].Filter1_Sweep);
          drawPot(CTRL_COL_2, CTRL_ROW_1, pl5[pl5presetNr].Filter1_Sweep_graph, pl5[pl5presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_instrument]);
        }
        //Filtertype
        if (abs(Potentiometer[3] - pl5[pl5presetNr].Filter1_Type_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl5[pl5presetNr].Filter1_Type_graph != Potentiometer[3]) {
            pl5[pl5presetNr].Filter1_Type_graph = Potentiometer[3];
            pl5[pl5presetNr].Filter1_Type = pl5[pl5presetNr].Filter1_Type_graph / 43;
            AudioConnection patchCord55(pl5filter1, pl5[pl5presetNr].Filter1_Type, envelope1, 0);
            drawPot(CTRL_COL_3, CTRL_ROW_1, pl5[pl5presetNr].Filter1_Type_graph, pl5[pl5presetNr].Filter1_Type, "", trackColor[desired_track]);
            drawChar(CTRL_COL_3, 7, filterType[pl5[pl5presetNr].Filter1_Type], ILI9341_WHITE);
          }
        }
      }
      break;
    case 2:
      if (msecs % 11 == 0) {
        if (abs(Potentiometer[0] - pl5[pl5presetNr].Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Env1_Attack_graph = Potentiometer[0];
          pl5[pl5presetNr].Env1_Attack = map(pl5[pl5presetNr].Env1_Attack_graph, 0, 127, 10, 700);
          pl5envelope1.attack(pl5[pl5presetNr].Env1_Attack);
          pl5envelope2.attack(pl5[pl5presetNr].Env1_Attack);
          drawPot(3, CTRL_ROW_2, pl5[pl5presetNr].Env1_Attack_graph, pl5[pl5presetNr].Env1_Attack, "Att", trackColor[desired_instrument]);
        }
        if (abs(Potentiometer[1] - pl5[pl5presetNr].Env1_Decay_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Env1_Decay_graph = Potentiometer[1];
          pl5[pl5presetNr].Env1_Decay = map(pl5[pl5presetNr].Env1_Decay_graph, 0, 127, 10, 700);
          pl5envelope1.decay(pl5[pl5presetNr].Env1_Decay);
          pl5envelope2.decay(pl5[pl5presetNr].Env1_Decay);
          drawPot(7, CTRL_ROW_2, pl5[pl5presetNr].Env1_Decay_graph, pl5[pl5presetNr].Env1_Decay, "Dec", trackColor[desired_instrument]);
        }
        if (abs(Potentiometer[2] - pl5[pl5presetNr].Env1_Sustain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Env1_Sustain_graph = Potentiometer[2];
          pl5[pl5presetNr].Env1_Sustain = pl5[pl5presetNr].Env1_Sustain_graph / 127.00;
          pl5envelope1.sustain(pl5[pl5presetNr].Env1_Sustain);
          pl5envelope2.sustain(pl5[pl5presetNr].Env1_Sustain);
          drawPot(11, CTRL_ROW_2, pl5[pl5presetNr].Env1_Sustain_graph, pl5[pl5presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_instrument]);
        }
        if (abs(Potentiometer[3] - pl5[pl5presetNr].Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Env1_Release_graph = Potentiometer[3];
          pl5[pl5presetNr].Env1_Release = map(pl5[pl5presetNr].Env1_Release_graph, 0, 127, 180, 1200);
          pl5envelope1.release(pl5[pl5presetNr].Env1_Release);
          pl5envelope2.release(pl5[pl5presetNr].Env1_Release);
          drawPot(15, CTRL_ROW_2, pl5[pl5presetNr].Env1_Release_graph, pl5[pl5presetNr].Env1_Release, "Rel", trackColor[desired_instrument]);
        }
      }
      break;
  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || enter_button) {


    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin5();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin5();
      }
    }
    //change preset
    if (gridTouchX >= 18 && gridTouchY == 1) {
      drawNrInRect(18, 1, pl5presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1) - pl5presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl5presetNr = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1);
      }
    }

    if (gridTouchY >= 2 && gridTouchY <= 4) {
      lastPotRow = 0;
    }

    if (gridTouchY >= 5 && gridTouchY <= 7) {
      lastPotRow = 1;
    }

    if (gridTouchY >= 8 && gridTouchY <= 10) {
      lastPotRow = 2;
    }
    if (gridTouchY >= 11 && gridTouchY <= 13) {
      lastPotRow = 3;
    }
  }
}

void savePlugin5() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing plugin5.txt...");
  SD.remove("plugin5.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening plugin5.txt...");
  myFile = SD.open("plugin5.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing plugin 5 to plugin5.txt...");
    //save plugin 5 variables
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      myFile.print((char)pl5[maxpreset].Filter1_Frequency_graph);
      myFile.print((char)pl5[maxpreset].Filter1_Resonance_graph);
      myFile.print((char)pl5[maxpreset].Filter1_Sweep_graph);
      myFile.print((char)pl5[maxpreset].Env1_Attack_graph);
      myFile.print((char)pl5[maxpreset].Env1_Decay_graph);
      myFile.print((char)pl5[maxpreset].Env1_Sustain_graph);
      myFile.print((char)pl5[maxpreset].Env1_Release_graph);
      myFile.print((char)pl5[maxpreset].selected_file_graph);
      myFile.print((char)pl5[maxpreset].Volume_graph);
    }
    tft.println("Done");


    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin5.txt");
  }
}

void loadPlugin5() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("plugin5.txt");
  if (myFile) {
    tft.println("opening plugin5.txt:");


    //load plugin 5 variables
    tft.print("reading plugin 5 from plugin5.txt...");
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      pl5[maxpreset].Filter1_Frequency_graph = myFile.read();
      pl5[maxpreset].Filter1_Resonance_graph = myFile.read();
      pl5[maxpreset].Filter1_Sweep_graph = myFile.read();
      pl5[maxpreset].Env1_Attack_graph = myFile.read();
      pl5[maxpreset].Env1_Decay_graph = myFile.read();
      pl5[maxpreset].Env1_Sustain_graph = myFile.read();
      pl5[maxpreset].Env1_Release_graph = myFile.read();
      pl5[maxpreset].selected_file_graph = myFile.read();
      pl5[maxpreset].Volume_graph = myFile.read();
    }
    tft.println("Done");

    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin5.txt");
  }
}