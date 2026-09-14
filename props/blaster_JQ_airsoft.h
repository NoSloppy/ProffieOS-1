/*
  blaster_JQ_airsoft.h prop file - Brian Conner 2026

  http://fredrik.hubbe.net/lightsaber/proffieos.html
  Copyright (c) 2016-2023 Fredrik Hubinette
  Fredrik Hubinette, Fernando da Rosa, Brian Conner, Matthew McGeary,
  Scott Weber and Alejandro Belluscio.
  Distributed under the terms of the GNU General Public License v3.
  http://www.gnu.org/licenses/

-------------------------------------------------------------------------------
Defines for use in the config file:
  #define BLASTER_DEFAULT_MODE          - Sets the mode at startup MODE_KILL|MODE_AUTO. Defaults to MODE_KILL.
  #define BLASTER_SHOTS_UNTIL_EMPTY 15  - Whatever number, not defined = unlimited shots.
  #define BLASTER_JAM_PERCENTAGE        - Range 0-100 percent. If this is not defined, random from 0-100%.
  #define COLOR_CHANGE_DIRECT           - Simply entering Color Change Mode will select the next color in the list and exit Color Change Mode.
-------------------------------------------------------------------------------

*Dual Buttons*
- Buttons: FIRE and MODE
  This is the "stock" configuration.
  Weapon will always start on the default mode (define with BLASTER_DEFAULT_MODE, KILL is default).
  The blaster is ON whenever power is applied.

    Fire                      - 1x Click FIRE.
    Switch MODE               - 1x click MODE.
    Play Force Effect         - 2x click MODE.
    Start/Stop Track          - 3x click MODE.
    Color Change              - 4x click and Hold MODE (cycle through color list one at a time)
                                Colors at start are Preset defaults, followed by Red, Blue, Green, White, ElectricViolet, Yellow, and Orange.
    Next Preset               - 1x Click AND Hold MODE until preset changes.
    Previous Preset           - 2x click and Hold MODE until preset changes.

-------------------------------------------------------------------------------
* PROP SOUNDS *
This prop manages the following sounds.
-------------------------------------------------------------------------------

bgnauto.wav     Played when auto fire starts.
auto.wav        Played while auto fire is going.
endauto.wav     Played when auto fire ends.
blast.wav       Is the semi-automatic fire sound. You can have as many as you want.
boot.wav        Played when ProffieOS boots up.
empty.wav       Sound when the weapon is out of rounds.
font.wav        Name of the preset.
full.wav        Sound made when the weapon is full of ammo.
hum.wav         Constant sound looping while not firing.
jam.wav         Sound made when the weapon jamed.
unjam.wav       Sound made when unjamming the blaster.
plioff.wav      Played while retracting the PLI bargraph.
plion.wav       Played while extending the PLI bargraph.
range.wav       Sounds of increasing weapon range/power.
mdkill.wav      Sound made when switching to KILL mode
mdauto.wav      Sound made when switching to AUTO mode
mode.wav        Fallback sound used when switching mode if none of the 3 above exist.
                  If no mode sounds are present at all, Talkie will speak the mode (if not disabled).
*/

#ifndef PROPS_BLASTER_JQ_AIRSOFT_H
#define PROPS_BLASTER_JQ_AIRSOFT_H

#define PROP_HAS_GETBLASTERMODE

#ifndef BLASTER_DEFAULT_MODE
#define BLASTER_DEFAULT_MODE MODE_KILL
#endif

#include "blaster.h"

#define PROP_TYPE BlasterJQAirsoft
#define PROP_HAS_BULLET_COUNT

// For mode sounds, specific "mdkill" and "mdauto" sound files may be used.
// If just a single "mode" sound for all switches exists, that will be used.
// If no mode sounds exist in the font, a talkie version will speak the mode on switching.
class BlasterJQAirsoft : public Blaster {
public:
  BlasterJQAirsoft() : Blaster() {}
  const char* name() override { return "BlasterJQAirsoft"; }

  enum BlasterMode {
    MODE_KILL,
    MODE_AUTO
  };

BlasterMode blaster_mode = BLASTER_DEFAULT_MODE;

#ifdef BLASTER_SHOTS_UNTIL_EMPTY
  const int max_shots_ = BLASTER_SHOTS_UNTIL_EMPTY;
#else
  const int max_shots_ = -1;
#endif

  int GetBlasterMode() const {
    return blaster_mode;
  }

  virtual void SetBlasterMode(BlasterMode to_mode) {
    if (!auto_firing_) {
      blaster_mode = to_mode;
      SaberBase::DoEffect(EFFECT_MODE, 0);
    }
  }

  virtual void NextBlasterMode() {
    switch(blaster_mode) {
      case MODE_KILL:
        SetBlasterMode(MODE_AUTO);
        return;
      case MODE_AUTO:
        SetBlasterMode(MODE_KILL);
        return;
    }
  }

  bool CheckEmpty() const {
    return max_shots_ != -1 && shots_fired_ >= max_shots_;
  }

  int GetBulletCount() {
    return max_shots_ - shots_fired_;
  }

  virtual bool DoEmpty() {
    if (CheckEmpty()) {
      SaberBase::DoEffect(EFFECT_EMPTY, 0);  // Trigger the empty effect
      return true;
    }
    return false;
  }

  virtual bool CheckJam(int percent) {
    int random = rand() % 100;
    return random < percent;
  }

  bool DoJam() {
#if defined(ENABLE_MOTION) && defined(BLASTER_JAM_PERCENTAGE)
    // If we're already jammed then we don't need to recheck. If we're not jammed then check if we just jammed.
    is_jammed_ = is_jammed_ ? true : CheckJam(BLASTER_JAM_PERCENTAGE);

    if (is_jammed_) {
      SaberBase::DoEffect(EFFECT_JAM, 0);
      return true;
    } else {
      return false;
    }
#else
    return false;
#endif
  }

  virtual void DoKill() {
    SFX_blast.Select(-1);
    SaberBase::DoEffect(EFFECT_FIRE, 0);
    shots_fired_++;
  }

  virtual void DoAutoFire() {
    SelectAutoFirePair(); // Set up the auto-fire pairing if the font suits it
    SaberBase::SetLockup(LOCKUP_AUTOFIRE);
    SaberBase::DoBeginLockup();
    auto_firing_ = true;
  }

  virtual void Fire() {
    if (DoEmpty()) return;

    switch (blaster_mode) {
      case MODE_KILL:
        DoKill();
        break;
      case MODE_AUTO:
        DoAutoFire();
        break;
    }
  }

  virtual void SelectAutoFirePair() {
    if (!SFX_auto.files_found() || !SFX_blast.files_found()) return;

    int autoCount = SFX_auto.files_found();
    int blastCount = SFX_blast.files_found();
    int pairSelection;

    // If we don't have a matched pair of autos and blasts, then don't override the sequence to get a matched pair.
    if (autoCount == blastCount) {
        pairSelection = rand() % autoCount;
        SFX_auto.Select(pairSelection);
        SFX_blast.Select(pairSelection);
    }
  }

  // Pull in parent's SetPreset, but turn the blaster on.
  void SetPreset(int preset_num, bool announce) override {
    PropBase::SetPreset(preset_num, announce);
    if (!SaberBase::IsOn()) {
      On();
    }
  }

  // Self-destruct pulled from Detonator. Inherit prop and add PollNextAction() to their loop function.
  // BEGINING of Detonator Code.
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

  virtual void PollNextAction() {
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

    virtual void selfDestruct() {
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
// END of Detonator Code.

  // Make clash do nothing except unjam if jammed.
  void Clash(bool stab, float strength) override {
    if (is_jammed_) {
      is_jammed_ = false;
      SaberBase::DoEffect(EFFECT_UNJAM, 0);
    }
  }

  // Make swings do nothing
  void DoMotion(const Vec3& motion, bool clear) override {
    PropBase::DoMotion(Vec3(0), clear);
  }

  bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override {
    switch (EVENTID(button, event, modifiers)) {

      case EVENTID(BUTTON_FIRE, EVENT_PRESSED, MODE_ON):
        Fire();
        return true;

      case EVENTID(BUTTON_FIRE, EVENT_RELEASED, MODE_ON):
        if (blaster_mode == MODE_AUTO) {
          if (SaberBase::Lockup()) {
            SaberBase::DoEndLockup();
            SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
            auto_firing_ = false;
          }
        }
        return true;

      case EVENTID(BUTTON_MODE_SELECT, EVENT_FIRST_SAVED_CLICK_SHORT, MODE_ON):
        NextBlasterMode();
        return true;

     case EVENTID(BUTTON_MODE_SELECT, EVENT_SECOND_SAVED_CLICK_SHORT, MODE_ON):
        if (GetWavPlayerPlaying(&SFX_force)) return false;  // Simple prevention of force overlap
        SaberBase::DoForce();
        return true;

      case EVENTID(BUTTON_MODE_SELECT, EVENT_THIRD_SAVED_CLICK_SHORT, MODE_ON):
        StartOrStopTrack();
        return true;

      case EVENTID(BUTTON_MODE_SELECT, EVENT_FOURTH_HELD_MEDIUM, MODE_ON):
        ToggleColorChangeMode();
        return true;

      case EVENTID(BUTTON_MODE_SELECT, EVENT_HELD_MEDIUM, MODE_ON):
      case EVENTID(BUTTON_MODE_SELECT, EVENT_HELD_MEDIUM, MODE_OFF):
        Off();
        next_preset();
        return true;

      case EVENTID(BUTTON_MODE_SELECT, EVENT_SECOND_HELD_MEDIUM, MODE_ON):
      case EVENTID(BUTTON_MODE_SELECT, EVENT_SECOND_HELD_MEDIUM, MODE_OFF):
        Off();
        previous_preset();
        return true;
    }
    return false;
  }

   // Blaster effects, auto fire is handled by begin/end lockup
  void SB_Effect(EffectType effect, EffectLocation location) override {
    switch (effect) {
      default: return;

      case EFFECT_FIRE:     hybrid_font.PlayCommon(&SFX_blast);   return;
      case EFFECT_MODE:     SayMode();                            return;
      case EFFECT_RANGE:    hybrid_font.PlayCommon(&SFX_range);   return;
      case EFFECT_EMPTY:    hybrid_font.PlayCommon(&SFX_empty);   return;
      case EFFECT_FULL:     hybrid_font.PlayCommon(&SFX_full);    return;
      case EFFECT_JAM:      hybrid_font.PlayCommon(&SFX_jam);     return;
      case EFFECT_UNJAM:    hybrid_font.PlayCommon(&SFX_unjam);   return;
      case EFFECT_PLI_ON:   hybrid_font.PlayCommon(&SFX_plion);   return;
      case EFFECT_PLI_OFF:  hybrid_font.PlayCommon(&SFX_plioff);  return;

    }
  }

  void SayMode() {
    switch (blaster_mode) {
      case MODE_KILL:
        if (SFX_mdkill) {
          hybrid_font.PlayCommon(&SFX_mdkill);
        } else if (SFX_mode) {
          hybrid_font.PlayCommon(&SFX_mode);
        } else {
#ifndef DISABLE_TALKIE
          talkie.Say(spKILL);
#else
          beeper.Beep(0.05, 2000.0);
#endif
        }
      break;
      case MODE_AUTO:
        if (SFX_mdauto) {
          hybrid_font.PlayCommon(&SFX_mdauto);
        } else if (SFX_mode) {
          hybrid_font.PlayCommon(&SFX_mode);
        } else {
#ifndef DISABLE_TALKIE
          talkie.Say(spAUTOFIRE);
#else
          beeper.Beep(0.05, 2000.0);
#endif
        }
      break;
    }
  }

  bool auto_firing_ = false;
  int shots_fired_ = 0;
  bool is_jammed_ = false;

};
#endif  // PROPS_BLASTER_JQ_AIRSOFT_H

#ifdef PROP_BOTTOM

#define ONCE_PER_BLASTER_EFFECT(X)    \
  X(auto)                             \
  X(mdkill)                           \
  X(mdauto)                           \
  X(blast)                            \
  X(empty)                            \
  X(jam)                              \
  X(destruct)

#ifdef INCLUDE_SSD1306

struct BlasterDisplayConfigFile : public ConfigFile {
  BlasterDisplayConfigFile() { link(&font_config); }
  void iterateVariables(VariableOP *op) override {
    CONFIG_VARIABLE2(ProffieOSFireImageDuration,     300.0f);
    CONFIG_VARIABLE2(ProffieOSModeKillImageDuration, 2000.0f);
    CONFIG_VARIABLE2(ProffieOSModeAutoImageDuration, 2000.0f);

    CONFIG_VARIABLE2(ProffieOSEmptyImageDuration,    1000.0f);
    CONFIG_VARIABLE2(ProffieOSJamImageDuration,      1000.0f);
    CONFIG_VARIABLE2(ProffieOSDestructImageDuration, 10000.0f);
  }

  // for OLED displays, the time a blast.bmp will play
  float ProffieOSFireImageDuration;
  // for OLED displays, the time a mdkill.bmp will play
  float ProffieOSModeKillImageDuration;
  // for OLED displays, the time a mdauto.bmp will play
  float ProffieOSModeAutoImageDuration;

  // for OLED displays, the time a empty.bmp will play
  float ProffieOSEmptyImageDuration;
  // for OLED displays, the time a jam.bmp will play
  float ProffieOSJamImageDuration;
  // for OLED displays, the time a destruct.bmp will play
  float ProffieOSDestructImageDuration;
};


template<typename PREFIX = ByteArray<>>
struct BlasterDisplayEffects  {
  BlasterDisplayEffects() : dummy_(0) ONCE_PER_BLASTER_EFFECT(INIT_IMG) {}
  int dummy_;
  ONCE_PER_BLASTER_EFFECT(DEF_IMG)
};

template<int Width, class col_t, typename PREFIX = ByteArray<>>
class BlasterDisplayController : public StandardDisplayController<Width, col_t, PREFIX> {
public:
  BlasterDisplayEffects<PREFIX> &img_;
  BlasterDisplayConfigFile &font_config;
  BlasterDisplayController() :
    img_(*getPtr<BlasterDisplayEffects<PREFIX>>()),
    font_config(*getPtr<BlasterDisplayConfigFile>()) {
  }

  void DrawScreenText(const char* message, int y, const Glyph* font) override {
    this->display_->DrawText(message, 0, y, font, 0.8f);
  }

  void DrawScreenBatteryBar(const Glyph& bar, float percent) override {
    this->display_->DrawBatteryBar(bar, percent, 8);
  }

  bool ShowVoltage() override {
    return false;
  }

  void ShowDefault(bool ignore_lockup = false) override {
    if (SaberBase::IsOn() &&
        SaberBase::Lockup() == SaberBase::LOCKUP_AUTOFIRE &&
        img_.IMG_auto &&
        !ignore_lockup) {
      this->SetFile(&img_.IMG_auto, 3600000.0);
      return;
    }
    StandardDisplayController<Width, col_t, PREFIX>::ShowDefault(ignore_lockup);
  }

  void SB_Effect2(EffectType effect, EffectLocation location) override {
    switch (effect) {
     case EFFECT_MODE:
        switch (prop.GetBlasterMode()) {
          case PROP_TYPE::MODE_KILL:
            this->ShowFileWithSoundLength(&img_.IMG_mdkill, font_config.ProffieOSModeKillImageDuration);
            break;
          case PROP_TYPE::MODE_AUTO:
            this->ShowFileWithSoundLength(&img_.IMG_mdauto, font_config.ProffieOSModeAutoImageDuration);
            break;
          default:
            break;
        }
        break;
      case EFFECT_FIRE:
        this->ShowFileWithSoundLength(&img_.IMG_blast,   font_config.ProffieOSFireImageDuration);
        break;
      case EFFECT_EMPTY:
        this->ShowFileWithSoundLength(&img_.IMG_empty,   font_config.ProffieOSEmptyImageDuration);
        break;
      case EFFECT_JAM:
        this->ShowFileWithSoundLength(&img_.IMG_jam,     font_config.ProffieOSJamImageDuration);
        break;
      default:
        StandardDisplayController<Width, col_t, PREFIX>::SB_Effect2(effect, location);
    }
  }

  void SB_Off2(typename StandardDisplayController<Width, col_t, PREFIX>::OffType offtype, EffectLocation location) override {
    if (offtype == StandardDisplayController<Width, col_t, PREFIX>::OFF_BLAST) {
      this->ShowFileWithSoundLength(&img_.IMG_destruct, font_config.ProffieOSDestructImageDuration);
    } else {
      StandardDisplayController<Width, col_t, PREFIX>::SB_Off2(offtype, location);
    }
  }
};

class MyDisplayController : public BlasterDisplayController<64, uint64_t> {
public:
  int MessageY() override {
    return 31;
  }

  int MessageTwoLineY() override {
    return 23;
  }
};

class MySSD1306 : public SSD1306Template<64, uint64_t> {
public:
  using SSD1306Template<64, uint64_t>::SSD1306Template;

  int HardwareHeight() override {
    return 48;
  }
};

#endif  // INCLUDE_SSD1306

#undef ONCE_PER_BLASTER_EFFECT

#endif  // PROP_BOTTOM
