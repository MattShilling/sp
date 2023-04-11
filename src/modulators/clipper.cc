#include "modulators/clipper.h"

#include <cmath>

Clipper::Clipper(double threshold_db)
    : threshold_db_(threshold_db),
      threshold_amplitude_(db_to_amplitude(threshold_db)) {}

double Clipper::clip(double amplitude) {
  if (std::abs(amplitude) > threshold_amplitude_) {
    // new amplitude = amplitude * (threshold_amplitude_ / abs_amplitude) =
    // threshold_amplitude_ * sgn(amplitude).
    return std::copysign(threshold_amplitude_, amplitude);
  }
  return amplitude;
}