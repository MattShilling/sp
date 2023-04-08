#include <array>
#include <fstream>
#include <iostream>

#include <fft.h>
#include <fft_settings.h>

#include "synthesis/wave_tables/wave_tables.h"
#include "synthesis/wt_osc.h"

// Has to be a power of 2, so we pick 2^16.
// According to the nyquist theorem, this means that the maximum positive
// frequency bin in our FFT will be 2^16/2 or 16384.
constexpr uint64_t sample_rate = 32768;

// Set frequency of our sine signal.
constexpr double sine_frequency = 1234.0;

// Ensure our sample rate is high enough.
static_assert(sample_rate > 2 * sine_frequency);

typedef std::array<real_type, sample_rate> RealArray1D;
typedef std::array<complex_type, sample_rate> ComplexArray1D;

int main() {
  WaveTableOscillator sin_osc(Sine, sine_frequency, sample_rate);

  // Generate 1s worth of our signal.
  RealArray1D samples;
  for (uint64_t sample_idx = 0; sample_idx < sample_rate; sample_idx++) {
    samples[sample_idx] = sin_osc.value();
    sin_osc.update();
  }

  // Take the DFT of our signal.
  ComplexArray1D output;
  const char *err_str = nullptr;
  bool res = simple_fft::FFT(samples, output, sample_rate, err_str);

  // Print any information provided by the FFT call.
  if (!res && err_str != nullptr) {
    std::cout << std::string(err_str) << std::endl;
  } else {
    std::cout << "FFT Success!" << std::endl;
  }

  // Look through all frequency bins and find the frequency component with the
  // highest amplitude.
  double max_amp = 0;
  double max_amp_freq = 0;
  for (size_t freq_hz = 0; freq_hz < (sample_rate / 2); freq_hz++) {
    double amp = std::abs(output[freq_hz]);
    double phase = std::arg(output[freq_hz]);
    if (amp > max_amp) {
      max_amp = amp;
      max_amp_freq = freq_hz;
    }
  }

  // Normalize amplitude across frequency bins.
  std::cout << "Detected amplitude = "
            << max_amp / static_cast<double>(sample_rate / 2) << std::endl;
  std::cout << "Detected frequency = " << max_amp_freq << "Hz" << std::endl;

  // Output samples to a CSV file for data review.
  std::ofstream output_file("samples.csv");
  if (!output_file.is_open()) {
    std::cerr << "Failed to open output file." << std::endl;
    return 1;
  }

  // Write the header.
  output_file << "time,amplitude" << std::endl;

  // Write the samples
  for (uint64_t sample_idx = 0; sample_idx < sample_rate; sample_idx++) {
    double time = static_cast<double>(sample_idx) / sample_rate;
    double amplitude = samples[sample_idx];
    output_file << time << "," << amplitude << std::endl;
  }

  output_file.close();
  std::cout << "samples.csv created successfully." << std::endl;
}