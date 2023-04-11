# Take an FFT of a sin oscillator and plot sin to CSV.
add_executable(wt_osc_sin_fft
    wt_osc_sin_fft.cc
)
target_link_libraries(wt_osc_sin_fft
    wt-osc
)
add_test(wt_osc_sin_fft
    wt_osc_sin_fft
)

# Save a CSV of a stereo sawtooth synth.
add_executable(save_wave
    save_wave.cc
)
target_link_libraries(save_wave
    modulators
    unit-utils
    wt-osc
)
add_test(save_wave
    save_wave
)
