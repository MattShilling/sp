#pragma once

class DryWetModulator {
public:
  DryWetModulator(double mix) : mix_(mix) {}

  double mix_dry_wet(double input_dry, double input_wet);

  void update_mix(double mix) { mix_ = mix; }

private:
  double mix_;
};
