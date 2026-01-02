#pragma once

#define AUDIO_DAC_SAMPLE_MAX 4095U
#define TAPPING_TERM 200

#ifdef AUDIO_ENABLE
    #include "audio/song_list.h"
    #define AUDIO_INIT_DELAY
    #define STARTUP_SONG SONG(MARIO_MUSHROOM)
    #define ADJUST_SONG SONG(ZELDA_PUZZLE)
    #define CAPSLOCK_ON_SONG SONG(MARIO_MUSHROOM)
    #define CAPSLOCK_OFF_SONG SONG(CAPS_LOCK_OFF_SOUND)
    #define WIN_SONG SONG(ONE_UP_SOUND)
    #define MAC_SONG SONG(ZELDA_TREASURE)
#endif


// enable basic MIDI features:
#define MIDI_BASIC

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4

