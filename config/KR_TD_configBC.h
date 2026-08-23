//KR_TD_configBC.h - Created by Brian Conner a.k.a. NoSloppy for KR Sabers' Thermal Detonator run 2026

#ifdef CONFIG_TOP
#include "proffieboard_v2_config.h"
#define NUM_BLADES 2
#define NUM_BUTTONS 2
#define VOLUME 2500
const unsigned int maxLedsPerStrip = 144;
#define CLASH_THRESHOLD_G 2.0
#define MOUNT_SD_SETTING

/* Optional defines - add or remove comment slashes( // ) at the line beginning to activate/deactivate
------------------------------------------------------------------------------------------------------*/
#define DETONATOR_TIMER_DURATION 6.0         // If countdown.wav is used, timer uses the wav file duration instead.
                                             // If this is not actively defined, the default is 6 seconds.
#define SPOKEN_BATTERY_LEVEL                 // Use to have battery level spoken (uses Voicepack sound files). If not defined, High/Mid/Low LED meter only.

#endif

#ifdef CONFIG_PROP
#include "../props/detonator_BC_buttons.h"
#endif

#ifdef CONFIG_PRESETS
Preset presets[] = {

{ "tdmod;ProffieOS_V2_Voicepack_C-3PO/common", "tracks/laptinek.wav",
/* 3 LEDs */
  StylePtr<Layers<
    TransitionLoop<Black,TrConcat<TrInstant,AlphaL<White,LinearSectionF<Int<5461>,Int<10922>>>,TrDelay<424>,AlphaL<White,LinearSectionF<Int<16384>,Int<10922>>>,TrDelay<423>,AlphaL<White,LinearSectionF<Int<27307>,Int<10922>>>,TrDelay<423>>>,
    LockupL<Pulsing<White,Black,755>,Black,Int<32768>,Int<32768>,Int<32768>>,
    TransitionEffectL<TrConcat<TrInstant,Layers<Black,AlphaL<Strobe<Black,White,15,30>,LayerFunctions<LinearSectionF<Int<16384>,Int<10922>>,LinearSectionF<Int<5461>,Int<10922>>>>>,TrDelay<319>>,EFFECT_LOCKUP_BEGIN>,
    /* Countdown Timer = USER1 */
    TransitionEffectL<TrConcat<TrInstant,Mix<Trigger<EFFECT_USER1,Variation,Int<1>,Int<1>>,Pulsing<White,Black,1000>,Pulsing<White,Black,500>,Strobe<Black,White,15,30>>,TrDelayX<Variation>>,EFFECT_USER1>,
    /* Disarm = USER2 */
    TransitionEffectL<TrConcat<TrInstant,Layers<Black,AlphaL<White,LinearSectionF<Int<27307>,Int<10922>>>>,TrDelay<100>,Black,TrDelay<40>,Layers<Black,AlphaL<White,LinearSectionF<Int<16384>,Int<10922>>>>,TrDelay<100>,Black,TrDelay<40>,Layers<Black,AlphaL<White,LinearSectionF<Int<5461>,Int<10922>>>>,TrDelay<100>,Black,TrDelay<40>,Layers<Black,AlphaL<White,LayerFunctions<LinearSectionF<Int<16384>,Int<10922>>,LinearSectionF<Int<5461>,Int<10922>>>>>,TrDelay<100>,Black,TrDelay<100>,Layers<Black,AlphaL<White,LayerFunctions<LinearSectionF<Int<16384>,Int<10922>>,LinearSectionF<Int<5461>,Int<10922>>>>>,TrFade<700>,Black,TrInstant>,EFFECT_USER2>,
    InOutTrL<TrConcat<TrInstant,Layers<Black,AlphaL<White,LayerFunctions<LinearSectionF<Int<16384>,Int<10922>>,LinearSectionF<Int<5461>,Int<10922>>>>>,TrDelay<395>,TrFade<100>>,TrInstant>,
    /* Poweroff */
    TransitionEffectL<TrConcat<TrInstant,Layers<Black,AlphaL<Strobe<Black,White,15,30>,LayerFunctions<LinearSectionF<Int<16384>,Int<10922>>,LinearSectionF<Int<5461>,Int<10922>>>>>,TrDelay<300>,Black,TrDelay<150>,Layers<Black,AlphaL<White,LayerFunctions<LinearSectionF<Int<16384>,Int<10922>>,LinearSectionF<Int<5461>,Int<10922>>>>>,TrFade<700>,Black,TrInstant>,EFFECT_RETRACTION>,
    /* Explosion */
    TransitionEffectL<TrConcat<TrInstant,Black,TrDelay<60>,White,TrDelay<150>,Black,TrDelay<25>,White,TrBoing<250,2>,Black,TrDelay<50>,White,TrDelay<300>,TrSmoothFade<1000>,Strobe<White,Black,15,35>,TrSmoothFade<2000>,Black,TrInstant>,EFFECT_BOOM>,
    TransitionEffectL<TrConcat<TrInstant,Layers<Black,AlphaL<White,SmoothStep<Scale<BatteryLevel,Int<0>,Int<35000>>,Int<-1>>>>,TrDelay<2000>,TrSmoothFade<1000>>,EFFECT_BATTERY_LEVEL>
  >>(),

/* Red Button */
  StylePtr<Layers<Red,LockupL<Blinking<Layers<Black,AlphaL<Red,LinearSectionF<Int<8192>,Int<16384>>>>,Layers<AlphaL<Black,LinearSectionF<Int<8192>,Int<16384>>>,AlphaL<Red,LinearSectionF<Int<24576>,Int<16384>>>>,755,500>,Black,Int<32768>,Int<32768>,Int<32768>>,
    TransitionEffectL<TrConcat<TrInstant,Layers<Black,Strobe<Black,Red,15,30>>,TrDelay<319>>,EFFECT_LOCKUP_BEGIN>,
    // Countdown Timer = USER1
    TransitionEffectL<TrConcat<TrInstant,Blinking<Red,Black,200,500>,TrDelayX<Variation>>,EFFECT_USER1>,
    // Disarm = USER2
    TransitionEffectL<TrConcat<TrInstant,Red,TrSmoothFade<420>,Black,TrInstant,Red,TrDelay<100>,Black,TrDelay<100>,Red,TrFade<700>,Black,TrInstant>,EFFECT_USER2>,
    InOutTrL<TrInstant,TrInstant>
  >>(),
"tmod"},

// { "CHOOSE_FONT;CHOOSE_VOICEPACK", "tracks/CHOOSE_TRACK.wav",
// /* 3 LEDs */
//   StylePtr<Layers<
//     TransitionLoop<Black,TrConcat<TrInstant,AlphaL<White,LinearSectionF<Int<5461>,Int<10922>>>,TrDelay<424>,AlphaL<White,LinearSectionF<Int<16384>,Int<10922>>>,TrDelay<423>,AlphaL<White,LinearSectionF<Int<27307>,Int<10922>>>,TrDelay<423>>>,
//     LockupL<Pulsing<White,Black,755>,Black,Int<32768>,Int<32768>,Int<32768>>,
//     TransitionEffectL<TrConcat<TrInstant,Layers<Black,AlphaL<Strobe<Black,White,15,30>,LayerFunctions<LinearSectionF<Int<16384>,Int<10922>>,LinearSectionF<Int<5461>,Int<10922>>>>>,TrDelay<319>>,EFFECT_LOCKUP_BEGIN>,
//     /* Countdown Timer = USER1 */
//     TransitionEffectL<TrConcat<TrInstant,Mix<Trigger<EFFECT_USER1,Variation,Int<1>,Int<1>>,Pulsing<White,Black,1000>,Pulsing<White,Black,500>,Strobe<Black,White,15,30>>,TrDelayX<Variation>>,EFFECT_USER1>,
//     /* Disarm = USER2 */
//     TransitionEffectL<TrConcat<TrInstant,Layers<Black,AlphaL<White,LinearSectionF<Int<27307>,Int<10922>>>>,TrDelay<100>,Black,TrDelay<40>,Layers<Black,AlphaL<White,LinearSectionF<Int<16384>,Int<10922>>>>,TrDelay<100>,Black,TrDelay<40>,Layers<Black,AlphaL<White,LinearSectionF<Int<5461>,Int<10922>>>>,TrDelay<100>,Black,TrDelay<40>,Layers<Black,AlphaL<White,LayerFunctions<LinearSectionF<Int<16384>,Int<10922>>,LinearSectionF<Int<5461>,Int<10922>>>>>,TrDelay<100>,Black,TrDelay<100>,Layers<Black,AlphaL<White,LayerFunctions<LinearSectionF<Int<16384>,Int<10922>>,LinearSectionF<Int<5461>,Int<10922>>>>>,TrFade<700>,Black,TrInstant>,EFFECT_USER2>,
//     InOutTrL<TrConcat<TrInstant,Layers<Black,AlphaL<White,LayerFunctions<LinearSectionF<Int<16384>,Int<10922>>,LinearSectionF<Int<5461>,Int<10922>>>>>,TrDelay<395>,TrFade<100>>,TrInstant>,
//     /* Poweroff */
//     TransitionEffectL<TrConcat<TrInstant,Layers<Black,AlphaL<Strobe<Black,White,15,30>,LayerFunctions<LinearSectionF<Int<16384>,Int<10922>>,LinearSectionF<Int<5461>,Int<10922>>>>>,TrDelay<300>,Black,TrDelay<150>,Layers<Black,AlphaL<White,LayerFunctions<LinearSectionF<Int<16384>,Int<10922>>,LinearSectionF<Int<5461>,Int<10922>>>>>,TrFade<700>,Black,TrInstant>,EFFECT_RETRACTION>,
//     /* Explosion */
//     TransitionEffectL<TrConcat<TrInstant,Black,TrDelay<60>,White,TrDelay<150>,Black,TrDelay<25>,White,TrBoing<250,2>,Black,TrDelay<50>,White,TrDelay<300>,TrSmoothFade<1000>,Strobe<White,Black,15,35>,TrSmoothFade<2000>,Black,TrInstant>,EFFECT_BOOM>,
//     TransitionEffectL<TrConcat<TrInstant,Layers<Black,AlphaL<White,SmoothStep<Scale<BatteryLevel,Int<0>,Int<35000>>,Int<-1>>>>,TrDelay<2000>,TrSmoothFade<1000>>,EFFECT_BATTERY_LEVEL>
//   >>(),

// /* Red Button */
//   StylePtr<Layers<Red,LockupL<Blinking<Layers<Black,AlphaL<Red,LinearSectionF<Int<8192>,Int<16384>>>>,Layers<AlphaL<Black,LinearSectionF<Int<8192>,Int<16384>>>,AlphaL<Red,LinearSectionF<Int<24576>,Int<16384>>>>,755,500>,Black,Int<32768>,Int<32768>,Int<32768>>,
//     TransitionEffectL<TrConcat<TrInstant,Layers<Black,Strobe<Black,Red,15,30>>,TrDelay<319>>,EFFECT_LOCKUP_BEGIN>,
//     // Countdown Timer = USER1
//     TransitionEffectL<TrConcat<TrInstant,Blinking<Red,Black,200,500>,TrDelayX<Variation>>,EFFECT_USER1>,
//     // Disarm = USER2
//     TransitionEffectL<TrConcat<TrInstant,Red,TrSmoothFade<420>,Black,TrInstant,Red,TrDelay<100>,Black,TrDelay<100>,Red,TrFade<700>,Black,TrInstant>,EFFECT_USER2>,
//     InOutTrL<TrInstant,TrInstant>
//   >>(),
// "CHOOSE_FONT"},

};
BladeConfig blades[] = {
 { 0,
     SimpleBladePtr<CH1LED,CH2LED,CH3LED,NoLED,
                    bladePowerPin1, bladePowerPin2, bladePowerPin3, -1>(),
    WS281XBladePtr<2, bladePin, Color8::GRB, PowerPINS<bladePowerPin4> >(),
     CONFIGARRAY(presets) },
  };
#endif

#ifdef CONFIG_BUTTONS
InvertedLatchingButton PowerButton(BUTTON_POWER, powerButtonPin, "pow");
Button AuxButton(BUTTON_AUX, auxPin, "aux");
#endif
