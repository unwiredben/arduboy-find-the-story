/*
   Copyright (C) 2020-2023 Ben Combee (@unwiredben)
   Copyright (c) 2016-2020, Scott Allen
   All rights reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <Arduboy2.h>
#include <ArduboyTones.h> 

#include "RLEDecoder.h"
#include "dragon_test.h"
#include "Util.h"

#include "press_a_bmp.h"
#include "unwired_logo_bmp.h"

/* global definitions for APIs */
Arduboy2Base arduboy;
ArduboyTones sound(arduboy.audio.enabled);

namespace FindTheStoryGame {

RLEBitmap dragonTest(dragon_test);
RLEPalette pal;

// coordinating game state
enum GameState {
  INITIAL_LOGO,
  TITLE_SCREEN,
  GAME_ACTIVE
};

GameState state = INITIAL_LOGO;

void enter_state(GameState newState) {
  arduboy.frameCount = 0;
  sound.noTone();
  state = newState;

  if (newState == INITIAL_LOGO) {
    pal.reset();
    pal.set(0, 1);
    pal.set(1, 1);
  }
  else if (newState == TITLE_SCREEN) {
    // reset game state for a new game
  } else if (newState == GAME_ACTIVE) {
    // reset UI state for a new level
  }
}

// void initial_logo() {
//   if (arduboy.frameCount == 1) {
//     arduboy.clear();
//     arduboy.drawCompressed(0, 0, unwiredgames_logo_cmpimg);
//   }
//   if (arduboy.frameCount > 90) {
//     enter_state(TITLE_SCREEN);
//   }
// }

void initial_logo() {
  arduboy.clear();

  constexpr int16_t x_max = 512 - WIDTH;
  constexpr int16_t y_max = 256 - HEIGHT;

  // pan x=0 to x=512-128
  constexpr int16_t first_x_pan = x_max;
  // pan y=0 to y=256-64
  constexpr int16_t first_y_pan = y_max + first_x_pan;
  // pan x=512-128 to x=0
  constexpr int16_t second_x_pan = x_max + first_y_pan;
  // pan y=256-64 to y=0
  constexpr int16_t second_y_pan = y_max + second_x_pan;
  // color cycle
  // constexpr int16_t color_cycle_end = second_y_pan + 256;

  int16_t x, y;
  static int8_t pass = 0;

  if (arduboy.frameCount == second_y_pan) {
    arduboy.frameCount = 0;
    pass = (pass + 1) % 3;

    pal.reset();
    if (pass == 0) {
      pal.set(0, 1);
      pal.set(1, 1);
    }
    else if (pass == 1) {
      pal.set(0, 1);
      for (uint16_t i = 0; i <= 127; ++i) {
        pal.set(i, 1);
      }
    }
    else if (pass == 2) {
      pal.set(1, 1);
      for (uint16_t i = 128; i <= 255; ++i) {
        pal.set(i, 1);
      }
    }
  }

  if (arduboy.frameCount < first_x_pan) {
    x = arduboy.frameCount;
    y = 0;
  }
  else if (arduboy.frameCount < first_y_pan) {
    x = x_max;
    y = (arduboy.frameCount - first_x_pan);
  }
  else if (arduboy.frameCount < second_x_pan) {
    x = x_max - (arduboy.frameCount - first_y_pan);
    y = y_max;
  }
  else if (arduboy.frameCount < second_y_pan) {
    x = 0;
    y = y_max - (arduboy.frameCount - second_x_pan);
  }
 
  dragonTest.decodeRLEToWindow(x, y, pal);
}

void title_screen() {
  if (arduboy.frameCount == 1) {
    arduboy.clear();
    // sprites.drawOverwrite(logo_x, logo_y, logo_bmp, 0);
  }
  if (arduboy.frameCount == 180) {
    arduboy.fillRect(24, 48, press_a_to_start_width, press_a_to_start_height,
                     BLACK);
    arduboy.drawCompressed(24, 48, press_a_to_start_cmpbmp);
  }

  if (arduboy.justPressed(A_BUTTON)) {
    enter_state(GAME_ACTIVE);
  }
}

void game_active() {
  // process input
  arduboy.clear();
  sound.noTone();
}

void setup(void) {
  arduboy.beginDoFirst();
  arduboy.setFrameRate(60);
  enter_state(INITIAL_LOGO);
}

void loop(void) {
  if (!(arduboy.nextFrameDEV()))
    return;

  arduboy.pollButtons();

  switch (state) {
  case INITIAL_LOGO:
    initial_logo();
    break;
  case TITLE_SCREEN:
    title_screen();
    break;
  case GAME_ACTIVE:
    game_active();
    break;
  }

  arduboy.display();
}

} // namespace FindTheStoryGame

void setup(void) { FindTheStoryGame::setup(); }
void loop(void) { FindTheStoryGame::loop(); }
