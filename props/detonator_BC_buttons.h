// detonator_BC_buttons.h Rev 3

/* Created by Brian Conner for KR Sabers' Thermal Detonator run 2026, based on detonator_Oli_buttons.h by OlivierFlying747-8
  https://fredrik.hubbe.net/lightsaber/proffieos.html
  Copyright (c) 2016-2025 Fredrik Hubinette
  Copyright (c) 2026 Brian Conner with contributions by:
  Fredrik Hubinette aka profezzorn and OlivierFlying747-8
  In case of problems, you can find us at: https://crucible.hubbe.net where somebody will be there to help.
  Distributed under the terms of the GNU General Public License v3.
  https://www.gnu.org/licenses/

Additions: Mute, Quote playback with non-overlapping, dedicated countdown timer sound, and more.

You can arm then disarm the TD, or arm and make it detonate by Clash for immediate detonation or via Countdown Timer for delayed detonation.
Once the Countdown Timer is active, it can't be turned off and will Detonate either with a Clash, or when the timer expires.

** Note for your install: This detonator prop file uses 2 buttons, POW & AUX (BTN1 and BTN2 pads on Proffieboard) and ProffieOS v8.x and above.

Sounds used:
------------
This prop version REQUIRES a ProffieOS Voicepack V1 or V2 for some of the sounds to work.
Typically, that is a folder named "common" on the root level of the SD card.

Download your choice of language and variation here:
https://fredrik.hubbe.net/lightsaber/sound/
Also, a large variety of FREE in-universe character Voicepacks available here:
https://crucible.hubbe.net/t/additional-voicepacks/4227
If you'd care to make a donation for Brian Conner's time making these Voicepacks:
https://www.buymeacoffee.com/brianconner

Your sound font should contain the following files.
There can be more than one of each, and if so, it's a good idea to group them together
in a subfolder named after the base sound (like quote/quote01.wav, quote/quote02.wav, etc...).
poweron.wav
poweroff.wav
bgnarm.wav
armhum.wav
endarm.wav
boom.wav
hum.wav (for regular idle/ON mode but not yet armed)
alt000/swingh.wav and swingl.wav
alt001/swingh.wav and swingl.wav
* Note on alt folders - alt000 are the smoothswing sounds when disarmed. alt001 for when armed.

Optional sounds:
----------------
font.wav
quote.wav
destruct.wav (Countdown Timer sound)

Optional defines for your CONFIG_TOP section:
---------------------------------------------
#define DESTRUCT_TIMER_DURATION 6.0         // default is 6 seconds.
#define SPOKEN_BATTERY_LEVEL                 // Use to have battery level spoken (uses Voicepack sound files) If not defined, High/Mid/Low LED meter only.

==========================================================================================================================================================
==========================================================================================================================================================
---------------------------------------
      Button Controls Summary
---------------------------------------
AUX Button:
(Twist, Swing, and Clash are supported for basic
functionality on TDs that do not have an AUX button active)

--------- When Disarmed ---------
1 click or swing        - arm

2 clicks or twist       - next preset     (pointing up)
                          previous preset (pointing down)
2 clicks held           - spoken battery level
                            percentage (pointing up)
                            volts      (pointing down)

--------- When Armed ---------
2 clicks or twist       - start countdown timer

1 click or Swing        - disarm
clash                   - instantly detonate

--------- Anytime ---------
1 click held            - start/stop track
3 clicks                - quote
3 clicks held           - toggle mute

4 clicks                - next track
4 clicks held           - toggle explosion animation

---------------------------------------
      Button Controls Detailed
---------------------------------------
Latching POWER Button:
  - Turn ON                     - Latch ON (starts disarmed)
  - Turn OFF                    - Latch OFF "He Agrees!"
                                  If a countdown timer was started, it will continue until Detonation.

AUX Button:
  - Change Preset               - 2x Clicks or Twist when Disarmed (plays font.wav)
                                    Next Preset     - While Pointing UP
                                    Previous Preset - While Pointing DOWN
  - Spoken Battery Level        - 2x Click and Hold while Disarmed (uses Voicepack/common sounds)
                                    Battery Level in percentage - While Pointing UP
                                    Battery Level in volts      - While Pointing DOWN
  - Play Quote                  - 3x Click at anytime (plays quote.wav)
  - Toggle Mute                 - 3x Click and Hold at anytime (Unmutes on preset change or OFF/Detonation)
  - Toggle Explosion Animation  - 4x Click and Hold at anytime (uses "enabled"/"disabled" voice sound)
                                    Choose to show Detonation on LEDs or not, reagrdless of bladestyle having EFFECT_BOOM.
  - Start/Stop track            - Hold at anytime.
  - Next Track                  - 4x Click.
                                  * Note - Next Track auto plays track.

  - Arm                         - 1x Click or Swing while Disarmed (plays bgnarm.wav followed by armhum.wav)
  - Disarm                      - 1x Click or Swing while Armed (plays endarm.wav)
  - Start Countdown Timer       - 2x Click or Twist when Armed.
                                    This plays destruct.wav. The delay to Detonation is the sound file's duration.
                                    If no destruct.wav exists, delay to Detonation is the user defined DESTRUCT_TIMER_DURATION.
                                    If not defined, the default Coundown Timer duration is 6 seconds.

Instantly Detonate              - Clash while Armed. Interrupts any countdown, resets everything, turns the detonator OFF.

Reset after Detonation          - To reset, toggle the POW button by closing and re-opening the Thumb Latch.
=================================================================================================================================
================================================================================================================================
*/

#ifndef PROPS_DETONATOR_BC_BUTTONS_H
#define PROPS_DETONATOR_BC_BUTTONS_H

#include "prop_base.h"
#include "../sound/sound_library.h"

#ifndef DESTRUCT_TIMER_DURATION
#define DESTRUCT_TIMER_DURATION 6.0f
#endif

#define PROP_TYPE DetonatorBCButtons

EFFECT(destruct);  // for optional Countdown Timer sound. If not in font, armhum plays straight through to Detonation.
EFFECT(mute);     // Notification before muted ignition to avoid confusion.

class DelayTimer {
public:
  DelayTimer() : triggered_(false), trigger_time_(0), duration_(0) {}

  void trigger(uint32_t duration) {
    triggered_ = true;
    trigger_time_ = millis();
    duration_ = duration;
  }

  void stopTimer() {
    PVLOG_DEBUG << "** Stopping timer.\n";
    triggered_ = false;
  }

  bool isTimerExpired() {
    if (!triggered_) return false;
    if (millis() - trigger_time_ > duration_) {
      stopTimer();
      return true;  // Timer has elapsed
    }
    return false;  // Timer is still running
  }

private:
  bool triggered_;
  uint32_t trigger_time_;
  uint32_t duration_;
};

class DetonatorBCButtons : public PROP_INHERIT_PREFIX PropBase {
public:
  DetonatorBCButtons() : PropBase() {}
  const char* name() override { return "DetonatorBCButtons"; }

  enum NextAction {
    NEXT_ACTION_NOTHING,
    NEXT_ACTION_ARM,
    NEXT_ACTION_BLOW,
  };

  void Setup() {
   sound_library_v2.init();
  }

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
          // Clear lockup first so OFF_BLAST doesn't play endarm.
          SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
          SaberBase::DoEndLockup();
          if (show_detonation_) {
            // Can't just uses OFF_BLAST. Need to avoid EFFECT_BLAST from SaberBase::DoOff(),
            // otherwise boom doesn't get a chance to play as it tries 
            // to play a non-existant blaster.wav on the same player.
            Off(OFF_IDLE);
            SaberBase::DoEffect(EFFECT_BOOM, 0);
            PVLOG_NORMAL << "+++++ BOOM!! +++++\n";
          } else if (SFX_boom) {
            // Detonate and shut off with no EFFECT_BOOM, and no EFFECT_RETRACTION
            hybrid_font.PlayMonophonic(&SFX_boom, NULL);
            Off(OFF_IDLE);
            PVLOG_NORMAL << "+++++ BOOM!! +++++\n";
          } else {
            Off(OFF_BLAST);
          }
          // Reset to idle smoothswings pair.
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
    float len = hybrid_font.GetCurrentEffectLength();
    // Switch from idle smoothswings to armed smoothswings.
    SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, 1);
    SetNextAction(NEXT_ACTION_ARM, len);
    PVLOG_NORMAL << "**** ARMED\n";
  }

  bool CountdownActive() const {
    return next_action_ == NEXT_ACTION_BLOW;
  }

  void Disarm() {
    armed_ = false;
    SaberBase::DoEffect(EFFECT_USER2, 0);
    SaberBase::DoEndLockup();
    SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
    SaberBase::DoEffect(EFFECT_ALT_SOUND, 0.0, 0);
    SetNextAction(NEXT_ACTION_NOTHING, 0);
    PVLOG_NORMAL << "**** DISARMED\n";
  }

  void Detonate(float boom_delay = DESTRUCT_TIMER_DURATION) {
    if (boom_delay > 0.0f) {
      if (SFX_destruct) {
/* make this to be really sexy, and use pos() and compensate for longer or shorter user defined durations.
wav would be delayed from starting if DESTRUCT_TIMER_DURATION is > 6seconds, and truncated from the front end of the wav if DESTRUCT_TIMER_DURATION< 6 seconds. */
        // End LOCKUP_ARMED but skip playing endarm
        SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
        SaberBase::DoEndLockup();
        hybrid_font.PlayMonophonic(&SFX_destruct, &SFX_hum);
        boom_delay = hybrid_font.GetCurrentEffectLength();
      }
    }
    // EFFECT_DESTRUCT used in blade style for countdown timer blade effect.
    // Use Variation as the function to sync timing (TrDelayX<Variation>)
    SaberBase::SetVariation(boom_delay * 1000);
    SaberBase::DoEffect(EFFECT_DESTRUCT, 0);
    SetNextAction(NEXT_ACTION_BLOW, boom_delay);
  }

  void Loop() override {
    PropBase::Loop();
    if (track_player_ && !track_player_->isPlaying()) {
      PVLOG_NORMAL << "** Track ended\n";
      track_player_.Free();
    }
    DetectTwist();
    DetectSwing();
    PollNextAction();
    sound_library_.Poll(wav_player);
    if (wav_player && !wav_player->isPlaying()) wav_player.Free();
    // Play optional mute.wav first.
    if (mute_all_delay_timer_.isTimerExpired()) {
      if (SetMute(true)) {
        unmute_on_deactivation_ = true;
        PVLOG_NORMAL << "**** MUTE\n";
      } else {
        SetMute(false);
        unmute_on_deactivation_ = false;
        PVLOG_NORMAL << "**** UNMUTE\n";
      }
    }
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
    On();
  }

  void DetonatorOff() {
    // To avoid playing Disarm animation at Detonation,
    // use EFFECT_RETRACTION instead of InOut in blade style.
    if (CountdownActive()) { PVLOG_NORMAL << "**** TOO LATE!! RUN!!!\n"; return; }
    armed_ = false;
    SaberBase::SetVariation(0);
    Off();
  }

  void FusorPreset() {
    if (fusor.angle1() > M_PI / 6) {
      // Pointing UP
      next_preset();
      PVLOG_NORMAL << "**** Next preset\n";
    }
    if (fusor.angle1() < -M_PI / 6) {
      // Pointing DOWN
      previous_preset();
      PVLOG_NORMAL << "**** Previous preset\n";
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
      SaberBase::DoEffect(EFFECT_BATTERY_LEVEL, 0);
    } else {
      sound_library_.SayNumber(battery_monitor.battery_percent(), SAY_WHOLE);
      sound_library_.SayPercent();
      PVLOG_NORMAL << "Battery Percentage: " <<battery_monitor.battery_percent() << "%\n";
      SaberBase::DoEffect(EFFECT_BATTERY_LEVEL, 0);
    }
  }

  bool chdir(const StringPiece dir) override {
    if (track_player_) {
      track_player_->Stop();
      track_player_.Free();
    }
    bool ret = PropBase::chdir(dir);
    track_[0] = 0;
    return ret;
  }

  bool PlayTrack() {
    if (!track_[0]) {
      if (!RunCommandAndFindNextSortedLine<128>(
              "list_current_tracks", nullptr, nullptr, track_, false)) {
        return false;
      }
    }
    PVLOG_NORMAL << "** Playing track = " << track_ << "\n";
    MountSDCard();
    EnableAmplifier();
    track_player_ = GetFreeWavPlayer();
    if (track_player_) {
      track_player_->Play(track_);
      return true;
    }
    return false;
  }

  void PlayStopTrack() {
    if (track_player_ && track_player_->isPlaying()) {
      track_player_->Stop();
      track_player_.Free();
      PVLOG_NORMAL << "** Track stopped\n";
      return;
    }
    if (track_player_) {
      track_player_.Free();
    }
    PlayTrack();
  }

  void NextTrack() {
    // Hot switch: stop the current track first.
    if (track_player_ && track_player_->isPlaying()) {
      track_player_->Stop();
      track_player_.Free();
    }
    char next_track[128];
    next_track[0] = 0;
    if (!RunCommandAndFindNextSortedLine<128>(
            "list_current_tracks", nullptr, track_, next_track, false)) {
      if (!RunCommandAndFindNextSortedLine<128>(
              "list_current_tracks", nullptr, nullptr, next_track, false)) {
        return;
      }
    }
    strcpy(track_, next_track);
    PVLOG_NORMAL << "** NextTrack: " << track_ << "\n";
    PlayTrack();
  }

  bool Parse(const char *cmd, const char* arg) override {
    if (PropBase::Parse(cmd, arg)) return true;

    if (!strcmp(cmd, "list_current_tracks")) {
      LOCK_SD(true);
      for (const char* dir = current_directory;
           dir;
           dir = next_current_directory(dir)) {
        PathHelper path(dir, "tracks");
        ListTracks(path);
      }
      LOCK_SD(false);
      return true;
    }
    if (!strcmp(cmd, "twist")) {
        Event(BUTTON_NONE, EVENT_TWIST);
        return true;
    }
    return false;
  }

  bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
    switch (EVENTID(button, event, modifiers)) {

// Mute Toggle Anytime. Resets on preset change or OFF/BOOM)
      case EVENTID(BUTTON_AUX, EVENT_THIRD_HELD_MEDIUM, MODE_ON):
        if (hybrid_font.PlayPolyphonic(&SFX_mute)) {
          mute_all_delay_timer_.trigger(SaberBase::sound_length * 1000);
        } else {
          mute_all_delay_timer_.trigger(0);
        }
        return true;

// TURN ON
      case EVENTID(BUTTON_POWER, EVENT_LATCH_ON, MODE_OFF):
        DetonatorOn();
        return true;

// TURN OFF
      case EVENTID(BUTTON_POWER, EVENT_LATCH_OFF, MODE_ON):
        DetonatorOff();
        return true;

// Play Quote
      case EVENTID(BUTTON_AUX, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_ON):
        if (SFX_quote) {
          if (GetWavPlayerPlaying(&SFX_quote)) return false;  // Simple prevention of quote overlap
          hybrid_font.PlayCommon(&SFX_quote);
        }
        return true;

// Change Preset / Start Countdown Timer
      case EVENTID(BUTTON_AUX, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_ON):
      case EVENTID(BUTTON_NONE, EVENT_TWIST, MODE_ON):
        if (CountdownActive()) { PVLOG_NORMAL << "**** TOO LATE!! RUN!!!\n"; return false; }
        if (armed_) {
          PVLOG_NORMAL << "**** Start Countdown Timer\n";
          Detonate();
        } else {
          SetMute(false);
          FusorPreset();
        }
        return true;

// Arm / Disarm
      case EVENTID(BUTTON_AUX, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_ON):
      case EVENTID(BUTTON_NONE, EVENT_SWING, MODE_ON):
        if (CountdownActive()) { PVLOG_NORMAL << "**** TOO LATE!! RUN!!!\n"; return false; }
        if (!armed_) {
          BeginArm();
        } else {
          Disarm();
        }
        return true;

// Start Or Stop Track
      case EVENTID(BUTTON_AUX, EVENT_FIRST_HELD_MEDIUM, MODE_ON):
        PVLOG_NORMAL << "** Track playback Toggled\n";
        PlayStopTrack();
        return true;

// Next Track
      case EVENTID(BUTTON_AUX, EVENT_FOURTH_CLICK_SHORT, MODE_ON):
        NextTrack();
        return true;

// Clash to Boom (only if Armed)
      case EVENTID(BUTTON_NONE, EVENT_CLASH, MODE_ON):
      case EVENTID(BUTTON_NONE, EVENT_STAB, MODE_ON):
        if (armed_) {
          Detonate(0);
        }
        return true;

// Battery Level
#ifdef SPOKEN_BATTERY_LEVEL
      case EVENTID(BUTTON_AUX, EVENT_SECOND_HELD_MEDIUM, MODE_ON):
        if (!armed_) FusorBatteryLevel();
        return true;
#endif

// Toggle Explosion Animation
      case EVENTID(BUTTON_AUX, EVENT_FOURTH_HELD_MEDIUM, MODE_ON):
        show_detonation_ = !show_detonation_;
        if (SFX_mnum) {
          show_detonation_ ? sound_library_v2.SayEnabled() : sound_library_.SayDisabled();
          PVLOG_NORMAL << "+++++ " << (show_detonation_ ? "" : "DON'T ") << "show_detonation_\n";
        } else {
          beeper.Beep(0.5, show_detonation_ ? 3000 : 1000);
        }
        return true;

    }  // switch (EVENTID)
    return false;
  }  // Event2

    RefPtr<BufferedWavPlayer> wav_player;
  RefPtr<BufferedWavPlayer> track_player_;
  char track_[128] = "";

private:
  DelayTimer mute_all_delay_timer_;
  NextAction next_action_       = NEXT_ACTION_NOTHING;
  uint32_t time_base_           = 0;            // from original detonator.h
  uint32_t next_event_time_     = 0;            // from original detonator.h
  bool armed_                   = false;        // once armed_, it can go boom with clash
  bool show_detonation_ = true;
}; // class DetonatorBCButtons

#endif // PROPS_DETONATOR_BC_BUTTONS_H