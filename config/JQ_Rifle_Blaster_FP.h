/* JQ_Rifle_Blaster_FP.h

Controls:
    Fire                      - 1x Click FIRE.
    Switch MODE               - 1x click MODE.
    Play Force Effect         - 2x click MODE.
    Start/Stop Track          - 3x click MODE.
    Color Change              - 4x click and Hold MODE (cycle through color list one at a time)
                                Colors at start are Preset defaults, followed by Red, Blue, Green, White, ElectricViolet, Yellow, and Orange.
    Next Preset               - 1x Click AND Hold MODE until preset changes.
    Previous Preset           - 2x click and Hold MODE until preset changes.
*/

#ifdef CONFIG_TOP
#include "proffieboard_v2_config.h"
#define NUM_BLADES 1
#define NUM_BUTTONS 2
#define VOLUME 30
const unsigned int maxLedsPerStrip = 144;
#define CLASH_THRESHOLD_G 1.0
#define MOUNT_SD_SETTING
#define COLOR_CHANGE_DIRECT

#define BLASTER_DEFAULT_MODE MODE_AUTO
//  #define BLASTER_SHOTS_UNTIL_EMPTY 300
//  #define BLASTER_JAM_PERCENTAGE 0
#define INCLUDE_SSD1306
#endif

#ifdef CONFIG_PROP
#include "../props/blaster_JQ_airsoft.h"
#endif

//  ******************* ColorChange Color list: *Preset's Default Color*, Red, Blue, Green, White, Purple, Yellow, and Orange.
//  *******************
//  *******************
#ifdef CONFIG_PRESETS
Preset presets[] = {

{ "DL44;ProffieOS_V2_Voicepack_English_A/common", "tracks/baroque.wav",
   StylePtr<Layers<
     Black,
     TransitionEffectL<TrConcat<TrInstant,Layers<
       AlphaL<RandomFlicker<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Black>,Bump<Int<1>>>,
       TransitionEffectL<TrConcat<TrSparkX<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Int<100>,Int<170>,Int<1>>,TrInstant>,EFFECT_FIRE>>,TrFade<250>,Black,TrInstant>,EFFECT_FIRE>,
     LockupTrL<Layers<
       TransitionLoop<Black,TrSparkX<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Int<100>,Int<170>,Int<1>>>,
       AlphaL<RandomFlicker<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Black>,Bump<Int<1>>>>,TrInstant,TrConcat<TrInstant,AlphaL<RandomFlicker<ColorChange<TrInstant,Rgb<187,255,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Black>,Bump<Int<1>>>,TrFade<250>>,SaberBase::LOCKUP_AUTOFIRE>
   >>(),
"FP1_E-11"},


//  *******************


{ "blaster1;ProffieOS_V2_Voicepack_English_A/common", "tracks/laptinek.wav",
   StylePtr<Layers<
     Black,
     TransitionEffectL<TrConcat<TrInstant,AlphaL<ColorChange<TrInstant,White,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,LinearSectionF<Int<27307>,Int<10922>>>,TrFade<200>>,EFFECT_FIRE>,
     LockupTrL<Layers<
       TransitionLoop<Black,TrConcat<TrWipe<100>,AlphaL<ColorChange<TrInstant,White,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,LinearSectionF<Int<27307>,Int<10922>>>,TrWipe<100>>>>,TrInstant,TrConcat<TrInstant,AlphaL<Mix<Int<3000>,Black,OrangeRed>,LinearSectionF<Int<27307>,Int<10922>>>,TrSmoothFade<1200>>,SaberBase::LOCKUP_AUTOFIRE>
   >>(),
"FP2-Aliens"},


//  *******************


{ "blaster1;ProffieOS_V2_Voicepack_English_A/common", "tracks/bargaining.wav",
   StylePtr<Layers<
     Black,
     TransitionEffectL<TrConcat<TrInstant,AlphaL<ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Bump<Int<-5000>,Int<25000>>>,TrFade<250>>,EFFECT_FIRE>,
     TransitionEffectL<TrJoin<TrConcat<TrInstant,AlphaL<StaticFire<ColorChange<TrInstant,DarkOrange,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,ColorChange<TrInstant,Yellow,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,0,3,0,2000,0>,Bump<Int<32000>,Int<25000>>>,TrWipe<300>>,TrSparkX<StaticFire<ColorChange<TrInstant,DarkOrange,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,ColorChange<TrInstant,Yellow,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,0,2,0,2000,0>,Int<100>,Int<150>,Int<1>>>,EFFECT_FIRE>,
     LockupTrL<Layers<
       TransitionLoopL<TrConcat<TrWipe<50>,StaticFire<ColorChange<TrInstant,OrangeRed,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,ColorChange<TrInstant,Yellow,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,0,3,0,2000,0>,TrWipe<150>>>,
       TransitionLoopL<TrConcat<TrInstant,AlphaL<ColorChange<TrInstant,Orange,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Bump<Int<0>,Int<25000>>>,TrFade<200>>>>,TrInstant,TrJoin<TrConcat<TrInstant,AlphaL<ColorChange<TrInstant,Rgb<50,0,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Bump<Int<32768>,Int<60000>>>,TrFade<400>>,TrWipeX<Int<400>>,TrWaveX<ColorChange<TrInstant,Rgb<50,0,0>,Red,Blue,Green,White,ElectricViolet,Yellow,Orange>,Int<1800>,Int<40>,Int<400>,Int<5000>>>,SaberBase::LOCKUP_AUTOFIRE>
   >>(),
"FP3_Spiker"},

};
//  *******************
//  *******************
//  *******************
BladeConfig blades[] = {
{ 0,
//  Main Blade:
   WS281XBladePtr<60, bladePin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3>>(),
   CONFIGARRAY(presets) },
};
#endif

#ifdef CONFIG_BUTTONS
Button FireButton(BUTTON_FIRE, powerButtonPin, "fire");
Button ModeButton(BUTTON_MODE_SELECT, auxPin, "modeselect");
#endif

class MyDisplayController : public BlasterDisplayController<64, uint64_t> {
public:
  int MessageY() override {
    return 31;
  }

  int MessageTwoLineY() override {
    return 23;
  }
};

#ifdef CONFIG_BOTTOM
MyDisplayController display_controller;
SSD1306Template<64, uint64_t> display(&display_controller);
#endif
