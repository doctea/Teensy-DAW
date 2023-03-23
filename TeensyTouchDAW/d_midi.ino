///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                         SEQUENCER CALLBACKS                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////





void process_clock() {


  if (master_clock.process_MIDItick()) {
    seq_MIDItick++;
    nfx6_MIDItick++;
    if (track[0].seqMode == 5) {

      for (int b = 0; b < 12; b++) {

        if (master_clock.get_MIDItick() % NFX5[NFX5presetNr].Pot_Value[b] == 0) {
          if (ratchet[NFX5presetNr][b][track[0].MIDItick_16]) {
            repeatED[b]++;
            if (repeatED[b] < NFX5[NFX5presetNr].repeats[b]) {
              if (dsend_noteOff[b]) {
                dsend_noteOff[b] = false;
                if (track[0].MIDIchannel < 17) {
                  usbMIDI.sendNoteOff(drumnote[b], track[0].MIDI_velocity, track[0].MIDIchannel);
                  MIDI.sendNoteOff(drumnote[b], track[0].MIDI_velocity, track[0].MIDIchannel);
                  for (int usbs = 0; usbs < 10; usbs++) {
                    if (!launchpad) {
                      usb_midi_devices[usbs]->sendNoteOff(drumnote[b], track[0].MIDI_velocity, track[0].MIDIchannel);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    for (int i = 0; i < NUM_TRACKS; i++) {
      track[i].MIDItick++;

      if (track[i].MIDItick % track[i].MIDItick_reset == 0) {
        track[i].tick_true = true;
        track[i].MIDItick_16++;
        track[i].MIDItick = 0;
        //Noteoff for drumtrack
        for (int b = 0; b < num_voice; b++) {
          if (dsend_noteOff[b]) {
            dsend_noteOff[b] = false;
            if (track[0].MIDIchannel < 17) {
              usbMIDI.sendNoteOff(drumnote[b], track[0].MIDI_velocity, track[0].MIDIchannel);
              MIDI.sendNoteOff(drumnote[b], track[0].MIDI_velocity, track[0].MIDIchannel);
              for (int usbs = 0; usbs < 10; usbs++) {
                if (!launchpad) {
                  usb_midi_devices[usbs]->sendNoteOff(drumnote[b], track[0].MIDI_velocity, track[0].MIDIchannel);
                }
              }
            }
          }
        }
        if (track[i].MIDItick_16 == NUM_STEPS) {
          track[i].MIDItick_16 = 0;
        }
      }
      if (track[i].seqMode == 6) {
        //if the actual step is high, play the notes
        if (track[i].notevalue_onTick[nfx6_MIDItick] > VALUE_NOTEOFF) {
          track[i].playNoteOnce = true;
          track[i].notePressed = true;
          track[i].notePlayed = track[i].notevalue_onTick[nfx6_MIDItick] + track[i].NoteOffset[phrase];
        }
        if (track[i].notevalue_onTick[nfx6_MIDItick] == VALUE_NOTEOFF) {
          track[i].notePressed = false;
        }
      }
    }

    if (seq_MIDItick % 6 == 0) {
      tick_16++;
      for (int b = 0; b < 12; b++) {
        repeatED[b] = 0;
      }



      if (debugTime) {
        SerialPrintSeq();
      }
      drawstepPosition(tick_16);
      //draw phrasenumber
      tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON + 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
      tft.setTextColor(ILI9341_WHITE);
      tft.setFont(Arial_9);
      tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 4, 3);
      tft.print(phrase + 1);
    }

    if (tick_16 == 15) {
      tick_16 = -1;
      phrase++;
      pixelphrase++;
      drawbarPosition();
      nfx6_MIDItick = 0;
      showSerialonce = true;
    }
    if (tick_16 == -1) {
      beatComponents();
      if (debugTime) {
        if (showSerialonce) {
          SerialPrintPlugins();
        }
      }
    }
    //differnt things happening while the clock is running
    if (phrase == MAX_PHRASES - 1) {
      master_clock.set_playing(false);
      phrase = -1;
      pixelphrase = -1;
      phrase = 0;
      nfx6_MIDItick = 0;
      tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);
    }
    if (phrase == end_of_loop - 1) {
      phrase = start_of_loop;
      pixelphrase = 0;
      nfx6_MIDItick = 0;
      tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);
    }
  }
}




// called when the step position changes. both the current
// position and last are passed to the callback
void step() {


  //send midinotes for drumtrack #1
  if (!track[0].solo_mutes_state) {
    if (!track[0].mute_state) {

      if (track[0].seqMode == 0) {
        for (int i = 0; i < 12; i++) {


          //if the actual step is high, play the notes
          if (channel1Clip[track[0].clip_songMode][i][track[0].MIDItick_16]) {
            if (!dsend_noteOff[i]) {
              drumnotes[i] = true;
              dsend_noteOff[i] = true;
              //DrumPluginPlay();
              if (track[0].MIDIchannel < 17) {
                usbMIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                MIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                for (int usbs = 0; usbs < 10; usbs++) {
                  if (!launchpad) {
                    usb_midi_devices[usbs]->sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                  }
                }
              }
            }
          }
        }
      }
      if (track[0].seqMode == 1) {
        if (track[0].clip_songMode < 8) {
          for (int i = 0; i < num_voice; i++) {


            if (beatArray[NFX1[track[0].clip_songMode].Pot_Value[i]][track[0].MIDItick_16]) {
              if (!dsend_noteOff[i]) {
                drumnotes[i] = true;
                dsend_noteOff[i] = true;
                if (track[0].MIDIchannel < 17) {
                  usbMIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                  MIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                  for (int usbs = 0; usbs < 10; usbs++) {
                    if (!launchpad) {
                      usb_midi_devices[usbs]->sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (track[0].seqMode == 4) {
        for (int i = 0; i < 12; i++) {
          //if (NFX4[NFX4presetNr].reset[i]<=NFX4[NFX4presetNr].Pot_Value[i])
          NFX4[NFX4presetNr].reset[i]++;

          //Serial.println(NFX4[1].reset[0]);
          if (NFX4[NFX4presetNr].reset[i] >= NFX4[NFX4presetNr].Pot_Value[i]) {
            NFX4[NFX4presetNr].reset[i] = 0;
          }

          //if the actual step is high, play the notes
          if (channel1Clip[track[0].clip_songMode][i][NFX4[NFX4presetNr].reset[i]]) {
            if (!dsend_noteOff[i]) {
              drumnotes[i] = true;
              dsend_noteOff[i] = true;
              //DrumPluginPlay();
              if (track[0].MIDIchannel < 17) {
                usbMIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                MIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                for (int usbs = 0; usbs < 10; usbs++) {
                  if (!launchpad) {
                    usb_midi_devices[usbs]->sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                  }
                }
              }
            }
          }
        }
      }
      if (track[0].seqMode == 5) {
        if (track[0].clip_songMode < 8) {
          for (int i = 0; i < 12; i++) {


            //if the actual step is high, play the notes
            if (channel1Clip[NFX5presetNr][i][track[0].MIDItick_16]) {
              if (!dsend_noteOff[i]) {
                drumnotes[i] = true;
                dsend_noteOff[i] = true;
                if (track[0].MIDIchannel < 17) {
                  usbMIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                  MIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                  for (int usbs = 0; usbs < 10; usbs++) {
                    if (!launchpad) {
                      usb_midi_devices[usbs]->sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }



  //send midinoteOn/Off´s for melodic track #2 -8
  for (int track_number = 1; track_number <= 7; track_number++) {
    if (!track[track_number].solo_mutes_state) {
      if (!track[track_number].mute_state) {


        if (track[track_number].seqMode == 0) {
          //if the actual step is high, play the notes
          if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16] > VALUE_NOTEOFF) {
            track[track_number].playNoteOnce = true;
            track[track_number].notePressed = true;
            track[track_number].notePlayed = ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16] + track[track_number].NoteOffset[phrase];

            //NoteOff
            if (track[track_number].MIDItick >= track[track_number].stepLength) {
              track[track_number].notePressed = false;
            }
          }
        }
        if (track[track_number].seqMode == 2) {

          cc23 = NFX2[NFX2presetNr].Pot_Value[2];
          cc24 = NFX2[NFX2presetNr].Pot_Value[3];
          if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16] > VALUE_NOTEOFF) {
            if (track[track_number].tick_true) {
              track[track_number].tick_true = false;
              maxVal = 0;
              if (NFX2[NFX2presetNr].Pot_Value[2] <= NFX2[NFX2presetNr].Pot_Value) {
                for (int i = 0; i < 12; i++) {
                  if (analogReadArray[i] > maxVal) {
                    maxVal = analogReadArray[i];
                    maxValIndex = i;
                    octave = random(cc23, cc24);
                  }
                }
              }

              if (NFX2[NFX2presetNr].Pot_Value[2] > NFX2[NFX2presetNr].Pot_Value) {
                for (int i = 11; i >= 0; i--) {
                  if (analogReadArray[i] > maxVal) {
                    maxVal = analogReadArray[i];
                    maxValIndex = i;
                    octave = random(cc24, cc23);
                  }
                }
              }
              track[track_number].playNoteOnce = true;
              track[track_number].notePressed = true;
              track[track_number].notePlayed = (maxValIndex) + (octave * 12) + track[track_number].NoteOffset[phrase];
              Serial.print(track[track_number].notePlayed);
              Serial.print("--");

              analogReadArray[maxValIndex] = (analogReadArray[maxValIndex] - NFX2[NFX2presetNr].Pot_Value[0]);
              Serial.println(maxValIndex);
            }

            //NoteOff
            if (track[track_number].MIDItick >= track[track_number].stepLength) {
              track[track_number].notePressed = false;
              Serial.println(track[track_number].notePlayed);
            }
          }
          if (analogReadArray[maxValIndex] <= NFX2[NFX2presetNr].Pot_Value[1]) {
            for (int i = 0; i < 12; i++) {
              analogReadArray[i] = NFX2[NFX2presetNr].Pot_Value;
            }
          }
        }
        if (track[track_number].seqMode == 3) {


          //if the actual step is high, play the notes
          if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16] > VALUE_NOTEOFF) {

            if (track[track_number].tick_true) {
              track[track_number].tick_true = false;
              Serial.println("Hello");
              NFX3[NFX3presetNr].Oct1 = random(NFX3[NFX3presetNr].Pot_Value[2], NFX3[NFX3presetNr].Pot_Value[3]);
              track[track_number].notePlayed = random(0, 11) + (NFX3[NFX3presetNr].Oct1 * 12);
              track[track_number].playNoteOnce = true;
              track[track_number].notePressed = true;
              Serial.print(track[track_number].notePlayed);
              Serial.print("--");
            }
            //NoteOff
            if (track[track_number].MIDItick >= track[track_number].stepLength) {
              track[track_number].notePressed = false;
              Serial.println(track[track_number].notePlayed);
            }
          }

          // }
          /*
          //if the last step wass high, stop the notes
          if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16 - 1] > VALUE_NOTEOFF) {
            track[track_number].notePressed = false;
            //PluginNoteOff();
          }
          */
        }
      }
    }
  }
}

void midiCC_view_Static(int mixerpage, byte desired_instrument) {
  clearWorkSpace();


  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
    drawPotCC(MixerColumn, 0, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], trackColor[desired_instrument]);
    drawNrInRect(MixerColumnPos, CTRL_ROW_0 + 1, track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);

    drawPotCC(MixerColumn, 1, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], trackColor[desired_instrument]);
    drawNrInRect(MixerColumnPos, CTRL_ROW_1 + 1, track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);

    drawPotCC(MixerColumn, 2, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], trackColor[desired_instrument]);
    drawNrInRect(MixerColumnPos, CTRL_ROW_2 + 1, track[desired_instrument].midicc_number_row_3[MixerColumn], trackColor[desired_instrument]);

    drawPotCC(MixerColumn, 3, track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], trackColor[desired_instrument]);
    drawNrInRect(MixerColumnPos, CTRL_ROW_3 + 1, track[desired_instrument].midicc_number_row_4[MixerColumn], trackColor[desired_instrument]);
  }
}

void midiCCpage1_Dynamic(int desired_instrument) {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (!button[14]) {
          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_1[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_1[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].MIDIchannel);
            MIDI.sendControlChange(track[desired_instrument].midicc_number_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].MIDIchannel);
          }

          /*if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_1[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_1[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_1[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumn, 0, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], trackColor[desired_instrument]);
              usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].MIDIchannel);
            }
          }*/
        }
        if (button[14]) {
          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_number_row_1[MixerColumn] = constrain((track[desired_instrument].midicc_number_row_1[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawNrInRect(MixerColumnPos, CTRL_ROW_0 + 1, track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);
          }

          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_number_row_1[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_number_row_1[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_number_row_1[MixerColumn] = Potentiometer[MixerColumn];
              drawNrInRect(MixerColumnPos, CTRL_ROW_0 + 1, track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);
            }
          }*/
        }
      }

      break;
    case 1:

      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (!button[14]) {

          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_2[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_2[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].MIDIchannel);
          }

          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_2[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_2[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_2[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], trackColor[desired_instrument]);
              usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].MIDIchannel);
            }
          }*/
        }
        if (button[14]) {
          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_number_row_2[MixerColumn] = constrain((track[desired_instrument].midicc_number_row_2[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawNrInRect(MixerColumnPos, CTRL_ROW_1 + 1, track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
          }
          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_number_row_2[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_number_row_2[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_number_row_2[MixerColumn] = Potentiometer[MixerColumn];
              drawNrInRect(MixerColumnPos, CTRL_ROW_1 + 1, track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
            }
          }*/
        }
      }

      break;
    case 2:

      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (!button[14]) {

          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_3[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_3[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].MIDIchannel);
          }


          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_3[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_3[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_3[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], trackColor[desired_instrument]);
              usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].MIDIchannel);
            }
          }*/
        }
        if (button[14]) {
          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_number_row_3[MixerColumn] = constrain((track[desired_instrument].midicc_number_row_3[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawNrInRect(MixerColumnPos, CTRL_ROW_2 + 1, track[desired_instrument].midicc_number_row_3[MixerColumn], trackColor[desired_instrument]);
          }
          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_number_row_2[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_number_row_2[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_number_row_2[MixerColumn] = Potentiometer[MixerColumn];
              drawNrInRect(MixerColumnPos, CTRL_ROW_2 + 1, track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
            }
          }*/
        }
      }
      // }

      break;
    case 3:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (!button[14]) {

          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_4[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_4[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].MIDIchannel);
          }


          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_4[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_4[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_4[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], trackColor[desired_instrument]);
              usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].MIDIchannel);
            }
          }*/
        }
        if (button[14]) {

          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_number_row_4[MixerColumn] = constrain((track[desired_instrument].midicc_number_row_4[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawNrInRect(MixerColumnPos, CTRL_ROW_3 + 1, track[desired_instrument].midicc_number_row_4[MixerColumn], trackColor[desired_instrument]);
          }

          /*if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_number_row_2[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_number_row_2[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_number_row_2[MixerColumn] = Potentiometer[MixerColumn];
              drawNrInRect(MixerColumnPos, CTRL_ROW_3 + 1, track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
            }
          }*/
        }
      }


      break;
  }
  if (ts.touched() || button[15]) {

    if (gridTouchY == 2 || gridTouchY == 3) {
      lastPotRow = 0;
    }

    if (gridTouchY == 5 || gridTouchY == 6) {
      lastPotRow = 1;
    }

    if (gridTouchY == 8 || gridTouchY == 9) {
      lastPotRow = 2;
    }
    if (gridTouchY == 11 || gridTouchY == 12) {
      lastPotRow = 3;
    }
  }
}

void startSeq() {
  phrase = start_of_loop;
  master_clock.set_playing(true);

  for (int i = 1; i <= 7; i++) {
    track[i].clip_songMode = track[i].arrangment1[start_of_loop];
  }
}
void stopSeq() {
  master_clock.set_playing(false);
  tick_16 = -1;
  phrase = start_of_loop - 1;
  pixelphrase = -1;
  phrase = 0;
  nfx6_MIDItick = 0;
  seq_MIDItick = -1;
  for (int track_number = 0; track_number < NUM_TRACKS; track_number++) {
    track[track_number].MIDItick_16 = -1;
    track[track_number].MIDItick = -1;
  }
  for (int track_number = 1; track_number <= 7; track_number++) {
    track[track_number].MIDItick_16 = -1;
    if (track[track_number].MIDIchannel < 17) {
      usbMIDI.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[tick_16] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
      MIDI.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[tick_16] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
    }
    if (track[track_number].MIDIchannel == 17) {
      envelope1.noteOff();
      envelope2.noteOff();
    }
    if (track[track_number].MIDIchannel == 19) {
      pl3envelope1.noteOff();
      pl3envelope2.noteOff();
    }
    if (track[track_number].MIDIchannel == 21) {
      pl5envelope1.noteOff();
      pl5envelope2.noteOff();
    }
    if (track[track_number].MIDIchannel == 22) {
      pl6envelope1.noteOff();
      pl6envelope2.noteOff();
    }
    if (track[track_number].MIDIchannel == 24) {
      pl8envelope1.noteOff();
      pl8envelope2.noteOff();
    }
    if (track[track_number].MIDIchannel == 25) {
      pl9string1.noteOff(VELOCITYOFF);
    }
  }
  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);
}







void myClock() {
  //master_clock.get_MIDItick()++;
  usbMIDI.sendRealTime(usbMIDI.Clock);

  if (master_clock.get_MIDItick() % 6 == 0) {
    tick_16++;

    drawstepPosition(tick_16);
    drawbarPosition();
  }

  Serial.println("Clock");
}

void myStart() {
  master_clock.set_playing(true);

  for (int i = 1; i <= 7; i++) {
    track[i].clip_songMode = track[i].arrangment1[0];
  }
  Serial.println("Start");
}
void myStop() {
  master_clock.set_playing(false);
  tick_16 = -1;
  phrase = -1;
  pixelphrase = -1;
  phrase = 0;

  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);

  Serial.println("Stop");
}

void myNoteOn(int channel, byte note, byte velocity) {

  if (launchpad) {

    for (int songpages = 0; songpages < 16; songpages++) {
      if (selectPage == SONGMODE_PAGE_1 + songpages) {
        LP_songmode(note);
      }
    }
    for (int gridNotes = 0; gridNotes < 64; gridNotes++) {
      if (note == LP_grid_notes[gridNotes]) {
        LP_grid_bool[gridNotes] = true;
      }
    }


    if (desired_instrument == 0) {
      for (int octNotes = 0; octNotes < 12; octNotes++) {
        if (note == LP_octave_notes[octNotes]) {
          LP_octave_bool[octNotes] = true;
          drumnotes[octNotes] = true;
        }
      }
    }

    else {
      for (int octNotes = 0; octNotes < 12; octNotes++) {
        if (note == LP_octave_notes[octNotes]) {
          channel = desired_instrument + 1;
          LP_octave_bool_keys[octNotes] = true;
          track[desired_instrument].notePressed = true;
          track[desired_instrument].playNoteOnce = true;
          track[desired_instrument].notePlayed = octNotes + (track[desired_instrument].shown_octaves * 12);
          track[desired_instrument].notePlayed = track[desired_instrument].notePlayed;
        }
      }
    }

    for (int stepss = 0; stepss < 16; stepss++) {
      if (note == LP_step_notes[stepss]) {
        LP_step_bool[stepss] = true;
      }
    }


    // hold for track button
    if (!button[10] && note == 8) {  //"E"  69
      button[8] = true;
    }
    // hold for plugin button
    if (!button[10] && note == 24) {  //"C"  67
      button[9] = true;
    }
    //  hold for Songarranger button
    if (note == 40) {  //"A"  65
      button[10] = true;
    }
    // hold for Mixer button
    if (!button[10] && note == 56) {  //"4"  52
      button[11] = true;
    }
    // hold for FX button
    if (!button[10] && note == 72) {  //"8"  56
      button[12] = true;
    }
    //  hold for recorder button
    if (!button[10] && note == 88) {  //"A"  65
      button[13] = true;
      selectPage = RECORDER_PAGE;
      recorder_Page_Static();
    }
    // hold for shift button
    if (!button[10] && note == 104) {
      button[14] = true;
    }
    // hold for enter button
    if (!button[10] && note == 120) {
      button[15] = true;
    }
  }

  if (!launchpad) {
    //send midinotes for drumtrack
    if (channel == 1) {
      LP_octave_bool[note - 60] = true;
      for (int files = 0; files < 12; files++) {
        if (note == (files + 60) || LP_octave_bool[files]) {
          drumnotes[files] = true;
        }
      }
    } else {
      LP_octave_bool_keys[0] = true;
      track[channel - 1].notePressed = true;
      track[channel - 1].playNoteOnce = true;
      track[channel - 1].notePlayed = note;
      track[channel - 1].notePlayed = note;
    }
    if (seq_rec) {
      ctrack[channel - 1].sequence[track[channel - 1].clip_selector].step[tick_16] = note;
    }
    // When a USB device with multiple virtual cables is used,
    // midi1.getCable() can be used to read which of the virtual
    // MIDI cables received this message.
  }
}

void myNoteOff(int channel, byte note, byte velocity) {
  if (launchpad) {

    for (int gridNotes = 0; gridNotes < 64; gridNotes++) {
      if (note == LP_grid_notes[gridNotes]) {
        LP_grid_bool[gridNotes] = false;
      }
    }

    if (desired_instrument == 0) {
      for (int octNotes = 0; octNotes < 12; octNotes++) {
        if (note == LP_octave_notes[octNotes]) {
          LP_octave_bool[octNotes] = false;
        }
      }
    }

    else {
      for (int octNotes = 0; octNotes < 12; octNotes++) {
        if (note == LP_octave_notes[octNotes]) {
          channel = desired_instrument + 1;
          LP_octave_bool_keys[octNotes] = false;
          track[desired_instrument].notePressed = false;
          track[desired_instrument].notePlayed = octNotes + (track[desired_instrument].shown_octaves * 12);
          track[desired_instrument].notePlayed = track[desired_instrument].notePlayed;
        }
      }
    }

    for (int stepss = 0; stepss < 16; stepss++) {
      if (note == LP_step_notes[stepss]) {
        LP_step_bool[stepss] = false;
      }
    }

    // hold for track button
    if (!button[10] && note == 8) {  //"E"  69
      button[8] = false;
    }
    // hold for plugin button
    if (!button[10] && note == 24) {  //"C"  67
      button[9] = false;
    }
    // hold for Mixer button
    if (note == 40) {  //"4"  52
      button[10] = false;
    }
    // hold for Mixer button
    if (!button[10] && note == 56) {  //"4"  52
      button[11] = false;
    }

    // hold for FX button
    if (!button[10] && note == 72) {  //"8"  56
      button[12] = false;
    }
    // hold for recorder button
    if (!button[10] && note == 88) {
      button[13] = false;
    }
    // hold for shift button
    if (!button[10] && note == 104) {
      button[14] = false;
    }
    // hold for enter button
    if (!button[10] && note == 120) {
      button[15] = false;
    }
  }
  if (!launchpad) {
    if (channel == 1) {
      LP_octave_bool[note - 60] = false;
      for (int files = 0; files < 12; files++) {
        if (note == (files + 60) && !LP_octave_bool[files]) {
          drumnotes[files] = false;
        }
      }
    } else {
      LP_octave_bool_keys[0] = false;
      track[channel - 1].notePressed = false;
      track[channel - 1].notePlayed = note;
      track[channel - 1].notePlayed = note;
    }
  }
}

void myControlChange(int channel, byte control, byte value) {
  if (control == 3) {
    Potentiometer[0] = value;
  }
  if (control == 9) {
    Potentiometer[1] = value;
  }
  if (control == 14) {
    Potentiometer[2] = value;
  }
  if (control == 15) {
    Potentiometer[3] = value;
  }




  //launchpad control up-est row, they send cc´s
  if (launchpad) {
    //cursor left
    if (otherCtrlButtons && control == 104 && value == 127) {
      button[0] = true;
      gridTouchX = constrain(gridTouchX - 1, 0, 19);
      drawCursor();
      showCoordinates();
    } else if (otherCtrlButtons && control == 104 && value != 127) {
      button[0] = false;
    }
    //cursor right
    if (otherCtrlButtons && control == 105 && value == 127) {
      button[1] = true;
      gridTouchX = constrain(gridTouchX + 1, 0, 19);
      drawCursor();
      showCoordinates();
    } else if (otherCtrlButtons && control == 105 && value != 127) {
      button[1] = false;
    }
    //cursor up
    if (otherCtrlButtons && control == 106 && value == 127) {
      button[2] = true;
      gridTouchY = constrain(gridTouchY - 1, 0, 14);
      drawCursor();
      showCoordinates();
    } else if (otherCtrlButtons && control == 106 && value != 127) {
      button[2] = false;
    }
    //cursor down
    if (otherCtrlButtons && control == 107 && value == 127) {
      button[3] = true;
      gridTouchY = constrain(gridTouchY + 1, 0, 14);
      drawCursor();
      showCoordinates();
    } else if (otherCtrlButtons && control == 107 && value != 127) {
      button[3] = false;
    }
    //last pot row
    if (otherCtrlButtons && control == 108 && value == 127) {
      button[4] = true;
      lastPotRow++;
      if (lastPotRow >= 4) {
        lastPotRow = 0;
      }
    } else if (otherCtrlButtons && control == 108 && value != 127) {
      button[4] = false;
    }
    //recbutton
    if (otherCtrlButtons && control == 109 && value == 127) {
      button[5] = true;
      if (seq_rec == false) {
        seq_rec = true;
        tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_RED);
        if (selectPage == RECORDER_PAGE) {
          startRecording();
          drawActiveRect(CTRL_COL_1, CTRL_ROW_1, 2, 1, audio_rec_rec, "Rec", ILI9341_ORANGE);
        }
      } else {
        seq_rec = false;
        tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_LIGHTGREY);
        if (selectPage == RECORDER_PAGE) {
          stopRecording();
          drawActiveRect(CTRL_COL_1, CTRL_ROW_1, 2, 2, audio_rec_rec, "Rec", ILI9341_GREEN);
        }
      }
    } else if (otherCtrlButtons && control == 109 && value != 127) {
      button[5] = false;
    }
    //playbutton
    if (otherCtrlButtons && control == 110 && value == 127) {
      button[6] = true;
      startSeq();
    } else if (otherCtrlButtons && control == 110 && value != 127) {
      button[6] = false;
    }
    //stopbutton
    if (otherCtrlButtons && control == 111 && value == 127) {
      button[7] = true;
      stopSeq();
    } else if (otherCtrlButtons && control == 111 && value != 127) {
      button[7] = false;
    }


    //select tracks
    if (button[8]) {                         //9th button
      if (control == 104 && value == 127) {  //"D"  68  1st button
        selectPage = DRUMTRACK;
        desired_instrument = 0;
        desired_track = 0;
        drumStepSequencer_Static();
      }
      for (int controlss = 1; controlss < 8; controlss++) {
        //select melodic track 2
        if (control == controlss + 104 && value == 127) {  //"F"  70 2nd button
          selectPage = controlss;
          desired_instrument = controlss;
          desired_track = controlss;
          gridStepSequencer(controlss);
        }
      }
    }

    //plugin selection
    if (button[9]) {
      for (int controlss = 0; controlss < 8; controlss++) {
        if (control == controlss + 104 && value == 127) {  //"D"  68  1st button
          desired_track = controlss;
          desired_instrument = controlss;
          //midicc_view
          for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
            if (track[desired_instrument].MIDIchannel == pluginSelection) {
              selectPage = MIDICC_PAGE_1;
              midiCC_view_Static(0, desired_track);
            }
            //plugin_1_view
            if (track[desired_instrument].MIDIchannel == pluginSelection + 17) {
              selectPage = pluginSelection + 40;
              Plugin_View_Static();
            }
          }
        }
      }
    }

    //  select Mixer
    if (button[11]) {                        //"8"  56
      if (control == 104 && value == 127) {  //"D"  68
        selectPage = MIXER_PAGE_1;
        mixerPage1_Static(0);
      }
      //select melodic track 2
      if (control == 105 && value == 127) {  //"F"  70
        selectPage = MIXER_PAGE_2;
        mixerPage2_Static();
      }
      //select melodic track 3
      if (control == 106 && value == 127) {  //"9"  57
        selectPage = MIXER_PAGE_3;
        mixerPage3_Static();
      }
    }
    //FX Selection
    if (button[12]) {
      if (control == 104 && value == 127) {
        selectPage = FX1_PAGE1;
        FX1reverb_static();
      }
      if (control == 105 && value == 127) {
        selectPage = FX2_PAGE1;
        FX2Bitcrush_static();
      }
      if (control == 106 && value == 127) {
        //delay
        selectPage = FX3_PAGE1;
        FX3Delay_static();
      }
      if (control == 108 && value == 127) {
        if (track[desired_instrument].seqMode == 1) {
          selectPage = NFX1_PAGE1;
          NoteFX1_Page_Static();
        }
        if (track[desired_instrument].seqMode == 2) {
          selectPage = NFX2_PAGE1;
          NoteFX2_Page_Static();
        }
        if (track[desired_instrument].seqMode == 3) {
          selectPage = NFX3_PAGE1;
          NoteFX3_Page_Static();
        }
        if (track[desired_instrument].seqMode == 4) {
          selectPage = NFX4_PAGE1;
          NoteFX4_Page_Static();
        }
        if (track[desired_instrument].seqMode == 5) {
          selectPage = NFX5_PAGE1;
          NoteFX5_Page_Static();
        }
        if (track[desired_instrument].seqMode == 6) {
          selectPage = NFX6_PAGE1;
          NoteFX6_Page_Static();
        }
      }
    }
  }
}