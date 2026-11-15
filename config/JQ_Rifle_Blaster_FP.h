/* JQ_Rifle_Blaster_FP.h - JQ6 - faster autofire shots all around, and no barrell cooldown effect (left commented for option)

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
#define SAVE_PRESET
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

  StylePtr<Layers<Black,
    TransitionEffectL<TrConcat<TrInstant,
      AlphaL<ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Bump<Int<1>,Int<2000>>>,TrFade<30>,Black,
      TrSparkX<ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Int<100>,Int<100>,Int<1>>>,EFFECT_FIRE>,

    LockupTrL<TransitionLoop<Black,TrConcat<TrInstant,Black,TrDelay<40>,
      AlphaL<RandomFlicker<ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Black>,Bump<Int<1>,Int<2000>>>,TrDelay<20>,
      TrSparkX<ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Int<100>,Int<100>,Int<1>>>>,
      TrInstant,
      TrConcat<TrInstant,
        AlphaL<RandomFlicker<ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Black>,Bump<Int<1>,Int<2000>>>,
        TrSparkX<ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Int<100>,Int<50>,Int<1>>>,
    SaberBase::LOCKUP_AUTOFIRE>

{ "01-E11;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 1 - custom Rgb<187,255,0> first
  StylePtr<Layers<
    Black,
    /* SEMI */
    TransitionEffectL<TrConcat<TrInstant,
      AlphaL<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Bump<Int<1>,Int<2000>>>,TrFade<30>,Black,
      TrSparkX<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Int<100>,Int<100>,Int<1>>>,EFFECT_FIRE>,
    /* AUTO */
    LockupTrL<TransitionLoop<Black,TrConcat<TrInstant,Black,TrDelay<40>,
      AlphaL<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Bump<Int<1>,Int<2000>>>,TrDelay<20>,
      TrSparkX<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Int<100>,Int<90>,Int<1>>>>,
      TrInstant,
      TrConcat<TrInstant,
        AlphaL<RandomFlicker<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Black>,Bump<Int<1>,Int<2000>>>,
        TrSparkX<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Int<100>,Int<50>,Int<1>>>,
    SaberBase::LOCKUP_AUTOFIRE>
  >>(),
"FP1\ne-11"},

//  *******************

{ "02-Aliens;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 2 (muzzle flash)- White first
  StylePtr<Layers<Black,
    /* SEMI */
    TransitionEffectL<TrConcat<TrInstant,
      /* Barrel */
      AlphaL<ColorChange<TrInstant,White,ElectricViolet,Yellow,Orange,Red,Blue,Green>,Bump<Int<32000>,Int<45000>>>,TrDelay<50>,TrFade<50>
      /* Optional cool down effect */
      //,AlphaL<Mix<Int<30000>,OrangeRed,Black>,Bump<Int<32000>,Int<45000>>>,TrFade<150>
      >,EFFECT_FIRE>,
    /* AUTO */
    LockupTrL<Layers<
      /* Barrel */
      TransitionLoop<Black,TrConcat<TrWipe<40>,AlphaL<ColorChange<TrInstant,White,ElectricViolet,Yellow,Orange,Red,Blue,Green>,Bump<Int<32000>,Int<45000>>>,TrWipe<40>>>>,TrInstant,
      /* End autofire effect */
      TrInstant,
      /* Optional cool down effect */
      // TrConcat<TrInstant,AlphaL<Mix<Int<28000>,Yellow,Black>,Bump<Int<32000>,Int<45000>>>,TrFade<100>,AlphaL<Mix<Int<30000>,OrangeRed,Black>,Bump<Int<32000>,Int<45000>>>,TrFade<150>>,
      SaberBase::LOCKUP_AUTOFIRE>
  >>(),
"FP2\naliens"},

//  *******************

{ "03-Robocop;ProffieOS_V2_Voicepack_English_A/common", "",
/*  Style 3 - (muzzle flash) DarkOrange first */
  StylePtr<Layers<Black,
    /* SEMI */
    TransitionEffectL<TrConcat<TrInstant,AlphaL<ColorChange<TrInstant,DarkOrange,Red,Blue,Green,White,ElectricViolet,Yellow>,Bump<Int<32000>,Int<45000>>>,TrDelay<50>,TrFade<50>>,EFFECT_FIRE>,
    /* AUTO */
    LockupTrL<TransitionLoop<Black,TrConcat<TrWipe<40>,AlphaL<
      ColorChange<TrInstant,DarkOrange,Red,Blue,Green,White,ElectricViolet,Yellow>,Bump<Int<32000>,Int<35000>>>,TrWipe<40>>>,TrInstant,TrInstant,SaberBase::LOCKUP_AUTOFIRE>
  >>(),
"FP3\nrobocop"},

//  *******************

{ "04-Terminator;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 1 - Orange first
  StylePtr<Layers<Black,
    /* SEMI */
    TransitionEffectL<TrConcat<TrInstant,
      AlphaL<ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow>,Bump<Int<1>,Int<2000>>>,TrFade<30>,Black,
      TrSparkX<ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow>,Int<100>,Int<100>,Int<1>>,TrDelay<130>>,EFFECT_FIRE>,
    /* AUTO */
    LockupTrL<TransitionLoop<Black,TrConcat<TrInstant,
      AlphaL<RandomFlicker<ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow>,Black>,Bump<Int<1>,Int<2000>>>,TrDelay<20>,
      TrSparkX<ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow>,Int<100>,Int<100>,Int<1>>>>,
      TrInstant,
      TrConcat<TrInstant,
        AlphaL<RandomFlicker<ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow>,Black>,Bump<Int<1>,Int<2000>>>,
        TrSparkX<ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow>,Int<100>,Int<80>,Int<1>>>,
    SaberBase::LOCKUP_AUTOFIRE>
  >>(),
"FP4\nt-800"},

//  *******************

{ "05-5th;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 2 (muzzle flash)- Purple first
  StylePtr<Layers<Black,
    TransitionEffectL<TrConcat<TrInstant,
      RandomFlicker<AlphaL<ColorChange<TrInstant,ElectricViolet,Yellow,Orange,Red,Blue,Green,White>,Bump<Int<32000>,Int<35000>>>,Black>,TrDelay<110>,TrFade<30>>,EFFECT_FIRE>,
    LockupTrL<Layers<
      TransitionLoop<Black,TrConcat<TrWipe<40>,
      AlphaL<ColorChange<TrInstant,ElectricViolet,Yellow,Orange,Red,Blue,Green,White>,Bump<Int<32000>,Int<35000>>>,TrWipe<40>>>>,TrInstant,TrConcat<TrInstant,AlphaL<Mix<Int<3000>,Black,OrangeRed>,Bump<Int<32000>,Int<35000>>>,TrFade<100>>,SaberBase::LOCKUP_AUTOFIRE>
  >>(),
"FP2\n5th"},

//  *******************

{ "06-TNG;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 1 - Blue first
  StylePtr<Layers<Black,
    TransitionEffectL<TrConcat<TrInstant,
      AlphaL<ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Bump<Int<1>,Int<2000>>>,TrFade<30>,Black,
      TrSparkX<ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Int<100>,Int<100>,Int<1>>>,EFFECT_FIRE>,

    LockupTrL<TransitionLoop<Black,TrConcat<TrInstant,Black,TrDelay<40>,
      AlphaL<RandomFlicker<ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Black>,Bump<Int<1>,Int<2000>>>,TrDelay<20>,
      TrSparkX<ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Int<100>,Int<100>,Int<1>>>>,
      TrInstant,
      TrConcat<TrInstant,
        AlphaL<RandomFlicker<ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Black>,Bump<Int<1>,Int<2000>>>,
        TrSparkX<ColorChange<TrInstant,Blue,Green,White,ElectricViolet,Yellow,Orange,Red>,Int<100>,Int<50>,Int<1>>>,
    SaberBase::LOCKUP_AUTOFIRE>
   >>(),
"FP4\ntng"},

//  *******************

{ "07-SciFi;ProffieOS_V2_Voicepack_English_A/common", "",
// Style 3 - Green first
  StylePtr<Layers<
    Black,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<ColorChange<TrInstant,Green,White,ElectricViolet,Yellow,Orange,Red,Blue>,Bump<Int<1>,Int<3000>>>,TrFade<250>>,EFFECT_FIRE>,
    TransitionEffectL<TrJoin<
      TrConcat<TrDelay<100>,AlphaL<StaticFire<ColorChange<TrInstant,Green,White,ElectricViolet,Yellow,Orange,Red,Blue>,ColorChange<TrInstant,Yellow,Red,Blue,Green,White,ElectricViolet,Orange>,0,3,0,2000,0>,Bump<Int<32000>,Int<25000>>>,TrWipe<150>>,
      TrSparkX<ColorChange<TrInstant,Green,White,ElectricViolet,Yellow,Orange,Red,Blue>,Int<100>,Int<150>,Int<1>>>,EFFECT_FIRE>,
    LockupTrL<Layers<
      TransitionLoopL<TrConcat<TrWipe<50>,ColorChange<TrInstant,Green,White,ElectricViolet,Yellow,Orange,Red,Blue>,TrWipe<90>>>,
      TransitionLoopL<TrConcat<TrInstant,AlphaL<ColorChange<TrInstant,Green,White,ElectricViolet,Yellow,Orange,Red,Blue>,Bump<Int<0>,Int<3000>>>,TrFade<200>>>>,
      TrInstant,
      TrJoin<
        TrConcat<TrInstant,AlphaL<Mix<Int<16384>,ColorChange<TrInstant,Green,White,ElectricViolet,Yellow,Orange,Red,Blue>,Black>,Bump<Int<32768>,Int<60000>>>,TrFade<100>>,
        TrWipeX<Int<100>>,
        TrSparkX<ColorChange<TrInstant,Green,White,ElectricViolet,Yellow,Orange,Red,Blue>,Int<100>,Int<100>,Int<1>>>,
    SaberBase::LOCKUP_AUTOFIRE>
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
class MyDisplayController : public BlasterDisplayController<64, uint64_t> {
public:
  int NumberOfTextLines() override {
    // User's desired number to display - scaling is used to accommodate.
    // Over-doing it will make things illegible.
    return 3;  
  }
};

class MySSD1306 : public SSD1306Template<64, uint64_t> {
public:
  using SSD1306Template<64, uint64_t>::SSD1306Template;

  int HardwareHeight() override {
    return 48;
  }
};

MyDisplayController display_controller;
MySSD1306 display(&display_controller);
#endif
