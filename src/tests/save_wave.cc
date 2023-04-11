#include <cstdint>
#include <string>

#include <AudioFile.h>

#include "synthesis/wave_tables/wave_tables.h"
#include "synthesis/wt_osc.h"

#include "modulators/clipper.h"
#include "modulators/dry_wet.h"

constexpr uint64_t sample_rate = 44100;
constexpr size_t num_channels = 2;
constexpr double A3 = 220.0;

int main() {
  AudioFile<double> output_wav;
  output_wav.setNumChannels(num_channels);
  // This will be a 1s wav.
  output_wav.setNumSamplesPerChannel(sample_rate);

  WaveTableOscillator sawtooth_osc(Sawtooth, 0.0, A3, sample_rate);
  WaveTableOscillator sawtooth_osc_offset(Sawtooth, 35.0 * M_PI / 180.0, A3,
                                          sample_rate);

  // Both channels will get 50% of each oscillator. If we don't mix the
  // sawtooths together, the phase offset will not be audible and that would be
  // lame.
  DryWetModulator stereo(0.5);
  // Clip to -30dB to protect your ears. Sawtooths can be loud!
  Clipper clipper(-30.0);

  for (size_t s = 0; s < output_wav.getNumSamplesPerChannel(); s++) {
    double left_channel =
        stereo.mix(sawtooth_osc.value(), sawtooth_osc_offset.value());
    output_wav.samples[0][s] = clipper.clip(left_channel);

    double right_channel =
        stereo.mix(sawtooth_osc_offset.value(), sawtooth_osc.value());
    output_wav.samples[1][s] = clipper.clip(right_channel);

    sawtooth_osc.update();
    sawtooth_osc_offset.update();
  }

  output_wav.save("sawtooth_stereo.wav", AudioFileFormat::Wave);

  return 0;
}