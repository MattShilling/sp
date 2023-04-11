#include "analysis/unit_utils.h"

#include <cmath>

double amplitude_to_db(double amplitude) {
  /**
   * Note: in the context of this function, we are dealing with amplitude
   * instead of power Since power is proportional to the square of the
   * amplitude, the relationship between the amplitude ratio and the power ratio
   * is:
   * - P2 / P1 = (A2 / A1)^2
   * Therefore, we can express the ratio in decibels as 20.0 * log10(amplitude)
   * using the logarithmic identity:
   * - log(x^y) = y * log(x)
   * -> dB = 10 * log10((A2 / A1)^2) becomes dB = 20 * log10((A2 / A1))
   */
  return 20.0 * std::log10(amplitude);
}

double db_to_amplitude(double decibels) {
  return std::pow(10.0, decibels / 20.0);
}
