#include <cmath>

#include "synthesis/wt_osc.h"

double WaveTableOscillator::value() const { return wt_.at(phase_); }

void WaveTableOscillator::update() {
  double phase_step = 2 * M_PI * frequency_ / static_cast<double>(sample_rate_);
  phase_ = std::fmod(phase_ + phase_step, 2 * M_PI);
}
