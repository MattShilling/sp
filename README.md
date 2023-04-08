# sp
signal processing


Design:
- use `python3 -m util/wt_gen.py` to generate a new wavetable.
    - uses https://docs.sympy.org/latest/tutorials/intro-tutorial/basic_operations.html for CAS
    - todo: visualization
- Ex: `python3 util/wt_gen.py "2 * (x/(2*pi) - floor(1/2 + x/(2*pi)))"`

https://thewolfsound.com/sine-saw-square-triangle-pulse-basic-waveforms-in-synthesis/


# Using FFTs

The output of a Fast Fourier Transform (FFT) algorithm is a discrete representation of the frequency components present in the input signal. Specifically, it transforms a sequence of equally spaced samples (usually of a time-domain signal) and transforms them into a new sequence of complex numbers representing the amplitudes and phases of the different frequency components in the original signal. This transformation is called the Discrete Fourier Transform (DFT).

In other words, the FFT algorithm takes a time-domain signal as input and produces a frequency-domain representation as output, where each element in the output sequence corresponds to a specific frequency and indicates the contribution of that frequency to the original signal. This is useful for analyzing the spectral content of signals, filtering, and various other signal processing applications.

For example, When you pass an array of 1000 samples with a sample rate of 1000 samples per second (1 kHz) to an FFT, the output will be an array of 1000 complex numbers, representing the frequency components of the input signal. These complex numbers contain information about the amplitude and phase of each frequency component.

The output array can be interpreted as follows:

- The first element of the output array (index 0) corresponds to the DC component (0 Hz) of the signal, which represents the average value or offset of the input signal.
Elements from index 1 to index 499 correspond to the positive frequency components, with each element representing a frequency bin of 1 Hz, as the sample rate is 1000 samples per second and there are 1000 samples. So, the element at index 1 represents 1 Hz, index 2 represents 2 Hz, and so on, up to index 499 representing 499 Hz.
- The element at index 500 corresponds to the Nyquist frequency, which is half the sample rate (500 Hz in this case). This is the highest frequency that can be accurately represented in the signal according to the Nyquist-Shannon sampling theorem.
- Elements from index 501 to 999 represent the negative frequency components (which are symmetrical to the positive ones for real-valued input signals) and are typically not used for analysis when dealing with real-valued input signals.

Usually, the magnitudes of the complex numbers are taken to understand the amplitude (`sqrt(real^2 + imaginary^2)`) of each frequency component, and this can be done by calculating the absolute value or the square of the magnitude. For further analysis, you can also compute the phase information by taking the arctangent of the imaginary part divided by the real part of each complex number (`atan2(imaginary, real)`).