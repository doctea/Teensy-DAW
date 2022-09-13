///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                         SEQUENCER CALLBACKS                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


byte thickness = 3;


// called when the step position changes. both the current
// position and last are passed to the callback
void step(int current, int last) {

  if (pattern[i][beatcount] == HIGH) {                                    // if the instrument is set to high at this point
    if (!held_notes[inst][127]) {
      held_notes[inst][127] = true;
    }
  }
  else {
    if (held_notes[inst][127]) {
      trellis.noteOff(i + 36, 0);                                           // if its low, shut up
      trellis.setPixelColor(i + 16, pixelcolor[i]);
      held_notes[inst][127] = false;
    }
  }
  for (int i = 0; i < 127; i++) {
    if (channel1Clip[ch1Clip][i][current] == HIGH) {
      usbMIDI.sendNoteOn(i, velocity, channel1channel);
    }
    else if (channel1Clip[ch1Clip][i][current + 1] == LOW) {
      usbMIDI.sendNoteOff(i, velocity, channel1channel);
    }
  }
  for (int i = 0; i < 127; i++) {
    if (channel2Clip[ch2Clip][i][current] == HIGH) {
      usbMIDI.sendNoteOn(i, velocity, channel2channel);
    }
    else if (channel2Clip[ch2Clip][i][current + 1] == LOW) {
      usbMIDI.sendNoteOff(i, velocity, channel2channel);
    }
  }
  for (int i = 0; i < 127; i++) {
    if (channel3Clip[ch3Clip][i][current] == HIGH) {
      usbMIDI.sendNoteOn(i, velocity, channel3channel);
    }
    else if (channel3Clip[ch3Clip][i][current + 1] == LOW) {
      usbMIDI.sendNoteOff(i, velocity, channel3channel);
    }
  }
  for (int i = 0; i < 127; i++) {
    if (channel4Clip[ch4Clip][i][current] == HIGH) {
      usbMIDI.sendNoteOn(i, velocity, channel4channel);
    }
    else if (channel4Clip[ch4Clip][i][current + 1] == LOW) {
      usbMIDI.sendNoteOff(i, velocity, channel4channel);
    }
  }
  for (int i = 0; i < 127; i++) {
    if (channel5Clip[ch5Clip][i][current] == HIGH) {
      usbMIDI.sendNoteOn(i, velocity, channel5channel);
    }
    else {
      usbMIDI.sendNoteOff(i, velocity, channel5channel);
    }
  }
  for (int i = 0; i < 127; i++) {
    if (channel6Clip[ch6Clip][i][current] == HIGH) {
      usbMIDI.sendNoteOn(i, velocity, channel6channel);
    }
    else {
      usbMIDI.sendNoteOff(i, velocity, channel6channel);
    }
  }
  for (int i = 0; i < 127; i++) {
    if (channel7Clip[ch7Clip][i][current] == HIGH) {
      usbMIDI.sendNoteOn(i, velocity, channel7channel);
    }
    else {
      usbMIDI.sendNoteOff(i, velocity, channel7channel);
    }
  }
  for (int i = 0; i < 127; i++) {
    if (channel8Clip[ch8Clip][i][current] == HIGH) {
      usbMIDI.sendNoteOn(i, velocity, channel8channel);
    }
    else {
      usbMIDI.sendNoteOff(i, velocity, channel8channel);
    }
  }

  for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
    for (int stepwidth = 1; stepwidth <= 16; stepwidth++) {
      tft.drawFastHLine(current * stepwidth + STEP_FRAME_W * 2, stepPositionY + songPointerThickness, STEP_FRAME_W, ILI9341_GREEN);
      tft.drawFastHLine((current - 1) * stepwidth + STEP_FRAME_W * 2, stepPositionY + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
    }
  }
  for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
    if (current == 0) {
      tft.drawFastHLine(STEP_FRAME_W * 17, stepPositionY + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);

    }
  }
  if (current == 0) {
    barClock++;
    pixelbarClock++;
    tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON - 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
    tft.setTextColor(ILI9341_WHITE);
    tft.setFont(Arial_9);
    tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 2, 3);
    tft.print(barClock + 1);
    for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
      tft.drawPixel(barClock + STEP_FRAME_W * 2, (songPositionY + songPointerThickness) , ILI9341_GREEN);
      tft.drawFastHLine(pixelbarClock * PHRASE_SEGMENT_LENGTH + STEP_FRAME_W * 2, gridPositionY + songPointerThickness, PHRASE_SEGMENT_LENGTH, ILI9341_GREEN);
      tft.drawFastHLine((pixelbarClock - 1) * PHRASE_SEGMENT_LENGTH + STEP_FRAME_W * 2, gridPositionY + songPointerThickness, PHRASE_SEGMENT_LENGTH, ILI9341_DARKGREY);
    }
    if (pixelbarClock == 255 / PHRASE_SEGMENT_LENGTH) {

      pixelbarClock = 0;
      tft.fillRect(STEP_FRAME_W * 2, gridPositionY, STEP_FRAME_W * 20, 4, ILI9341_DARKGREY);
    }
    if (barClock == 255) {

      barClock = 0;
      tft.fillRect(STEP_FRAME_W * 2, songPositionY, STEP_FRAME_W * 20, 4, ILI9341_DARKGREY);
    }
  }

}

// the callback that will be called by the sequencer when it needs
// to send midi commands. this specific callback is designed to be
// used with a standard midi cable.
//
// the following image will show you how your MIDI cable should
// be wired to the Arduino:
// http://arduino.cc/en/uploads/Tutorial/MIDI_bb.png
void midi(byte channel, byte command, byte arg1, byte arg2) {

  if (command < 128) {
    // shift over command
    command <<= 4;
    // add channel to the command
    command |= channel1channel;
  }

}