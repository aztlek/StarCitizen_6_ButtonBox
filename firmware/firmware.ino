/*
 * firmware.ino
 * 
 * @author Luis Alejandro Bernal Romero (Aztlek)
 * 
 * The Button Box is made up of a series of switches, which can be 
 * used to make certain controls of the ship "more physical", thus 
 * facilitating the piloting of the ship in Star Citizen. For 
 * example, it can be used to raise and lower the landing gear, to 
 * turn the ship on and off, to lower and raise the shields and 
 * everything else you want.
 * 
 * This is the firmware of the Button Box, the software for the 
 * Arduino Pro Micro to process the actions of the switches and 
 * convert them into actions of the joystick.
 * 
 * The button box works like a joystick that has six buttons and 
 * no axis.
 */
 
/* 
 * 
 * Copyright (C) 2020 Luis Alejandro Bernal Romero (Aztlek)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

 /*
  * The Button Box is made up of a series of switches, which can be 
  * used to make certain controls of the ship "more physical", thus 
  * facilitating the piloting of the ship in Star Citizen. For 
  * example, it can be used to raise and lower the landing gear, to 
  * turn the ship on and off, to lower and raise the shields and 
  * everything else you want.
  */
 
#include <Keypad.h>
#include <Joystick.h>

const byte NUMROWS = 2;
const byte NUMCOLS = 3;
const byte MAXKEYS = NUMROWS * NUMCOLS;

byte keys[NUMROWS][NUMCOLS] = {
  {0, 1, 2},
  {3, 4, 5}
};
byte rowPins[NUMROWS] = {21, 20};
byte colPins[NUMCOLS] = {19, 18, 15};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, NUMROWS, NUMCOLS );

Joystick_ joystick( 
                    JOYSTICK_DEFAULT_REPORT_ID, 
                    
                    // "normal" joystick
                    JOYSTICK_TYPE_JOYSTICK, 
                    
                    // Six buttons
                    MAXKEYS, 
                    
                    // No hat
                    0, 
                    
                    // No axis
                    false, false, false, false, false, false, false, false, false, false, false
                  );


void setup() {
    joystick.begin();
}


void loop() {
    // Fills kpd.key[ ] array with up-to 6 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys()) {
      // Scan the whole key list.
      for (int i = 0; i < MAXKEYS; i++) {
        // Only find keys that have changed state.
        if ( kpd.key[i].stateChanged ) {
          byte code = kpd.key[i].kchar;
          // Report active key state : PRESSED or RELEASED
          switch ( kpd.key[i].kstate ) {
              case PRESSED:
                joystick.pressButton(code);
                break;
              case RELEASED:
                joystick.releaseButton(code);
                break;
          }
        }
      }
    }
}  // End loop
