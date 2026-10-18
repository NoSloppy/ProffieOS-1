/*
saber_BC_4buttons.h
  http://fredrik.hubbe.net/lightsaber/proffieos.html
  Copyright (c) 2016-2019 Fredrik Hubinette
  Copyright (c) 2023-2025 Brian Conner with contributions by:
  Fredrik Hubinette, Fernando da Rosa, Matthew McGeary, and Scott Weber.
  Distributed under the terms of the GNU General Public License v3.
  http://www.gnu.org/licenses/

Derived from saber_BC_buttons.h.

Includes 4-button controls for a dual-blade staff on one Proffieboard V3.9.
This prop treats the saber as two independent 2-button control sets:
  - POW1 / AUX1 control the MAIN blade
  - POW2 / AUX2 control the SECOND blade

Proffieboard V3.9 button mapping:
  POW1 -> powerButtonPin -> BUTTON_POWER
  AUX1 -> auxPin         -> BUTTON_AUX
  POW2 -> blade5Pin      -> BC4_POW2_BUTTON
  AUX2 -> aux2Pin        -> BC4_AUX2_BUTTON

Required config:
  #define NUM_BUTTONS 4

  #ifdef CONFIG_PROP
  #include "../props/saber_BC_4buttons.h"
  #endif

  #ifdef CONFIG_BUTTONS
  Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");     // POW1 - main blade
  Button AuxButton(BUTTON_AUX, auxPin, "aux");                 // AUX1 - main blade
  Button Pow2Button(BUTTON_AUX2, blade5Pin, "pow2");           // POW2 - second blade
  Button Aux2Button(BUTTON_SELECT, aux2Pin, "aux2");           // AUX2 - second blade
  #endif

  Wire the four buttons to the pads named above on the Proffieboard V3.9.

Features:
- Independent 2-button behavior for both blades.
- Per-blade ignition / retraction / muted ignition.
- Per-blade blaster blocks, lockup, drag, lightning block, force, battle mode,
  spam blast, and power-save dim.
- Shared board-global audio, preset, menu, battery, quotes, color, and blade-array
  features.

Optional defines:

#define BC4_GLOBAL_FROM_BOTH_GROUPS  - Allow POW2/AUX2 to trigger board-global controls.
#define BC_SWING_ON                  - Swing ignition.
#define BC_TWIST_ON                  - Twist ignition.
#define BC_TWIST_OFF                 - Twist-off.
#define BC_THRUST_ON                 - Thrust ignition.
#define NO_BLADE_NO_GEST_ONOFF       - Disable gesture ignition when no blade is inserted.
#define BC_FORCE_PUSH                - Enable force push gesture.
#define BC_FORCE_PUSH_LENGTH         - Push gesture timeout, default 5.
#define BC_NO_BM                     - Disable battle mode.
#define BC_GESTURE_AUTO_BATTLE_MODE  - Gesture ignition also enters battle mode.
#define BC_ENABLE_AUTO_SWING_BLAST   - Swing after blast enters timed auto-blast mode.
#define BC_LOCKUP_DELAY              - Delay before auto lockup / melt, default 200.
#define BC_SWING_ON_SPEED            - Swing speed needed for swing ignition, default 250.
#define MOTION_TIMEOUT               - Time to keep motion active after power-off.
#define BC_BUTTON_CLICKER            - Optional button click sound when off.
#define FEMALE_TALKIE_VOICE          - Female voicepack variation.
#define MENU_SPEC_TEMPLATE           - Use OS menu system instead of BC menus.
#define DYNAMIC_BLADE_LENGTH         - Enable blade-length editing menu.

Gesture controls:
- There are three gesture types: swing, thrust and twist.
- Gesture ignition turns on both controlled blades.
- Twist-off turns off both controlled blades.
- Thrust ignition and stab use the shared IMU and the active blade group.
- For button-driven actions, the blade is determined only by the button group
  being used. There is no "pointing up means second blade" behavior.
- Orientation still applies where expected: bypass preon/postoff when pointing up,
  drag when pointing down, preset up/down/first, and similar controls.

Global controls are main-pair-only by default. They include:
- preset change and scroll presets
- volume menu and blade-length / OS menu
- spoken and on-demand battery level
- track start/stop
- quote player and sequential/random toggle
- color change and revert color
- blade ID scan and next blade array

If BC4_GLOBAL_FROM_BOTH_GROUPS is defined, those controls are also available
from POW2/AUX2.

====================== MAIN BLADE (POW1 / AUX1) ======================
| Sorted by ON or OFF state: (what it's like while using saber) |
======================================================================

-------- When blade is OFF -------
Turn Blade ON             - Short Click POW1, or use a Gesture Ignition.
Turn ON without Preon     - Short Click POW1 (while pointing UP), or use a Gesture Ignition.
Turn Blade ON Muted       - Hold POW1 then Twist, or Double Click POW1.
Scroll Presets            - Hold POW1. Rotate hilt to cycle through presets.
                            Right = Next, Left = Previous.
                            Click POW1 to ignite with chosen preset, or click
                            and hold POW1 again to exit.
Next Preset               - Long Click then release POW1 (NOT pointing UP or DOWN).
Prev Preset               - Long Click then release POW1 (while pointing DOWN).
Jump to First Preset      - Long Click then release POW1 (while pointing UP).
Play/Stop Track           - 4x Click POW1.
BC Volume Menu:
        Enter Menu        - Hold POW1 and Clash.
        Volume UP         - Rotate Right.
        Volume DOWN        - Rotate Left.
        Quick MAX Vol     - Hold POW1 while in Volume Menu.
        Quick MIN Vol     - Double Click and Hold POW1 while in Volume Menu.
        Save and Exit     - Click POW1.
        Cancel and Exit   - Double Click POW1.
BC Blade Length Edit:
        Enter Mode        - Double Click and Hold POW1.
        Adjust            - Rotate Right or Left
        Save and Exit     - Click POW1.
        Cancel and Exit   - Double Click POW1.
Spoken Battery Level
        in percentage     - 3x Click and Hold POW1.
        in volts          - 3x Click and Hold POW1 (while pointing DOWN).
On-Demand Batt Level      - 3x Click and Hold POW1, release after a second.
Quote Player              - 3x Click POW1.
Toggle Sequential or
       Random quotes      - 3x Click POW1 (while pointing DOWN).
Trigger Blade ID Scan     - 4x Click POW1 and Hold, release after one second.
Next Blade Array          - 4x Click POW1 and Hold.
User Effect 5             - Hold POW1 then Rotate Left 60 degrees.
User Effect 6             - Hold POW1 then Rotate Right 60 degrees.
Turn OFF blade            - Hold POW1 until off -or- Twist if using BC_TWIST_OFF.
Turn OFF bypass postoff   - Turn OFF (while pointing UP).

-------- When blade is ON -------
Play/Stop Track           - 4x Click POW1.
Next Preset Fast          - Hold POW1 and Twist (NOT pointing UP or DOWN).
Previous Preset Fast      - Hold POW1 and Twist (while pointing DOWN).
First Preset Fast         - Hold POW1 and Twist (while pointing UP).
Clash                     - No button, just hit the blade against something.
Blaster Deflection        - Click or Double Click POW1.
Spam Blaster Blocks       - 4x Click and Hold POW1 (while pointing DOWN).
Toggle Battle Mode        - Double Click and Hold POW1, release after a second
                            (while pointing UP).
Force Effect              - Double Click and Hold POW1, release after a second
                            (while NOT pointing UP).
Lockup                    - Hold POW1 + Clash. Release button to end.
Drag                      - Hold POW1 + Clash (while pointing DOWN). Release
                            button to end.
Lightning Block           - Hold POW1 + Click AUX1. Release button to end.
Color Change Mode         - 3x Click and Hold POW1.
Revert ColorChange        - 3x Click and Hold POW1, release after a second.
Quote Player              - 3x Click POW1.
Toggle Sequential or
       Random quotes      - 3x Click POW1 (while pointing DOWN).
Force Push                - Push hilt perpendicularly from a stop.
PowerSave Dim Blade       - Hold AUX1 then Twist (while pointing UP).
User Effect 1             - Hold POW1 then Rotate Left 60 degrees.
User Effect 2             - Hold POW1 then Rotate Right 60 degrees.
User Effect 3             - Hold AUX1 then Rotate Left 60 degrees.
User Effect 4             - Hold AUX1 then Rotate Right 60 degrees.
Turn OFF blade            - Hold POW1 until off -or- Twist if using BC_TWIST_OFF.
Turn OFF bypass postoff   - Turn OFF (while pointing UP).

---------------------------------------
      MAIN blade summary by clicks
---------------------------------------
--------- When blade is OFF ---------
1 click POW1             - turn main blade ON
                          turn main blade ON bypass preon (pointing up)
1 click POW1 long        - next preset
                          previous preset (pointing down)
                          first preset (pointing up)
1 click POW1 held        - scroll presets
    then twist          - turn main blade ON muted
    then clash          - enter BC volume menu
    then rotate left    - user effect 5
    then rotate right   - user effect 6
2 clicks POW1            - turn main blade ON muted
2 clicks held            - blade length edit, or OS system menu instead
3 clicks POW1            - quote
                          toggle sequential or random quotes (pointing down)
3 clicks long           - on-demand battery level
3 clicks held           - spoken battery level in percentage
                          spoken battery level in volts (pointing down)
4 clicks POW1            - play / stop track
4 clicks long           - manually trigger blade ID scan
4 clicks held           - manually switch to next blade array

--------- When blade is ON ---------
1 click POW1             - blaster deflection
1 click POW1 held       - turn main blade OFF
    then twist          - first preset fast
                          next preset fast
                          previous preset fast (pointing down)
    then clash          - lockup
    then rotate left    - user effect 1
    then rotate right   - user effect 2
1 click AUX1             - blaster deflection
1 click AUX1 held       - lockup
    then rotate left    - user effect 3
    then rotate right   - user effect 4
2 clicks POW1            - blaster deflection
2 clicks POW1 long       - force (not pointing up)
                          - toggle battle mode (pointing up)
2 clicks AUX1            - blaster deflection
3 clicks POW1            - quote
                          toggle sequential or random quotes (pointing down)
3 clicks POW1 long       - revert colorchange to config
3 clicks POW1 held       - color change mode
4 clicks POW1 held       - toggle spam blasts (pointing down)
hold POW1 + click AUX1   - lightning block
hold AUX1 + twist        - dim (pointing up)

====================== SECOND BLADE (POW2 / AUX2) ======================
| Sorted by ON or OFF state: (what it's like while using saber) |
=======================================================================

-------- When blade is OFF -------
Turn Blade ON             - Short Click POW2.
Turn ON without Preon     - Short Click POW2 (while pointing UP for the second blade).
Turn Blade ON Muted       - Hold POW2 then Twist, or Double Click POW2.
Scroll Presets            - Same as main pair only if BC4_GLOBAL_FROM_BOTH_GROUPS
                            is defined; otherwise ignored.
Next Preset               - Same as main pair only if BC4_GLOBAL_FROM_BOTH_GROUPS
                            is defined; otherwise ignored.
Prev Preset               - Same as main pair only if BC4_GLOBAL_FROM_BOTH_GROUPS
                            is defined; otherwise ignored.
Jump to First Preset      - Same as main pair only if BC4_GLOBAL_FROM_BOTH_GROUPS
                            is defined; otherwise ignored.
Play/Stop Track           - Same as main pair only if BC4_GLOBAL_FROM_BOTH_GROUPS
                            is defined; otherwise ignored.
BC Volume Menu            - Same as main pair only if BC4_GLOBAL_FROM_BOTH_GROUPS
                            is defined; otherwise ignored.
BC Blade Length Edit      - Same as main pair only if BC4_GLOBAL_FROM_BOTH_GROUPS
                            is defined; otherwise ignored.
Spoken Battery Level      - Same as main pair only if BC4_GLOBAL_FROM_BOTH_GROUPS
                            is defined; otherwise ignored.
On-Demand Batt Level      - Same as main pair only if BC4_GLOBAL_FROM_BOTH_GROUPS
                            is defined; otherwise ignored.
Quote Player              - Same as main pair only if BC4_GLOBAL_FROM_BOTH_GROUPS
                            is defined; otherwise ignored.
Trigger Blade ID Scan     - Same as main pair only if BC4_GLOBAL_FROM_BOTH_GROUPS
                            is defined; otherwise ignored.
Next Blade Array          - Same as main pair only if BC4_GLOBAL_FROM_BOTH_GROUPS
                            is defined; otherwise ignored.
User Effect 5             - Hold POW2 then Rotate Left 60 degrees.
User Effect 6             - Hold POW2 then Rotate Right 60 degrees.
Turn OFF blade            - Hold POW2 until off -or- Twist if using BC_TWIST_OFF.
Turn OFF bypass postoff   - Turn OFF (while pointing UP for the second blade).

-------- When blade is ON -------
Blaster Deflection        - Click or Double Click POW2.
Spam Blaster Blocks       - 4x Click and Hold POW2 (while pointing DOWN for the second blade).
Toggle Battle Mode        - Double Click and Hold POW2, release after a second
                            (while pointing UP for the second blade).
Force Effect              - Double Click and Hold POW2, release after a second
                            (while NOT pointing UP).
Lockup                    - Hold POW2 + Clash. Release button to end.
Drag                      - Hold POW2 + Clash (while pointing DOWN for the second blade).
Lightning Block           - Hold POW2 + Click AUX2. Release button to end.
Color Change Mode         - 3x Click and Hold POW2.
Revert ColorChange        - 3x Click and Hold POW2, release after a second.
Quote Player              - 3x Click POW2.
Toggle Sequential or
       Random quotes      - 3x Click POW2 (while pointing DOWN).
Force Push                - Push hilt perpendicularly from a stop.
PowerSave Dim Blade       - Hold AUX2 then Twist (while pointing UP for the second blade).
User Effect 1             - Hold POW2 then Rotate Left 60 degrees.
User Effect 2             - Hold POW2 then Rotate Right 60 degrees.
User Effect 3             - Hold AUX2 then Rotate Left 60 degrees.
User Effect 4             - Hold AUX2 then Rotate Right 60 degrees.
Turn OFF blade            - Hold POW2 until off -or- Twist if using BC_TWIST_OFF.
Turn OFF bypass postoff   - Turn OFF (while pointing UP for the second blade).

---------------------------------------
     SECOND blade summary by clicks
---------------------------------------
--------- When blade is OFF ---------
1 click POW2             - turn second blade ON
1 click POW2 long        - preset actions only if global controls are enabled
1 click POW2 held        - scroll presets only if global controls are enabled
2 clicks POW2            - turn second blade ON muted
3 clicks POW2            - quote only if global controls are enabled
4 clicks POW2 long       - none
4 clicks POW2 held       - none
hold POW2 then twist     - turn second blade ON muted
hold POW2 then clash     - enter lockup / drag
hold POW2 then click AUX2 - lightning block

--------- When blade is ON ---------
1 click POW2             - blaster deflection
1 click POW2 held       - turn second blade OFF
    then twist          - first preset fast / next preset fast / previous preset fast
    then clash          - lockup
    then rotate left    - user effect 1
    then rotate right   - user effect 2
1 click AUX2             - blaster deflection
1 click AUX2 held       - lockup
    then rotate left    - user effect 3
    then rotate right   - user effect 4
2 clicks POW2            - blaster deflection
2 clicks POW2 long       - force (not pointing up)
                          - toggle battle mode (pointing up)
3 clicks POW2            - quote only if global controls are enabled
3 clicks POW2 long       - revert colorchange only if global controls are enabled
3 clicks POW2 held       - color change only if global controls are enabled
4 clicks POW2 held       - spam blast
hold POW2 + click AUX2   - lightning block
hold AUX2 + twist        - dim (pointing up)
*/


#ifndef PROPS_SABER_BC_4BUTTONS_H
#define PROPS_SABER_BC_4BUTTONS_H

#ifndef NUM_BUTTONS
#error "saber_BC_4buttons.h requires NUM_BUTTONS to be defined as 4"
#elif NUM_BUTTONS != 4
#error "saber_BC_4buttons.h requires NUM_BUTTONS == 4"
#endif

#ifndef BC_DUAL_BLADES
#define BC_DUAL_BLADES
#endif

#ifndef BC4_POW2_BUTTON
#define BC4_POW2_BUTTON BUTTON_AUX2
#endif
#ifndef BC4_AUX2_BUTTON
#define BC4_AUX2_BUTTON BUTTON_SELECT
#endif

#ifdef PROP_TYPE
#undef PROP_TYPE
#endif
#define PROP_TYPE SaberBC4Buttons

#if defined(BC_NO_BM) && defined(BC_GESTURE_AUTO_BATTLE_MODE)
#error "BC_NO_BM and BC_GESTURE_AUTO_BATTLE_MODE cannot be enabled together"
#endif

#include "prop_base.h"
#include "../sound/hybrid_font.h"
#include "../sound/sound_library.h"
#include "../modes/select_cancel_mode.h"
#include "../modes/settings_menues.h"

#ifndef BC_MAIN_BLADE
#define BC_MAIN_BLADE 1
#endif
#ifndef BC_SECOND_BLADE
#define BC_SECOND_BLADE 2
#endif
#ifndef BC_SWING_ON_SPEED
#define BC_SWING_ON_SPEED 250
#endif
#ifndef BC_LOCKUP_DELAY
#define BC_LOCKUP_DELAY 200
#endif
#ifndef BC_FORCE_PUSH_LENGTH
#define BC_FORCE_PUSH_LENGTH 5
#endif
#ifndef MOTION_TIMEOUT
#define MOTION_TIMEOUT (60 * 15 * 1000)
#endif
#ifndef BUTTON_DOUBLE_CLICK_TIMEOUT
#define BUTTON_DOUBLE_CLICK_TIMEOUT 300
#endif
#ifndef BUTTON_SHORT_CLICK_TIMEOUT
#define BUTTON_SHORT_CLICK_TIMEOUT 300
#endif
#ifndef BUTTON_HELD_TIMEOUT
#define BUTTON_HELD_TIMEOUT 300
#endif
#ifndef BUTTON_HELD_MEDIUM_TIMEOUT
#define BUTTON_HELD_MEDIUM_TIMEOUT 800
#endif
#ifndef BUTTON_HELD_LONG_TIMEOUT
#define BUTTON_HELD_LONG_TIMEOUT 2000
#endif

static_assert(BC4_POW2_BUTTON != BUTTON_POWER &&
              BC4_POW2_BUTTON != BUTTON_AUX &&
              BC4_POW2_BUTTON != BC4_AUX2_BUTTON,
              "BC4_POW2_BUTTON must be a unique button ID");
static_assert(BC4_AUX2_BUTTON != BUTTON_POWER &&
              BC4_AUX2_BUTTON != BUTTON_AUX &&
              BC4_AUX2_BUTTON != BUTTON_BLADE_DETECT &&
              BC4_POW2_BUTTON != BUTTON_BLADE_DETECT,
              "BC4_AUX2_BUTTON must be a unique button ID");
static_assert((BC4_POW2_BUTTON & (BC4_POW2_BUTTON - 1)) == 0 &&
              (BC4_AUX2_BUTTON & (BC4_AUX2_BUTTON - 1)) == 0,
              "BC4 button IDs must each use one modifier bit");
static_assert(BC_MAIN_BLADE != BC_SECOND_BLADE,
              "BC_MAIN_BLADE and BC_SECOND_BLADE must be different");

EFFECT(dim);        // for EFFECT_POWERSAVE
EFFECT(battery);    // for EFFECT_BATTERY_LEVEL
EFFECT(bmbegin);    // for Begin Battle Mode
EFFECT(bmend);      // for End Battle Mode
EFFECT(push);       // for Force Push gesture
EFFECT(tr);         // for EFFECT_TRANSITION_SOUND, use with User Effects.
EFFECT(mute);       // Notification before muted ignition to avoid confusion.
EFFECT(array);      // for Manual Blade Array switching
#ifdef BC_BUTTON_CLICKER
EFFECT(press);      // for button press clicks when OFF only.
#endif

template<class SPEC>
struct BC4ScrollPresetsMode : public SPEC::SteppedMode {
  void next() override { beeper.Beep(0.05, 4000); prop_next_preset(); }
  void prev() override { beeper.Beep(0.05, 3000); prop_previous_preset(); }
  void update() override {
#ifdef ENABLE_IDLE_SOUND
    SFX_font.SetFollowing(nullptr);
#endif
  }
  void exit() override {
    PVLOG_NORMAL << "** Exit Scroll Presets\n";
    beeper.Beep(0.05, 3000);
    beeper.Silence(0.05);
    beeper.Beep(0.05, 3000);
    beeper.Silence(0.05);
    beeper.Beep(0.10, 2000);
    SPEC::SteppedMode::exit();
  }
  bool mode_Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
    switch (EVENTID(button, event, 0)) {
      case EVENTID(BUTTON_POWER, EVENT_FIRST_SAVED_CLICK_SHORT, 0):
        SaberBase::TurnOn();
        exit();
        return true;
      case EVENTID(BUTTON_POWER, EVENT_FIRST_HELD_MEDIUM, 0):
        exit();
        return true;
    }
    return false;
  }

};

template<class SPEC>
struct BC4VolumeMode : public SPEC::SteppedMode {
  const int max_volume_ = VOLUME;
  const int min_volume_ = VOLUME * 0.10;
  float initial_volume_ = 0;
  int initial_percentage_ = 0;
  int percentage_ = 0;

  void mode_activate(bool onreturn) override {
    initial_volume_ = dynamic_mixer.get_volume();
    initial_percentage_ = round(initial_volume_ / max_volume_ * 10) * 10;
    percentage_ = initial_percentage_;
    SaberBase::DoEffect(EFFECT_VOLUME_LEVEL, 0);
    mode::getSL<SPEC>()->SayEditVolume();
    announce_volume();
    SPEC::SteppedMode::mode_activate(onreturn);
  }
  void announce_volume() {
    if (percentage_ <= 10) {
      mode::getSL<SPEC>()->SayMinimumVolume();
    } else if (percentage_ >= 100) {
      mode::getSL<SPEC>()->SayMaximumVolume();
    } else {
      mode::getSL<SPEC>()->SayWhole(percentage_);
      mode::getSL<SPEC>()->SayPercent();
    }
  }
  void mode_deactivate() override {
    announce_volume();
    mode::getSL<SPEC>()->SayVolumeMenuEnd();
    SPEC::SteppedMode::mode_deactivate();
    if (percentage_ <= 10) PVLOG_NORMAL << "** Minimum Volume\n";
    else if (percentage_ >= 100) PVLOG_NORMAL << "** Maximum Volume\n";
    else PVLOG_NORMAL << "** Final Volume " << percentage_ << "%\n";
  }
  void next() override {
    int volume = dynamic_mixer.get_volume() + max_volume_ * 0.10;
    if (volume >= max_volume_) {
      QuickMaxVolume();
    }
    else {
      dynamic_mixer.set_volume(volume);
      sound_library_.fadeout(0.2);
      mode::getSL<SPEC>()->SayVolumeUp();
    }
  }
  void prev() override {
    int volume = dynamic_mixer.get_volume() - max_volume_ * 0.10;
    if (volume <= min_volume_) {
      QuickMinVolume();
    }
    else {
      dynamic_mixer.set_volume(volume);
      sound_library_.fadeout(0.2);
      mode::getSL<SPEC>()->SayVolumeDown();
    }
  }
  void QuickMaxVolume() {
    dynamic_mixer.set_volume(max_volume_);
    PVLOG_NORMAL << "** Maximum Volume\n";
    mode::getSL<SPEC>()->SayMaximumVolume();
  }
  void QuickMinVolume() {
    dynamic_mixer.set_volume(min_volume_);
    PVLOG_NORMAL << "** Minimum Volume\n";
    mode::getSL<SPEC>()->SayMinimumVolume();
  }
  void update() override {
    percentage_ = round(dynamic_mixer.get_volume() / (float)max_volume_ * 10) * 10;
    PVLOG_NORMAL << "** Volume " << percentage_ << "%\n";
    SaberBase::DoEffect(EFFECT_VOLUME_LEVEL, 0);
  }
  void select() override {
    PVLOG_NORMAL << "** Saved - Exit Volume Menu\n";
    mode::getSL<SPEC>()->SaySave();
    SPEC::SteppedMode::select();
  }
  void exit() override {
    PVLOG_NORMAL << "** Cancelled - Exit Volume Menu\n";
    percentage_ = initial_percentage_;
    dynamic_mixer.set_volume(initial_volume_);
    mode::getSL<SPEC>()->SayCancel();
    SPEC::SteppedMode::exit();
  }
  bool mode_Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
    switch (EVENTID(button, event, 0)) {
      case EVENTID(BUTTON_POWER, EVENT_FIRST_HELD_MEDIUM, 0):
        QuickMaxVolume();
        return true;
      case EVENTID(BUTTON_POWER, EVENT_SECOND_HELD_MEDIUM, 0):
      case EVENTID(BUTTON_AUX, EVENT_FIRST_HELD_MEDIUM, 0):
        QuickMinVolume();
        return true;
    }
    return SPEC::SelectCancelMode::mode_Event2(button, event, modifiers);
  }
};

#ifdef DYNAMIC_BLADE_LENGTH
template<class SPEC>
struct BC4SelectBladeMode : public SPEC::MenuBase {
  int current_blade() { return this->pos_ + 1; }
  ShowColorSingleBladeTemplate<Pulsing<White,Black,800>,Pulsing<White,Black,800>> highlighted_blade_;
  uint16_t size() override { return NUM_BLADES; }
  void mode_activate(bool onreturn) override {
    mode::getSL<SPEC>()->SaySelectBlade();
    SPEC::SteppedMode::mode_activate(onreturn);
    highlighted_blade_.Start(current_blade());
    PVLOG_NORMAL << "** Highlighting blade to edit: " << current_blade() << "\n";
  }
  void mode_deactivate() override { prop_UpdateStyle(); }
  void next() override {
    highlighted_blade_.Stop(current_blade());
    SPEC::MenuBase::next();
    highlighted_blade_.Start(current_blade());
    PVLOG_NORMAL << "** Highlighting blade to edit: " << current_blade() << "\n";
  }
  void prev() override {
    highlighted_blade_.Stop(current_blade());
    SPEC::MenuBase::prev();
    highlighted_blade_.Start(current_blade());
    PVLOG_NORMAL << "** Highlighting blade to edit: " << current_blade() << "\n";
  }
  void say() override {
    mode::getSL<SPEC>()->SayBlade();
    mode::getSL<SPEC>()->SayWhole(current_blade());
  }
  void select() override {
    PVLOG_NORMAL << "** Editing blade length.\n";
    mode::menu_current_blade = current_blade();
    highlighted_blade_.Stop(current_blade());
    popMode();
    pushMode<typename SPEC::ChangeBladeLengthMode>();
  }
};

template<class SPEC>
struct BC4ChangeBladeLengthBlade1 : public mode::ChangeBladeLengthBlade1<SPEC> {
  int steps_per_revolution() override { return 30; }
  void select() override {
    PVLOG_NORMAL << "** Saved blade length : " << this->getLength() << "\n";
    prop_SetBladeLength(this->blade(), this->getLength());
    prop_SaveState();
    mode::getSL<SPEC>()->SaySave();
    popMode();
  }
  void update() override {
    hybrid_font.PlayPolyphonic(&SFX_mclick);
    this->say_time_ = Cyclint<uint32_t>(millis()) +
        static_cast<uint32_t>(SaberBase::sound_length * 1000) + 300;
    if (!this->say_time_) this->say_time_++;
    this->fadeout(SaberBase::sound_length);
  }
};
#endif

template<class SPEC>
struct BC4MenuSpec {
  typedef BC4VolumeMode<SPEC> BCVolumeMenu;
  typedef BC4ScrollPresetsMode<SPEC> BCScrollPresetsMenu;
#ifdef DYNAMIC_BLADE_LENGTH
  typedef BC4SelectBladeMode<SPEC> BCSelectBladeMenu;
  typedef mode::ShowLengthStyle<SPEC> ShowLengthStyle;
  typedef BC4ChangeBladeLengthBlade1<SPEC> ChangeBladeLengthMode;
#endif
  typedef mode::SelectCancelMode SelectCancelMode;
  typedef mode::SteppedMode<SPEC> SteppedMode;
  typedef mode::SteppedModeBase<SPEC> SteppedModeBase;
  typedef mode::MenuBase<SPEC> MenuBase;
  typedef SoundLibraryV2 SoundLibrary;
};

class BC4DelayTimer {
public:
  BC4DelayTimer() : triggered_(false), trigger_time_(0), duration_(0) {}
  void trigger(uint32_t duration) {
    triggered_ = true;
    trigger_time_ = millis();
    duration_ = duration;
  }
  bool isTimerExpired() {
    if (!triggered_ || millis() - trigger_time_ <= duration_) return false;
    triggered_ = false;
    return true;
  }
private:
  bool triggered_;
  uint32_t trigger_time_;
  uint32_t duration_;
};

class SaberBC4Buttons : public PROP_INHERIT_PREFIX PropBase {
public:
  static constexpr BladeSet BC_MAIN_BLADE_SET = BladeSet::fromBlade(BC_MAIN_BLADE);
  static constexpr BladeSet BC_SECOND_BLADE_SET = BladeSet::fromBlade(BC_SECOND_BLADE);
  static const BladeSet controlled_blades_;

  SaberBC4Buttons() : PropBase() {}
  const char* name() override { return "SaberBC4Buttons"; }

#ifndef MENU_SPEC_TEMPLATE
  void Setup() override { MKSPEC<BC4MenuSpec>::SoundLibrary::init(); }
#endif

  void EnterVolumeMenu() {
    if (!current_style() || current_mode != this) return;
#ifdef MENU_SPEC_TEMPLATE
    sound_library_.SayEditVolume();
    pushMode<MKSPEC<MENU_SPEC_TEMPLATE>::ChangeVolumeMode>();
#else
    pushMode<MKSPEC<BC4MenuSpec>::BCVolumeMenu>();
#endif
  }

  void EnterScrollPresets() {
    if (current_mode != this) return;
    PVLOG_NORMAL << "** Enter Scroll Presets\n";
    BeepEnterFeature();
#ifdef ENABLE_IDLE_SOUND
    hybrid_font.StopIdleSound();
    SFX_font.SetFollowing(nullptr);
#endif
    scroll_presets_beep_delay_timer_.trigger(350);
    pushMode<MKSPEC<BC4MenuSpec>::BCScrollPresetsMenu>();
  }

  void EnterBladeLengthMode() {
#if defined(DYNAMIC_BLADE_LENGTH) && !defined(MENU_SPEC_TEMPLATE)
    if (!current_style() || current_mode != this) return;
    sound_library_.SayEditBladeLength();
#if NUM_BLADES > 1
    pushMode<MKSPEC<BC4MenuSpec>::BCSelectBladeMenu>();
#else
    pushMode<MKSPEC<BC4MenuSpec>::ChangeBladeLengthMode>();
#endif
#endif
  }

  void Loop() override {
    PropBase::Loop();
    DetectTwist();
    sound_library_.Poll(wav_player);
    if (wav_player && !wav_player->isPlaying()) wav_player.Free();

    if (SaberBase::IsOn()) {
      DetectSwing();
      for (int i = 0; i < 2; ++i) {
        if ((state_[i].auto_lockup || state_[i].auto_melt) &&
            !swinging_ && fusor.swing_speed() > (state_[i].auto_lockup ? 120 : 60) &&
            millis() - clash_impact_millis_ > BC_LOCKUP_DELAY &&
            SaberBase::Lockup()) {
          SaberBase::DoEndLockup();
          SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
          state_[i].auto_lockup = false;
          state_[i].auto_melt = false;
        }
      }
      Vec3 mss = fusor.mss();
      if (fabs(mss.x) < 3.0 && mss.y * mss.y + mss.z * mss.z > 70 &&
          fusor.swing_speed() < 30 && fabs(fusor.gyro().x) < 10) {
        if (millis() - push_begin_millis_ > BC_FORCE_PUSH_LENGTH) {
          Event(BUTTON_NONE, EVENT_PUSH);
          push_begin_millis_ = millis();
        }
      } else {
        push_begin_millis_ = millis();
      }
    } else if (millis() - saber_off_time_ < MOTION_TIMEOUT) {
      SaberBase::RequestMotion();
      if (swinging_ && fusor.swing_speed() < 90) swinging_ = false;
      if (!swinging_ && fusor.swing_speed() > BC_SWING_ON_SPEED) {
        swinging_ = true;
        Event(BUTTON_NONE, EVENT_SWING);
      }
    }

    Vec3 mss = fusor.mss();
    if (mss.y * mss.y + mss.z * mss.z < 20.0 && fabs(mss.x) > 14 &&
        fusor.swing_speed() < 150) {
      if (millis() - thrust_begin_millis_ > 15) {
        Event(BUTTON_NONE, EVENT_THRUST);
        thrust_begin_millis_ = millis();
      }
    } else {
      thrust_begin_millis_ = millis();
    }

    if (mute_main_delay_timer_.isTimerExpired()) FinishMutedIgnition(0);
    if (mute_second_delay_timer_.isTimerExpired()) FinishMutedIgnition(1);
    if (scroll_presets_beep_delay_timer_.isTimerExpired())
      SaberBase::DoEffect(EFFECT_NEWFONT, 0);
  }

  void DetectTwist() {
    if (DetectTwistStrokes() && ProcessTwistEvents()) {
      strokes[NELEM(strokes)-1].type = UNKNOWN_GESTURE;
      strokes[NELEM(strokes)-2].type = UNKNOWN_GESTURE;
      return;
    }
    DoSavedTwist();
  }

  void DoSavedTwist() {
    Stroke* stroke = &strokes[NELEM(strokes)-1];
    if ((stroke->type != TWIST_LEFT && stroke->type != TWIST_RIGHT) ||
        stroke->end_millis == 0 || stroke->length() < 100 ||
        millis() - stroke->end_millis < 300) return;
    Event(BUTTON_NONE, stroke->type == TWIST_LEFT ? EVENT_TWIST_LEFT : EVENT_TWIST_RIGHT);
    stroke->type = UNKNOWN_GESTURE;
  }

  void BeepEnterFeature() {
    beeper.Beep(0.05, 2000); beeper.Silence(0.05);
    beeper.Beep(0.05, 2000); beeper.Silence(0.05);
    beeper.Beep(0.10, 3000);
  }
  void BeepExitFeature() {
    beeper.Beep(0.05, 3000); beeper.Silence(0.05);
    beeper.Beep(0.05, 3000); beeper.Silence(0.05);
    beeper.Beep(0.10, 2000);
  }

  bool isPointingUp(bool second) {
    return second ? fusor.angle1() < -M_PI / 3 : fusor.angle1() > M_PI / 3;
  }
  bool isPointingDown(bool second) {
    return second ? fusor.angle1() > M_PI / 3 : fusor.angle1() < -M_PI / 3;
  }
  bool BladeIsOn(int blade) {
    return SaberBase::OnBlades()[blade ? BC_SECOND_BLADE : BC_MAIN_BLADE];
  }
  BladeSet BladeSetFor(int blade) {
    return blade ? BC_SECOND_BLADE_SET : BC_MAIN_BLADE_SET;
  }
  BladeSet GetBladeAboveHorizon() {
    return fusor.angle1() > 0 ? BC_MAIN_BLADE_SET : BC_SECOND_BLADE_SET;
  }
  int ButtonGroup(enum BUTTON button, uint32_t modifiers, EVENT event) {
    if (button == BC4_POW2_BUTTON || button == BC4_AUX2_BUTTON) return 1;
    if (button == BUTTON_POWER || button == BUTTON_AUX) return 0;
    if (modifiers & (BC4_POW2_BUTTON | BC4_AUX2_BUTTON)) return 1;
    if (modifiers & (BUTTON_POWER | BUTTON_AUX)) return 0;
    if (button == BUTTON_NONE && (event == EVENT_CLASH || event == EVENT_STAB ||
                                  event == EVENT_THRUST))
      return fusor.angle1() <= 0;
    return 0;
  }
  enum BUTTON VirtualButton(enum BUTTON button, int blade) {
    if (!blade) return button;
    if (button == BC4_POW2_BUTTON) return BUTTON_POWER;
    if (button == BC4_AUX2_BUTTON) return BUTTON_AUX;
    return button;
  }
  uint32_t VirtualModifiers(uint32_t modifiers, int blade) {
    uint32_t second_buttons = BC4_POW2_BUTTON | BC4_AUX2_BUTTON;
    uint32_t result = modifiers & ~(BUTTON_POWER | BUTTON_AUX | second_buttons);
    if (blade) {
      if (modifiers & BC4_POW2_BUTTON) result |= BUTTON_POWER;
      if (modifiers & BC4_AUX2_BUTTON) result |= BUTTON_AUX;
    } else {
      if (modifiers & BUTTON_POWER) result |= BUTTON_POWER;
      if (modifiers & BUTTON_AUX) result |= BUTTON_AUX;
    }
    return result;
  }
  bool GlobalAllowed(int blade) {
#ifdef BC4_GLOBAL_FROM_BOTH_GROUPS
    return true;
#else
    return blade == 0;
#endif
  }

  void TurnBladeOn(BladeSet target_blade) {
    target_blade = target_blade | ~controlled_blades_;
    bool muted = state_[target_blade[BC_SECOND_BLADE] ? 1 : 0].muted;
    int index = target_blade[BC_SECOND_BLADE] ? 1 : 0;
    if (SaberBase::OnBlades().off()) {
      if (isPointingUp(index) || muted)
        FastOn(EffectLocation(0, target_blade));
      else
        On(EffectLocation(0, target_blade));
    } else {
      SaberBase::TurnOn(EffectLocation(0, target_blade));
    }
  }

  void TurnBladeOff(BladeSet target_blade) {
    int blade = target_blade[BC_SECOND_BLADE] ? 1 : 0;
    SaberBase::OffType off_type = isPointingUp(blade) ?
        SaberBase::OFF_FAST : SaberBase::OFF_NORMAL;
    if ((SaberBase::OnBlades() & ~target_blade).off()) {
      Off(off_type, EffectLocation(0, target_blade));
    } else {
      SaberBase::TurnOff(off_type, EffectLocation(0, target_blade));
    }
    ResetBladeState(blade);
    saber_off_time_ = millis();
    if (SaberBase::OnBlades().off()) {
      ResetBladeState(0);
      ResetBladeState(1);
      if (unmute_on_deactivation_) {
        SetMute(false);
        unmute_on_deactivation_ = false;
      }
    }
  }

  void ResetBladeState(int blade) {
    state_[blade].battle_mode = false;
    state_[blade].spam_blast = false;
    state_[blade].muted = false;
    state_[blade].auto_lockup = false;
    state_[blade].auto_melt = false;
  }

  void StartMutedIgnition(int blade) {
    if (hybrid_font.PlayPolyphonic(&SFX_mute))
      (blade ? mute_second_delay_timer_ : mute_main_delay_timer_)
          .trigger(SaberBase::sound_length * 1000);
    else
      (blade ? mute_second_delay_timer_ : mute_main_delay_timer_).trigger(0);
  }
  void FinishMutedIgnition(int blade) {
    SetMute(true);
    unmute_on_deactivation_ = true;
    state_[blade].muted = true;
    TurnBladeOn(BladeSetFor(blade));
    PVLOG_NORMAL << (blade ? "** Second Blade" : "** Main Blade")
                 << " Turned ON Muted\n";
  }

  void DoBlasterBlock(BladeSet blades) {
    if (!BladeIsOn(active_blade_) || state_[active_blade_].spam_blast || on_pending_) return;
    SaberBase::DoEffect(EFFECT_BLAST, EffectLocation(0, blades));
    last_blast_millis_ = millis();
  }
  void DoLightningBlock(BladeSet blades) {
    if (!BladeIsOn(active_blade_) || state_[active_blade_].spam_blast || on_pending_) return;
    SaberBase::SetLockup(SaberBase::LOCKUP_LIGHTNING_BLOCK, blades);
    lockup_owner_ = active_blade_;
    SaberBase::DoBeginLockup();
  }
  bool DoLockup(BladeSet blades, int blade) {
    if (SaberBase::Lockup() || !BladeIsOn(blade)) return false;
    if (isPointingDown(blade)) {
      SaberBase::SetLockup(SaberBase::LOCKUP_DRAG, blades);
    } else if (!state_[blade].battle_mode) {
      SaberBase::SetLockup(SaberBase::LOCKUP_NORMAL, blades);
    } else {
      return false;
    }
    lockup_owner_ = blade;
    SaberBase::DoBeginLockup();
    return true;
  }
  void EndLockup(int blade) {
    if (SaberBase::Lockup() && lockup_owner_ == blade) {
      SaberBase::DoEndLockup();
      SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
    }
  }

  void DoForce(BladeSet blades) {
    if (!BladeIsOn(active_blade_) || state_[active_blade_].spam_blast || on_pending_) return;
    if (GetWavPlayerPlaying(&SFX_force)) return;
    SaberBase::DoEffect(EFFECT_FORCE, EffectLocation(0, blades));
  }
  void ToggleBattleMode(int blade) {
#ifndef BC_NO_BM
    state_[blade].battle_mode = !state_[blade].battle_mode;
    PVLOG_NORMAL << (state_[blade].battle_mode ? "** Entering" : "** Exiting")
                 << " Battle Mode\n";
    if (state_[blade].battle_mode) {
      if (!hybrid_font.PlayPolyphonic(&SFX_bmbegin))
        hybrid_font.PlayPolyphonic(&SFX_force);
    } else if (!hybrid_font.PlayPolyphonic(&SFX_bmend)) {
      beeper.Beep(0.5, 3000);
    }
#endif
  }
  void ToggleSpamBlast(int blade) {
    if (!BladeIsOn(blade)) return;
    state_[blade].spam_blast = !state_[blade].spam_blast;
    PVLOG_NORMAL << (state_[blade].spam_blast ? "** Entering" : "** Exiting")
                 << " Spam Blast Mode\n";
    sound_library_.SayZoomingIn();
  }
  void DoSpamBlast(int blade) {
    if (!BladeIsOn(blade) || !state_[blade].spam_blast) return;
    SaberBase::DoEffect(EFFECT_BLAST, EffectLocation(0, BladeSetFor(blade)));
    last_blast_millis_ = millis();
  }
  void ToggleColorChangeMode() {
#ifndef DISABLE_COLOR_CHANGE
    if (!state_[active_blade_].spam_blast) PropBase::ToggleColorChangeMode();
#endif
  }

  void DoChangePreset(bool fast) {
    if (fusor.angle1() > M_PI / 3) {
      fast ? first_preset_fast() : first_preset();
    } else if (fusor.angle1() < -M_PI / 3) {
      fast ? previous_preset_fast() : previous_preset();
    } else {
      fast ? next_preset_fast() : next_preset();
    }
    if (fast && (state_[0].muted || state_[1].muted)) {
      unmute_on_deactivation_ = true;
      SetMute(true);
    }
  }
  void DoTrackStartOrStop() {
    if (state_[active_blade_].spam_blast) return;
    PVLOG_NORMAL << "** Track playback Toggled\n";
    StartOrStopTrack();
  }
  void DoQuote() {
    if (state_[active_blade_].spam_blast) return;
    if (SFX_quote) {
      if (GetWavPlayerPlaying(&SFX_quote)) return;
      sequential_quote_ ? SFX_quote.SelectNext() : SFX_quote.Select(-1);
      SaberBase::DoEffect(EFFECT_QUOTE, 0);
    } else if (!GetWavPlayerPlaying(&SFX_force)) {
      SaberBase::DoForce();
    }
  }
  void ToggleSequentialQuote() {
    sequential_quote_ = !sequential_quote_;
    PVLOG_NORMAL << (sequential_quote_ ? "** Quotes play sequentially\n" :
                                         "** Quotes play randomly\n");
    if (SFX_mnum)
      sequential_quote_ ? sound_library_v2.SaySequential() : sound_library_.SayRandom();
    else
      beeper.Beep(0.5, sequential_quote_ ? 3000 : 1000);
  }
  void DoSpokenBatteryLevel() {
    if (battery_monitor.battery() < 0.5) {
      sound_library_.SayTheBatteryLevelIs();
      sound_library_.SayDisabled();
      return;
    }
    sound_library_.SayTheBatteryLevelIs();
    if (fusor.angle1() < -M_PI / 4) {
      sound_library_.SayNumber(battery_monitor.battery(), SAY_DECIMAL);
      sound_library_.SayVolts();
    } else {
      sound_library_.SayNumber(battery_monitor.battery_percent(), SAY_WHOLE);
      sound_library_.SayPercent();
    }
    is_speaking_ = true;
    SaberBase::DoEffect(EFFECT_BATTERY_LEVEL, 0);
  }
  void OnDemandBatteryLevel() {
    SaberBase::DoEffect(EFFECT_BATTERY_LEVEL, 0);
  }

  void DoUserEffect(int blade, bool aux, bool right) {
    EffectType effect;
    if (BladeIsOn(blade))
      effect = aux ? (right ? EFFECT_USER3 : EFFECT_USER4) :
                     (right ? EFFECT_USER1 : EFFECT_USER2);
    else
      effect = aux ? (right ? EFFECT_USER7 : EFFECT_USER8) :
                     (right ? EFFECT_USER5 : EFFECT_USER6);
    SaberBase::DoEffect(effect, EffectLocation(0, BladeSetFor(blade)));
  }

  EffectLocation GetThrustBladeLocation() {
    Vec3 mss = fusor.mss();
    if (mss.x > 14) thrusting_blade_ = BC_SECOND_BLADE_SET;
    else if (mss.x < -14) thrusting_blade_ = BC_MAIN_BLADE_SET;
    return EffectLocation(0, thrusting_blade_);
  }

  void DoAccel(const Vec3& accel, bool clear) override {
    fusor.DoAccel(accel, clear);
    accel_loop_counter_.Update();
    Vec3 diff = fusor.clash_mss();
    float value;
    if (clear) {
      accel_ = accel;
      diff = Vec3(0, 0, 0);
      value = 0;
    } else {
#ifndef PROFFIEOS_DONT_USE_GYRO_FOR_CLASH
      value = (diff.len() + fusor.gyro_clash_value()) / 2.0;
#else
      value = diff.len();
#endif
    }
    if (value > CLASH_THRESHOLD_G * (1 + fusor.gyro().len() / 500.0
#if defined(ENABLE_AUDIO) && defined(AUDIO_CLASH_SUPPRESSION_LEVEL)
        + dynamic_mixer.audio_volume() * (AUDIO_CLASH_SUPPRESSION_LEVEL * 1E-10) *
          dynamic_mixer.get_volume()
#endif
        )) {
      if ((accel_ - fusor.down()).len2() > (accel - fusor.down()).len2()) diff = -diff;
      bool stab = fabs(diff.x) > 2.0 * sqrtf(diff.y * diff.y + diff.z * diff.z) &&
                  fusor.swing_speed() < 150;
      if (!clash_pending1_) {
        forward_stab_ = stab && diff.x < 0;
        clash_pending1_ = true;
        pending_clash_is_stab1_ = stab;
        pending_clash_strength1_ = value;
      } else {
        pending_clash_strength1_ =
            std::max<float>(value, static_cast<float>(pending_clash_strength1_));
      }
    }
    accel_ = accel;
  }

  bool use_fake_id_ = false;
  float fake_id_ = 0;
  size_t best_config_before_faking_ = SIZE_MAX;
#ifdef BLADE_ID_SCAN_MILLIS
  float id(bool announce = false) override {
    if (use_fake_id_) {
      float real_id = PropBase::id(announce);
      if (FindBestConfigForId(real_id) != best_config_before_faking_) {
        use_fake_id_ = false;
        find_blade_again_pending_ = true;
        return real_id;
      }
      return fake_id_;
    }
    return PropBase::id(announce);
  }
  int GetNoBladeLevelBefore() override {
    int ohm = best_config_before_faking_ != SIZE_MAX ?
        blades[best_config_before_faking_].ohm : current_config->ohm;
    best_config_before_faking_ = SIZE_MAX;
    return ohm / NO_BLADE;
  }
#else
  float id(bool announce = false) override {
    return use_fake_id_ ? fake_id_ : PropBase::id(announce);
  }
#endif
  void TriggerBladeID() {
    use_fake_id_ = false;
    best_config_before_faking_ = SIZE_MAX;
    FindBladeAgain();
    PlayArraySound();
  }
  void NextBladeArray() {
    if (!use_fake_id_) best_config_before_faking_ = current_config - blades;
    size_t next = (current_config - blades + 1) % NELEM(blades);
    fake_id_ = blades[next].ohm;
    use_fake_id_ = true;
    FindBladeAgain();
    PlayArraySound();
  }
  void PlayArraySound() {
    if (SFX_array) {
      SFX_array.Select(current_config - blades);
      hybrid_font.PlayPolyphonic(&SFX_array);
    } else if (!hybrid_font.PlayPolyphonic(&SFX_bladein)) {
      hybrid_font.PlayCommon(&SFX_font);
    }
  }

#ifdef SPEAK_BLADE_ID
  void SpeakBladeID(float id) override {
    sound_library_v2.SayBlade();
    sound_library_.SayNumber(id, SAY_WHOLE);
  }
#endif

  bool Parse(const char* cmd, const char* arg) override {
    if (PropBase::Parse(cmd, arg)) return true;
    if (!strcmp(cmd, "twist")) {
      Event(BUTTON_NONE, EVENT_TWIST);
      return true;
    }
    if (!strcmp(cmd, "left")) {
      Event(BUTTON_NONE, EVENT_TWIST_LEFT);
      return true;
    }
    if (!strcmp(cmd, "right")) {
      Event(BUTTON_NONE, EVENT_TWIST_RIGHT);
      return true;
    }
    return false;
  }

  RefPtr<BufferedWavPlayer> wav_player;

#ifdef BC_BUTTON_CLICKER
  bool Event(enum BUTTON button, EVENT event) override {
    if (!IsOn() && event == EVENT_PRESSED) hybrid_font.PlayPolyphonic(&SFX_press);
    return PropBase::Event(button, event);
  }
#endif

  bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
    int blade = ButtonGroup(button, modifiers, event);
    active_blade_ = blade;
    if (event == EVENT_PRESSED && button != BUTTON_NONE && !SaberBase::IsOn()) {
      saber_off_time_ = millis();
      SaberBase::RequestMotion();
    }
    if (event == EVENT_RELEASED &&
        (button == BUTTON_POWER || button == BUTTON_AUX ||
         button == BC4_POW2_BUTTON || button == BC4_AUX2_BUTTON)) {
      if (SaberBase::Lockup() && lockup_owner_ == blade) {
        EndLockup(blade);
        return true;
      }
      return false;
    }

    enum BUTTON virtual_button = VirtualButton(button, blade);
    uint32_t virtual_modifiers = VirtualModifiers(modifiers, blade);
    bool global = GlobalAllowed(blade);
    switch (EVENTID(virtual_button, event, virtual_modifiers)) {
      case EVENTID(BUTTON_POWER, EVENT_PRESSED, MODE_ON):
      case EVENTID(BUTTON_AUX, EVENT_PRESSED, MODE_ON):
        DoSpamBlast(blade);
        return true;

      case EVENTID(BUTTON_POWER, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_OFF):
      case EVENTID(BUTTON_POWER, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_ON):
        if (!BladeIsOn(blade)) TurnBladeOn(BladeSetFor(blade));
        else DoBlasterBlock(BladeSetFor(blade));
        return true;

      case EVENTID(BUTTON_POWER, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_OFF):
        StartMutedIgnition(blade);
        return true;
      case EVENTID(BUTTON_POWER, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_ON):
        DoBlasterBlock(BladeSetFor(blade));
        return true;

      case EVENTID(BUTTON_POWER, EVENT_FIRST_HELD_MEDIUM, MODE_ON):
        if (BladeIsOn(blade)) TurnBladeOff(BladeSetFor(blade));
        return true;

      case EVENTID(BUTTON_POWER, EVENT_FIRST_CLICK_LONG, MODE_OFF):
      case EVENTID(BUTTON_POWER, EVENT_FIRST_CLICK_LONG, MODE_ON):
        if (global) DoTrackStartOrStop();
        return true;

      case EVENTID(BUTTON_POWER, EVENT_FIRST_HELD_LONG, MODE_OFF):
        if (global) EnterScrollPresets();
        return true;

      case EVENTID(BUTTON_POWER, EVENT_SECOND_HELD_MEDIUM, MODE_OFF):
        if (!global) return true;
#ifdef MENU_SPEC_TEMPLATE
        hybrid_font.StopIdleSound();
        EnterMenu();
#else
        EnterBladeLengthMode();
#endif
        return true;

      case EVENTID(BUTTON_POWER, EVENT_FOURTH_HELD_MEDIUM, MODE_OFF):
        if (global) NextBladeArray();
        return true;
      case EVENTID(BUTTON_POWER, EVENT_FOURTH_CLICK_LONG, MODE_OFF):
        if (global) TriggerBladeID();
        return true;

      case EVENTID(BUTTON_POWER, EVENT_SECOND_CLICK_LONG, MODE_ON):
        if (!BladeIsOn(blade) || state_[blade].spam_blast || on_pending_) return true;
        if (isPointingUp(blade)) ToggleBattleMode(blade);
        else DoForce(BladeSetFor(blade));
        return true;

      case EVENTID(BUTTON_POWER, EVENT_THIRD_HELD_MEDIUM, MODE_ON):
        if (global) ToggleColorChangeMode();
        return true;
      case EVENTID(BUTTON_POWER, EVENT_THIRD_CLICK_LONG, MODE_ON):
        if (global && !state_[blade].spam_blast) {
          SaberBase::SetVariation(0);
          sound_library_v2.SayResetToDefaultColor();
        }
        return true;
      case EVENTID(BUTTON_POWER, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_ON):
      case EVENTID(BUTTON_POWER, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_OFF):
        if (global) {
          if (fusor.angle1() < -M_PI / 4) ToggleSequentialQuote();
          else DoQuote();
        }
        return true;

      case EVENTID(BUTTON_AUX, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_OFF):
      case EVENTID(BUTTON_AUX, EVENT_FIRST_CLICK_LONG, MODE_OFF):
        if (global) DoChangePreset(false);
        return true;
      case EVENTID(BUTTON_AUX, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_ON):
      case EVENTID(BUTTON_AUX, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_ON):
        DoBlasterBlock(BladeSetFor(blade));
        return true;

      case EVENTID(BUTTON_POWER, EVENT_CLICK_SHORT, MODE_OFF | BUTTON_AUX):
        if (global) DoSpokenBatteryLevel();
        return true;
      case EVENTID(BUTTON_POWER, EVENT_FIRST_CLICK_LONG, MODE_OFF | BUTTON_AUX):
        if (global) OnDemandBatteryLevel();
        return true;
      case EVENTID(BUTTON_AUX, EVENT_CLICK_SHORT, MODE_OFF | BUTTON_POWER):
      case EVENTID(BUTTON_NONE, EVENT_CLASH, MODE_OFF | BUTTON_POWER):
        if (global) EnterVolumeMenu();
        return true;

      case EVENTID(BUTTON_POWER, EVENT_TWIST, MODE_OFF):
        StartMutedIgnition(blade);
        return true;
      case EVENTID(BUTTON_NONE, EVENT_TWIST, MODE_OFF | BUTTON_POWER):
        StartMutedIgnition(blade);
        return true;
      case EVENTID(BUTTON_NONE, EVENT_TWIST, MODE_ON | BUTTON_POWER):
        if (global) DoChangePreset(true);
        return true;

      case EVENTID(BUTTON_NONE, EVENT_CLASH, MODE_ON | BUTTON_POWER):
      case EVENTID(BUTTON_NONE, EVENT_CLASH, MODE_ON | BUTTON_AUX):
        return DoLockup(BladeSetFor(blade), blade);
      case EVENTID(BUTTON_AUX, EVENT_CLICK_SHORT, MODE_ON | BUTTON_POWER):
        DoLightningBlock(BladeSetFor(blade));
        return true;

      case EVENTID(BUTTON_POWER, EVENT_FOURTH_HELD_MEDIUM, MODE_ON):
        if (!BladeIsOn(blade)) return true;
        if (isPointingDown(blade)) ToggleSpamBlast(blade);
        else if (isPointingUp(blade))
          SaberBase::DoEffect(EFFECT_POWERSAVE, EffectLocation(0, BladeSetFor(blade)));
        return true;
      case EVENTID(BUTTON_NONE, EVENT_TWIST, MODE_ON | BUTTON_AUX):
        if (BladeIsOn(blade) && isPointingUp(blade))
          SaberBase::DoEffect(EFFECT_POWERSAVE, EffectLocation(0, BladeSetFor(blade)));
        return true;

      case EVENTID(BUTTON_NONE, EVENT_TWIST_RIGHT, MODE_ON | BUTTON_POWER):
        DoUserEffect(blade, false, true);
        return true;
      case EVENTID(BUTTON_NONE, EVENT_TWIST_LEFT, MODE_ON | BUTTON_POWER):
        DoUserEffect(blade, false, false);
        return true;
      case EVENTID(BUTTON_NONE, EVENT_TWIST_RIGHT, MODE_ON | BUTTON_AUX):
        DoUserEffect(blade, true, true);
        return true;
      case EVENTID(BUTTON_NONE, EVENT_TWIST_LEFT, MODE_ON | BUTTON_AUX):
        DoUserEffect(blade, true, false);
        return true;
      case EVENTID(BUTTON_NONE, EVENT_TWIST_RIGHT, MODE_OFF | BUTTON_POWER):
        DoUserEffect(blade, false, true);
        return true;
      case EVENTID(BUTTON_NONE, EVENT_TWIST_LEFT, MODE_OFF | BUTTON_POWER):
        DoUserEffect(blade, false, false);
        return true;
      case EVENTID(BUTTON_NONE, EVENT_TWIST_RIGHT, MODE_OFF | BUTTON_AUX):
        DoUserEffect(blade, true, true);
        return true;
      case EVENTID(BUTTON_NONE, EVENT_TWIST_LEFT, MODE_OFF | BUTTON_AUX):
        DoUserEffect(blade, true, false);
        return true;

      case EVENTID(BUTTON_NONE, EVENT_CLASH, MODE_ON):
        if (state_[blade].battle_mode && !swinging_) {
          clash_impact_millis_ = millis();
          SaberBase::SetLockup(SaberBase::LOCKUP_NORMAL, BladeSetFor(blade));
          lockup_owner_ = blade;
          state_[blade].auto_lockup = true;
          SaberBase::DoBeginLockup();
          return true;
        }
        return false;

      case EVENTID(BUTTON_NONE, EVENT_THRUST, MODE_ON):
        if (millis() - last_thrust_millis_ < 200 ||
            millis() - saber_on_time_ < 2000) return false;
        GetThrustBladeLocation();
        if (BladeIsOn(0) && BladeIsOn(1)) {
          SaberBase::SetClashStrength(2.0);
          SaberBase::DoEffect(EFFECT_STAB, EffectLocation(0, thrusting_blade_));
        } else if (thrusting_blade_ == BC_MAIN_BLADE_SET && BladeIsOn(1)) {
          TurnBladeOn(BC_MAIN_BLADE_SET);
        } else if (thrusting_blade_ == BC_SECOND_BLADE_SET && BladeIsOn(0)) {
          TurnBladeOn(BC_SECOND_BLADE_SET);
        }
        last_thrust_millis_ = millis();
        return true;

      case EVENTID(BUTTON_NONE, EVENT_STAB, MODE_ON):
        if (on_pending_) return false;
        clash_impact_millis_ = millis();
        if (!SaberBase::Lockup() && !swinging_) {
          int melt_blade = forward_stab_ ? 0 : 1;
          SaberBase::SetLockup(SaberBase::LOCKUP_MELT, BladeSetFor(melt_blade));
          lockup_owner_ = melt_blade;
          state_[melt_blade].auto_melt = true;
          SaberBase::DoBeginLockup();
        }
        return true;

#ifdef BC_SWING_ON
      case EVENTID(BUTTON_NONE, EVENT_SWING, MODE_OFF):
        if (!NoBladeDisableGestures()) return true;
        if (millis() - saber_off_time_ > 500) {
          FastOn(EffectLocation(0, controlled_blades_));
          GestureEnableBattleMode();
        }
        return true;
#endif
#ifdef BC_TWIST_ON
      case EVENTID(BUTTON_NONE, EVENT_TWIST, MODE_OFF):
        if (!NoBladeDisableGestures()) return true;
        if (millis() - last_twist_millis_ > 300 &&
            millis() - saber_off_time_ > 500) {
          FastOn(EffectLocation(0, controlled_blades_));
          GestureEnableBattleMode();
          last_twist_millis_ = millis();
        }
        return true;
#endif
#ifdef BC_TWIST_OFF
      case EVENTID(BUTTON_NONE, EVENT_TWIST, MODE_ON):
        if (!NoBladeDisableGestures()) return true;
        if (millis() - last_twist_millis_ > 500) {
          last_twist_millis_ = millis();
          if (BladeIsOn(0)) TurnBladeOff(BC_MAIN_BLADE_SET);
          if (BladeIsOn(1)) TurnBladeOff(BC_SECOND_BLADE_SET);
        }
        return true;
#endif
#ifdef BC_THRUST_ON
      case EVENTID(BUTTON_NONE, EVENT_THRUST, MODE_OFF):
        if (!NoBladeDisableGestures()) return true;
        if (millis() - saber_off_time_ > 1000) {
          GestureEnableBattleMode();
          GetThrustBladeLocation();
          FastOn(EffectLocation(0, thrusting_blade_ | ~controlled_blades_));
        }
        return true;
#endif
#ifdef BC_FORCE_PUSH
      case EVENTID(BUTTON_NONE, EVENT_PUSH, MODE_ON):
        if (millis() - last_push_millis_ > 2000) {
          if (!hybrid_font.PlayPolyphonic(&SFX_push))
            SaberBase::DoEffect(EFFECT_FORCE, 0);
          last_push_millis_ = millis();
        }
        return true;
#endif
#ifdef BC_ENABLE_AUTO_SWING_BLAST
      case EVENTID(BUTTON_NONE, EVENT_SWING, MODE_ON):
        if (millis() - last_blast_millis_ < 1000) {
          SaberBase::DoEffect(EFFECT_BLAST, EffectLocation(0, GetBladeAboveHorizon()));
          last_blast_millis_ = millis();
        }
        break;
#endif

#ifdef BLADE_DETECT_PIN
      case EVENTID(BUTTON_BLADE_DETECT, EVENT_LATCH_ON, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_BLADE_DETECT, EVENT_LATCH_ON, MODE_ANY_BUTTON | MODE_OFF):
        blade_detected_ = true;
        FindBladeAgain();
        SaberBase::DoBladeDetect(true);
        return true;
      case EVENTID(BUTTON_BLADE_DETECT, EVENT_LATCH_OFF, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_BLADE_DETECT, EVENT_LATCH_OFF, MODE_ANY_BUTTON | MODE_OFF):
        blade_detected_ = false;
        FindBladeAgain();
        SaberBase::DoBladeDetect(false);
        return true;
#endif
    }
    return false;
  }

  void SB_Effect(EffectType effect, EffectLocation location) override {
    switch (effect) {
      case EFFECT_POWERSAVE:
        if (!hybrid_font.PlayPolyphonic(&SFX_dim)) {
          beeper.Beep(0.1, 1300);
          beeper.Beep(0.1, 900);
          beeper.Beep(0.1, 600);
          beeper.Beep(0.1, 300);
        }
        return;
      case EFFECT_BATTERY_LEVEL:
        if (is_speaking_) {
          is_speaking_ = false;
          return;
        }
        if (!hybrid_font.PlayPolyphonic(&SFX_battery)) {
          beeper.Beep(1.0, 475);
          beeper.Beep(0.5, 693);
          beeper.Beep(0.16, 625);
          beeper.Beep(0.16, 595);
          beeper.Beep(0.16, 525);
          beeper.Beep(1.1, 950);
          beeper.Beep(0.5, 693);
        }
        return;
      case EFFECT_IGNITION:
        saber_on_time_ = millis();
        return;
      case EFFECT_TRANSITION_SOUND:
        if (SFX_tr) hybrid_font.PlayPolyphonic(&SFX_tr);
        return;
      default:
        break;
    }
  }

  void Clash2(bool stab, float strength) override {
    SaberBase::SetClashStrength(strength);
    if (Event(BUTTON_NONE, stab ? EVENT_STAB : EVENT_CLASH)) {
      IgnoreClash(400);
      return;
    }
    IgnoreClash(100);
    if (!SaberBase::IsOn() || SaberBase::Lockup() ||
        SaberBase::GetColorChangeMode() != SaberBase::COLOR_CHANGE_MODE_NONE) return;
    if (stab) {
      SaberBase::DoEffect(EFFECT_STAB, GetThrustBladeLocation());
    } else {
      BladeSet clash_blade = (current_modifiers &
          (BUTTON_POWER | BUTTON_AUX | BC4_POW2_BUTTON | BC4_AUX2_BUTTON)) ?
          BladeSetFor(ButtonGroup(BUTTON_NONE, current_modifiers, EVENT_CLASH)) :
          GetBladeAboveHorizon();
      SaberBase::DoEffect(EFFECT_CLASH, EffectLocation(0, clash_blade));
    }
  }

private:
  struct BladeState {
    bool battle_mode = false;
    bool spam_blast = false;
    bool muted = false;
    bool auto_lockup = false;
    bool auto_melt = false;
  };

  void GestureEnableBattleMode() {
#ifdef BC_GESTURE_AUTO_BATTLE_MODE
    state_[0].battle_mode = true;
    state_[1].battle_mode = true;
#endif
  }
  bool NoBladeDisableGestures() {
#ifdef NO_BLADE_NO_GEST_ONOFF
    if (!blade_present()) return false;
#endif
    return true;
  }

  BC4DelayTimer mute_main_delay_timer_;
  BC4DelayTimer mute_second_delay_timer_;
  BC4DelayTimer scroll_presets_beep_delay_timer_;
  BladeState state_[2];
  int active_blade_ = 0;
  int lockup_owner_ = -1;
  bool sequential_quote_ = false;
  bool is_speaking_ = false;
  bool forward_stab_ = false;

  uint32_t thrust_begin_millis_ = millis();
  uint32_t push_begin_millis_ = millis();
  uint32_t clash_impact_millis_ = millis();
  uint32_t last_thrust_millis_ = millis();
  uint32_t last_twist_millis_ = millis();
  uint32_t last_push_millis_ = millis();
  uint32_t last_blast_millis_ = millis();
  uint32_t saber_off_time_ = millis();
  uint32_t saber_on_time_ = millis();
  BladeSet thrusting_blade_ = BC_MAIN_BLADE_SET;
};

const BladeSet SaberBC4Buttons::controlled_blades_ =
    SaberBC4Buttons::BC_MAIN_BLADE_SET | SaberBC4Buttons::BC_SECOND_BLADE_SET;

#undef PROP_TYPE
#define PROP_TYPE SaberBC4Buttons

#endif
