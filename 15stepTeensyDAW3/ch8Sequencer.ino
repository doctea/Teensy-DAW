void gridStepSequencer(byte desired_instrument) {  //static Display rendering
  clearWorkSpace();
  drawStepSequencerStatic(desired_instrument);
}

void melodicStepSequencer(byte desired_instrument) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    TS_Point p = ts.getPoint();
    int touched_step = gridTouchX - 2;
    byte touched_note = gridTouchY - 1;
    byte tone_start = track[desired_instrument].shown_octaves * 12;
    byte tone_end = (track[desired_instrument].shown_octaves + 1) * 12;

    //draw active steps
    for (byte steps = 0; steps < STEP_QUANT; steps++) {
      if (ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[steps] > VALUE_NOTEOFF) {
        //if (clip[desired_instrument][track[desired_instrument].clip_selector][steps] > VALUE_NOTEOFF) {
        int dot_on_X = (steps * STEP_FRAME_W) + DOT_OFFSET_X;
        int dot_on_Y = ((ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[steps] - tone_start) * STEP_FRAME_H) + DOT_OFFSET_Y;
        //int dot_on_Y = ((clip[desired_instrument][track[desired_instrument].clip_selector][steps] - tone_start) * STEP_FRAME_H) + DOT_OFFSET_Y;
        tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, trackColor[desired_instrument]);
      }
    }

    //draw the octave number
    tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 4, STEP_FRAME_W * 2, STEP_FRAME_H * 3 + 1, ILI9341_DARKGREY);
    tft.setCursor(STEP_FRAME_W * 18 + 12, STEP_FRAME_H * 5);
    tft.setFont(Arial_16);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.print(track[desired_instrument].shown_octaves);


    //draw MIDIChannel number
    tft.setCursor(STEP_FRAME_W * 18 + 8, STEP_FRAME_H * 11 + 3);
    tft.setFont(Arial_10);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.print(track[desired_instrument].MIDIchannel);


    //octave selection
    if (ts.touched()) {
      if (gridTouchX == OCTAVE_CHANGE_LEFTMOST || gridTouchX == OCTAVE_CHANGE_RIGHTMOST - 1) {
        if (gridTouchY >= OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
          track[desired_instrument].shown_octaves--;
          clearStepsGrid();
        }
        if (gridTouchY >= OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
          track[desired_instrument].shown_octaves++;
          clearStepsGrid();
        }
      }


      //midichannel selection
      if (gridTouchX >= 18 && gridTouchY == 11) {
        int MIDIChannelAssign = Potentiometer1;
        track[desired_instrument].MIDIchannel = map(MIDIChannelAssign, 0, 1023, 1, 20);


        //draw MIDIchannel number
        tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 11 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        tft.setCursor(STEP_FRAME_W * 18 + 8, STEP_FRAME_H * 11 + 3);
        tft.setFont(Arial_10);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(track[desired_instrument].MIDIchannel);
      }

      //manually assigning steps to the grid;
      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
        track[desired_instrument].tone = touched_note + track[desired_instrument].shown_octaves * 12;
        int dot_on_X = touched_step * STEP_FRAME_W + DOT_OFFSET_X;
        int dot_on_Y = touched_note * STEP_FRAME_H + DOT_OFFSET_Y;
        int notevalue_on_step = ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step];

        if (notevalue_on_step == VALUE_NOTEOFF) {
          ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step] = track[desired_instrument].tone;
          //clip[desired_instrument][track[desired_instrument].clip_selector][touched_step] = track[desired_instrument].tone;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, trackColor[desired_instrument]);  //draw the active steps circles
        } else if (notevalue_on_step > VALUE_NOTEOFF) {
          ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step] = VALUE_NOTEOFF;
          //clip[desired_instrument][track[desired_instrument].clip_selector][touched_step] = VALUE_NOTEOFF;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the active steps circles
        }
      }
      if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
        track[desired_instrument].clip_selector = (gridTouchX / 2) - 1;
        clearStepsGrid();
      }
    }
  }
}