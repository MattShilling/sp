#include "modulators/dry_wet.h"

double DryWetModulator::mix(double input_dry, double input_wet) {
  return input_dry * (1.0 - mix_) + (mix_ * input_wet);
}
