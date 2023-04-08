#pragma once

#include "modulators/dry_wet.h"
#include "synthesis/wt_osc.h"

class RingModulator {
public:
  RingModulator(WaveTableOscillator osc, double mix) : osc_(osc), mix_(mix) {}

  double process_input(double input);

private:
  WaveTableOscillator osc_;
  DryWetModulator mix_;
};
