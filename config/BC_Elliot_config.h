// BC_Elliot_config.h

#ifdef CONFIG_TOP
#include "proffieboard_v3_config.h"
#define NUM_BLADES 2
#define NUM_BUTTONS 1

// ------ Audio Stuff --------

#define VOLUME 1800
// #define BOOT_VOLUME 300
#define FILTER_CUTOFF_FREQUENCY 90
#define FILTER_ORDER 8
// #define ENABLE_IDLE_SOUND
 #define BC_BUTTON_CLICKER

// ------ Blade Stuff ------

const unsigned int maxLedsPerStrip = 144;
#define DYNAMIC_BLADE_LENGTH
//#define SHARED_POWER_PINS

// ------ SD Card Stuff -------

#define MOUNT_SD_SETTING
#define SAVE_COLOR_CHANGE
#define SAVE_PRESET

// ------ System Stuff --------

#define DISABLE_DIAGNOSTIC_COMMANDS
#define DISABLE_BASIC_PARSER_STYLES
#define IDLE_OFF_TIME 60 * 5 * 1000
#define MOTION_TIMEOUT 60 * 5 * 1000
// #define CONFIG_STARTUP_DELAY 3000
// #define PROFFIEOS_LOG_LEVEL 500

// ------- Motion and Gesture stuff -------

#define CLASH_THRESHOLD_G 3.5
#define ENABLE_SPINS
// #define BC_SWING_ON
// #define BC_SWING_ON_SPEED 600 // Default 250
// #define BC_THRUST_ON
#define BC_TWIST_ON
#define BC_TWIST_OFF
// #define BC_FORCE_PUSH
// #define BC_FORCE_PUSH_LENGTH 5
//    BC Multiblast continues as long as swinging within 1 second. 
#define BC_ENABLE_AUTO_SWING_BLAST
#define ENABLE_SPINS
// #define GESTURE_AUTO_BATTLE_MODE
#define BC_LOCKUP_DELAY 200
// Use this define to turn on an optional "iPod® Clickwheel" sound when rotating the hilt in smooth colorchange mode (Color Wheel).
// mclick.wav will play, so the sound should probably be a very subtle "tick" sound.
// The value is the number of ticks per 360 hilt rotation. Higher number = more ticks per angle change.
// Suggested Range 50 - 120. Using zero or not defining will turn ticks off.
#define SMOOTH_COLORCHANGE_TICKS_PER_REVOLUTION 120
// Rotation sensitivity
#define STEPS_PER_REVOLUTION 24


#endif

#ifdef CONFIG_PROP
#include "../props/saber_BC_buttons_personal.h"
#endif

#ifdef CONFIG_PRESETS
#include "aliases/TrueWhites/BC_effects_1.h"
#include "aliases/TrueWhites/BC_effects_2.h"
#include "aliases/TrueWhites/BC_effects_Red.h"
#include "aliases/TrueWhites/BC_effects_White.h"
#include "aliases/TrueWhites/BC_12color_8effect_SS.h"     // All in one blade style from CC Fork. SS = SwingSpeed included 

using OnDemandVolumeLevel = TransitionEffectL<TrConcat<TrExtendX<Int<1000>,TrSmoothFade<200>>,AlphaL<Gradient<Blue,Green>,SmoothStep<VolumeLevel,Int<-1>>>,TrSmoothFade<500>>,EFFECT_VOLUME_LEVEL>;
using OnDemandBatteryLevel = AlphaL<TransitionEffectL<TrConcat<TrSmoothFade<500>,AlphaL<Mix<BatteryLevel,Red,Green>,SmoothStep<Scale<BatteryLevel,Int<0>,Int<35000>>,Int<-1>>>,TrDelay<1000>,AlphaL<Mix<BatteryLevel,Red,Green>,SmoothStep<Scale<BatteryLevel,Int<0>,Int<35000>>,Int<-1>>>,TrSmoothFade<1000>>,EFFECT_BATTERY_LEVEL>,Ifon<Int<0>,Int<32768>>>;

/* ---- Presets list ---- /*

a_VADER/Father_V2/ANH
a_INQUISITOR/2ndSistr
a_INQUISITOR/9thSistr
a_BANE/TheBane  // w/ice monosfx - USER2
a_BANE/RuleOfTwo
a_SIDIOUS/TheReturn
a_ASAJJ/NiteSist
a_DOOKU/Duke  // Matched Preons/outs
a_DOOKU/Dooku_CW
a_SAVAGE/Savage_Opress
a_DARTH_MAUL/CrimsonMenace
a_INQUISITOR/RevaUltimate
aa_Syndicate/SithChant  // check it out
a_STARKILLER/Secret_Apprentice  // w/ice monosfx - broken out fx because force choke anim - USER2
aa_KSith/Aggression  // w/ colorchange 2 colors
a_KYLO/KyloUltimate
Paradigm  // BC_12color_8effect_SS - USER1
a_REY/Empress
aa_Greyscale/Seethe_Greyscale
aa_Juansith/HATE
aa_Blueforce/IgnitionUltimate
aa_HarrySolo/AGONY
aa_KSith/Proto
aa_KSith/Desolation
aa_KSith/Ascension
Arcane
aa_KSith/Traveler
GhostsOfTheGrey
aa_LordBlako/PitchBlk
a_PONG_KRELL/PongKrll
Proto2
PsyBorg
a_DARKSABER/DarkV3
a_LUKE/ESB_Graflex
a_LUKE/LS6
a_LEIA/Royalty
a_REY/Scavengers_Destiny_Ultimate
aa_Blueforce/LiquidStatic
a_KANAN/BlndNite    // BC_12color_8effect_SS - USER1
a_EZRA/StapleSword  // BC_12color_8effect_SS - USER1
a_AHSOKA/AhsokaUltimate
a_TEMPLE_GUARD/TempleGuardian  // BC_12color_8effect_SS - USER1
aa_NoSloppy/Crushed
aa_HarrySolo/WORKBENCH
a_SHIPS/Falcon
a_SHIPS/Tie
a_SHIPS/Xwing
a_SHIPS/Slave1_2.1_Proffie // Seismic Charge again with USER2

*/


Preset Sinister [] = {

// ====================== Bad Guys ========================

{ "a_VADER/Father_V2/ANH;ProffieOS_V2_Voicepack_Vader_V2/common;commonBU", "a_VADER/Father_V2/tracks/track1.wav",
// Red...always
  StylePtr<Layers<
    AudioFlicker<Red,Rgb<128,0,0>>,
    BC_effects_Red,
    InOutTrL<TrWipe<1000>,TrWipeInX<WavLen<EFFECT_RETRACTION>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"father_v2\nanh"},


{ "a_INQUISITOR/2ndSistr;ProffieOS_V2_Voicepack_7th_Sister/Masked/common;commonBU", "tracks/FallenOrderTracks/JFO5.wav",
//Second Sister Base Red
  StylePtr<Layers<
    Mix<SwingSpeed<300>,AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>>,StyleFire<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<25,0,0>>,RotateColorsX<Variation,Rgb<60,0,0>>>,300>,RotateColorsX<Variation,Rgb<80,0,0>>,0,6,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>>>,
    BC_effects_Red,
  // Ignition and Retraction
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<1000>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<1000>>,EFFECT_IGNITION>,
    // AlphaL<Black,SmoothStep<Scale<SlowNoise<Int<1800>>,Int<22000>,Int<40000>>,Int<24000>>>, // Black cooling tip.....meh
    // bend
   InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    AlphaL<TransitionEffectL<TrConcat<TrFade<3000>,AlphaL<Pulsing<RotateColorsX<Variation,Rgb<128,0,0>>,RotateColorsX<Variation,Red>,350>,Bump<Int<0>,Int<7000>>>,TrInstant>,EFFECT_PREON>,Scale<Trigger<EFFECT_IGNITION,Int<1>,Int<5000>,Int<1>>,Int<32768>,Int<0>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"second\nsister"},



{ "a_INQUISITOR/9thSistr;ProffieOS_V2_Voicepack_7th_Sister/Unmasked/common;commonBU", "tracks/FallenOrderTracks/JFO7.wav",
//Second Sister Base Red
  StylePtr<Layers<
    Mix<SwingSpeed<500>,AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>>,StyleFire<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<150,0,0>>,RotateColorsX<Variation,Rgb<60,0,0>>>,300>,RotateColorsX<Variation,Rgb<180,0,0>>,0,2,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>>>,
    BC_effects_Red,
    // Ignition and Retraction
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<1000>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<1000>>,EFFECT_IGNITION>,
    // AlphaL<Black,SmoothStep<Scale<SlowNoise<Int<1800>>,Int<22000>,Int<40000>>,Int<24000>>>, // Black cooling tip.....meh
    // bend
   InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    AlphaL<TransitionEffectL<TrConcat<TrFade<3000>,AlphaL<Pulsing<RotateColorsX<Variation,Rgb<128,0,0>>,RotateColorsX<Variation,Red>,350>,Bump<Int<0>,Int<7000>>>,TrInstant>,EFFECT_PREON>,Scale<Trigger<EFFECT_IGNITION,Int<1>,Int<5000>,Int<1>>,Int<32768>,Int<0>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"ninth\nsister"},



{ "a_BANE/TheBane;ProffieOS_V2_Voicepack_Bane/common;commonBU", "a_BANE/tracks/track2.wav", // AudioFlicker Red Base Color Wheel Changeable
   
  StylePtr<Layers<
    AudioFlicker<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<60,0,0>>,500>,RotateColorsX<Variation,Rgb<128,0,0>>>,
        // Ice Force
    TransitionEffectL< 
      TrConcat<TrFade<7000>,Rgb<10,0,75>,// blade turns solid cold 1000ms before ice full coverage
      TrDelay<1000>>,EFFECT_USER2>,  // hidden by ice overlay at this point, so no reason to have anything more than 1000 before back to Base color
    TransitionEffectL< TrConcat<TrWipe<8000>, //wipe in stripes ice freezing effect
    TransitionEffect<Stripes<10000,-1000,Rgb<50,75,165>,Rgb<25,37,82>,Rgb<50,75,165>,Rgb<13,19,41>>,Sparkle<Rgb<100,150,230>,Rgb<100,200,255>,50,300>,TrFade<11500>,TrDelay<20000>,EFFECT_USER2>, // Stripes fade to solid over remaining 4 seconds from freezing edge's finish until 12000 then hold for next joined delay to end at 15000, so 3000 more.
      TrDelay<7000>,Sparkle<Rgb<100,150,230>,Rgb<100,200,255>,50,300>, //after 15000 (TrConcat makes it 8000 + 7000) from effect start, full blade to this shade of white for wiping away (seamless color from end of stripes fade to solid)
      TrJoin<TrWipe<7000>,TrSmoothFade<9500>>>,EFFECT_USER2>, // wipe ice away and melt to thinner opacity , but not 100%, leave like 30% by using longer fade duration than the wipe takes. 
    TransitionEffectL<TrConcat<
      TrJoin<TrWaveX<BrownNoiseFlicker<Rgb<100,200,255>,DeepSkyBlue,60>,     Int<400>,  Int<50>, Int<1000>,Int<0>>,    // burst
        TrWaveX<BrownNoiseFlicker<Rgb<100,200,255>,SteelBlue,600>,      Int<15000>,Int<400>,Int<8000>,Int<0>>,         // leading freeze edge
        TrWaveX<Sparkle<AlphaL<Rgb<100,200,255>,Int<0>>,Rgb<100,200,255>,3000,200>,Int<15000>,Int<100>,Int<8000>,Int<-7000>>>,    // crystalizing in edge's wake
    AlphaL<Rgb<100,200,255>,Int<0>>,
      TrJoin<TrWaveX<BrownNoiseFlicker<Rgb<100,200,255>,DeepSkyBlue,300>,    Int<300>,  Int<50>, Int<1000>,Int<0>>,  // burst
        TrWaveX<Sparkle<AlphaL<Rgb<100,200,255>,Int<0>>,Rgb<100,200,255>,3000,200>,Int<40000>,Int<300>,Int<7000>,Int<3000>>, // crystalizing in thaw's path
        TrWaveX<BrownNoiseFlicker<DarkOrange,Yellow,80>,     Int<15000>,Int<400>,Int<7000>,Int<0>>>>,EFFECT_USER2>, // leading thawing edge
    // Dim Blade 50% "Power Save" button combo
    EffectSequence<EFFECT_POWERSAVE,
        AlphaL<Black,Int<16384>>,
        AlphaL<Black,Int<0>>>,
    // Clash 2 - for red blades
    TransitionEffectL<TrConcat<TrInstant,GreenYellow,TrDelay<25>,AlphaL<TransitionEffect<TransitionEffect<Strobe<Black,Red,20,20>,BrownNoiseFlicker<Rgb<100,200,255>,Black,300>,TrInstant,TrFade<300>,EFFECT_CLASH>,Rgb<100,200,255>,TrInstant,TrDelay<150>,EFFECT_CLASH>,Bump<Scale<BladeAngle<>,Int<25000>,Int<8000>>,Int<18000>>>,TrFade<600>>,EFFECT_CLASH>,
    // Stab - OrangeRed stripes
    TransitionEffectL<TrConcat<TrInstant,GreenYellow,TrDelay<25>,AlphaL<Black,Int<0>>,TrWipeIn<300>,AlphaL<Stripes<5000,1000,Orange,DarkOrange,Rgb<150,60,0>,Rgb<60,30,0>,Rgb<150,14,0>,OrangeRed>,SmoothStep<Int<20000>,Int<20000>>>,TrJoin<TrSmoothFade<900>,TrWipe<700>>>,EFFECT_STAB>,
    // Blast v1
    TransitionEffectL<TrConcat<
        // Impact Flash - BC always
        TrInstant,GreenYellow,TrDelay<25>>,EFFECT_BLAST>,
        // Waves
        BlastL<Rgb<100,200,255>,850,250,351>,
        // Impact point afterimage
        //AlphaL<TransitionEffectL<TrConcat<TrFade<200>,Red,TrFade<600>>,EFFECT_BLAST>,BlastF<700,250,100000>>,
        AlphaL<TransitionEffectL<TrConcat<TrFade<300>,Rgb<70,70,255>,TrFade<300>>,EFFECT_BLAST>,BlastF<700,250,100000>>,
        // Impact point
        //BlastL<Rgb<100,200,255>,500,350,100000>,
        BlastL<Rgb<100,200,255>,300,350,100000>,
    // Lockup 2 - BC custom range mid-blade - Red or Yellow blade alt colors
    TransitionEffectL<TrConcat<TrInstant,Strobe<GreenYellow,Black,20,30>,TrFade<200>,BrownNoiseFlickerL<AlphaL<White,Int<16000>>,Int<5000>>,TrJoinR<TrWipe<200>,TrWipeIn<200>,TrFade<300>>>,EFFECT_LOCKUP_END>,
    LockupTrL<Layers<
        //Random Strobe Flash no dimming
        AlphaL<TransitionLoopL<TrConcat<TrDelayX<Scale<SlowNoise<Int<3000>>,Int<30>,Int<800>>>,Mix<SlowNoise<Int<1000>>,Black,Black,White,Black>,TrDelayX<Scale<SlowNoise<Int<1000>>,Int<10>,Int<50>>>>>,Int<32768>>,
        //AlphaL<White,StrobeF<Scale<SlowNoise<Int<1000>>,Int<0>,Int<2>>,Scale<SlowNoise<Int<1000>>,Int<10>,Int<50>>>>,
        // Bottom Layer Bump - random width
        AlphaL<Strobe<Rgb<200,200,200>,BrownNoiseFlicker<White,Blue,300>,30,20>,                                    Bump<Scale<BladeAngle<5000,28000>,Scale<BladeAngle<8000,16000>,Int<3000>,Int<44000>>,Int<3000>>,Scale<SlowNoise<Int<3000>>,Int<10000>,Int<18000>>>>,
        // Top Layer Bump - fixed width
        AlphaL<Strobe<White,BrownNoiseFlicker<White,Black,200>,50,30>,                                              Bump<Scale<BladeAngle<5000,28000>,Scale<BladeAngle<8000,16000>,Int<3000>,Int<44000>>,Int<3000>>,Int<10000>>>>,
        // Begin Lockup Transition
        TrConcat<TrInstant,AlphaL<Blinking<White,Strobe<BrownNoiseFlicker<Orange,Black,500>,Black,15,30>,60,500>,   Bump<Scale<BladeAngle<5000,28000>,Scale<BladeAngle<8000,16000>,Int<3000>,Int<44000>>,Int<3000>>,Scale<SlowNoise<Int<3000>>,Int<25000>,Int<32000>>>>,TrFade<500>>,
        // End Lockup Transition
        TrSmoothFade<900>,SaberBase::LOCKUP_NORMAL>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Strobe<GreenYellow,Black,20,30>,                                  Bump<Scale<BladeAngle<5000,28000>,Scale<BladeAngle<8000,16000>,Int<3000>,Int<44000>>,Int<3000>>,Int<15000>>>,TrFade<600>>,EFFECT_LOCKUP_BEGIN>,
    TransitionEffectL<TrConcat<TrInstant,GreenYellow,TrDelay<25>,HumpFlickerL<Strobe<AlphaL<White,Int<20000>>,Black,20,30>,30>,TrSmoothFade<225>>,EFFECT_LOCKUP_BEGIN>,
    // Non-Responsive Drag - BC custom drag fadeout
    LockupTrL<AlphaL<AudioFlicker<BrownNoiseFlicker<Strobe<Black,OrangeRed,20,25>,Yellow,200>,White>,SmoothStep<Int<30000>,Int<2000>>>,TrConcat<TrInstant,GreenYellow,TrDelay<25>,AlphaL<Black,Int<0>>,TrFade<150>>,TrColorCycle<1500,-2000,100>,SaberBase::LOCKUP_DRAG>,
    // Lightning Block - Non-responsive. BC custom color (purple hint w/ random strobe flashes because....lightning)  
    LockupTrL<Layers<
       //Random Strobe Flash and 16000 = 50% Base blade dimming to make lb pop
        AlphaL<Black,Int<16000>>,
        AlphaL<White,StrobeF<Scale<SlowNoise<Int<1000>>,Int<0>,Int<6>>,Scale<SlowNoise<Int<1000>>,Int<10>,Int<50>>>>,
        AlphaL<RandomFlicker<Strobe<Rgb<100,200,255>,Rgb<60,0,255>,50,10>,BrownNoiseFlicker<Rgb<60,0,255>,Black,500>>,LayerFunctions<
        Bump<Scale<SlowNoise<Int<2000>>,Int<3000>,Int<16000>>,Scale<BrownNoiseF<Int<10>>,Int<14000>,Int<8000>>>,
        Bump<Scale<SlowNoise<Int<2300>>,Int<26000>,Int<8000>>,Scale<NoisySoundLevel,Int<5000>,Int<10000>>>,
        Bump<Scale<SlowNoise<Int<2300>>,Int<20000>,Int<30000>>,Scale<IsLessThan<SlowNoise<Int<1500>>,Int<8000>>,Scale<NoisySoundLevel,Int<5000>,Int<0>>,Int<0>>>>>>,
        // Begin Lightning Transition
        TrConcat<TrInstant,GreenYellow,TrDelay<25>,BrownNoiseFlicker<Rgb<60,0,255>,Black,500>,TrFade<100>>,
        // End Lightning Transition    
        TrConcat<TrInstant,GreenYellow,TrDelay<25>,BrownNoiseFlicker<Rgb<60,0,255>,Black,500>,TrFade<150>,BrownNoiseFlickerL<AlphaL<Rgb<100,200,255>,Int<16000>>,Int<50>>,TrJoinR<TrWipe<200>,TrWipeIn<200>,TrFade<400>> >,SaberBase::LOCKUP_LIGHTNING_BLOCK>,
    // Melt - BC custom melt effects, uses twistangle<>
    LockupTrL<
        AlphaL<Mix<TwistAngle<>,Yellow,RandomPerLEDFlicker<Orange,OrangeRed>,BrownNoiseFlicker<Rgb<78,0,0>,Rgb<137,32,1>,150>,StyleFire<Rgb<80,0,0>,Red,0,4,FireConfig<0,2000,5>,FireConfig<3000,0,0>,FireConfig<0,4000,0>>>,
        // Melt Shape
        SmoothStep<Scale<TwistAngle<>,Int<24000>,Int<29000>>,Int<2000>>>,
        // Melt Begin and End transitions
        TrConcat<TrInstant,GreenYellow,TrDelay<25>,AlphaL<Black,Int<0>>,TrWipeIn<600>>,TrColorCycle<1500,-2000,100>,SaberBase::LOCKUP_MELT>, 
    // bend
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"the\nbane"},



{ "a_BANE/RuleOfTwo;ProffieOS_V2_Voicepack_Bane/common;commonBU", "a_BANE/tracks/track3.wav", // AudioFlicker Red Base Color Wheel Changeable
   
  StylePtr<Layers<
    AudioFlicker<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<60,0,0>>,500>,RotateColorsX<Variation,Rgb<128,0,0>>>,
    BC_effects_Red, 
    // bend
   InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"rule of\ntwo"},



{ "a_SIDIOUS/TheReturn;ProffieOS_V2_Voicepack_Emperor/common;commonBU", "tracks/Palpatheme_SHORT.wav",
//Red-ish...always
  StylePtr<Layers<
    Mix<SwingSpeed<500>,AudioFlicker<Gradient<Gradient<BrownNoiseFlicker<Black,Orange,400>,Red>,Red,Red,Red,Red,Red,Red,Red>,Rgb<120,0,0>>,Gradient<BrownNoiseFlicker<Black,DarkOrange,400>,BrownNoiseFlicker<Black,Rgb<128,0,0>,400>,BrownNoiseFlicker<Black,Rgb<128,0,0>,400>,BrownNoiseFlicker<Black,Rgb<128,0,0>,400>>>,
    BC_effects_Red,
    InOutTrL<TrConcat<TrWipe<200>,Strobe<Black,Rgb<100,100,155>,45,60>,TrJoinR<TrSmoothFade<190>,TrWipe<200>>>,TrWipeInX<WavLen<EFFECT_RETRACTION>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"the return\nof the sith"},



{ "a_VENTRESS/NiteSist;ProffieOS_V2_Voicepack_Ventress/common;commonBU", "tracks/Sister1.wav",
  StylePtr<Layers<
    HumpFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>,15>,
    BC_effects_Red,
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<500>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<500>>,EFFECT_IGNITION>,
    // bend
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    AlphaL<TransitionEffectL<TrConcat<TrFade<3000>,AlphaL<Pulsing<RotateColorsX<Variation,Rgb<128,0,0>>,RotateColorsX<Variation,Red>,350>,Bump<Int<0>,Int<7000>>>,TrInstant>,EFFECT_PREON>,Scale<Trigger<EFFECT_IGNITION,Int<1>,Int<5000>,Int<1>>,Int<32768>,Int<0>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"assaj\nventress"}, 




{ "a_DOOKU/Duke;ProffieOS_V2_Voicepack_Dooku/common;commonBU", "a_DOOKU/tracks/Duke1_Short.wav",
  StylePtr<Layers<
    AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>>,
    BC_effects_Red,
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<500>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<500>>,EFFECT_IGNITION>,
    // bend
   InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    AlphaL<TransitionEffectL<TrConcat<TrFade<3000>,AlphaL<Pulsing<RotateColorsX<Variation,Rgb<128,0,0>>,RotateColorsX<Variation,Red>,350>,Bump<Int<0>,Int<7000>>>,TrInstant>,EFFECT_PREON>,Scale<Trigger<EFFECT_IGNITION,Int<1>,Int<5000>,Int<1>>,Int<32768>,Int<0>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"dooku"},



{ "a_DOOKU/Dooku_CW;ProffieOS_V2_Voicepack_Dooku_CW/common;commonBU", "a_DOOKU/tracks/Duke2_Short.wav",
  StylePtr<Layers<
    RandomFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,BrownNoiseFlickerL<Rgb<100,50,50>,Int<100>>>>,
    BC_effects_Red,
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<Rgb<100,50,50>>,TrFade<500>>,EFFECT_RETRACTION>,
    // bend
   InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // AlphaL<TransitionEffectL<TrConcat<TrFade<3000>,AlphaL<Pulsing<RotateColorsX<Variation,Rgb<128,0,0>>,RotateColorsX<Variation,Red>,350>,Bump<Int<0>,Int<7000>>>,TrInstant>,EFFECT_PREON>,Scale<Trigger<EFFECT_IGNITION,Int<1>,Int<5000>,Int<1>>,Int<32768>,Int<0>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"clone wars\ndooku"}, 



{ "a_SAVAGE/Savage_Opress;ProffieOS_V2_Voicepack_Savage/common;commonBU", "tracks/Sister2_short.wav",
//Second Sister Base Red
  StylePtr<Layers<
    Mix<SwingSpeed<300>,AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>>,StyleFire<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<25,0,0>>,RotateColorsX<Variation,Rgb<60,0,0>>>,300>,RotateColorsX<Variation,Rgb<80,0,0>>,0,6,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>>>,
    BC_effects_Red,
    // Ignition and Retraction
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<1000>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<1000>>,EFFECT_IGNITION>,
    // bend
   InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // AlphaL<TransitionEffectL<TrConcat<TrFade<3000>,AlphaL<Pulsing<RotateColorsX<Variation,Rgb<128,0,0>>,RotateColorsX<Variation,Red>,350>,Bump<Int<0>,Int<7000>>>,TrInstant>,EFFECT_PREON>,Scale<Trigger<EFFECT_IGNITION,Int<1>,Int<5000>,Int<1>>,Int<32768>,Int<0>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"savage\nopress"},



{ "a_DARTH_MAUL/CrimsonMenace;ProffieOS_V2_Voicepack_Maul/common;commonBU", "a_DARTH_MAUL/tracks/Maul_Solo_Theme.wav", // AudioFlicker Red Base Color Wheel Changeable
   
  StylePtr<Layers<
    AudioFlicker<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<60,0,0>>,500>,RotateColorsX<Variation,Rgb<128,0,0>>>,
    BC_effects_Red, 
    // bend
   InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"darth\nmaul"},



{ "a_INQUISITOR/RevaUltimate;common;commonBU", "tracks/FallenOrderTracks/JFO9.wav",
  StylePtr<Layers<
    StripesX<Int<1500>,Scale<SlowNoise<Int<2500>>,Int<-3000>,Int<-5000>>,RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<80,0,0>>,RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<20,0,0>>,RotateColorsX<Variation,Red>>,
    BC_effects_Red,
    TransitionEffectL<TrConcat<TrFadeX<WavLen<>>,AudioFlickerL<White>,TrInstant>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<600>>,EFFECT_IGNITION>,
    InOutTrL<TrWipeSparkTip<Rgb<200,100,100>,300>,TrWipeInX<WavLen<EFFECT_RETRACTION>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"reva\nultimate"},



{ "aa_Syndicate/SithChant;ProffieOS_V2_Voicepack_The_Presence/common;commonBU", "aa_Syndicate/SithChant/tracks/music_from_the_dark_side_edit.wav",
  StylePtr<Layers<
    Stripes<6000,-3000,RotateColorsX<Variation,Rgb<200,0,0>>,RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<150,0,0>>>,
    BC_effects_Red,
    // Ignition and Retraction
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<Rgb<128,128,128>>,TrFade<1000>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,BrownNoiseFlicker<Red,Black,500>,TrJoin<TrFade<1000>,TrWipe<800>>>,EFFECT_IGNITION>,
    AlphaL<Black,SmoothStep<Scale<SlowNoise<Int<1800>>,Int<22000>,Int<40000>>,Int<24000>>>, // Black cooling tip.....meh
    // bend
   InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"sith\nchant"},



{ "a_STARKILLER/Secret_Apprentice;ProffieOS_V2_Voicepack_Starkiller/common;commonBU", "a_STARKILLER/tracks/SKT4.wav", // AudioFlicker Red Base Color Wheel Changeable
   
  StylePtr<Layers<
    AudioFlicker<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<60,0,0>>,500>,RotateColorsX<Variation,Rgb<128,0,0>>>,
    // Ice Force
    TransitionEffectL< 
      TrConcat<TrFade<7000>,Rgb<10,0,75>,// blade turns solid cold 1000ms before ice full coverage
      TrDelay<1000>>,EFFECT_USER2>,  // hidden by ice overlay at this point, so no reason to have anything more than 1000 before back to Base color
    TransitionEffectL< TrConcat<TrWipe<8000>, //wipe in stripes ice freezing effect
    TransitionEffect<Stripes<10000,-1000,Rgb<50,75,165>,Rgb<25,37,82>,Rgb<50,75,165>,Rgb<13,19,41>>,Sparkle<Rgb<100,150,230>,Rgb<100,200,255>,50,300>,TrFade<11500>,TrDelay<20000>,EFFECT_USER2>, // Stripes fade to solid over remaining 4 seconds from freezing edge's finish until 12000 then hold for next joined delay to end at 15000, so 3000 more.
      TrDelay<7000>,Sparkle<Rgb<100,150,230>,Rgb<100,200,255>,50,300>, //after 15000 (TrConcat makes it 8000 + 7000) from effect start, full blade to this shade of white for wiping away (seamless color from end of stripes fade to solid)
      TrJoin<TrWipe<7000>,TrSmoothFade<9500>>>,EFFECT_USER2>, // wipe ice away and melt to thinner opacity , but not 100%, leave like 30% by using longer fade duration than the wipe takes. 
    TransitionEffectL<TrConcat<
      TrJoin<TrWaveX<BrownNoiseFlicker<Rgb<100,200,255>,DeepSkyBlue,60>,     Int<400>,  Int<50>, Int<1000>,Int<0>>,    // burst
        TrWaveX<BrownNoiseFlicker<Rgb<100,200,255>,SteelBlue,600>,      Int<15000>,Int<400>,Int<8000>,Int<0>>,         // leading freeze edge
        TrWaveX<Sparkle<AlphaL<Rgb<100,200,255>,Int<0>>,Rgb<100,200,255>,3000,200>,Int<15000>,Int<100>,Int<8000>,Int<-7000>>>,    // crystalizing in edge's wake
    AlphaL<Rgb<100,200,255>,Int<0>>,
      TrJoin<TrWaveX<BrownNoiseFlicker<Rgb<100,200,255>,DeepSkyBlue,300>,    Int<300>,  Int<50>, Int<1000>,Int<0>>,  // burst
        TrWaveX<Sparkle<AlphaL<Rgb<100,200,255>,Int<0>>,Rgb<100,200,255>,3000,200>,Int<40000>,Int<300>,Int<7000>,Int<3000>>, // crystalizing in thaw's path
        TrWaveX<BrownNoiseFlicker<DarkOrange,Yellow,80>,     Int<15000>,Int<400>,Int<7000>,Int<0>>>>,EFFECT_USER2>, // leading thawing edge
    // Dim Blade 50% "Power Save" button combo
    EffectSequence<EFFECT_POWERSAVE,
        AlphaL<Black,Int<16384>>,
        AlphaL<Black,Int<0>>>,
    // Clash 2 - for red blades
    TransitionEffectL<TrConcat<TrInstant,GreenYellow,TrDelay<25>,AlphaL<TransitionEffect<TransitionEffect<Strobe<Black,Red,20,20>,BrownNoiseFlicker<Rgb<100,200,255>,Black,300>,TrInstant,TrFade<300>,EFFECT_CLASH>,Rgb<100,200,255>,TrInstant,TrDelay<150>,EFFECT_CLASH>,Bump<Scale<BladeAngle<>,Int<25000>,Int<8000>>,Int<18000>>>,TrFade<600>>,EFFECT_CLASH>,
    // Stab - OrangeRed stripes
    TransitionEffectL<TrConcat<TrInstant,GreenYellow,TrDelay<25>,AlphaL<Black,Int<0>>,TrWipeIn<300>,AlphaL<Stripes<5000,1000,Orange,DarkOrange,Rgb<150,60,0>,Rgb<60,30,0>,Rgb<150,14,0>,OrangeRed>,SmoothStep<Int<20000>,Int<20000>>>,TrJoin<TrSmoothFade<900>,TrWipe<700>>>,EFFECT_STAB>,
    // Blast v1
    TransitionEffectL<TrConcat<
        // Impact Flash - BC always
        TrInstant,GreenYellow,TrDelay<25>>,EFFECT_BLAST>,
        // Waves
        BlastL<Rgb<100,200,255>,850,250,351>,
        // Impact point afterimage
        //AlphaL<TransitionEffectL<TrConcat<TrFade<200>,Red,TrFade<600>>,EFFECT_BLAST>,BlastF<700,250,100000>>,
        AlphaL<TransitionEffectL<TrConcat<TrFade<300>,Rgb<70,70,255>,TrFade<300>>,EFFECT_BLAST>,BlastF<700,250,100000>>,
        // Impact point
        //BlastL<Rgb<100,200,255>,500,350,100000>,
        BlastL<Rgb<100,200,255>,300,350,100000>,
    // Lockup 2 - BC custom range mid-blade - Red or Yellow blade alt colors
    TransitionEffectL<TrConcat<TrInstant,Strobe<GreenYellow,Black,20,30>,TrFade<200>,BrownNoiseFlickerL<AlphaL<White,Int<16000>>,Int<5000>>,TrJoinR<TrWipe<200>,TrWipeIn<200>,TrFade<300>>>,EFFECT_LOCKUP_END>,
    LockupTrL<Layers<
        //Random Strobe Flash no dimming
        AlphaL<TransitionLoopL<TrConcat<TrDelayX<Scale<SlowNoise<Int<3000>>,Int<30>,Int<800>>>,Mix<SlowNoise<Int<1000>>,Black,Black,White,Black>,TrDelayX<Scale<SlowNoise<Int<1000>>,Int<10>,Int<50>>>>>,Int<32768>>,
        //AlphaL<White,StrobeF<Scale<SlowNoise<Int<1000>>,Int<0>,Int<2>>,Scale<SlowNoise<Int<1000>>,Int<10>,Int<50>>>>,
        // Bottom Layer Bump - random width
        AlphaL<Strobe<Rgb<200,200,200>,BrownNoiseFlicker<White,Blue,300>,30,20>,                                    Bump<Scale<BladeAngle<5000,28000>,Scale<BladeAngle<8000,16000>,Int<3000>,Int<44000>>,Int<3000>>,Scale<SlowNoise<Int<3000>>,Int<10000>,Int<18000>>>>,
        // Top Layer Bump - fixed width
        AlphaL<Strobe<White,BrownNoiseFlicker<White,Black,200>,50,30>,                                              Bump<Scale<BladeAngle<5000,28000>,Scale<BladeAngle<8000,16000>,Int<3000>,Int<44000>>,Int<3000>>,Int<10000>>>>,
        // Begin Lockup Transition
        TrConcat<TrInstant,AlphaL<Blinking<White,Strobe<BrownNoiseFlicker<Orange,Black,500>,Black,15,30>,60,500>,   Bump<Scale<BladeAngle<5000,28000>,Scale<BladeAngle<8000,16000>,Int<3000>,Int<44000>>,Int<3000>>,Scale<SlowNoise<Int<3000>>,Int<25000>,Int<32000>>>>,TrFade<500>>,
        // End Lockup Transition
        TrSmoothFade<900>,SaberBase::LOCKUP_NORMAL>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Strobe<GreenYellow,Black,20,30>,                                  Bump<Scale<BladeAngle<5000,28000>,Scale<BladeAngle<8000,16000>,Int<3000>,Int<44000>>,Int<3000>>,Int<15000>>>,TrFade<600>>,EFFECT_LOCKUP_BEGIN>,
    TransitionEffectL<TrConcat<TrInstant,GreenYellow,TrDelay<25>,HumpFlickerL<Strobe<AlphaL<White,Int<20000>>,Black,20,30>,30>,TrSmoothFade<225>>,EFFECT_LOCKUP_BEGIN>,
    // Non-Responsive Drag - BC custom drag fadeout
    LockupTrL<AlphaL<AudioFlicker<BrownNoiseFlicker<Strobe<Black,OrangeRed,20,25>,Yellow,200>,White>,SmoothStep<Int<30000>,Int<2000>>>,TrConcat<TrInstant,GreenYellow,TrDelay<25>,AlphaL<Black,Int<0>>,TrFade<150>>,TrColorCycle<1500,-2000,100>,SaberBase::LOCKUP_DRAG>,
    // Lightning Block - Non-responsive. BC custom color (purple hint w/ random strobe flashes because....lightning)  
    LockupTrL<Layers<
       //Random Strobe Flash and 16000 = 50% Base blade dimming to make lb pop
        AlphaL<Black,Int<16000>>,
        AlphaL<White,StrobeF<Scale<SlowNoise<Int<1000>>,Int<0>,Int<6>>,Scale<SlowNoise<Int<1000>>,Int<10>,Int<50>>>>,
        AlphaL<RandomFlicker<Strobe<Rgb<100,200,255>,Rgb<60,0,255>,50,10>,BrownNoiseFlicker<Rgb<60,0,255>,Black,500>>,LayerFunctions<
        Bump<Scale<SlowNoise<Int<2000>>,Int<3000>,Int<16000>>,Scale<BrownNoiseF<Int<10>>,Int<14000>,Int<8000>>>,
        Bump<Scale<SlowNoise<Int<2300>>,Int<26000>,Int<8000>>,Scale<NoisySoundLevel,Int<5000>,Int<10000>>>,
        Bump<Scale<SlowNoise<Int<2300>>,Int<20000>,Int<30000>>,Scale<IsLessThan<SlowNoise<Int<1500>>,Int<8000>>,Scale<NoisySoundLevel,Int<5000>,Int<0>>,Int<0>>>>>>,
        // Begin Lightning Transition
        TrConcat<TrInstant,GreenYellow,TrDelay<25>,BrownNoiseFlicker<Rgb<60,0,255>,Black,500>,TrFade<100>>,
        // End Lightning Transition    
        TrConcat<TrInstant,GreenYellow,TrDelay<25>,BrownNoiseFlicker<Rgb<60,0,255>,Black,500>,TrFade<150>,BrownNoiseFlickerL<AlphaL<Rgb<100,200,255>,Int<16000>>,Int<50>>,TrJoinR<TrWipe<200>,TrWipeIn<200>,TrFade<400>> >,SaberBase::LOCKUP_LIGHTNING_BLOCK>,
    // Melt - BC custom melt effects, uses twistangle<>
    LockupTrL<
        AlphaL<Mix<TwistAngle<>,Yellow,RandomPerLEDFlicker<Orange,OrangeRed>,BrownNoiseFlicker<Rgb<78,0,0>,Rgb<137,32,1>,150>,StyleFire<Rgb<80,0,0>,Red,0,4,FireConfig<0,2000,5>,FireConfig<3000,0,0>,FireConfig<0,4000,0>>>,
        // Melt Shape
        SmoothStep<Scale<TwistAngle<>,Int<24000>,Int<29000>>,Int<2000>>>,
        // Melt Begin and End transitions
        TrConcat<TrInstant,GreenYellow,TrDelay<25>,AlphaL<Black,Int<0>>,TrWipeIn<600>>,TrColorCycle<1500,-2000,100>,SaberBase::LOCKUP_MELT>, 
    // bend
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"starkiller"},



{ "aa_KSith/Aggression;ProffieOS_V2_Voicepack_Malgus2/common;commonBU", "tracks/FallenOrderTracks/JFO11a.wav", // colorchange 2 colors
  StylePtr<Layers<
    ColorChange<TrWipe<500>,StyleFire<BrownNoiseFlicker<Rgb<95,0,210>,RandomPerLEDFlicker<Rgb<42,0,105>,Rgb<21,0,52>>,300>,Rgb<10,0,26>,0,6,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>>,StyleFire<Red,Rgb<60,0,0>,0,6,FireConfig<0,2000,5>,FireConfig<0,0,0>,FireConfig<0,2000,5>,FireConfig<0,2000,5>>>,
    BC_effects_Red,
    TransitionEffectL<TrConcat<TrInstant,AudioFlickerL<RotateColorsX<Variation,Rgb<160,60,255>>>,TrFade<1200>>,EFFECT_IGNITION>,
   // bend
   InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<100,200,255>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"starkiller"},



{ "a_KYLO/KyloUltimate;ProffieOS_V2_Voicepack_Kylo_V2/common;commonBU", "a_KYLO/KyloUltimate/tracks/Kylo1.wav",
  StylePtr<Layers<
    StyleFire<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<25,0,0>>,RotateColorsX<Variation,Rgb<60,0,0>>>,300>,RotateColorsX<Variation,Rgb<80,0,0>>,0,6,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>>,
    BC_effects_Red,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<RotateColorsX<Variation,Rgb<255,150,150>>,40>,TrFade<1200>>,EFFECT_IGNITION>,
    InOutTrL<TrWipe<400>,TrWipeInX<WavLen<EFFECT_RETRACTION>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"kylo\nultimate"},


{ "Paradigm;ProffieOS_V2_Voicepack_HK-47/common;commonBU", "tracks/FallenOrderTracks/JFO15.wav",
  // The ol' ThirteenColorTenEffect for OS6 now
  StylePtr<Layers<
    BC_12color_8effect_SS, // 96 possible blade combos in one style. Uses BC_SWAP.
    BC_effects_Red,
    InOutTrL<TrJoin<TrWipeX<WavLen<EFFECT_IGNITION>>,TrSparkX<White,Int<400>,WavLen<EFFECT_IGNITION>,Int<0>>>,TrWipeInX<WavLen<EFFECT_RETRACTION>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
  "paradigm"
},

{ "a_REY/Empress;ProffieOS_V2_Voicepack_Rey/common;commonBU", "a_REY/tracks/DarkReyBC.wav",
  StylePtr<Layers<
    HumpFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>,15>,
    BC_effects_Red,
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<500>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<500>>,EFFECT_IGNITION>,
    InOutTrL<TrJoin<TrWipeX<Int<300>>,TrWaveX<White,Int<5000>,Int<50>,Int<300>,Int<0>>>,TrWipeInX<WavLen<EFFECT_RETRACTION> >>,
    AlphaL<TransitionEffectL<TrConcat<TrFade<3000>,AlphaL<Pulsing<RotateColorsX<Variation,Rgb<128,0,0>>,RotateColorsX<Variation,Red>,350>,Bump<Int<0>,Int<7000>>>,TrInstant>,EFFECT_PREON>,Scale<Trigger<EFFECT_IGNITION,Int<1>,Int<5000>,Int<1>>,Int<32768>,Int<0>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"empress"}, 


{ "aa_Greyscale/Seethe_Greyscale;ProffieOS_V2_Voicepack_JARVIS/common;commonBU", "",
  StylePtr<Layers<
    // Red audioflicker
    AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<200,0,0>>>,
    // Force effect, temporarily allows a swing effect where solid dark orange takes over the blade when swinging
    TransitionEffectL<TrConcat<TrFade<200>,AlphaL<RotateColorsX<Variation,Rgb<255,45,0>>,SwingSpeed<500>>,TrDelay<30000>,AlphaL<RotateColorsX<Variation,Rgb<255,45,0>>,SwingSpeed<500>>,TrFade<800>>,EFFECT_FORCE>,
    // Unstable swing
    AlphaL<BrownNoiseFlicker<RotateColorsX<Variation,Red>,Black,300>,SwingSpeed<315>>,
    // Timed "breathing" emitter flare
    Mix<Sin<Int<8>>,AlphaL<RotateColorsX<Variation,Rgb<255,45,0>>,Bump<Int<0>,Int<6000>>>,AlphaL<RotateColorsX<Variation,Rgb<255,45,0>>,Bump<Int<0>,Int<22000>>>>,
    BC_effects_Red,
    // bend with surge
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<500>>,EFFECT_IGNITION>,
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1800>,Int<235000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1800>,Int<210000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"seethe"},


{ "aa_Juansith/HATE;ProffieOS_V2_Voicepack_Malgus2/common;commonBU", "",
//Second Sister Base Red
  StylePtr<Layers<
    Mix<SwingSpeed<300>,AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>>,StyleFire<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<25,0,0>>,RotateColorsX<Variation,Rgb<60,0,0>>>,300>,RotateColorsX<Variation,Rgb<80,0,0>>,0,6,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>>>,
    BC_effects_Red,
    // Ignition and Retraction
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<1000>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<1000>>,EFFECT_IGNITION>,
    // AlphaL<Black,SmoothStep<Scale<SlowNoise<Int<1800>>,Int<22000>,Int<40000>>,Int<24000>>>, // Black cooling tip.....meh
    // bend
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1500>,Int<110000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    AlphaL<TransitionEffectL<TrConcat<TrFade<3000>,AlphaL<Pulsing<RotateColorsX<Variation,Rgb<128,0,0>>,RotateColorsX<Variation,Red>,350>,Bump<Int<0>,Int<7000>>>,TrInstant>,EFFECT_PREON>,Scale<Trigger<EFFECT_IGNITION,Int<1>,Int<5000>,Int<1>>,Int<32768>,Int<0>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"hate"},



{ "aa_Blueforce/IgnitionUltimate;ProffieOS_V2_Voicepack_Stranger/common;commonBU", "",
StylePtr<Layers<
  Stripes<2000,-2500,RotateColorsX<Variation,Red>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<60,0,0>>,Black>,BrownNoiseFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<30,0,0>>,200>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<80,0,0>>,RotateColorsX<Variation,Rgb<30,0,0>>>>,
  TransitionLoopL<TrConcat<TrWaveX<RandomFlicker<RotateColorsX<Variation,Red>,BrownNoiseFlicker<RotateColorsX<Variation,Rgb<80,0,0>>,Black,300>>,Int<400>,Int<100>,Int<200>,Int<0>>,AlphaL<Red,Int<0>>,TrDelayX<Scale<SlowNoise<Int<1500>>,Int<200>,Int<1200>>>>>,
  AlphaL<BrownNoiseFlicker<Red,Black,300>,SwingSpeed<400>>,
  BC_effects_Red,
  InOutTrL<
    TrConcat<TrInstant,BrownNoiseFlicker<White,DarkOrange,300>,TrDelay<20>,Black,TrWipe<300>,Stripes<2500,-5000,BrownNoiseFlicker<RotateColorsX<Variation,Red>,Black,20>,Black,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<255,20,0>>,White>,RotateColorsX<Variation,Rgb<128,34,0>>>,TrFade<300>,BrownNoiseFlicker<RotateColorsX<Variation,Red>,Black,20>,TrBoing<300,3>>,
    TrConcat<TrInstant,BrownNoiseFlicker<White,DarkOrange,300>,TrFade<250>,AlphaL<Black,Int<0>>,TrJoin<TrWipeInX<Int<850>>,TrWaveX<White,Int<800>,Int<400>,Int<850>,Int<32768>>>>>,
// Comment out this following line to use a non-stutter version ignition
  //TransitionEffectL<TrConcat<TrWaveX<White,Int<800>,Int<200>,Int<300>,Int<0>>,BrownNoiseFlicker<White,DarkOrange,300>,TrDelay<20>,Black,TrDelay<650>,BrownNoiseFlicker<White,DarkOrange,300>,TrDelay<20>,Black,TrDelay<100>,BrownNoiseFlicker<White,Red,70>,TrFade<500>,Black,TrInstant>,EFFECT_IGNITION>,
  TransitionEffectL<TrConcat<TrDelay<1100>,BrownNoiseFlicker<White,DarkOrange,300>,TrDelay<50>>,EFFECT_RETRACTION>,
  TransitionEffectL<TrConcat<
    TrInstant,AlphaL<BrownNoiseFlicker<Red,Black,100>,Bump<Int<0>,Int<30000>>>,TrDelay<100>,AlphaL<BrownNoiseFlicker<Red,Black,100>,Bump<Int<0>,Int<30000>>>,TrFade<100>,Black,
    TrDelay<50>,AlphaL<BrownNoiseFlicker<White,Black,100>,Bump<Int<0>,Int<50000>>>,TrDelay<150>,AlphaL<BrownNoiseFlicker<White,DarkOrange,300>,Bump<Int<0>,Int<70000>>>,TrFade<150>,Black,
    TrFade<100>,AlphaL<BrownNoiseFlicker<Rgb<255,100,100>,Black,40>,Bump<Int<0>,Int<40000>>>,TrFade<400>,AlphaL<BrownNoiseFlicker<Red,Black,40>,Bump<Int<0>,Int<20000>>>,TrFade<450>,Black,
    
    TrInstant,AlphaL<BrownNoiseFlicker<White,Black,100>,Bump<Int<0>,Int<70000>>>,TrDelay<250>,AlphaL<BrownNoiseFlicker<White,DarkOrange,300>,Bump<Int<0>,Int<50000>>>,TrFade<200>,Black,
    TrFade<100>,AlphaL<BrownNoiseFlicker<Rgb<255,100,100>,Black,40>,Bump<Int<0>,Int<40000>>>,TrFade<500>,AlphaL<BrownNoiseFlicker<Red,Black,40>,Bump<Int<0>,Int<20000>>>,TrFade<600>,Black,

    TrInstant,AlphaL<BrownNoiseFlicker<White,Black,100>,Bump<Int<0>,Int<10000>>>,TrDelay<100>,AlphaL<BrownNoiseFlicker<White,Red,300>,Bump<Int<0>,Int<5000>>>,TrFade<150>,Black,
    TrDelay<350>,Black,
    TrInstant,AlphaL<BrownNoiseFlicker<White,Black,100>,Bump<Int<0>,Int<10000>>>,TrDelay<70>,AlphaL<BrownNoiseFlicker<White,Red,300>,Bump<Int<0>,Int<5000>>>,TrFade<40>,Black,
    TrDelay<20>,Black,

    TrInstant,AlphaL<BrownNoiseFlicker<Red,Black,100>,Bump<Int<0>,Int<30000>>>,TrDelay<50>,AlphaL<BrownNoiseFlicker<Red,Black,100>,Bump<Int<0>,Int<30000>>>,TrFade<50>,Black,
    TrDelay<50>,AlphaL<BrownNoiseFlicker<White,Black,100>,Bump<Int<0>,Int<50000>>>,TrDelay<100>,AlphaL<BrownNoiseFlicker<White,DarkOrange,300>,Bump<Int<0>,Int<70000>>>,TrFade<150>,Black,
    TrFade<100>,AlphaL<BrownNoiseFlicker<Rgb<255,100,100>,Black,40>,Bump<Int<0>,Int<40000>>>,TrFade<300>,AlphaL<BrownNoiseFlicker<Red,Black,40>,Bump<Int<0>,Int<20000>>>,TrFade<400>,

    AlphaL<BrownNoiseFlicker<White,Red,100>,Bump<Int<0>,Int<10000>>>,
    TrFade<175>,AlphaL<BrownNoiseFlicker<White,DarkOrange,300>,Bump<Int<0>,Int<20000>>>,TrFade<175>,AlphaL<BrownNoiseFlicker<White,Red,100>,Bump<Int<0>,Int<10000>>>,
    TrFade<115>,AlphaL<BrownNoiseFlicker<White,DarkOrange,100>,Bump<Int<0>,Int<40000>>>,TrFade<115>,AlphaL<BrownNoiseFlicker<White,Red,300>,Bump<Int<0>,Int<20000>>>,
    TrFade<100>,AlphaL<BrownNoiseFlicker<White,DarkOrange,100>,Bump<Int<0>,Int<60000>>>,TrFade<100>,AlphaL<BrownNoiseFlicker<White,Red,300>,Bump<Int<0>,Int<40000>>>,
    TrFade<75>,BrownNoiseFlicker<White,DarkOrange,300>,TrFade<50>,Black,TrFade<50>,BrownNoiseFlicker<RotateColorsX<Variation,Red>,Rgb<200,150,150>,20>,
    TrSmoothFade<100>>,EFFECT_PREON>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"ignition\nultimate"},


{ "aa_HarrySolo/AGONY;ProffieOS_V2_Voicepack_Cassian_Andor/common;commonBU", "",
  StylePtr<Layers<
    HumpFlicker<Blue,Stripes<22000,-100,RotateColorsX<Variation,Rgb<48,0,105>>,RotateColorsX<Variation,Rgb<95,0,210>>,RotateColorsX<Variation,Rgb<22,0,49>>>,10>,
    BC_effects_Red,
    InOutTrL<TrJoin<TrWipeX<Int<600>>,TrWaveX<White,Int<1200>,Int<400>,Int<600>,Int<0>>>,
             TrJoin<TrWipeInX<WavLen<EFFECT_RETRACTION>>,TrWaveX<White,Percentage<WavLen<EFFECT_RETRACTION>,150>,Int<400>,WavLen<EFFECT_RETRACTION>,Int<32768>>>>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<200>>,EFFECT_IGNITION>,
    AlphaL<TransitionEffectL<TrConcat<TrFade<1500>,AlphaL<HumpFlickerL<Rgb<120,120,165>,10>,Bump<Int<0>,Int<4000>>>,TrFade<1500>,AlphaL<HumpFlickerL<Rgb<120,120,165>,15>,Bump<Int<0>,Int<5000>>>,TrFade<1500>,AlphaL<HumpFlickerL<Rgb<120,120,165>,20>,Bump<Int<0>,Int<6000>>>,TrFade<1000>>,EFFECT_PREON>,Ifon<Int<0>,Int<32768>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"agony"},


{ "aa_KSith/Proto;ProffieOS_V2_Voicepack_Narrator/common;commonBU", "",
  StylePtr<Layers<
// Main Blade
    // Jedi Base Orange
    StripesX<Int<16000>,Int<-1000>,RotateColorsX<Variation,DarkOrange>,Pulsing<RotateColorsX<Variation,Rgb<90,24,0>>,RotateColorsX<Variation,DarkOrange>,800>,RotateColorsX<Variation,DarkOrange>>,
    // Jedi Force Orange
    TransitionEffectL<TrConcat<TrFade<600>,RandomFlicker<RotateColorsX<Variation,DarkOrange>,RotateColorsX<Variation,Rgb<160,43,0>>>,TrDelay<3000>,RotateColorsX<Variation,DarkOrange>,TrFade<800>>,EFFECT_FORCE>,
    // Jedi Swing Orange
    AlphaL<RotateColorsX<Variation,Rgb<255,178,110>>,Scale<IsLessThan<SwingSpeed<600>,Int<13600>>,Scale<SwingSpeed<600>,Int<-19300>,Int<32768>>,Int<0>>>,
    BC_effects_1,
    // Ignition and Retraction
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<500>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<500>>,EFFECT_IGNITION>,
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1800>,Int<235000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1800>,Int<210000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"proto"},




{ "aa_KSith/Desolation;ProffieOS_V2_Voicepack_Optimus_Prime/common", "tracks/FallenOrderTracks/JFO12.wav",
  StylePtr<Layers<
// Main Blade
    // Jedi base Yellow
    StripesX<Int<16000>,Int<-1000>,RotateColorsX<Variation,Rgb<180,180,0>>,Pulsing<RotateColorsX<Variation,Rgb<64,64,0>>,RotateColorsX<Variation,Rgb<180,180,0>>,800>,RotateColorsX<Variation,Rgb<180,180,0>>>,
    // Jedi Force Yellow
    TransitionEffectL<TrConcat<TrFade<600>,RandomFlicker<RotateColorsX<Variation,Rgb<180,180,0>>,RotateColorsX<Variation,Rgb<113,113,0>>>,TrDelay<3000>,RotateColorsX<Variation,Rgb<180,180,0>>,TrFade<800>>,EFFECT_FORCE>,
    // Jedi Swing Yellow
    AlphaL<RotateColorsX<Variation,Rgb<230,180,80>>,Scale<IsLessThan<SwingSpeed<600>,Int<13600>>,Scale<SwingSpeed<600>,Int<-19300>,Int<32768>>,Int<0>>>,
    BC_effects_Red,
    // Ignition and Retraction
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<500>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<500>>,EFFECT_IGNITION>,
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1800>,Int<235000>>>,TrSparkX<Yellow,Int<400>,BendTimePowInvX<Int<1800>,Int<210000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"desolation"},



{ "aa_KSith/Ascension;ProffieOS_V2_Voicepack_Yoda/common;commonBU", "tracks/battleofheros.wav",
  StylePtr<Layers<
    StripesX<Int<3000>,Int<-3000>,RotateColorsX<Variation,Blue>,RotateColorsX<Variation,Rgb<0,0,60>>,RotateColorsX<Variation,Rgb<50,50,255>>,RotateColorsX<Variation,Rgb<0,0,128>>>,
    AlphaL<Rgb<100,100,255>,SwingSpeed<600>>,
    BC_effects_1,
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<500>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<500>>,EFFECT_IGNITION>,
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1800>,Int<235000>>>,TrSparkX<Rgb<100,200,255>,Int<400>,BendTimePowInvX<Int<1800>,Int<210000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"ascension"},



{ "Arcane;ProffieOS_V2_Voicepack_Arcann/Masked/common;commonBU", "",
  StylePtr<Layers<
    HumpFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>,15>,
    BC_effects_Red,
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<500>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<500>>,EFFECT_IGNITION>,
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1800>,Int<235000>>>,TrSparkX<Rgb<255,100,100>,Int<400>,BendTimePowInvX<Int<1800>,Int<210000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    AlphaL<TransitionEffectL<TrConcat<TrFade<3000>,AlphaL<Pulsing<RotateColorsX<Variation,Rgb<128,0,0>>,RotateColorsX<Variation,Red>,350>,Bump<Int<0>,Int<7000>>>,TrInstant>,EFFECT_PREON>,Scale<Trigger<EFFECT_IGNITION,Int<1>,Int<5000>,Int<1>>,Int<32768>,Int<0>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"arcane"}, 



{ "aa_KSith/Traveler;ProffieOS_V2_Voicepack_Kota/common;commonBU", "tracks/FallenOrderTracks/JFO3.wav",
  StylePtr<Layers<
    Mix<SwingSpeed<500>,AudioFlicker<Gradient<Gradient<BrownNoiseFlicker<Black,Orange,400>,Red>,Red,Red,Red,Red,Red,Red,Red>,Rgb<120,0,0>>,Gradient<BrownNoiseFlicker<Black,DarkOrange,400>,BrownNoiseFlicker<Black,Rgb<128,0,0>,400>,BrownNoiseFlicker<Black,Rgb<128,0,0>,400>,BrownNoiseFlicker<Black,Rgb<128,0,0>,400>>>,
    BC_effects_Red,       
    InOutTrL<TrConcat<TrWipe<200>,Strobe<Black,Rgb<100,100,155>,45,60>,TrJoinR<TrSmoothFade<190>,TrWipe<200>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"traveler"},


{ "GhostsOfTheGrey;common;commonBU", "", 
  StylePtr<Layers<
    StripesX<Int<6000>,Int<-1000>,RotateColorsX<Variation,Rgb<50,50,75>>,RotateColorsX<Variation,Rgb<100,100,150>>,RotateColorsX<Variation,Rgb<24,24,35>>>,AlphaL<White,Scale<IsLessThan<SwingSpeed<600>,Int<13600>>,Scale<SwingSpeed<600>,Int<-19300>,Int<32768>>,Int<0>>>,
    AlphaL<Stripes<4000,-2000,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<100,100,150>>,Black>,White,RotateColorsX<Variation,Rgb<100,100,150>>,White>,Scale<IsLessThan<SwingSpeed<600>,Int<13600>>,Scale<SwingSpeed<600>,Int<-19300>,Int<32768>>,Int<0>>>,
    BC_effects_White,  
    InOutTrL<TrWipe<400>,TrConcat<TrFadeX<Percentage<WavLen<EFFECT_RETRACTION>,50>>,Stripes<3000,2000,White,Rgb<100,100,100>>,TrFadeX< Percentage<WavLen<EFFECT_RETRACTION>,50> >>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"ghosts of\nthe grey"},


{ "aa_LordBlako/PitchBlk;ProffieOS_V2_Voicepack_Thrawn/common;commonBU", "tracks/MSV.wav",
//Second Sister Base Red
  StylePtr<Layers<
    Mix<SwingSpeed<300>,StyleFire<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<25,0,0>>,Black>,300>,RotateColorsX<Variation,Rgb<40,0,0>>,0,6,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>>,AudioFlicker<RotateColorsX<Variation,Rgb<200,0,0>>,RotateColorsX<Variation,Rgb<20,0,0>>>>,
    BC_effects_Red,
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<Rgb<100,200,255>>,TrFade<1000>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<Rgb<100,200,255>,50>,TrFade<1000>>,EFFECT_IGNITION>,
    // AlphaL<Black,SmoothStep<Scale<SlowNoise<Int<1800>>,Int<22000>,Int<40000>>,Int<24000>>>, // Black cooling tip.....meh
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1800>,Int<235000>>>,TrSparkX<Rgb<100,200,255>,Int<400>,BendTimePowInvX<Int<1800>,Int<210000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    AlphaL<TransitionEffectL<TrConcat<TrFade<3000>,AlphaL<Pulsing<RotateColorsX<Variation,Rgb<128,0,0>>,RotateColorsX<Variation,Red>,350>,Bump<Int<0>,Int<7000>>>,TrInstant>,EFFECT_PREON>,Scale<Trigger<EFFECT_IGNITION,Int<1>,Int<5000>,Int<1>>,Int<32768>,Int<0>>>,
    // Emitter cooldown
    TransitionEffectL<TrConcat<TrInstant,
      AlphaL<Rgb<100,200,255>,Bump<Int<0>,Int<6000>>>,TrFadeX<  Int<1875> >,
      AlphaL<Orange,Bump<Int<0>,Int<4000>>>,TrFadeX<  Int<1875> >,
      AlphaL<Red,Bump<Int<0>,Int<2000>>>,TrFadeX< Int<3750> >>,EFFECT_RETRACTION>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"pitch\nblack"},


{ "a_PONG_KRELL/PongKrll;ProffieOS_V2_Voicepack_Rex/common;commonBU", "a_PONG_KRELL/tracks/Krell.wav",
  StylePtr<Layers<
    Pulsing<Yellow,Chartreuse,20>,
    BC_effects_1,
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<500>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<500>>,EFFECT_IGNITION>,
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1800>,Int<235000>>>,TrSparkX<White,Int<400>,BendTimePowInvX<Int<1800>,Int<210000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"pong\nkrell"},


{ "Proto2;ProffieOS_V2_Voicepack_C-3PO/common;commonBU", "Proto2/tracks/proto2.wav", // Color Cycle to Glitchy Pulsing Blade Default = Green
  StylePtr<Layers<   
    ColorCycle<RotateColorsX<Variation,Rgb<0,128,0>>,100,-3250,RotateColorsX<Variation,BlinkingX<RandomFlicker<RandomBlink<13000,RotateColorsX<Variation,Rgb<128,200,128>>,RotateColorsX<Variation,Black>>,RotateColorsX<Variation,Green>>,RandomFlicker<RotateColorsX<Variation,Rgb<0,128,0>>,RotateColorsX<Variation,Rgb<30,30,30>>>,Scale<SlowNoise<Int<16000>>,Int<300>,Int<1000>>,Scale<SlowNoise<Int<16000>>,Int<200>,Int<650>>>>,50,3000,3000>,
    BC_effects_1,
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<500>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<500>>,EFFECT_IGNITION>,
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1800>,Int<235000>>>,TrSparkX<White,Int<400>,BendTimePowInvX<Int<1800>,Int<210000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"proto 2"},


{ "PsyBorg;ProffieOS_V2_Voicepack_GladOS/common;commonBU", "tracks/FallenOrderTracks/JFO7.wav",
  StylePtr<Layers<
// Main Blade - variation applied 21844 (green)
    // Jedi base Blue
    StripesX<Int<16000>,Int<-1000>,RotateColorsX<Int<21844>,Blue>,Pulsing<RotateColorsX<Int<21844>,Rgb<0,0,90>>,RotateColorsX<Int<21844>,Blue>,800>,RotateColorsX<Int<21844>,Blue>>,
    // Jedi Force Blue
    TransitionEffectL<TrConcat<TrFade<600>,RandomFlicker<RotateColorsX<Variation,Blue>,RotateColorsX<Variation,Rgb<0,0,160>>>,TrDelay<3000>,RotateColorsX<Variation,Blue>,TrFade<800>>,EFFECT_FORCE>,
    // Jedi Swing Blue
    AlphaL<RotateColorsX<Variation,Rgb<70,70,255>>,Scale<IsLessThan<SwingSpeed<600>,Int<13600>>,Scale<SwingSpeed<600>,Int<-19300>,Int<32768>>,Int<0>>>,
    BC_effects_1,
    // Ignition and Retraction
    TransitionEffectL<TrConcat<TrFade<300>,AudioFlickerL<White>,TrFade<500>>,EFFECT_RETRACTION>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,50>,TrFade<500>>,EFFECT_IGNITION>,
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1800>,Int<235000>>>,TrSparkX<White,Int<400>,BendTimePowInvX<Int<1800>,Int<210000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"psyborg"},


{ "a_DARKSABER/DarkV3;ProffieOS_V2_Voicepack_Din_Djarin/common;commonBU", "a_DARKSABER/DarkV3/tracks/Mandalorian.wav",
  StylePtr<Layers<
    Mix<SwingSpeed<400>,RotateColorsX<Variation,Rgb<80,100,150>>,RotateColorsX<Variation,Rgb<130,150,225>>>,
    BrownNoiseFlickerL<Stripes<5000,-300,RotateColorsX<Variation,Rgb<15,25,55>>,RotateColorsX<Variation,Rgb<60,75,120>>,RotateColorsX<Variation,Rgb<0,10,20>>,RotateColorsX<Variation,Rgb<40,50,75>>>,Int<38400>>,
    AudioFlickerL<RotateColorsX<Variation,Rgb<25,35,75>>>,
    AlphaL<RotateColorsX<Variation,Rgb<155,175,225>>,SwingSpeed<600>>,
    BC_effects_White,
    // InOutTrL<TrWipeSparkTipX<White,BendTimePowInvX<Int<1000>,Int<180000>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    InOutTrL<TrJoin<TrWipeX<BendTimePowInvX<Int<1800>,Int<235000>>>,TrSparkX<White,Int<400>,BendTimePowInvX<Int<1800>,Int<210000>>,Int<1600>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"   dark\n    v3"},




// ====================== Good Guys ========================



{"a_LUKE/ESB_Graflex;ProffieOS_V2_Voicepack_Luke_ROTJ/common;commonBU", "a_LUKE/ESB_Graflex/tracks/LvsV.wav", // 6 RandomFlicker Blue base Color Wheel Changeable
  StylePtr<Layers<
    Mix<SwingSpeed<400>,RandomFlicker<RotateColorsX<Variation,Blue>,RotateColorsX<Variation,Rgb<0,0,128>>>,Mix<SwingSpeed<800>,RotateColorsX<Variation,Blue>,RotateColorsX<Variation,Rgb<150,150,255>>>>,
    BC_effects_1,
    // bend
    InOutTrL<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),"esb\ngraflex"},


{ "a_LUKE/LS6;ProffieOS_V2_Voicepack_Luke_ROTJ/common;commonBU", "a_LUKE/LS6/tracks/jabba_scene.wav", // 1 AudioFlicker Green Color Wheel Changeable   
  StylePtr<Layers<
  // Main Blade Color/Styles Base
    // AudioFlicker Default = Green
    AudioFlicker<RotateColorsX<Variation,Green>,RotateColorsX<Variation,Rgb<0,128,0>>>,
    BC_effects_1, 
    // bend
    InOutTrL<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"luke\nskywalker"},


{ "a_LEIA/Royalty;ProffieOS_V2_Voicepack_Luke_ROTJ/common;commonBU", "a_LEIA/Royalty/tracks/Leia1.wav", //  3 AudioFlicker DeepSkyBlue base Color Wheel Changeable
  StylePtr<Layers<
    AudioFlicker<RotateColorsX<Variation,DeepSkyBlue>,RotateColorsX<Variation,Rgb<0,0,128>>>,
    BC_effects_1,
    // bend
    InOutTrL<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"royalty"},


{ "a_REY/Scavengers_Destiny_Ultimate;ProffieOS_V2_Voicepack_Luke_ROTJ/common;commonBU", "a_REY/Scavengers_Destiny_Ultimate/tracks/ReyEp9b.wav", // 5 AudioFlicker Default = Golden Yellow Color Wheel Changeable 
  StylePtr<Layers<
      AudioFlicker<RotateColorsX<Variation,Rgb<180,130,0>>,RotateColorsX<Variation,Rgb<90,65,0>>>,
      BC_effects_1,
    // bend
    InOutTrL<TrWipeX<BendTimePowInvX<Int<1500>,Int<135000>>>,TrWipeInX<BendTimePowX<WavLen<EFFECT_RETRACTION>,Int<180000>>>>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Green,Bump<Int<0>,Int<1000>>>,TrDelay<90>,AlphaL<DodgerBlue,Bump<Int<0>,Int<1000>>>,TrFade<100>,AlphaL<DeepSkyBlue,Bump<Int<0>,Int<1000>>>,TrDelay<200>>,EFFECT_PREON>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"scavenger's\ndestiny"},



{ "aa_Blueforce/LiquidStatic;ProffieOS_V2_Voicepack_Black_Bishop/common;commonBU", "",
  StylePtr<Layers<
    StripesX<Sin<Int<12>,Int<3000>,Int<7000>>,Scale<SwingSpeed<100>,Int<75>,Int<125>>,StripesX<Sin<Int<10>,Int<1000>,Int<3000>>,Scale<SwingSpeed<100>,Int<75>,Int<100>>,Pulsing<Blue,Mix<Int<2570>,Black,Blue>,1200>,Mix<SwingSpeed<200>,Mix<Int<16000>,Black,Blue>,Black>>,Mix<Int<7710>,Black,Blue>,Pulsing<Mix<Int<6425>,Black,Blue>,StripesX<Sin<Int<10>,Int<2000>,Int<3000>>,Sin<Int<10>,Int<75>,Int<100>>,Blue,Mix<Int<12000>,Black,Blue>>,2000>,Pulsing<Mix<Int<16448>,Black,Blue>,Mix<Int<642>,Black,Blue>,3000>>,
    AlphaL<StaticFire<Blue,Mix<Int<256>,Black,Blue>,0,1,10,2000,2>,Int<10000>>,
    AlphaL<LightCyan,SmoothStep<Int<2000>,Int<-6000>>>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,40>,TrFade<1200>>,EFFECT_IGNITION>,
    TransitionEffectL<TrConcat<TrFadeX<WavLen<EFFECT_RETRACTION>>,Stripes<3000,3500,Blue,RandomPerLEDFlicker<Mix<Int<7710>,Black,Blue>,Black>,BrownNoiseFlicker<Blue,Mix<Int<3855>,Black,Blue>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,Blue>,Mix<Int<3855>,Black,Blue>>>,TrInstant>,EFFECT_RETRACTION>,
    BC_effects_1,
    InOutTrL<TrWipeSparkTip<White,300>,TrWipeInSparkTipX<LightCyan,WavLen<EFFECT_RETRACTION>,Int<401>>>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<White,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,Int<2000>,Sum<Int<2000>,Int<4000>>>,Int<-2000>>>,TrDelayX<WavLen<EFFECT_PREON>>>,EFFECT_PREON>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<White,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,Int<2000>,Sum<Int<2000>,Int<3000>>>,Int<-4000>>>,TrDelayX<WavLen<EFFECT_POSTOFF>>>,EFFECT_POSTOFF>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"liquid\nstatic"},


{ "a_KANAN/BlndNite;ProffieOS_V2_Voicepack_Kanan/common;commonBU", "tracks/Kanan2.wav",
    StylePtr<Layers<
    // AudioFlicker<Rgb16<5845,16975,65535>,Blue>,
    BC_12color_8effect_SS, // 1. AudioFlicker 8.DeepSkyBlue
    BC_effects_1,
    InOutTrL<TrWipeSparkTip<White,300>,TrWipeInX<WavLen<EFFECT_RETRACTION>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
  "blind\nknight"},


{ "a_EZRA/StapleSword;ProffieOS_V2_Voicepack_Ezra/common;commonBU", "tracks/EzraTheme.wav",
  StylePtr<Layers<
    // AudioFlicker<Rgb<0,200,0>,Rgb16<11805,52226,29351>>,
    BC_12color_8effect_SS, // 1. AudioFlicker 9.Blue
    BC_effects_1,
    InOutTrL<TrWipeSparkTip<White,300>,TrWipeInX<WavLen<EFFECT_RETRACTION>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
  "staple\nsword"},


{ "a_AHSOKA/AhsokaUltimate;ProffieOS_V2_Voicepack_Ahsoka_CW/common;commonBU", "a_AHSOKA/AhsokaUltimate/tracks/ItsOverNow.wav", // AudioFlicker Bright Swing Color Wheel Changeable - Default = Silver White
  StylePtr<Layers<
    Mix<SwingSpeed<500>,AudioFlicker<RotateColorsX<Variation,Rgb<110,150,255>>,RotateColorsX<Variation,Rgb<80,90,130>>>,Mix<SwingSpeed<800>,AudioFlicker<RotateColorsX<Variation,Rgb<110,150,255>>,RotateColorsX<Variation,White>>,RotateColorsX<Variation,White>>>,
    BC_effects_White,
    InOutTrL<TrWipeSparkTip<White,400>,TrWipeInX<WavLen<EFFECT_RETRACTION>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
  "ahsoka\nultimate"},


{ "a_TEMPLE_GUARD/TempleGuardian;ProffieOS_V2_Voicepack_Skoll/common;commonBU", "a_TEMPLE_GUARD/tracks/TempleGuard.wav",
  StylePtr<Layers<
    BC_12color_8effect_SS, // 4. Pulsing 3.Golden Yellow
    BC_effects_1,
    InOutTrL<TrWipeSparkTip<White,300>,TrWipeInX<WavLen<EFFECT_RETRACTION>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
  "temple\nguardian"},


{ "aa_NoSloppy/Crushed;ProffieOS_V2_Voicepack_Cortana/common;commonBU", "",
  StylePtr<Layers<
    BrownNoiseFlicker<Black,Rgb16<22863,5695,53231>,50>,
    Pulsing<PulsingL<Rgb16<22863,5695,53231>,Int<800>>,Red,1900>,
    AlphaL<StaticFire<Black,BrownNoiseFlicker<Black,Rgb16<22863,5695,53231>,600>,0,4,2,4000,0>,Scale<IsLessThan<SwingSpeed<600>,Int<13600>>,Scale<SwingSpeed<500>,Int<-19300>,Int<32768>>,Int<0>>>,
     BC_effects_Red,
    InOutTrL<TrWipeSparkTip<White,600>,TrWipeInX<WavLen<EFFECT_RETRACTION>>>,
    AlphaL<ColorSelect<WavNum<EFFECT_PREON>,TrInstant,
    Layers<
      TransitionEffectL<TrConcat<TrDelay<200>,AlphaL<Black,Int<0>>,TrFade<1300>,Layers<
      StripesX<Sin<Int<12>,Int<3000>,Int<7000>>,Scale<SwingSpeed<100>,Int<75>,Int<125>>,StripesX<Sin<Int<10>,Int<1000>,Int<3000>>,Scale<SwingSpeed<100>,Int<75>,Int<100>>,Pulsing<RotateColorsX<Variation,Rgb<180,0,0>>,RotateColorsX<Variation,Rgb<15,0,0>>,1200>,Mix<SwingSpeed<200>,RotateColorsX<Variation,Rgb<90,0,0>>,Black>>,RotateColorsX<Variation,Rgb<40,0,0>>,Pulsing<RotateColorsX<Variation,Rgb<36,0,0>>,StripesX<Sin<Int<10>,Int<2000>,Int<3000>>,Sin<Int<10>,Int<75>,Int<100>>,RotateColorsX<Variation,Rgb<180,0,0>>,RotateColorsX<Variation,Rgb<60,0,0>>>,2000>,Pulsing<RotateColorsX<Variation,Rgb<90,0,0>>,RotateColorsX<Variation,Rgb<5,2,0>>,3000>>,
      AlphaL<StyleFire<RotateColorsX<Variation,Rgb<128,0,0>>,RotateColorsX<Variation,Rgb<2,1,0>>,0,1,FireConfig<10,2000,2>,FireConfig<10,2000,2>,FireConfig<10,2000,2>,FireConfig<0,0,25>>,Int<10000>>>,TrDelay<1000>>,EFFECT_PREON>,
      TransitionEffectL<TrConcat<TrFade<1500>,SparkleL<ColorSelect<Sin<Int<1>,Int<68>>,TrFade<300>,Red,Rgb16<22863,5695,53231>,White>,200,500>,TrDelay<1000>>,EFFECT_PREON>,
      TransitionEffectL<TrConcat<TrDelay<1000>,AlphaL<Black,Int<0>>,TrFade<800>,AlphaL<StaticFire<Black,Rgb16<22863,5695,53231>,0,3,0,6000>,Bump<Int<0>,Int<5000>>>,TrInstant,AlphaL<AlphaL<White,NoisySoundLevelCompat>,Bump<Int<0>,Int<25000>>>,TrDelay<700>>,EFFECT_PREON>,
      TransitionEffectL<TrConcat<TrDelay<1000>,AlphaL<Black,Int<0>>,TrFade<700>,AlphaL<StaticFire<Black,Rgb16<22863,5695,53231>,0,3,0,3000>,Int<16000>>,TrDelay<700>>,EFFECT_PREON>>,
    Layers<
      TransitionEffectL<TrConcat<TrInstant,AlphaL<Layers<
      BrownNoiseFlicker<Black,Rgb16<22863,5695,53231>,50>,
      Pulsing<PulsingL<Rgb16<22863,5695,53231>,Int<800>>,Red,1900>>,SmoothStep<Int<5000>,Int<-1>>>,TrDelay<55>,Black,TrDelay<56>,AlphaL<Layers<
      BrownNoiseFlicker<Black,Rgb16<22863,5695,53231>,50>,
      Pulsing<PulsingL<Rgb16<22863,5695,53231>,Int<800>>,Red,1900>>,SmoothStep<Int<9830>,Int<-1>>>,TrDelay<55>,Black,TrDelay<56>,AlphaL<Layers<
      BrownNoiseFlicker<Black,Rgb16<22863,5695,53231>,50>,
      Pulsing<PulsingL<Rgb16<22863,5695,53231>,Int<800>>,Red,1900>>,SmoothStep<Int<14745>,Int<-1>>>,TrDelay<55>,Black,TrDelay<56>,AlphaL<Layers<
      BrownNoiseFlicker<Black,Rgb16<22863,5695,53231>,50>,
      Pulsing<PulsingL<Rgb16<22863,5695,53231>,Int<800>>,Red,1900>>,SmoothStep<Int<19660>,Int<-1>>>,TrDelay<55>,Black,TrDelay<56>,AlphaL<Layers<
      BrownNoiseFlicker<Black,Rgb16<22863,5695,53231>,50>,
      Pulsing<PulsingL<Rgb16<22863,5695,53231>,Int<800>>,Red,1900>>,SmoothStep<Int<24576>,Int<-1>>>,TrDelay<55>,Black,TrDelay<56>,AlphaL<Layers<
      BrownNoiseFlicker<Black,Rgb16<22863,5695,53231>,50>,
      Pulsing<PulsingL<Rgb16<22863,5695,53231>,Int<800>>,Red,1900>>,SmoothStep<Int<29491>,Int<-1>>>,TrDelay<55>,Black,TrDelay<56>,AlphaL<Layers<
      BrownNoiseFlicker<Black,Rgb16<22863,5695,53231>,50>,
      Pulsing<PulsingL<Rgb16<22863,5695,53231>,Int<800>>,Red,1900>>,SmoothStep<Int<32768>,Int<-1>>>,TrDelay<55>,Black,TrDelay<56>>,EFFECT_PREON>>>,Ifon<Int<0>,Int<32768>>>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
  "crushed"},


{ "aa_HarrySolo/WORKBENCH;ProffieOS_V2_Voicepack_Huyang/common;commonBU", "",
  StylePtr<
  Layers<Black,
      AlphaL<Layers< //Swing color
        AlphaL<HumpFlicker<Blue,Rgb<0,0,100>,50>,SmoothStep<Int<8000>,Int<-3000>>>,
        AlphaL<HumpFlicker<Cyan,Rgb<0,120,200>,50>,SmoothStep<Int<2500>,Int<-6000>>>>,
      SmoothStep<Scale<SwingSpeed<250>,Int<-2000>,Int<16000>>,Int<-2000>>>,
    TransitionLoopL<TrConcat<TrFade<1000>,AlphaL<RotateColorsX<Variation,Rgb<100,90,150>>,Bump<Int<0>,ChangeSlowly<NoisySoundLevel,Int<50000>>>>,TrDelay<3000>,AlphaL<RotateColorsX<Variation,Rgb<100,90,150>>,Bump<Int<0>,ChangeSlowly<NoisySoundLevel,Int<50000>>>>,TrFade<1000>,AlphaL<Black,Int<0>>,TrDelay<2000>>>,
  ColorSelect<WavNum<EFFECT_CLASH>,TrInstant,
    //clsh01.wav handle with care
    Layers<
    TransitionEffectL<TrConcat<TrInstant,HumpFlicker<White,Black,50>,TrWipeIn<560>>,EFFECT_CLASH>,
    TransitionEffectL<TrConcat<TrDelay<70>,AlphaL<Red,SmoothStep<Int<5000>,Int<-1>>>,TrFade<250>,Black,TrInstant,AlphaL<Red,SmoothStep<Int<5000>,Int<-1>>>,TrFade<250>,Black,TrInstant,AlphaL<Red,SmoothStep<Int<5000>,Int<-1>>>,TrFade<250>>,EFFECT_CLASH>>,
    // clsh02.wav excessive impact
    TransitionEffectL<TrConcat<TrInstant,White,TrDelay<20>,Blinking<AlphaL<BrownNoiseFlicker<Red,DarkOrange,500>,Bump<Int<0>,Int<60000>>>,Black,100,500>,TrJoin<TrFade<1200>,TrWipeIn<1200>>>,EFFECT_CLASH>,
    // clash03.wav please stop
    Layers<
    TransitionEffectL<TrJoin<TrSparkX<BrownNoiseFlicker<Red,DarkOrange,500>,Int<100>,Int<800>,Int<0>>,TrConcat<TrDelay<300>,AlphaL<Black,Int<0>>,TrFade<300>,AlphaL<White,Bump<Int<0>,Int<30000>>>,TrFade<500>>>,EFFECT_CLASH>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<RotateColorsX<Variation,Red>,Bump<Int<0>,Int<3000>>>,TrDelay<500>,AlphaL<Black,Int<0>>,TrDelay<350>,AlphaL<RotateColorsX<Variation,Red>,Bump<Int<0>,Int<3000>>>,TrDelay<500>,AlphaL<Black,Int<0>>,TrDelay<350>,AlphaL<RotateColorsX<Variation,Red>,Bump<Int<0>,Int<3000>>>,TrDelay<500>,AlphaL<Black,Int<0>>,TrInstant>,EFFECT_CLASH>>,
    // clsh04.wav dueling prohibited
    Layers<
    TransitionEffectL<TrConcat<TrInstant,AlphaL<RotateColorsX<Variation,Red>,Bump<Int<0>,Int<3000>>>,TrDelay<500>,AlphaL<Black,Int<0>>,TrDelay<716>,AlphaL<RotateColorsX<Variation,Red>,Bump<Int<0>,Int<3000>>>,TrDelay<500>,AlphaL<Black,Int<0>>,TrDelay<716>,AlphaL<RotateColorsX<Variation,Red>,Bump<Int<0>,Int<3000>>>,TrDelay<500>,AlphaL<Black,Int<0>>,TrInstant>,EFFECT_CLASH>,
    TransitionEffectL<TrJoin<TrSparkX<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,DarkOrange>,500>,Int<100>,Int<800>,Int<0>>,TrConcat<TrDelay<266>,AlphaL<Black,Int<0>>,TrBoing<250,1>,AlphaL<Red,Bump<Int<0>>>,TrWipeIn<250>>>,EFFECT_CLASH>>,
    // clash05.wav not best idea
    Layers<
    TransitionEffectL<TrConcat<TrDelay<100>,AlphaL<Black,Int<0>>,TrFade<100>,AlphaL<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,DarkOrange>,500>,SmoothStep<Int<6000>,Int<-5000>>>,TrFade<100>,AlphaL<OrangeRed,SmoothStep<Int<1000>,Int<-5000>>>,TrFade<200>>,EFFECT_CLASH>,
    TransitionEffectL<TrJoin<TrConcat<TrInstant,AlphaL<White,Bump<Int<0>,Int<8000>>>,TrFade<200>>,TrSparkX<White,Int<500>,Int<300>,Int<0>>>,EFFECT_CLASH>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Black,SmoothStep<Int<8000>,Int<6000>>>,TrDelay<300>>,EFFECT_CLASH>>>,
    ColorSelect<WavNum<EFFECT_BLAST>,TrInstant,
      // blst01.wav repair completed
      TransitionEffectL<TrConcat<TrBoing<1300,8>,AlphaL<PulsingL<HumpFlickerL<RotateColorsX<Variation,Rgb<0,40,255>>,50>,Int<800>>,LinearSectionF<Bump<Int<16384>>,Sin<Int<100>>>>,TrWipe<460>,HumpFlickerL<RotateColorsX<Variation,Rgb<0,40,255>>,50>,TrDelay<300>>,EFFECT_BLAST>,
      // blst02.wav repair failed
      TransitionEffectL<TrConcat<TrBoing<250,3>,AlphaL<BlinkingL<HumpFlickerL<RotateColorsX<Variation,Rgb<0,40,255>>,50>,Int<160>,Int<500>>,LinearSectionF<Sin<Int<500>,Int<8000>,Int<-10000>>,Int<25000>>>,TrWipeInSparkTip<Red,300>,BlinkingL<AlphaL<HumpFlickerL<Red,50>,SmoothStep<Int<1000>,Int<-1>>>,Int<500>,Int<500>>,TrDelay<1530>>,EFFECT_BLAST>,
      // blst03.wav repair interrupted
      TransitionEffectL<TrConcat<TrInstant,AlphaL<Blinking<RotateColorsX<Variation,Rgb<128,128,200>>,Blue,400,500>,LinearSectionF<Sin<Int<400>,Int<32768>,Int<-500>>,Scale<RandomF,Int<100>,Int<1000>>>>,TrDelay<2000>,AlphaL<Black,Int<0>>,TrBoing<300,1>,AlphaL<White,Bump<Int<0>>>,TrInstant>,EFFECT_BLAST>,
      // blst04.wav no deflecting please
      TransitionEffectL<TrConcat<TrBoing<300,1>,AlphaL<Red,Bump<Int<0>>>,TrWipeIn<100>,PulsingL<AlphaL<HumpFlickerL<Red,50>,SmoothStep<Int<1000>,Int<-1>>>,Int<800>>,TrDelay<4380>,AlphaL<White,LinearSectionF<Sin<Int<300>>,Sin<Int<200>,Int<1000>>>>,TrDelay<450>>,EFFECT_BLAST>>,
    // force
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Blinking<RotateColorsX<Variation,Rgb<128,128,200>>,Blue,400,500>,LinearSectionF<Sin<Int<300>,Int<32768>,Int<-500>>,Scale<RandomF,Int<300>,Int<1000>>>>,TrFade<1075>,AlphaL<Black,Int<0>>,TrJoin<TrCenterWipeX<Int<1000>>,TrWaveX<White,Int<1000>,Int<200>,Int<2000>>>,Layers<
      AlphaL<White,LayerFunctions<SmoothStep<Scale<RandomF,Int<-5000>,Int<2000>>,Int<-1>>,SmoothStep<Scale<RandomF,Int<37768>,Int<30768>>,Int<1>>>>,
      AlphaL<ColorSequence<500,DarkOrange,Green,Blue>,LinearSectionF<Sin<Int<100>,Int<32768>,Int<-500>>,Scale<RandomF,Int<300>,Int<2000>>>>>,TrDelay<2750>,AlphaL<Black,Int<0>>,TrConcat<TrBoing<650,5>,AlphaL<HumpFlickerL<Green,50>,LayerFunctions<SmoothStep<Int<30768>,Int<1>>,SmoothStep<Int<2000>,Int<-1>>>>,TrInstant>>,EFFECT_FORCE>,
    LockupTrL<Layers<
      AudioFlicker<RotateColorsX<Variation,DodgerBlue>,RotateColorsX<Variation,Rgb16<0,43202,44565>>>,
      TransitionLoopL<TrConcat<TrDelayX<Scale<RandomF,Int<700>,Int<4000>>>,AlphaL<White,LinearSectionF<RandomF,Int<500>>>,TrDelay<400>>>,
      Layers<
        TransitionEffectL<TrConcat<TrDelayX<Int<8738>>,AlphaL<RotateColorsX<Variation,Cyan>,LayerFunctions<Bump<Int<0>>,Bump<Int<32768>>>>,TrBoing<735,3>,AlphaL<Black,Int<0>>,TrDelay<7118>,AlphaL<RotateColorsX<Variation,Cyan>,LayerFunctions<Bump<Int<0>>,Bump<Int<32768>>>>,TrBoing<951,3>,AlphaL<Black,Int<0>>,TrDelay<6273>,AlphaL<RotateColorsX<Variation,Cyan>,LayerFunctions<Bump<Int<0>>,Bump<Int<32768>>>>,TrBoing<735,3>,AlphaL<Black,Int<0>>,TrDelay<7118>,AlphaL<RotateColorsX<Variation,Cyan>,LayerFunctions<Bump<Int<0>>,Bump<Int<32768>>>>,TrBoing<951,3>,AlphaL<Black,Int<0>>,TrDelay<4546>>,EFFECT_LOCKUP_BEGIN>,
        TransitionEffectL<TrConcat<TrDelay<10300>,AlphaL<Black,Int<0>>,TrFade<400>,BrownNoiseFlicker<RotateColorsX<Variation,Cyan>,Black,500>,TrFade<300>,AlphaL<Black,Int<0>>,TrDelay<7767>,AlphaL<Black,Int<0>>,TrFade<400>,BrownNoiseFlicker<RotateColorsX<Variation,Cyan>,Black,500>,TrFade<300>,AlphaL<Black,Int<0>>,TrDelay<5990>,AlphaL<Black,Int<0>>,TrFade<400>,BrownNoiseFlicker<RotateColorsX<Variation,Cyan>,Black,500>,TrFade<300>,AlphaL<Black,Int<0>>,TrDelay<7784>,AlphaL<Black,Int<0>>,TrFade<400>,BrownNoiseFlicker<RotateColorsX<Variation,Cyan>,Black,500>,TrFade<300>>,EFFECT_LOCKUP_BEGIN>>>,TrConcat<TrBoing<300,2>,AlphaL<AudioFlicker<RotateColorsX<Variation,DodgerBlue>,RotateColorsX<Variation,Rgb16<0,43202,44565>>>,Bump<Int<0>>>,TrWipe<275>>,TrWipeIn<500>,SaberBase::LOCKUP_NORMAL>,
      ColorSelect<WavNum<EFFECT_LOCKUP_END>,TrInstant,
        // endlock1.wav success
        TransitionEffectL<TrConcat<TrWipeIn<500>,Black,TrInstant,White,TrDelay<25>,Black,TrFade<500>,HumpFlickerL<RotateColorsX<Variation,Rgb<0,40,255>>,100>,TrDelay<100>>,EFFECT_LOCKUP_END>,
        // endlock2.wav fail
        TransitionEffectL<TrConcat<TrWipeInSparkTip<White,460>,Black,TrBoing<250,2>,AlphaL<RotateColorsX<Variation,DodgerBlue>,SmoothStep<Int<12000>,Int<-1>>>,TrInstant,AlphaL<ColorSequence<75,Cyan,Black,Red,Black,Blue,DodgerBlue,Rgb<50,50,0>,Black>,SmoothStep<Scale<RandomF,Int<0>,Int<1500>>,Int<-1>>>,TrDelay<2673>>,EFFECT_LOCKUP_END>>,
    InOutTrL<TrJoin<TrConcat<TrInstant,AlphaL<White,Bump<Int<0>>>,TrFade<200>>,TrSparkX<White,Int<300>,Int<200>,Int<0>>>,TrConcat<TrBoing<2737,31>,AlphaL<AlphaL<DodgerBlue,Bump<Int<0>,Scale<Trigger<EFFECT_RETRACTION,Int<2737>,Int<1000>,Int<500>>,Int<65000>,Int<0>>>>,Scale<Trigger<EFFECT_RETRACTION,Int<2737>,Int<1000>,Int<500>>,Int<32768>,Int<0>>>,TrInstant>>,
    TransitionEffectL<TrConcat<TrDelay<150>,AlphaL<Black,Int<0>>,TrBoing<300,2>,AlphaL<HumpFlickerL<White,50>,Bump<Int<0>,Int<16000>>>,TrDelay<400>,AlphaL<HumpFlickerL<White,50>,Bump<Int<0>,Int<16000>>>,TrConcat<TrFade<407>,AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<0,40,255>>,50>,Bump<Int<0>,Int<25000>>>,TrInstant>>,EFFECT_PREON>,
    TransitionEffectL<TrJoin<TrConcat<TrInstant,AlphaL<White,Bump<Int<0>,Int<8000>>>,TrFade<200>>,TrSparkX<White,Int<500>,Int<300>,Int<0>>>,EFFECT_PREON>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Black,SmoothStep<Int<8000>,Int<6000>>>,TrDelay<300>>,EFFECT_PREON>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<RotateColorsX<Variation,DodgerBlue>,Bump<Int<0>,ChangeSlowly<NoisySoundLevel,Int<50000>>>>,TrFadeX<Percentage<WavLen<>,50>>>,EFFECT_POSTOFF>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<ColorSequence<75,Cyan,Black,Green,Black,Blue,Black,Rgb<50,50,0>,Black>,SmoothStep<Sin<Int<300>,Int<0>,Int<12000>>,Int<-1>>>,TrDelay<700>,AlphaL<RandomFlicker<Rgb<70,100,200>,ColorSequence<350,Cyan,Green,Blue,Rgb<50,50,0>,Black>>,SmoothStep<Scale<Trigger<EFFECT_BOOT,Int<4000>,Int<1000>,Int<500>>,Int<20000>,Int<0>>,Int<-1>>>,TrDelay<4300>>,EFFECT_BOOT>,
    TransitionEffectL<TrConcat<TrDelay<1000>,BlinkingL<AlphaL<HumpFlickerL<Red,50>,SmoothStep<Int<1000>,Int<-1>>>,Int<500>,Int<500>>,TrFade<4026>>,EFFECT_BOOT>,
    TransitionEffectL<TrConcat<TrFade<1000>,AlphaL<AudioFlicker<Rgb<100,90,150>,Black>,Bump<Int<0>,ChangeSlowly<NoisySoundLevel,Int<50000>>>>,TrFade<250>,AlphaL<DodgerBlue,Bump<Int<0>,Int<60000>>>,TrWipeIn<100>>,EFFECT_NEWFONT>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"workbench"},


{"a_SHIPS/Falcon;ProffieOS_V2_Voicepack_Luke_ROTJ/common;commonBU", "a_SHIPS/Falcon/tracks/Falcon.wav", // 11 Stripes based Pulse - Default = Blue Color Wheel Changeable   
  StylePtr<Layers<    
    Stripes<10000,-2000,RotateColorsX<Variation,DeepSkyBlue>,RotateColorsX<Variation,Rgb<0,0,128>>>,
    BC_effects_1, 
    // Engines Starting Ignition, cyle down retraction
    InOutTrL<TrJoin<TrWipe<500>,TrWipeIn<500>>,TrColorCycle<6000,-600,-100>>,
    TransitionEffectL<TrConcat<TrInstant,StrobeL<AlphaL<White,LayerFunctions<Bump<Int<0>>,Bump<Int<32768>>>>,Int<25>,Int<30>>,TrFade<1500>>,EFFECT_IGNITION>,
    TransitionEffectL<TrConcat<TrInstant,White,TrFade<50>>,EFFECT_IGNITION>,
    TransitionEffectL<TrConcat<TrFadeX< Percentage<WavLen<EFFECT_PREON>,30> >,AlphaL<BrownNoiseFlicker<RotateColorsX<Variation,DeepSkyBlue>,Rgb<100,100,150>,300>,LayerFunctions<Bump<Int<0>,Int<10000>>,Bump<Int<32768>,Int<10000>>>>,TrDelayX< Percentage<WavLen<EFFECT_PREON>,70> >>,EFFECT_PREON>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"millenium\nfalcon"},

{"a_SHIPS/Tie;ProffieOS_V2_Voicepack_Luke_ROTJ/common;commonBU", "a_SHIPS/Tie/tracks/Tie.wav", // 11 Stripes based Pulse - Default = Green Color Wheel Changeable   
  StylePtr<Layers< 
    Stripes<10000,-2000,RotateColorsX<Variation,Green>,RotateColorsX<Variation,Rgb<0,60,0>>,RotateColorsX<Variation,Rgb<50,255,50>>,RotateColorsX<Variation,Rgb<0,128,0>>>,
    BC_effects_1, 
    // Engines Starting Ignition, cyle down retraction
    InOutTrL<TrJoin<TrWipe<500>,TrWipeIn<500>>,TrColorCycle<6000,-600,-100>>,
    TransitionEffectL<TrConcat<TrInstant,StrobeL<AlphaL<White,LayerFunctions<Bump<Int<0>>,Bump<Int<32768>>>>,Int<25>,Int<30>>,TrFade<1500>>,EFFECT_IGNITION>,
    TransitionEffectL<TrConcat<TrInstant,White,TrFade<50>>,EFFECT_IGNITION>,
    TransitionEffectL<TrConcat<TrFadeX< Percentage<WavLen<EFFECT_PREON>,30> >,AlphaL<BrownNoiseFlicker<RotateColorsX<Variation,Green>,Rgb<100,100,150>,300>,LayerFunctions<Bump<Int<0>,Int<10000>>,Bump<Int<32768>,Int<10000>>>>,TrDelayX< Percentage<WavLen<EFFECT_PREON>,70> >>,EFFECT_PREON>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"tie\nfighter"},


{"a_SHIPS/Xwing;ProffieOS_V2_Voicepack_Luke_ROTJ/common;commonBU", "a_SHIPS/Xwing/tracks/Xwing.wav", // 11 Stripes Pulse - Default = Red base Color Wheel Changeable   
    StylePtr<Layers<    
        Stripes<10000,-2000,RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<60,0,0>>,RotateColorsX<Variation,Rgb<255,50,50>>,RotateColorsX<Variation,Rgb<128,0,0>>>,
        BC_effects_Red, 
    // Engines Starting Ignition, cyle down retraction
        InOutTrL<TrJoin<TrWipe<500>,TrWipeIn<500>>,TrColorCycle<6000,-600,-100>>,
        TransitionEffectL<TrConcat<TrInstant,StrobeL<AlphaL<White,LayerFunctions<Bump<Int<0>>,Bump<Int<32768>>>>,Int<25>,Int<30>>,TrFade<1500>>,EFFECT_IGNITION>,
        TransitionEffectL<TrConcat<TrInstant,White,TrFade<50>>,EFFECT_IGNITION>,
        TransitionEffectL<TrConcat<TrFadeX< Percentage<WavLen<EFFECT_PREON>,30> >,AlphaL<BrownNoiseFlicker<RotateColorsX<Variation,Red>,Rgb<100,100,150>,300>,LayerFunctions<Bump<Int<0>,Int<10000>>,Bump<Int<32768>,Int<10000>>>>,TrDelayX< Percentage<WavLen<EFFECT_PREON>,70> >>,EFFECT_PREON>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"x-wing\nfighter"},


{"a_SHIPS/Slave1_2.1_Proffie;ProffieOS_V2_Voicepack_Luke_ROTJ/common;commonBU", "a_SHIPS/Slave1/tracks/Pursuit.wav", // Center out stripes - custom preon and ignition
// Slave 1 with seismic charge preon and USER2
   
 StylePtr<Layers<
  Mix<SmoothStep<Int<16384>,Int<4000>>,Stripes<10000,500,Rgb<0,30,80>,Rgb<0,60,180>>,Stripes<10000,-500,Rgb<0,30,80>,Rgb<0,60,180>>>,
// Dim Blade 50% "Power Save" button combo
  EffectSequence<EFFECT_POWERSAVE,
  AlphaL<Black,Int<16384>>,
  AlphaL<Black,Int<0>>>,
// Clash - 3 stage fading impact spot
    TransitionEffectL<TrConcat<TrInstant,GreenYellow,TrDelay<25>,AlphaL<TransitionEffect<BrownNoiseFlicker<Rgb<255,150,0>,Black,50>,Moccasin,TrInstant,TrFade<300>,EFFECT_CLASH>,Bump<Scale<BladeAngle<>,Int<25000>,Int<8000>>,Int<18000>>>,TrFade<600>>,EFFECT_CLASH>,
// Stab 
    TransitionEffectL<TrConcat<TrInstant,GreenYellow,TrDelay<25>,AlphaL<Black,Int<0>>,TrWipeIn<300>,AlphaL<Stripes<5000,1000,DarkOrange,Rgb<80,60,0>,Orange,Rgb<60,30,0>,Black,DarkOrange,Orange>,SmoothStep<Int<20000>,Int<2000>>>,TrJoin<TrSmoothFade<900>,TrWipe<700>>>,EFFECT_STAB>,
// Blast
    MultiTransitionEffectL<TrConcat<TrDelay<700>,AlphaL<Black,Int<0>>,TrFade<800>,LocalizedClashL<HumpFlicker<DarkOrange,Red,50>,2000,50,EFFECT_BLAST>,TrFade<600>>,EFFECT_BLAST>,
    LocalizedClashL<Blinking<White,Black,130,800>,1560,50,EFFECT_BLAST>,
    LocalizedClashL<Blinking<Red,Black,130,500>,1560,15,EFFECT_BLAST>,
// Lockup
    LockupTrL<Layers<
       AlphaL<Blinking<Tomato,Strobe<Yellow,Black,15,30>,60,500>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SlowNoise<Int<3000>>,Int<8000>,Int<18000>>>>,
       AlphaL<BrownNoiseFlicker<Yellow,Black,50>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,
     TrConcat<TrInstant,
       AlphaL<Blinking<White,Strobe<BrownNoiseFlicker<Yellow,Black,500>,Black,15,30>,60,500>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SlowNoise<Int<3000>>,Int<25000>,Int<32000>>>>,TrFade<500>>,TrSmoothFade<900>,SaberBase::LOCKUP_NORMAL>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Strobe<GreenYellow,Black,20,30>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<15000>>>,TrFade<600>>,EFFECT_LOCKUP_BEGIN>,
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<Strobe<AlphaL<White,Int<20000>>,Black,20,30>,30>,TrSmoothFade<250>>,EFFECT_LOCKUP_BEGIN>,
    TransitionEffectL<TrConcat<TrInstant,Strobe<GreenYellow,Black,20,30>,TrFade<100>>,EFFECT_LOCKUP_BEGIN>,
    TransitionEffectL<TrConcat<TrInstant,Strobe<GreenYellow,Black,20,30>,TrFade<200>,BrownNoiseFlickerL<AlphaL<White,Int<16000>>,Int<50>>,TrJoinR<TrWipe<200>,TrWipeIn<200>,TrFade<300>>>,EFFECT_LOCKUP_END>,
// Non-Responsive Drag
    LockupTrL<AlphaL<AudioFlicker<BrownNoiseFlicker<Strobe<Black,OrangeRed,20,25>,Yellow,200>,White>,SmoothStep<Int<30000>,Int<2000>>>,TrConcat<TrInstant,GreenYellow,TrDelay<25>,AlphaL<Black,Int<0>>,TrFade<150>>,TrColorCycle<1500,-2000,100>,SaberBase::LOCKUP_DRAG>,
// Lightning Block    
    ResponsiveLightningBlockL<RandomFlicker<Strobe<White,Rgb16<21301,0,65535>,50,10>,BrownNoiseFlicker<Rgb16<21301,0,65535>,Black,500>>,
    //Begin Lightning Transition
      TrConcat<TrInstant,GreenYellow,TrDelay<25>,BrownNoiseFlicker<Rgb16<21301,0,65535>,Black,500>,TrFade<100>>,
    //End Lightning Transition
      TrConcat<TrInstant,GreenYellow,TrDelay<25>,BrownNoiseFlicker<Rgb16<21301,0,65535>,Black,500>,TrFade<150>,BrownNoiseFlickerL<AlphaL<White,Int<16000>>,Int<50>>,TrJoinR<TrWipe<200>,TrWipeIn<200>,TrFade<400>> >>,  
// Melt
    LockupTrL<
    //Mely Colors
    AlphaL<Mix<TwistAngle<>,Yellow,RandomPerLEDFlicker<Orange,OrangeRed>,BrownNoiseFlicker<Rgb16<20095,128,128>,Rgb16<35103,8175,298>,150>,StyleFire<Rgb16<20393,93,93>,Red,0,4,FireConfig<0,2000,5>,FireConfig<3000,0,0>,FireConfig<0,4000,0>>>,
    // Melt Shape
    SmoothStep<Scale<TwistAngle<>,Int<24000>,Int<29000>>,Int<2000>>>,
    //Melt Begin and End transitions
    TrConcat<TrInstant,GreenYellow,TrDelay<25>,AlphaL<Black,Int<0>>,TrWipeIn<600>>,TrColorCycle<1500,-2000,100>,SaberBase::LOCKUP_MELT>,

  // ===== EFFECT_USER2: Preon -> Ignition (blade already on) =====
  // Hold blade dark until preon is done, then reveal with center wipe
  TransitionEffectL<TrConcat<TrInstant,Black,TrDelay<3025>,TrCenterWipe<300>>,EFFECT_USER2>,

  // Preon layers
  TransitionEffectL<TrConcat<TrDelay<2125>,Cyan,TrFade<100>,Black,TrDelay<10>,Cyan,TrFade<150>>,EFFECT_USER2>,
  TransitionEffectL<TrConcat<TrDelay<2125>,AlphaL<White,Bump<Int<16384>,Int<32768>>>,TrFade<100>,Black,TrDelay<10>,AlphaL<White,Bump<Int<16384>,Int<32768>>>,TrFade<150>>,EFFECT_USER2>,
  TransitionEffectL<TrConcat<TrDelay<2100>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<3000>>>,TrDelay<100>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<4000>>>,
    TrSmoothFade<50>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<5000>>>,
    TrSmoothFade<50>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<10000>>>,
    TrSmoothFade<50>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<20000>>>,
    TrSmoothFade<175>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<30000>>>,
    TrSmoothFade<125>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<35000>>>,
    TrSmoothFade<150>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<30000>>>,
    TrSmoothFade<75>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<20000>>>,
    TrSmoothFade<50>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<8000>>>,
    TrSmoothFade<25>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<3000>>>,TrFade<50>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<20000>>>,TrDelay<25>>,EFFECT_USER2>,
  TransitionEffectL<TrConcat<TrInstant,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Scale<Trigger<EFFECT_USER2,Int<2000>,Int<1000>,Int<500>>,Int<-1000>,Int<16500>>,Int<1500>>>,TrDelay<2000>>,EFFECT_USER2>,
  TransitionEffectL<TrConcat<TrDelay<1100>,AlphaL<Red,Int<0>>,TrSmoothFade<700>,Black,TrDelay<100>,AlphaL<White,Bump<Int<16384>,Int<3000>>>,TrDelay<100>>,EFFECT_USER2>,

  // Ignition layers, shifted by preon duration
  TransitionEffectL<TrConcat<TrDelay<3025>,Cyan,TrDelay<50>>,EFFECT_USER2>,
  TransitionEffectL<TrConcat<TrDelay<3025>,TrInstant,BrownNoiseFlicker<DeepSkyBlue,White,100>,TrFade<800>>,EFFECT_USER2>,
  TransitionEffectL<TrConcat<
    TrDelay<3025>,
    TrDelay<1500>,GreenYellow,TrDelay<25>,AlphaL<BrownNoiseFlicker<Red,White,100>,Bump<Scale<SlowNoise<Int<30000>>,Int<3000>,Int<6000>>,ChangeSlowly<SlowNoise<Int<30000>>,Int<20000>>>>,TrDelay<100>,AlphaL<Red,Int<0>>,
    TrDelay<400>,GreenYellow,TrDelay<25>,AlphaL<BrownNoiseFlicker<Orange,White,100>,Bump<Scale<SlowNoise<Int<30000>>,Int<6000>,Int<10000>>,ChangeSlowly<SlowNoise<Int<30000>>,Int<20000>>>>,TrDelay<100>,AlphaL<Red,Int<0>>,
    TrDelay<200>,GreenYellow,TrDelay<25>,AlphaL<BrownNoiseFlicker<Black,White,100>,Bump<ChangeSlowly<SlowNoise<Int<30000>>,Int<60000>>,ChangeSlowly<SlowNoise<Int<30000>>,Int<20000>>>>,TrDelay<300>,AlphaL<Red,Int<0>>,
    TrDelay<200>,GreenYellow,TrDelay<25>,AlphaL<BrownNoiseFlicker<Yellow,Red,100>,Bump<Scale<SlowNoise<Int<30000>>,Int<10000>,Int<28000>>,ChangeSlowly<SlowNoise<Int<30000>>,Int<20000>>>>,TrDelay<200>,AlphaL<Red,Int<0>>,
    TrDelay<500>,GreenYellow,TrDelay<25>,AlphaL<BrownNoiseFlicker<Orange,White,100>,Bump<ChangeSlowly<SlowNoise<Int<30000>>,Int<60000>>,ChangeSlowly<SlowNoise<Int<30000>>,Int<20000>>>>,TrDelay<200>,AlphaL<Red,Int<0>>,
    TrDelay<100>,GreenYellow,TrDelay<25>,AlphaL<BrownNoiseFlicker<Red,White,100>,Bump<Scale<SlowNoise<Int<30000>>,Int<5000>,Int<13000>>,ChangeSlowly<SlowNoise<Int<30000>>,Int<20000>>>>,TrDelay<100>,AlphaL<Red,Int<0>>,
    TrDelay<500>,GreenYellow,TrDelay<25>>,EFFECT_USER2>,

// Ignition Powerup
    TransitionEffectL<TrConcat<TrInstant,BrownNoiseFlicker<DeepSkyBlue,White,100>,TrFade<800>>,EFFECT_IGNITION>,
// In/out using Trigger for instantaneous Center-out wipes
   InOutTrL<TrConcat<TrInstant,Layers<
    AlphaL<Black,SmoothStep<Scale<Trigger<EFFECT_IGNITION,Int<300>,Int<1000>,Int<500>>,Int<16385>,Int<0>>,Int<-1>>>,
    AlphaL<Black,SmoothStep<Scale<Trigger<EFFECT_IGNITION,Int<300>,Int<1000>,Int<500>>,Int<16384>,Int<32768>>,Int<0>>>>,TrDelay<1000>>,TrJoin<TrWipe<700>,TrWipeIn<700>>>,
   TransitionEffectL<TrConcat<TrInstant,Cyan,TrDelay<50>>,EFFECT_IGNITION>,
// Asteroid impacts after detonation - timed sequence
   TransitionEffectL<TrConcat<
    TrDelay<1500>,GreenYellow,TrDelay<25>,AlphaL<BrownNoiseFlicker<Red,White,100>,Bump<Scale<SlowNoise<Int<30000>>,Int<3000>,Int<6000>>,ChangeSlowly<SlowNoise<Int<30000>>,Int<20000>>>>,TrDelay<100>,AlphaL<Red,Int<0>>,
    TrDelay<400>,GreenYellow,TrDelay<25>,AlphaL<BrownNoiseFlicker<Orange,White,100>,Bump<Scale<SlowNoise<Int<30000>>,Int<6000>,Int<10000>>,ChangeSlowly<SlowNoise<Int<30000>>,Int<20000>>>>,TrDelay<100>,AlphaL<Red,Int<0>>,
    TrDelay<200>,GreenYellow,TrDelay<25>,AlphaL<BrownNoiseFlicker<Black,White,100>,Bump<ChangeSlowly<SlowNoise<Int<30000>>,Int<60000>>,ChangeSlowly<SlowNoise<Int<30000>>,Int<20000>>>>,TrDelay<300>,AlphaL<Red,Int<0>>,
    TrDelay<200>,GreenYellow,TrDelay<25>,AlphaL<BrownNoiseFlicker<Yellow,Red,100>,Bump<Scale<SlowNoise<Int<30000>>,Int<10000>,Int<28000>>,ChangeSlowly<SlowNoise<Int<30000>>,Int<20000>>>>,TrDelay<200>,AlphaL<Red,Int<0>>,
    TrDelay<500>,GreenYellow,TrDelay<25>,AlphaL<BrownNoiseFlicker<Orange,White,100>,Bump<ChangeSlowly<SlowNoise<Int<30000>>,Int<60000>>,ChangeSlowly<SlowNoise<Int<30000>>,Int<20000>>>>,TrDelay<200>,AlphaL<Red,Int<0>>,
    TrDelay<100>,GreenYellow,TrDelay<25>,AlphaL<BrownNoiseFlicker<Red,White,100>,Bump<Scale<SlowNoise<Int<30000>>,Int<5000>,Int<13000>>,ChangeSlowly<SlowNoise<Int<30000>>,Int<20000>>>>,TrDelay<100>,AlphaL<Red,Int<0>>,
    TrDelay<500>,GreenYellow,TrDelay<25>>,EFFECT_IGNITION>,
// Seismic Charge preon effect. use with linked preon sound
  TransitionEffectL<TrConcat<TrDelay<2125>,Cyan,TrFade<100>,Black,TrDelay<10>,Cyan,TrFade<150>  >,EFFECT_PREON>,
  TransitionEffectL<TrConcat<TrDelay<2125>,AlphaL<White,Bump<Int<16384>,Int<32768>>>,TrFade<100>, Black,TrDelay<10>,AlphaL<White,Bump<Int<16384>,Int<32768>>>,TrFade<150>  >,EFFECT_PREON>,
  TransitionEffectL<TrConcat<TrDelay<2100>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<3000>>>,TrDelay<100>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<4000>>>,
    TrSmoothFade<50>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<5000>>>,
    TrSmoothFade<50>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<10000>>>,
    TrSmoothFade<50>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<20000>>>,
    TrSmoothFade<175>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<30000>>>,
    TrSmoothFade<125>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<35000>>>,
    TrSmoothFade<150>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<30000>>>,
    TrSmoothFade<75>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<20000>>>,
    TrSmoothFade<50>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<8000>>>,
    TrSmoothFade<25>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<3000>>>,TrFade<50>,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Int<16384>,Int<20000>>>,TrDelay<25>>,EFFECT_PREON>,

  TransitionEffectL<TrConcat<TrInstant,AlphaL<BrownNoiseFlicker<DeepSkyBlue,White,100>,Bump<Scale<Trigger<EFFECT_PREON,Int<2000>,Int<1000>,Int<500>>,Int<-1000>,Int<16500>>,Int<1500>>>,TrDelay<2000>>,EFFECT_PREON>,
  TransitionEffectL<TrConcat<TrDelay<1100>,AlphaL<Red,Int<0>>,TrSmoothFade<700>,Black,TrDelay<100>,AlphaL<White,Bump<Int<16384>,Int<3000>>>,TrDelay<100>>,EFFECT_PREON>,
    // On-Demand
    OnDemandVolumeLevel,
    OnDemandBatteryLevel
  >>(),
// Button
  StylePtr<Layers<White,InOutTrL<TrFade<300>,TrFade<300>>>>(),
"slave 1"},

};


struct AccentsLED {
static constexpr float MaxAmps = 0.02;
static constexpr float MaxVolts = 3.2;
static constexpr float P2Amps = 0.10;
static constexpr float P2Volts = 3.0;
static constexpr float R = 0; // Resistor value
static const int Red = 0;
static const int Green = 0;
static const int Blue = 255;
};


BladeConfig blades[] = {

{ 0,
  WS281XBladePtr<144, bladePin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3> >(),                                   // Main Blade
  SimpleBladePtr<AccentsLED, NoLED, NoLED, NoLED, bladePowerPin1, -1, -1, -1>(),                                              // Button
  CONFIGARRAY(Sinister),
"00_NO_BLADE_save"}, 

{ 0,
  WS281XBladePtr<144, bladePin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3> >(),                                   // Main Blade
  SimpleBladePtr<AccentsLED, NoLED, NoLED, NoLED, bladePowerPin1, -1, -1, -1>(),                                              // Button
  CONFIGARRAY(Sinister),
"01_Elliot_save"}, 

};
#endif

#ifdef CONFIG_BUTTONS
Button PowerButton(BUTTON_POWER, auxPin, "pow"); 
// Button AuxButton(BUTTON_AUX, auxPin, "aux");
#endif

// // Button connect to 3.3v instead of GND. Up to 5v is OK
// PullDownButton PowerButton(BUTTON_POWER, powerButtonPin, "pow"); // isn't this backwards?

// // Analog Potentiometer 
// ChangeVolumeAnalogReceiver volume_function;
// PotClass pot(0, &volume_function);

// // Or, you can use it to change the variation (color):

// ChangeVariationAnalogReceiver variation_function;
// PotClass pot(0, &variation_function);

// // Rotary Encoder

// ChangePresetRotaryReceiver rotary_receiver;
// Rotary<8, 9> rotary(&rotary_receiver);
/*
The receiver decides what the rotary events do.
There are currently receivers for changing presets, 
changing variation and one that just prints things out. 
More receivers can be added as needed. 
(I should probably create one for changing the volume.)
*/

// Support for 128x64 OLED
// #ifdef CONFIG_BOTTOM
// SSD1306Template<128, uint64_t> display(0x3C);
// #endif

