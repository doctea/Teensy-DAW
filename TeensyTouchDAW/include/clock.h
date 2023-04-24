
elapsedMillis msecs;
elapsedMicros msecsclock;

#include <MIDI.h>
extern MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>> MIDI;

class Clock {
public:
  uint32_t _next_clock = 0;
  uint32_t _clock = 160;
  uint32_t MIDItick = -1;
  uint32_t step_tick = -1;
  uint32_t bar_tick = -1;
  bool seq_run = false;
  bool seq_rec = false;
  bool playing = false;
  byte master_tempo = 120;
  int syncPin = -1;
  uint32_t previousMillis_clock = 0;


  void setup(int new_syncPin) {
    syncPin = new_syncPin;
    if (syncPin >= 0) {
      digitalWrite(syncPin, LOW);
      pinMode(syncPin, OUTPUT);
    }
  }

  bool is_playing() {
    return playing;
  }
  void set_playing(bool p = false) {
    this->playing = p;
  }
  void set_tempo(int tempo) {
    master_tempo = tempo;


    _clock = 60000000L / tempo / 24;
  }
  int get_tempo() {
    return master_tempo;
  }
  void send_MIDIclock() {
    usbMIDI.sendRealTime(usbMIDI.Clock);
    MIDI.sendRealTime(midi::Clock);
  }
  void send_sync_clock() {


    if (syncPin >= 0) {
      digitalWrite(syncPin, HIGH);
      uint32_t currentMillis = millis();
      if (currentMillis - previousMillis_clock >= 10) {
        previousMillis_clock = currentMillis;
        digitalWrite(syncPin, LOW);
      }
    }
  }
  bool process_MIDItick() {

    if (playing) {

      if (msecsclock >= _clock) {
        MIDItick++;
        send_MIDIclock();
        msecsclock = 0;

        return true;
      }
    }
    return false;
  }
  uint32_t get_MIDItick() {
    return MIDItick;
  }



  uint32_t get_step_tick() {
    return MIDItick % 6;
  }
  bool is_tick_on_step() {
    return MIDItick % 6 == 0;
  }


  uint32_t get_bar_tick() {
    return MIDItick % 96;
  }
  bool is_tick_on_bar() {
    return MIDItick % 96 == 0;
  }
};

Clock master_clock;