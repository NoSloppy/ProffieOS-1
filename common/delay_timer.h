#ifndef DELAY_TIMER_H
#define DELAY_TIMER_H

// Returns a reference to the shared deadline timestamp (milliseconds).
inline uint32_t& delay_until_ms() {
  static uint32_t ts = 0;
  return ts;
}

// Set the timer to expire `duration_ms` from now, overwriting any
// existing deadline.  Used when only one error source is active.
inline void StartDelayTimer(uint32_t duration_ms) {
  delay_until_ms() = millis() + duration_ms;
}

// Extend the expiration. Used for multiple errors
// so that their delays stack rather than reset.
inline void AppendToDelayTimer(uint32_t duration_ms) {
  uint32_t now = millis();
  if (delay_until_ms() < now) delay_until_ms() = now;
  delay_until_ms() += duration_ms;
}

// Returns true while the deadline is still in the future.
inline bool DelayTimerActive() {
  return millis() < delay_until_ms();
}

#endif  // DELAY_TIMER_H