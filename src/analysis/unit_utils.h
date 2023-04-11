#pragma once

/**
 * @brief Calculate the amplitude of a signal from [-1.0, 1.0].
 *
 * @param amplitude The amplitude of a signal from [-1.0, 1.0].
 * @return The provided amplitude converted to decibels.
 */
double amplitude_to_db(double amplitude);

double db_to_amplitude(double decibels);
