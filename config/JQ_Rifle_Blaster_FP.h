/* JQ_Rifle_Blaster_FP.h

Controls:
    Fire                      - 1x Click FIRE.
    Switch MODE               - 1x click MODE.
    Play Force Effect         - 2x click MODE.
    Start/Stop Track          - 3x click MODE.
    Next Track                - 3x click and Hold MODE (auto-plays next track, when either playing OR stopped)
                                * Note - Tracks should be stored in either <font>/tracks/*.wav, or in common/tracks/*.wav.
                                         and will be selected in alphabetical order.
    Color Change              - 4x click and Hold MODE (cycle through color list one at a time)
                                Colors at start are Preset defaults, followed by Red, Blue, Green, White, ElectricViolet, Yellow, and Orange.
    Next Preset               - 1x Click AND Hold MODE until preset changes.
    Previous Preset           - 2x click and Hold MODE until preset changes.
*/

#ifdef CONFIG_TOP
#include "proffieboard_v2_config.h"
#define NUM_BLADES 1
#define NUM_BUTTONS 2
#define VOLUME 2000
const unsigned int maxLedsPerStrip = 144;
#define CLASH_THRESHOLD_G 1.0
#define MOUNT_SD_SETTING
#define COLOR_CHANGE_DIRECT
#define SAVE_COLOR_CHANGE

#define BLASTER_DEFAULT_MODE MODE_AUTO
//  #define BLASTER_SHOTS_UNTIL_EMPTY 300
//  #define BLASTER_JAM_PERCENTAGE 0
#define INCLUDE_SSD1306
// #define CONFIG_STARTUP_DELAY 3000
#define ENABLE_DEVELOPER_COMMANDS
#endif

#ifdef CONFIG_PROP
#include "../props/blaster_JQ_airsoft.h"
#endif

// ColorChange Color list: *Preset's custom Default Color is first if present*, otherwise cycles-> Red, Blue, Green, White, Purple, Yellow, and Orange.

#ifdef CONFIG_PRESETS
Preset presets[] = {

{ "01-E11;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 1 - custom Rgb<187,255,0> first
  StylePtr<Layers<
    Black,
    TransitionEffectL<TrConcat<TrInstant,Layers<
      AlphaL<RandomFlicker<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Black>,Bump<Int<1>>>,
      TransitionEffectL<TrConcat<TrSparkX<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Int<100>,Int<170>,Int<1>>,TrInstant>,EFFECT_FIRE>>,TrFade<250>,Black,TrInstant>,EFFECT_FIRE>,
    LockupTrL<Layers<
      TransitionLoop<Black,TrSparkX<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Int<100>,Int<170>,Int<1>>>,
      AlphaL<RandomFlicker<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Black>,Bump<Int<1>>>>,TrInstant,TrConcat<TrInstant,AlphaL<RandomFlicker<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Black>,Bump<Int<1>>>,TrFade<250>>,SaberBase::LOCKUP_AUTOFIRE>
  >>(),
"FP1\ne-11"},

//  *******************

{ "02-Aliens;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 2 (muzzle flash)- White first
  StylePtr<Layers<
    Black,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<ColorChange<TrInstant,White,ElectricViolet,Yellow,Orange,Red,Blue,Green>,LinearSectionF<Int<27307>,Int<10922>>>,TrFade<200>,AlphaL<Mix<Int<3000>,Black,OrangeRed>,LinearSectionF<Int<27307>,Int<10922>>>,TrSmoothFade<300>>,EFFECT_FIRE>,
    LockupTrL<Layers<
      TransitionLoop<Black,TrConcat<TrWipe<100>,AlphaL<ColorChange<TrInstant,White,ElectricViolet,Yellow,Orange,Red,Blue,Green>,LinearSectionF<Int<27307>,Int<10922>>>,TrWipe<100>>>>,TrInstant,TrConcat<TrInstant,AlphaL<Mix<Int<3000>,Black,OrangeRed>,LinearSectionF<Int<27307>,Int<10922>>>,TrSmoothFade<800>>,SaberBase::LOCKUP_AUTOFIRE>
  >>(),
"FP2\naliens"},

//  *******************

{ "03-Robocop;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 3 - Standard Flame colors first
  StylePtr<Layers<
    Black,
// SEMI
    TransitionEffectL<TrJoin<TrConcat<TrInstant,
      // Muzzle
      AlphaL<StaticFire<
          // Warm color
          ColorChange<TrInstant,DarkOrange,Red,Blue,Green,White,ElectricViolet,Yellow>,
          // Hot color
          ColorChange<TrInstant,Yellow,Red,Blue,Green,White,ElectricViolet,Orange>,0,3,0,2000,0>,Bump<Int<32000>,Int<25000>>>,TrWipe<300>>,
      // Barrel
      TrSparkX<StaticFire<
          // Warm color
          ColorChange<TrInstant,DarkOrange,Red,Blue,Green,White,ElectricViolet,Yellow>,
          // Hot color
          ColorChange<TrInstant,Yellow,Red,Blue,Green,White,ElectricViolet,Orange>,0,2,0,2000,0>,Int<100>,Int<150>,Int<1>>>,EFFECT_FIRE>,
      // Emitter
      TransitionEffectL<TrConcat<TrInstant,AlphaL<
        ColorChange<TrInstant,DarkOrange,Red,Blue,Green,White,ElectricViolet,Yellow>,Bump<Int<-5000>,Int<25000>>>,TrFade<250>>,EFFECT_FIRE>,
// AUTO
    LockupTrL<Layers<
        // Barrel to Muzzle
        TransitionLoopL<TrConcat<TrWipe<50>,StaticFire<
          // Warm color
          ColorChange<TrInstant,OrangeRed,Red,Blue,Green,White,ElectricViolet,Yellow>,
          // Hot color
          ColorChange<TrInstant,Yellow,Red,Blue,Green,White,ElectricViolet,Orange>,0,3,0,2000,0>,TrWipe<150>>>,
        // Emitter
        TransitionLoopL<TrConcat<TrInstant,AlphaL<
          ColorChange<TrInstant,OrangeRed,Red,Blue,Green,White,ElectricViolet,Yellow>,Bump<Int<0>,Int<25000>>>,TrFade<200>>>>,
      // Begin lockup
      TrInstant,
      // End lockup (cool down effect)
      TrJoin<TrConcat<TrInstant,AlphaL<Mix<Int<16384>,
        ColorChange<TrInstant,OrangeRed,Red,Blue,Green,White,ElectricViolet,Yellow>,Black>,Bump<Int<32768>,Int<60000>>>,TrFade<400>>,TrWipeX<Int<400>>, // Muzzle cool followed by dim wave to tip
      TrWaveX<Mix<Int<16384>,
        ColorChange<TrInstant,OrangeRed,Red,Blue,Green,White,ElectricViolet,Yellow>,Black>,Int<1800>,Int<40>,Int<400>,Int<5000>>>,SaberBase::LOCKUP_AUTOFIRE>
  >>(),
"FP3\nrobocop"},

//  *******************

{ "04-Terminator;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 1 - Orange first
  StylePtr<Layers<
    Black,
// SEMI
    TransitionEffectL<TrConcat<TrInstant,Layers<
      // Emitter
      AlphaL<RandomFlicker<
        ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow>,Black>,Bump<Int<1>>>,
      // Barrel
      TransitionEffectL<TrConcat<TrSparkX<
        ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow>,Int<100>,Int<170>,Int<1>>,TrInstant>,EFFECT_FIRE>>,TrFade<250>,Black,TrInstant>,EFFECT_FIRE>,
// AUTO
    LockupTrL<Layers<
      // Barrel
      TransitionLoop<Black,TrSparkX<
        ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow>,Int<100>,Int<170>,Int<1>>>,
      // Emitter
      AlphaL<RandomFlicker<
        ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow>,Black>,Bump<Int<1>>>>,
    // Begin lockup
    TrInstant,
    // End lockup
    TrConcat<TrInstant,
      // Emitter cooldown
      AlphaL<RandomFlicker<
        ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow>,Black>,Bump<Int<1>>>,TrFade<250>>,SaberBase::LOCKUP_AUTOFIRE>
  >>(),
"FP4\nt-800"},

//  *******************

{ "05-5th;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 2 (muzzle flash)- Purple first
  StylePtr<Layers<
    Black,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<
      ColorChange<TrInstant,ElectricViolet,Yellow,Orange,Red,Blue,Green,White>,LinearSectionF<Int<27307>,Int<10922>>>,TrFade<200>>,EFFECT_FIRE>,
    LockupTrL<Layers<
      TransitionLoop<Black,TrConcat<TrWipe<100>,AlphaL<
      ColorChange<TrInstant,ElectricViolet,Yellow,Orange,Red,Blue,Green,White>,LinearSectionF<Int<27307>,Int<10922>>>,TrWipe<100>>>>,TrInstant,
      TrConcat<TrInstant,AlphaL<Mix<Int<3000>,Black,OrangeRed>,LinearSectionF<Int<27307>,Int<10922>>>,TrSmoothFade<400>>,SaberBase::LOCKUP_AUTOFIRE>
  >>(),
"FP2\n5th"},

//  *******************

{ "06-TNG;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 1 - Blue first
   StylePtr<Layers<
     Black,
     TransitionEffectL<TrConcat<TrInstant,Layers<
       AlphaL<RandomFlicker<
       ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Black>,Bump<Int<1>>>,
       TransitionEffectL<TrConcat<TrSparkX<
       ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Int<100>,Int<170>,Int<1>>,TrInstant>,EFFECT_FIRE>>,TrFade<250>,Black,TrInstant>,EFFECT_FIRE>,
     LockupTrL<Layers<
       TransitionLoop<Black,TrSparkX<
       ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Int<100>,Int<170>,Int<1>>>,
       AlphaL<RandomFlicker<
       ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Black>,Bump<Int<1>>>>,TrInstant,TrConcat<TrInstant,AlphaL<RandomFlicker<
       ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Black>,Bump<Int<1>>>,TrFade<250>>,SaberBase::LOCKUP_AUTOFIRE>
   >>(),
"FP4\ntng"},

//  *******************

{ "07-SciFi;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 3 - Green first
   StylePtr<Layers<
     Black,
     TransitionEffectL<TrConcat<TrInstant,AlphaL<
      ColorChange<TrInstant,Green,White,ElectricViolet,Yellow,Orange,Red,Blue>,Bump<Int<-5000>,Int<25000>>>,TrFade<250>>,EFFECT_FIRE>,
     TransitionEffectL<TrJoin<TrConcat<TrInstant,AlphaL<
       StaticFire<
        ColorChange<TrInstant,Green, White,ElectricViolet,Yellow,Orange,Red,           Blue>,
        ColorChange<TrInstant,Yellow,Red,  Blue,          Green, White, ElectricViolet,Orange>,0,3,0,2000,0>,Bump<Int<32000>,Int<25000>>>,TrWipe<300>>,TrSparkX<StaticFire<ColorChange<TrInstant,Green,White,ElectricViolet,Yellow,Orange,Red,Blue>,ColorChange<TrInstant,Yellow,Red,Blue,Green,White,ElectricViolet,Orange>,0,2,0,2000,0>,Int<100>,Int<150>,Int<1>>>,EFFECT_FIRE>,
     LockupTrL<Layers<
       TransitionLoopL<TrConcat<TrWipe<50>,
       StaticFire<Mix<Int<16384>,
        ColorChange<TrInstant,Green, White,ElectricViolet,Yellow,Orange,Red,           Blue>,Black>,
        ColorChange<TrInstant,Yellow,Red,  Blue,          Green, White, ElectricViolet,Orange>,0,3,0,2000,0>,TrWipe<150>>>,
       TransitionLoopL<TrConcat<TrInstant,AlphaL<
        ColorChange<TrInstant,Green, White,ElectricViolet,Yellow,Orange,Red,           Blue>,Bump<Int<0>,Int<25000>>>,TrFade<200>>>>,TrInstant,TrJoin<TrConcat<TrInstant,AlphaL<Mix<Int<16384>,ColorChange<TrInstant,Green,White,ElectricViolet,Yellow,Orange,Red,Blue>,Black>,Bump<Int<32768>,Int<60000>>>,TrFade<400>>,TrWipeX<Int<400>>,TrWaveX<Mix<Int<16384>,ColorChange<TrInstant,Green,White,ElectricViolet,Yellow,Orange,Red,Blue>,Black>,Int<1800>,Int<40>,Int<400>,Int<5000>>>,SaberBase::LOCKUP_AUTOFIRE>
   >>(),
"FP3\nsci fi"},

};

//  *******************

BladeConfig blades[] = {
{ 0,
//  Main Blade:
   WS281XBladePtr<70, bladePin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3>>(),
   CONFIGARRAY(presets),
   "JQ_save"},
};
#endif

#ifdef CONFIG_BUTTONS
Button FireButton(BUTTON_FIRE, powerButtonPin, "fire");
Button ModeButton(BUTTON_MODE_SELECT, auxPin, "modeselect");
#endif

#ifdef CONFIG_BOTTOM
MyDisplayController display_controller;
MySSD1306 display(&display_controller);
#endif
