// detonator_BC_buttons.h Rev 1

/* Created by Brian Conner for KR Thermal Detonator run 2026, based on detonator_Oli_buttons.h by OlivierFlying747-8
  https://fredrik.hubbe.net/lightsaber/proffieos.html
  Copyright (c) 2016-2025 Fredrik Hubinette
  Copyright (c) 2026 Brian Conner with contributions by:
  Fredrik Hubinette aka profezzorn and OlivierFlying747-8
  In case of problems, you can find us at: https://crucible.hubbe.net where somebody will be there to help.
  Distributed under the terms of the GNU General Public License v3.
  https://www.gnu.org/licenses/

I modified the code from detonator_Oli_buttons.h to customize for use with KR Sabers TD 2026.

I removed some functionality; 1 button, OFF mode (latching is POWER, expected "dead" when closed), volume up/down, stealth timer, OLED display functionality, some defines, etc...
Added Mute, Quote playback with non-overlapping, dedicated countdown timer sound.

You can arm then disarm the TD, or arm and make it detonate (via clash for immediate detonation or via countdown timer for
delayed detonation).
Once the countdown timer is active, it can't be turned off and will go boom either with a Clash, or when the timer expires.

This prop suppots the use of a non-latching POW button so it is compatible with OlivierFlying747-8's multi_prop, or any non-latching power button scenario.
To use it with non-latching POW button, add "#define DETONATOR_BUTTON_POWER_IS_MOMENTARY" to your CONFIG_TOP section..

This detonator prop file is written for use with 2 button Thermal Detonators and ProffieOS v8.x and above.
** Note for your button wiring: This detonator prop file uses POW & AUX buttons (BTN1 and BTN2 pads on Proffieboard) unlike detonator.h which uses POW & AUX2).

=================================================================================================================================
Button Controls:
================

Latching POWER Button:
  - Turn ON (starts disarmed)   - Latch ON
  - Turn OFF                    - Latch OFF "He Agrees!" (disarms if armed, will stop armhum.wav & plays endarm.wav if armhum.wav was playing) *BC - plays poweroff?
                                    If a countdown timer was started, it will continue until boom.wav.
Momentary POWER Button:
  - Turn ON (starts disrmed)    - Short Click while OFF
  - Turn OFF                    - Short Click while ON (disarm if armed, will stop armhum.wav & plays endarm.wav if armhum.wav was playing)
                                    If a countdown timer was started, it will continue until boom.wav

AUX Button:

  - Toggle Mute                 - 3x Click and Hold (Unmutes on preset change or OFF/BOOM)
  - Play Quote                  - 3x Click
  - Start/Stop track            - Hold while Disarmed
  - Change Preset               - 2x Click or Twist when Disarmed (plays font.wav)
          Next Preset     - While Pointing UP
          Previous Preset - While Pointing DOWN
          First Preset    - While NOT pointing UP or DOWN

  - Arm                         - Short Click while ON - or - Shake to ARM.(plays bgnarm.wav followed by armhum.wav)
  - Disarm                      - 2x Click while Armed (plays endarm.wav)
  - Detonate:                   - Hold while Armed to start Countdown Timer (plays countdown.wav)
                                  - or -
                                  Clash while Armed to instantly trigger Boom (interrupts any countdown)
                                  Detonation resets everything, turns the detonator OFF.
  - Spoken Battery Level        - 2x Click and Hold while Disarmed:
                                    Pointing UP   - Battery Level in percentage
                                    Pointing DOWN - Battery Level in volts


CLASH (while Aarmed or while ON and stealth timer running option1 or 2):
  - Instantly trigger boom (interrupts any countdown), resets everything, turns the detonator OFF.
=================================================================================================================================

============= LIST OF .wav USED in this detonator: ==============================================================================
This prop version REQUIRES a ProffieOS Voicepack V1 or V2 for some of the sounds to work.
Typically, that is a folder named "common" on the root level of the SD card.

Download your choice of language and variation here:
https://fredrik.hubbe.net/lightsaber/sound/
Also, a large variety of FREE in-universe character Voicepacks available here:
https://crucible.hubbe.net/t/additional-voicepacks/4227
If you'd care to make a donation for Brian Conner's time making these Voicepacks:
https://www.buymeacoffee.com/brianconner

Your sound font should contain the below listed files to use detonator_BC_buttons.h to it's full potential:

poweron
poweroff
armhum.wav
bgnarm.wav
boom.wav
endarm.wav
hum.wav (for regular idle/ON but not armed)

Optional .wav files:
====================

boot.wav? *BC-goes right to on.. plays boot?
font.wav
quote.wav
countdown.wav

List of optional detonator defines:
#define DETONATOR_BUTTON_POWER_IS_MOMENTARY    // If your detonator pow button is NOT latching (it's momentary) and has been defined as such in your config.
#define DETONATOR_TIMER_DURATION 6.0f          // default is 6 seconds during delayed detonation.  (set timing in seconds)
=================================================================================================================================
*/

#ifndef PROPS_DETONATOR_BC_BUTTONS_H
#define PROPS_DETONATOR_BC_BUTTONS_H

#include "prop_base.h"
#include "../sound/sound_library.h"

#ifndef DETONATOR_TIMER_DURATION
#define DETONATOR_TIMER_DURATION 6.0f // default is 6 seconds (set timing in seconds)
#endif

#define PROP_TYPE DetonatorBCButtons

EFFECT(countdown);      // for countdown timer sound. optional. if not in font, plays armhum straight through

class DetonatorBCButtons : public PROP_INHERIT_PREFIX PropBase {
public:
  DetonatorBCButtons() : PropBase() {}
  const char* name() override { return "DetonatorBCButtons"; }

  enum NextAction {
    NEXT_ACTION_NOTHING,
    NEXT_ACTION_ARM,
    NEXT_ACTION_BLOW,
  };

  void SetPower(bool on) {}

  void SetNextAction(NextAction what, float when_sec) {
    time_base_ = millis();
    next_event_time_ = when_sec * 1000;
    next_action_ = what;
  }

  void PollNextAction() {
    if (millis() - time_base_ > next_event_time_) {
      switch (next_action_) {
        case NEXT_ACTION_NOTHING:
          break;
        case NEXT_ACTION_ARM:
          armed_ = true;
          break;
        case NEXT_ACTION_BLOW:
          // NOTE: Don't send EFFECT_ALT_SOUND here. Doing so (switching the
          // smoothswing alt bank back to idle) right before Off(OFF_BLAST)
          // restarts/kills the currently playing hum_player_ (via
          // RestartHum() in hybrid_font.h) at the exact moment boom.wav
          // needs to play, which was silencing/undermining the boom sound.
          // Since we're about to turn everything off anyway, there's no
          // need to restore the idle alt-sound bank first.
          // Clear the lockup state (no sound side effect, unlike
          // DoEndLockup()/EFFECT_ALT_SOUND above) so it doesn't stay stuck
          // at LOCKUP_ARMED after the detonator turns itself off.
          SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
          Off(OFF_BLAST);
          // Make sure boom isn't muted by whatever hum volume was last set
          // (e.g. by smoothswing ducking) before this player gets reused.
          // This must happen *after* Off(OFF_BLAST), because EFFECT_BOOM
          // creates the replacement player there.
          hybrid_font.SetHumVolume(1.0);
          // Reset everything that's been blown to bits: silently reset the
          // alt-sound bank back to idle (alt0) so the next poweron doesn't
          // start up armed. OFF_BLAST does not do this on its own, and using
          // DoEffect(EFFECT_ALT_SOUND, ...) here (instead of the silent
          // ResetCurrentAlternative()) would trigger RestartHum() and
          // re-kill the boom player, same as above.
          ResetCurrentAlternative();
          armed_ = false;
          break;
      }
      next_action_ = NEXT_ACTION_NOTHING;
    }
  }

  void BeginArm() {
    SaberBase::SetLockup(SaberBase::LOCKUP_ARMED);
    SaberBase::DoBeginLockup();
    len = hybrid_font.GetCurrentEffectLength();
    SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, 1);  // Switch from idle smoothswings to armed smoothswings.
    SetNextAction(NEXT_ACTION_ARM, len);
  }

  bool CountdownActive() const {
    return next_action_ == NEXT_ACTION_BLOW;
  }

  void Disarm() {
    SaberBase::DoEndLockup();
    SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
    SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, 0);
    armed_ = false;
    SetNextAction(NEXT_ACTION_NOTHING, 0);
  }


  void ToggleCountdown() {
    if (armed_) {
                                                          // *BC - make this section use pos() with `len` to start wav like humStart does.
      if (SFX_countdown) {
        // hybrid_font.PlayMonophonic(&SFX_countdown, &SFX_hum);
        // Stop arm lockup loop without playing endarm, then play countdown
        // as monophonic. This is intentional: countdown should transition
        // straight into countdown.wav/boom.wav with no endarm.wav in
        // between. endarm.wav is only meant to play on Disarm() (manually
        // cancelling the arm) or on power-off, so SetLockup(LOCKUP_NONE) is
        // called *before* DoEndLockup() here so that SB_EndLockup() (in
        // sound/hybrid_font.h) sees LOCKUP_NONE and skips endarm.wav.
        SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
        SaberBase::DoEndLockup();
        hybrid_font.PlayMonophonic(&SFX_countdown, &SFX_hum);
      }
PVLOG_NORMAL << "************************* SetNextAction(NEXT_ACTION_BLOW" << DETONATOR_TIMER_DURATION << "\n";
      SetNextAction(NEXT_ACTION_BLOW, DETONATOR_TIMER_DURATION);
    } else {
PVLOG_NORMAL << "*************************  ToggleCountdown called, NOT armed, NEXT_ACTION_NOTHING\n";
      SaberBase::DoEndLockup();
      SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
      SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, 0);
      SetNextAction(NEXT_ACTION_NOTHING, 0);
    }
  }

  void Loop() override {
    PropBase::Loop();
    DetectTwist();
    DetectShake();
    PollNextAction();
    sound_library_.Poll(wav_player);
    if (wav_player && !wav_player->isPlaying()) wav_player.Free();
  }

  void Setup() {
   sound_library_v2.init();
  }

  // Pull in parent's SetPreset, but turn the detonator on.
  void SetPreset(int preset_num, bool announce) override {
    PropBase::SetPreset(preset_num, announce);
    if (!SFX_poweron && !SaberBase::IsOn()) {
      On();
    }
  }

  void DetonatorOn() {
    armed_ = false;
    SetPower(true);
    On();
  }

  void DetonatorOff() {
// +      if (CountdownActive()) return;
// +      if (armed_) {
// +        Disarm();
// +      } else {
// +        armed_ = false;
// +      }
    armed_ = false;
    SetPower(false);
    Off();
  }

  bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
    switch (EVENTID(button, event, modifiers)) {

// Mute Toggle Anytime. Resets on preset change or OFF/BOOM)
      case EVENTID(BUTTON_AUX, EVENT_THIRD_HELD_MEDIUM, MODE_ON):
        if (!SetMute(true)) SetMute(false);
PVLOG_NORMAL << "************************* MUTE/UNMUTE\n";
        return true;

// TURN ON
#ifndef DETONATOR_BUTTON_POWER_IS_MOMENTARY
      case EVENTID(BUTTON_POWER, EVENT_LATCH_ON, MODE_OFF):
#else
      // This is for using this detonator without a latching button.
      case EVENTID(BUTTON_POWER, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_OFF):
#endif
        DetonatorOn();
        return true;

// TURN OFF
#ifndef DETONATOR_BUTTON_POWER_IS_MOMENTARY
      case EVENTID(BUTTON_POWER, EVENT_LATCH_OFF, MODE_ON):
#else
      // This is for using this detonator without a latching button.
      case EVENTID(BUTTON_POWER, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_ON):
#endif
        DetonatorOff();
        return true;

// Play Quote
      case EVENTID(BUTTON_AUX, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_ON):
        if (SFX_quote) {
          if (GetWavPlayerPlaying(&SFX_quote)) return false;  // Simple prevention of quote overlap
          hybrid_font.PlayCommon(&SFX_quote);
        }
        return true;

// Change Preset / Disarm
      case EVENTID(BUTTON_AUX, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_ON):
      case EVENTID(BUTTON_NONE, EVENT_TWIST, MODE_ON):
        // if (armed_) {
        //   armed_ = false;
        //   ToggleCountdown();
        if (CountdownActive()) {
          return true;
        } else if (armed_) {
          PVLOG_NORMAL << "**** Disarm\n";
          Disarm();
        } else {
          FusorPreset();
        }
        return true;

// Arm
      case EVENTID(BUTTON_AUX, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_ON):
      case EVENTID(BUTTON_NONE, EVENT_SHAKE, MODE_ON):
        if (!armed_) {
          BeginArm();
        }
        return true;

// Start Countdown Timer / Start Or Stop Track
      case EVENTID(BUTTON_AUX, EVENT_FIRST_HELD_MEDIUM, MODE_ON):
        // if (armed_) {
        if (CountdownActive()) {
          return true;
        } else if (armed_) {
          PVLOG_NORMAL << "**** Start Countdown Timer\n";
          ToggleCountdown();
        } else {
          StartOrStopTrack();
        }
        return true;

// Clash to Boom if Armed or when timer is running
      case EVENTID(BUTTON_NONE, EVENT_CLASH, MODE_ON):
        if (armed_) {
PVLOG_NORMAL << "*************************  Clash to Boom,  armed, NEXT_ACTION_BLOW\n";
          SetNextAction(NEXT_ACTION_BLOW, 0);
        } else {
PVLOG_NORMAL << "*************************  Clash to Boom,  NOT armed, return true\n";
        }
        return true;


// Battery Level
      case EVENTID(BUTTON_AUX, EVENT_SECOND_HELD_MEDIUM, MODE_ON):
        if (!armed_) {
          FusorBatteryLevel();
        }
        return true;

    }  // switch (EVENTID)
    return false;
  }  // Event2


  void SB_Effect(EffectType effect, EffectLocation location) override {
    switch (effect) {
      default: return;
    }  // switch (effect)
  }  // SB_Effect

  RefPtr<BufferedWavPlayer> wav_player;

  void FusorPreset() {
    if (fusor.angle1() > M_PI / 3) {
      // Pointing UP
      next_preset();
      PVLOG_DEBUG << "** Next preset\n";
    } else {
      if (fusor.angle1() < -M_PI / 3) {
        // Pointing DOWN
        previous_preset();
        PVLOG_DEBUG << "** Previous preset\n";
      } else {
        // Not pointing towards UP or DOWN (between -20° & +20°)
        first_preset();
        PVLOG_DEBUG << "** Jumped to first preset\n";
      }
    }
  }

  void FusorBatteryLevel() {
    // Avoid weird battery readings when using USB
    if (battery_monitor.battery() < 0.5) {
      sound_library_.SayTheBatteryLevelIs();
      sound_library_.SayDisabled();
      return;
    }
    sound_library_.SayTheBatteryLevelIs();
    // pointing DOWN
    if (fusor.angle1() < -M_PI / 4) {
      sound_library_.SayNumber(battery_monitor.battery(), SAY_DECIMAL);
      sound_library_.SayVolts();
      PVLOG_NORMAL << "Battery Voltage: " << battery_monitor.battery() << "\n";
    } else {
      sound_library_.SayNumber(battery_monitor.battery_percent(), SAY_WHOLE);
      sound_library_.SayPercent();
      PVLOG_NORMAL << "Battery Percentage: " <<battery_monitor.battery_percent() << "%\n";
    }
  }

private:
  // State variables
  NextAction next_action_       = NEXT_ACTION_NOTHING;
  uint32_t time_base_           = 0;            // from original detonator.h
  uint32_t next_event_time_     = 0;            // from original detonator.h
  //bool powered_               = true;         // from original detonator.h, but not used any more.
  float len                     = 0.0f;         // countdown timer duration (in seconds)
  bool armed_                   = false;        // once armed_, it can go boom with clash


}; // class DetonatorBCButtons

#endif // PROPS_DETONATOR_BC_BUTTONS_H
