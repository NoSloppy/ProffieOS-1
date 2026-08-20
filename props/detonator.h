/*
detonator.h prop file.
  http://fredrik.hubbe.net/lightsaber/proffieos.html
  Copyright (c) 2016-2025 Fredrik Hubinette
  Distributed under the terms of the GNU General Public License v3.
  http://www.gnu.org/licenses/

This prop simulates a thermal detonator (or similar explosive prop).
The "blade" output represents the detonator's active/armed state visual indicator.
It is designed primarily for latch-switch power control combined with a
momentary button for the arming and detonation sequence.

Features:
- Power ON/OFF via a latch switch (BUTTON_POWER). Detonator lights up when latched ON.
- Arming sequence initiated by pressing and holding AUX2 while powered ON.
  Uses LOCKUP_ARMED effect — plays lockup sound/animation until arming completes.
  The arming time is tied to the length of the lockup sound file in the font.
- Detonation triggered by releasing AUX2 after the detonator is fully armed.
  Plays blast effect, then powers OFF automatically.
- Safe disarm — releasing AUX2 before arming completes cancels the arm sequence
  with no detonation.
- Change Preset and Start/Stop Track available at any time via AUX2 Double Click.
- Clash and swing/motion gestures are intentionally disabled.
- Optional DELAYED_OFF mode: by default the detonator powers on immediately at
  boot and after a preset change. Define DELAYED_OFF to require an explicit
  latch-on to power up instead.

---------------------------------------------------------------------------
Optional defines:
  #define DELAYED_OFF   - Detonator starts powered OFF at boot and after preset change.
                          Requires the latch switch to be cycled to power ON.
                          Without this define the detonator defaults to powered ON at boot.

---------------------------------------------------------------------------
Button / switch assignment in CONFIG_BUTTONS:
  Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");   // Latch switch  - powers ON/OFF
  Button AuxButton(BUTTON_AUX2, aux2Pin, "aux2");            // Momentary     - arms/detonates, preset change, track

---------------------------------------------------------------------------
Optional Blade style elements:
  LOCKUP_ARMED            - Use a lockup layer (e.g. LockupTrL or similar) triggered by
                            SaberBase::LOCKUP_ARMED in the blade style to show the
                            arming animation while AUX2 is held.
  EFFECT_BLAST            - Use a blast layer in the blade style to animate the detonation flash.

---------------------------------------------------------------------------
Sound files (place in font folder):
  hum.wav        // idle hum while powered ON
  out.wav        // power ON effect (latch switch closed)
  in.wav         // power OFF / detonation shutdown effect
  lockup*.wav    // arming sequence sound — duration controls arm time
  blast*.wav     // detonation / explosion sound

==================================================
| Controls                                       |
==================================================

-------- Detonator powered OFF --------
Power ON                  - Latch POWER switch ON.
                            Detonator lights up and hum begins. Armed state is reset.
                            * If DELAYED_OFF is not defined, power ON happens automatically at boot.
Change Preset             - Double Click AUX2.

-------- Detonator powered ON --------
Power OFF                 - Latch POWER switch OFF.
                            Works at any time, including mid-arm sequence.

Arm Detonator             - Press and hold AUX2.
                            Lockup/arming effect plays. Detonator is fully armed
                            once the lockup sound finishes.
Detonate                  - Release AUX2 (after arming is complete).
                            Plays blast effect then automatically powers OFF.
                            * Detonator must be powered ON again before next use.
Safe Disarm               - Release AUX2 (before arming is complete).
                            Arming is cancelled. No detonation occurs.
                            Detonator remains powered ON and ready.

Start/Stop Track          - Double Click AUX2.

*/

#ifndef PROPS_DETONATOR_H
#define PROPS_DETONATOR_H

#include "prop_base.h"

#define PROP_TYPE Detonator

class Detonator : public PROP_INHERIT_PREFIX PropBase {
public:
  Detonator() : PropBase() {}
  const char* name() override { return "Detonator"; }

#ifdef DELAYED_OFF
  bool powered_ = false;
  void SetPower(bool on) { powered_ = on; }
#else
  bool powered_ = true;
  void SetPower(bool on) {}
#endif

  bool armed_ = false;

  enum NextAction {
    NEXT_ACTION_NOTHING,
    NEXT_ACTION_ARM,
    NEXT_ACTION_BLOW,
  };

  NextAction next_action_ = NEXT_ACTION_NOTHING;
  uint32_t time_base_;
  uint32_t next_event_time_;

  void SetNextAction(NextAction what, uint32_t when) {
    time_base_ = millis();
    next_event_time_ = when;
    next_action_ = what;
  }

  void SetNextActionF(NextAction what, float when) {
    SetNextAction(what, when * 1000);
  }

  void PollNextAction() {
    if (millis() - time_base_ > next_event_time_) {
      switch (next_action_) {
        case NEXT_ACTION_NOTHING:
          break;
        case NEXT_ACTION_ARM:
          armed_ = true;
          // TODO: Should we have separate ARMING and ARMED states?
          break;
        case NEXT_ACTION_BLOW:
          Off(OFF_BLAST);
          break;
      }
      next_action_ = NEXT_ACTION_NOTHING;
    }
  }

  void beginArm() {
    SaberBase::SetLockup(SaberBase::LOCKUP_ARMED);
    SaberBase::DoBeginLockup();
#ifdef ENABLE_AUDIO
    float len = hybrid_font.GetCurrentEffectLength();
#else
    float len = 1.6;
#endif
    SetNextActionF(NEXT_ACTION_ARM, len);
  }

  void blast() {
    SaberBase::DoEndLockup();
#ifdef ENABLE_AUDIO
    float len = hybrid_font.GetCurrentEffectLength();
#else
    float len = 0.0;
#endif
    SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
    if (armed_) {
      SetNextActionF(NEXT_ACTION_BLOW, len);
    } else {
      SetNextAction(NEXT_ACTION_NOTHING, 0);
    }
  }

  void Loop() override {
    PropBase::Loop();
    PollNextAction();
  }

#if NUM_BUTTONS >= 2
  // Make clash do nothing
  void Clash(bool stab, float strength) override {}
#endif

  // Make swings do nothing
  void DoMotion(const Vec3& motion, bool clear) override { }

  bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
    switch (EVENTID(button, event, modifiers)) {
      case EVENTID(BUTTON_POWER, EVENT_LATCH_ON, MODE_OFF):
        armed_ = false;
        SetPower(true);
        On();
        return true;

      case EVENTID(BUTTON_POWER, EVENT_LATCH_OFF, MODE_ON):
      case EVENTID(BUTTON_POWER, EVENT_LATCH_OFF, MODE_OFF):
        SetPower(false);
        Off();
        return true;

      case EVENTID(BUTTON_AUX2, EVENT_DOUBLE_CLICK, MODE_OFF):
        if (powered_) rotate_presets();
        return true;

      case EVENTID(BUTTON_AUX2, EVENT_DOUBLE_CLICK, MODE_ON):
        StartOrStopTrack();
        return true;

      case EVENTID(BUTTON_AUX2, EVENT_PRESSED, MODE_ON):
        beginArm();
        break;

      case EVENTID(BUTTON_AUX2, EVENT_RELEASED, MODE_ON):
        blast();
        return armed_;

        // TODO: Long click when off?
    }
    return false;
  }
};

#endif
