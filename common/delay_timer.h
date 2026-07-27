#ifndef DELAY_TIMER_H
#define DELAY_TIMER_H

// Returns a reference to the shared deadline timestamp (milliseconds).
inline uint32_t& delay_until_ms() {
  static uint32_t ts = 0;
  return ts;
}

// Set the timer to expire `duration_ms` from now, overwriting any
// existing deadline.  Use when only one error source is active.
inline void StartDelayTimer(uint32_t duration_ms) {
  delay_until_ms() = millis() + duration_ms;
}

// Extend the deadline by `duration_ms` from wherever it currently sits
// (or from now if it has already expired).  Use when multiple error
// sources may fire in quick succession so that their delays stack rather
// than reset.
inline void AppendToDelayTimer(uint32_t duration_ms) {
  uint32_t now = millis();
  if (delay_until_ms() < now) delay_until_ms() = now;
  delay_until_ms() += duration_ms;
}

// Returns true while the deadline is still in the future.
inline bool DelayTimerActive() {
  return millis() < delay_until_ms();
}

// Flag set by PlayErrorMessage() when an error wav is queued, cleared by
// SoundQueueSingleton::Loop() when the queue drains.  Allows hybrid_font.h
// to defer boot/font sounds until the error wav actually finishes playing
// without depending on SoundQueueSingleton (defined later in the build).
inline bool& error_sound_active() {
  static bool s = false;
  return s;
}

#endif  // DELAY_TIMER_H
