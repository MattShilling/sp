#pragma once

#include <array>
#include <cmath>

struct WaveTable {
private:
  constexpr static const size_t size_ = 2048;
  constexpr static const double domain_ = 2 * M_PI;
  constexpr static const double step_ = domain_ / size_;

public:
  double min;
  double max;
  std::array<double, size_> data;

  double at(const double unwrapped_x) const {
    // Wrap to domain.
    const double wrapped_x = ::fmod(unwrapped_x, domain_);

    // Convert to indices spanning wrapped_x in table.
    // Left side.
    size_t idx0 = static_cast<size_t>(wrapped_x / step_);
    // Right side.
    size_t idx1 = (idx0 + 1) % size_;

    // Calculate slope.
    double slope = (data[idx1] - data[idx0]) / step_;

    // y = mx + b.
    // b = data[idx0].
    // Set idx0 to origin:
    // -> x = wrapped_x - (step_ * idx0).
    double x = wrapped_x - (step_ * idx0);
    // y = slope * x + data[idx0].
    return slope * x + data[idx0];
  }
};
