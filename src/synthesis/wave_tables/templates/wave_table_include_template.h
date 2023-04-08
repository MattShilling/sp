#pragma once

{% for wave_table in wave_tables %}#include "synthesis/wave_tables/{{ wave_table.name.lower() }}_table.h"
{% endfor %}
