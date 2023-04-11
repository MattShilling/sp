#include "modulators/ring_mod.h"

double RingModulator::process_input(double input) {
  double processed = input * osc_.value();
  osc_.update();
  return mix_.mix(input, processed);
}
