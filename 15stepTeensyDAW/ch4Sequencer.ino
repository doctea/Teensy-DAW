
void gridchannel4Sequencer () {   //static Display rendering
  clearWorkSpace();
  drawMelodicSequencerStatic(ch4COLOR);
  tft.print(ch4Octaves);
}

void channel4Sequencer () {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    TS_Point p = ts.getPoint();
    gridTouchX = map(p.x, 180, 3730, 0, 19);  // mapping the touch coordinates to a grid of 20
    gridTouchY = map(p.y, 260, 3760, 0, 14);  //mapping the touch coordinates to a grid of 15

        byte tone_start = ch4Octaves * 12;
    byte tone_end = (ch4Octaves + 1) * 12;
    for (byte tone = tone_start ; tone < tone_end ; tone++) {
      for (byte steps = 0 ; steps < STEP_QUANT ; steps++) {
        if (channel4Clip[ch4Clip][tone][steps]) {
          tft.fillCircle((steps * STEP_FRAME_W) + DOT_OFFSET_X, ((tone - tone_start) * STEP_FRAME_H) + DOT_OFFSET_Y, DOT_RADIUS, trackColor[ch4COLOR]);
        }
      }
    }



    //octave selection
    if (ts.touched()) {
      if (gridTouchX > OCTAVE_CHANGE_LEFTMOST && gridTouchX < OCTAVE_CHANGE_RIGHTMOST  && gridTouchY > OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
        ch4Octaves--;
        clearStepsGrid();
      }
      if (gridTouchX > OCTAVE_CHANGE_LEFTMOST && gridTouchX < OCTAVE_CHANGE_RIGHTMOST  && gridTouchY > OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
        ch4Octaves++;
        clearStepsGrid();
      }
      //draw the octave number
      tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 4, STEP_FRAME_W * 2, STEP_FRAME_H * 4, ILI9341_DARKGREY);
      tft.setCursor(STEP_FRAME_W * 18 + 12, STEP_FRAME_H * 5 + 8);
      tft.setFont(Arial_16);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(1);
      tft.print(ch4Octaves);

      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
        ch4tone = (gridTouchY - 1) + ch4Octaves * 12;
        int step_number = gridTouchX - 2;
        if (channel4Clip[ch4Clip][ch4tone][step_number] == LOW) {
          channel4Clip[ch4Clip][ch4tone][step_number] = HIGH;
          tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, trackColor[ch4COLOR]); //draw the active steps circles
        }
        else if (channel4Clip[ch4Clip][ch4tone][step_number] == HIGH) {
          channel4Clip[ch4Clip][ch4tone][step_number] = LOW;
          tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY); //draw the active steps circles
        }
      }
      if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
        ch4Clip = (gridTouchX / 2) - 1;
        clearStepsGrid();
      }
    }

  }
}