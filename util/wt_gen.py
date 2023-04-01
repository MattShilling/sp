import argparse
import numpy as np
from sympy import *
from jinja2 import Environment, FileSystemLoader

parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('expression', type=str,
                    help='expression for wavetable')

args = parser.parse_args()
print(f'Evaluating: {args.expression}')

# Parameters for creating the lookup table.
domain = 2 * np.pi
steps = 20

# CAS-ify.
x = symbols("x")
expr = sympify(args.expression)

# Minimum and maximum values are useful for normalization.
minimum = np.inf
maximum = 0
values = []
# Evaluate expression across the domain.
for i in np.linspace(0, domain, steps):
    value = expr.evalf(subs={x: i})
    if value < minimum:
        minimum = value
    if value > maximum:
        maximum = value
    values.append(f'{value:.20f}')

#
# Render and save template.
#
environment = Environment(loader=FileSystemLoader("src/synthesis/wave_tables/"))
template = environment.get_template("wave_table_template.h")

content = template.render(
    name='test',
    minimum=minimum,
    maximum=maximum,
    values=values
)

filename = f'wave.h'
with open(filename, mode="w", encoding="ascii") as f:
    f.write(content)
