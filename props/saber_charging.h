#ifndef PROPS_SABER_CHARGING_H
#define PROPS_SABER_CHARGING_H

// Standalone charging voice announcements — works with any prop file.
//
// Plays charging.wav when USB charging starts.
// Plays chargingcompleted.wav when the battery is fully charged
// (charger stops while USB is still connected).
//
// Usage in config file:
//   #ifdef CONFIG_PROP
//   #include "../props/saber_fett263_buttons.h"  // or any other prop
//   #include "../props/saber_charging.h"
//   #endif
//
// Place charging.wav and/or chargingcompleted.wav in your font directory or common/.
// Files are optional — missing ones are silently skipped.
//
// Requires Proffieboard V3 or later (chargeDetectPin).

#include "../sound/effect.h"
#include "../sound/hybrid_font.h"
#include "../common/looper.h"

EFFECT(charging);
EFFECT(chargingcompleted);

class ChargingVoice : public Looper {
public:
  const char* name() override { return "ChargingVoice"; }

//   void Loop() override {
// #if PROFFIEBOARD_VERSION - 0 >= 3
//     uint32_t now = millis();
//     if (now - last_charge_check_ < 500) return;
//     last_charge_check_ = now;

//     bool charging_now = !digitalRead(chargeDetectPin);

//     if (first_check_) {
//       // Silently record the initial state so we only react to changes that
//       // happen while the saber is already running — not to whatever the charger
//       // pin reads at boot. When the kill switch is off and USB powers the board,
//       // the charger pin is already asserted on startup even with no battery
//       // connected; skipping the first transition prevents a false announcement.
//       was_charging_ = charging_now;
//       first_check_ = false;
//       return;
//     }

//     if (charging_now != was_charging_) {
//       if (charging_now) {
//         // Charger became active while saber was already running — battery is present.
//         if (SFX_charging) hybrid_font.PlayCommon(&SFX_charging);
//       } else if (USBD_Connected()) {
//         // Charger stopped but USB still present — battery is full.
//         if (SFX_chargingcompleted) hybrid_font.PlayCommon(&SFX_chargingcompleted);
//       }
//       // USB simply unplugged — no sound.
//       was_charging_ = charging_now;
//     }
// #endif
//   }


  void Loop() override {
#if PROFFIEBOARD_VERSION - 0 >= 3
    uint32_t now = millis();
    if (now - last_charge_check_ < 500) return;
    last_charge_check_ = now;

    int raw_pin = digitalRead(chargeDetectPin);
    bool observed_charging = !raw_pin;
    bool usb_connected = USBD_Connected();

    // Reset the completion latch when USB is disconnected.
    if (!usb_connected) {
      completion_announced_ = false;
    }

    if (first_check_) {
      was_charging_ = observed_charging;
      candidate_charging_ = observed_charging;
      candidate_since_ = now;
      first_check_ = false;

      Serial.print("ChargingVoice: Initial pin=");
      Serial.print(raw_pin);
      Serial.print(" charging=");
      Serial.println(observed_charging ? "YES" : "NO");
      return;
    }

    // Record every observed change, but do not announce it yet.
    if (observed_charging != candidate_charging_) {
      candidate_charging_ = observed_charging;
      candidate_since_ = now;

      Serial.print("ChargingVoice: Candidate millis=");
      Serial.print(now);
      Serial.print(" pin=");
      Serial.print(raw_pin);
      Serial.print(" charging=");
      Serial.print(observed_charging ? "YES" : "NO");
      Serial.print(" USB=");
      Serial.println(USBD_Connected() ? "YES" : "NO");
    }

    // Accept a state change only after it remains stable for 5 seconds.
    if (candidate_charging_ != was_charging_ &&
        now - candidate_since_ >= 5000) {

      Serial.print("ChargingVoice: CONFIRMED millis=");
      Serial.print(now);
      Serial.print(" charging=");
      Serial.print(candidate_charging_ ? "YES" : "NO");
      Serial.print(" USB=");
      Serial.println(USBD_Connected() ? "YES" : "NO");

      if (usb_connected && !completion_announced_) {
        if (candidate_charging_) {
          if (SFX_charging)
            hybrid_font.PlayCommon(&SFX_charging);
        } else {
          // Announce completion only once per USB connection.
          // Set the latch before playing the sound.
          completion_announced_ = true;

          if (SFX_chargingcompleted)
            hybrid_font.PlayCommon(&SFX_chargingcompleted);
        }
      }

      was_charging_ = candidate_charging_;
    }
#endif
  }


private:
#if PROFFIEBOARD_VERSION - 0 >= 3
  bool was_charging_ = false;
  bool candidate_charging_ = false;
  bool first_check_ = true;
  bool completion_announced_ = false;
  uint32_t last_charge_check_ = 0;
  uint32_t candidate_since_ = 0;
#endif
};

ChargingVoice charging_voice;

#endif  // PROPS_SABER_CHARGING_H