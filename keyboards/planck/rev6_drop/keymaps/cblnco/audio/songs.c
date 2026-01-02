#include "quantum.h"

#ifdef AUDIO_ENABLE
#    include "audio/song_list.h"
#    include "audio/songs.h"

float one_up_song[][2]              = SONG(ONE_UP_SOUND);
float mario_mushroom_song[][2]      = SONG(MARIO_MUSHROOM);
float coin_song[][2]                = SONG(COIN_SOUND);
float zelda_treasure_song[][2]      = SONG(ZELDA_TREASURE);
float zelda_puzzle_song[][2]        = SONG(ZELDA_PUZZLE);
float zelda_chest_opening_song[][2] = SONG(ZELDA_CHEST_OPENING);

#endif
