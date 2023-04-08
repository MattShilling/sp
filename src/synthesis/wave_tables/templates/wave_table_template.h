#pragma once

#include "synthesis/wave_table.h"

const WaveTable {{ name }} {
    .min = {{ minimum }},
    .max = {{ maximum }},
    .data = {
        {% for value in values %}{{ value }},
        {% endfor %}
    }
};
