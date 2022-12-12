void Plugin_6_Settings() {


  pl6filter1.frequency(pl6[pl6presetNr].Filter1_Frequency);
  pl6filter1.resonance(pl6[pl6presetNr].Filter1_Resonance);
  pl6filter1.octaveControl(pl6[pl6presetNr].Filter1_Sweep);
  pl6mixer1.gain(0, 1);
  pl6mixer1.gain(1, 0);
  pl6mixer1.gain(2, 0);
  pl6mixer1.gain(3, 0);
  pl6envelope1.delay(0);
  pl6envelope1.attack(pl6[pl6presetNr].Env1_Attack);
  pl6envelope1.hold(0);
  pl6envelope1.decay(500);
  pl6envelope1.sustain(0.8);
  pl6envelope1.release(pl6[pl6presetNr].Env1_Release);

  pl6dc1.amplitude(1);

  pl6envelope2.delay(0);
  pl6envelope2.attack(pl6[pl6presetNr].Env1_Attack);
  pl6envelope2.hold(0);
  pl6envelope2.decay(500);
  pl6envelope2.sustain(0.8);
  pl6envelope2.release(pl6[pl6presetNr].Env1_Release);
  pl6amp.gain(1);
}

void Plugin6_Page_Static(byte Pagenumber) {
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawNrInRect(18, 1, pl6presetNr, ILI9341_PURPLE);
  drawPot(CTRL_COL_0, CTRL_ROW_0, pl6[pl6presetNr].selected_file_raw_graph, pl6[pl6presetNr].selected_raw_file, "RAW", ILI9341_BLACK);


  drawPot(CTRL_COL_0, CTRL_ROW_1, pl6[pl6presetNr].Filter1_Frequency_graph, pl6[pl6presetNr].Filter1_Frequency, "Freq", trackColor[desired_instrument]);
  drawPot(CTRL_COL_1, CTRL_ROW_1, pl6[pl6presetNr].Filter1_Resonance_graph, pl6[pl6presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_instrument]);
  drawPot(CTRL_COL_2, CTRL_ROW_1, pl6[pl6presetNr].Filter1_Sweep_graph, pl6[pl6presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_instrument]);
  drawPot(CTRL_COL_3, CTRL_ROW_1, pl6[pl6presetNr].Filter1_Type_graph, pl6[pl6presetNr].Filter1_Type, "", trackColor[desired_track]);
  drawChar(CTRL_COL_3, 7, filterType[pl6[pl6presetNr].Filter1_Type], ILI9341_WHITE);

  drawPot(CTRL_COL_0, CTRL_ROW_2, pl6[pl6presetNr].Env1_Attack_graph, pl6[pl6presetNr].Env1_Attack, "Atck", trackColor[desired_instrument]);
  drawPot(CTRL_COL_1, CTRL_ROW_2, pl6[pl6presetNr].Env1_Decay_graph, pl6[pl6presetNr].Env1_Decay, "Dec", trackColor[desired_instrument]);
  drawPot(CTRL_COL_2, CTRL_ROW_2, pl6[pl6presetNr].Env1_Sustain_graph, pl6[pl6presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_instrument]);
  drawPot(CTRL_COL_3, CTRL_ROW_2, pl6[pl6presetNr].Env1_Release_graph, pl6[pl6presetNr].Env1_Release, "Rel", trackColor[desired_instrument]);
}
void Plugin6_Page1_Dynamic() {
  switch (lastPotRow) {
    case 0:
      // if (msecs % 20 == 0) {

      if (abs(Potentiometer[0] - pl6[pl6presetNr].selected_file_raw_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl6[pl6presetNr].selected_file_raw_graph != Potentiometer[0]) {
          pl6[pl6presetNr].selected_file_raw_graph = Potentiometer[0];
          pl6[pl6presetNr].selected_raw_file = map(Potentiometer[0], 0, 127, 0, MAX_RAW_FILES);
          drawPot(CTRL_COL_0, CTRL_ROW_0, pl6[pl6presetNr].selected_file_raw_graph, pl6[pl6presetNr].selected_raw_file, "RAW", ILI9341_BLACK);
        }
      }
      // }
      break;
    case 1:
      // if (msecs % 20 == 0) {
      if (abs(Potentiometer[0] - pl6[pl6presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl6[pl6presetNr].Filter1_Frequency_graph != Potentiometer[0]) {
          pl6[pl6presetNr].Filter1_Frequency_graph = Potentiometer[0];
          pl6filter1.frequency(pl6[pl6presetNr].Filter1_Frequency);
          pl6[pl6presetNr].Filter1_Frequency = map(Potentiometer[0], 0, 127, 40, 5900.00);
          drawPot(CTRL_COL_0, CTRL_ROW_1, pl6[pl6presetNr].Filter1_Frequency_graph, pl6[pl6presetNr].Filter1_Frequency, "Frq", trackColor[desired_instrument]);
        }
      }
      if (abs(Potentiometer[1] - pl6[pl6presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl6[pl6presetNr].Filter1_Resonance_graph != Potentiometer[1]) {
          pl6[pl6presetNr].Filter1_Resonance_graph = Potentiometer[1];
          pl6[pl6presetNr].Filter1_Resonance = pl6[pl6presetNr].Filter1_Resonance_graph / 25.40;
          pl6filter1.resonance(pl6[pl6presetNr].Filter1_Resonance);
          drawPot_2(CTRL_COL_1, CTRL_ROW_1, pl6[pl6presetNr].Filter1_Resonance_graph, pl6[pl6presetNr].Filter1_Resonance_graph, "Res", trackColor[desired_instrument]);
        }
      }
      if (abs(Potentiometer[2] - pl6[pl6presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl6[pl6presetNr].Filter1_Sweep_graph != Potentiometer[2]) {
          pl6[pl6presetNr].Filter1_Sweep_graph = Potentiometer[2];
          pl6[pl6presetNr].Filter1_Sweep = pl6[pl6presetNr].Filter1_Sweep_graph / 18.14;
          pl6filter1.octaveControl(pl6[pl6presetNr].Filter1_Sweep);
          drawPot_3(CTRL_COL_2, CTRL_ROW_1, pl6[pl6presetNr].Filter1_Sweep_graph, pl6[pl6presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_instrument]);
        }
      }
      //Filtertype
      if (abs(Potentiometer[3] - pl6[pl6presetNr].Filter1_Type_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl6[pl6presetNr].Filter1_Type_graph != Potentiometer[3]) {
          pl6[pl6presetNr].Filter1_Type_graph = Potentiometer[3];
          pl6[pl6presetNr].Filter1_Type = pl6[pl6presetNr].Filter1_Type_graph / 43;
          selectFilterType(22, pl6[pl6presetNr].Filter1_Type);
          drawPot_4(CTRL_COL_3, CTRL_ROW_1, pl6[pl6presetNr].Filter1_Type_graph, pl6[pl6presetNr].Filter1_Type, "", trackColor[desired_track]);
          drawChar(CTRL_COL_3, 7, filterType[pl6[pl6presetNr].Filter1_Type], ILI9341_WHITE);
        }
      }
      // }
      break;
    case 2:
      // if (msecs % 20 == 0) {
      if (abs(Potentiometer[0] - pl6[pl6presetNr].Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl6[pl6presetNr].Env1_Attack_graph != Potentiometer[0]) {
          pl6[pl6presetNr].Env1_Attack_graph = Potentiometer[0];
          pl6[pl6presetNr].Env1_Attack = map(pl6[pl6presetNr].Env1_Attack_graph, 0, 127, 10, 700);
          pl6envelope1.attack(pl6[pl6presetNr].Env1_Attack);
          pl6envelope2.attack(pl6[pl6presetNr].Env1_Attack);
          drawPot(3, CTRL_ROW_2, pl6[pl6presetNr].Env1_Attack_graph, pl6[pl6presetNr].Env1_Attack, "Att", trackColor[desired_instrument]);
        }
      }
      if (abs(Potentiometer[1] - pl6[pl6presetNr].Env1_Decay_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl6[pl6presetNr].Env1_Decay_graph != Potentiometer[1]) {
          pl6[pl6presetNr].Env1_Decay_graph = Potentiometer[1];
          pl6[pl6presetNr].Env1_Decay = map(pl6[pl6presetNr].Env1_Decay_graph, 0, 127, 10, 700);
          pl6envelope1.decay(pl6[pl6presetNr].Env1_Decay);
          pl6envelope2.decay(pl6[pl6presetNr].Env1_Decay);
          drawPot_2(7, CTRL_ROW_2, pl6[pl6presetNr].Env1_Decay_graph, pl6[pl6presetNr].Env1_Decay, "Dec", trackColor[desired_instrument]);
        }
      }
      if (abs(Potentiometer[2] - pl6[pl6presetNr].Env1_Sustain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl6[pl6presetNr].Env1_Sustain_graph != Potentiometer[2]) {
          pl6[pl6presetNr].Env1_Sustain_graph = Potentiometer[2];
          pl6[pl6presetNr].Env1_Sustain = pl6[pl6presetNr].Env1_Sustain_graph / 127.00;
          pl6envelope1.sustain(pl6[pl6presetNr].Env1_Sustain);
          pl6envelope2.sustain(pl6[pl6presetNr].Env1_Sustain);
          drawPot_3(11, CTRL_ROW_2, pl6[pl6presetNr].Env1_Sustain_graph, pl6[pl6presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_instrument]);
        }
      }
      if (abs(Potentiometer[3] - pl6[pl6presetNr].Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl6[pl6presetNr].Env1_Release_graph != Potentiometer[3]) {
          pl6[pl6presetNr].Env1_Release_graph = Potentiometer[3];
          pl6[pl6presetNr].Env1_Release = map(pl6[pl6presetNr].Env1_Release_graph, 0, 127, 180, 1200);
          pl6envelope1.release(pl6[pl6presetNr].Env1_Release);
          pl6envelope2.release(pl6[pl6presetNr].Env1_Release);
          drawPot_4(15, CTRL_ROW_2, pl6[pl6presetNr].Env1_Release_graph, pl6[pl6presetNr].Env1_Release, "Rel", trackColor[desired_instrument]);
        }
      }

      break;
  }

  TS_Point p = ts.getPoint();
  if (ts.touched() || enter_button) {


    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin6();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin6();
      }
    }
    //change preset
    if (gridTouchX >= 18 && gridTouchY == 1) {
      drawNrInRect(18, 1, pl6presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1) - pl6presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl6presetNr = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1);
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

void savePlugin6() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing plugin6.txt...");
  SD.remove("plugin6.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening plugin6.txt...");
  myFile = SD.open("plugin6.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing plugin 6 to plugin6.txt...");
    //save plugin 6 variables
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      myFile.print((char)pl6[maxpreset].Filter1_Frequency_graph);
      myFile.print((char)pl6[maxpreset].Filter1_Resonance_graph);
      myFile.print((char)pl6[maxpreset].Filter1_Sweep_graph);
      myFile.print((char)pl6[maxpreset].Env1_Attack_graph);
      myFile.print((char)pl6[maxpreset].Env1_Decay_graph);
      myFile.print((char)pl6[maxpreset].Env1_Sustain_graph);
      myFile.print((char)pl6[maxpreset].Env1_Release_graph);
      myFile.print((char)pl6[maxpreset].selected_file_raw_graph);
      myFile.print((char)pl6[maxpreset].Volume_graph);
    }
    tft.println("Done");

    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin6.txt");
  }
}

void loadPlugin6() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("plugin6.txt");
  if (myFile) {
    tft.println("opening plugin6.txt:");

    // read from the file until there's nothing else in it:
    //load plugin 6 variables
    tft.print("reading plugin 6 from plugin6.txt...");
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      pl6[maxpreset].Filter1_Frequency_graph = myFile.read();
      pl6[maxpreset].Filter1_Resonance_graph = myFile.read();
      pl6[maxpreset].Filter1_Sweep_graph = myFile.read();
      pl6[maxpreset].Env1_Attack_graph = myFile.read();
      pl6[maxpreset].Env1_Decay_graph = myFile.read();
      pl6[maxpreset].Env1_Sustain_graph = myFile.read();
      pl6[maxpreset].Env1_Release_graph = myFile.read();
      pl6[maxpreset].selected_file_raw_graph = myFile.read();
      pl6[maxpreset].Volume_graph = myFile.read();
    }
    tft.println("Done");

    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin6.txt");
  }
}