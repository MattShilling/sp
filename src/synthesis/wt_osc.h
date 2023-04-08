#pragma once

#include "synthesis/wave_table.h"

class WaveTableOscillator {
public:
  WaveTableOscillator(const WaveTable &wt, double phase_offset,
                      double frequency, uint64_t sample_rate)
      : wt_(wt), phase_(0.0), phase_offset_(phase_offset),
        frequency_(frequency), sample_rate_(sample_rate) {}

  double value() const;
  void update();

private:
  const WaveTable &wt_;
  double phase_;
  double phase_offset_;
  double frequency_;
  uint64_t sample_rate_;
};
