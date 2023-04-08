import json
import argparse
import numpy as np
from sympy import *
from typing import List
from dataclasses import dataclass
from jinja2 import Environment, FileSystemLoader

TEMPLATES_DIR = 'src/synthesis/wave_tables/templates'
WAVE_TABLE_CONFIG = 'src/synthesis/wave_tables/wave_table_list.json'


def evaluate_expression(expression: str):
    # Parameters for creating the lookup table.
    domain = 2 * np.pi
    steps = 2048

    # CAS-ify.
    x = symbols("x")
    expr = sympify(expression)

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
        values.append(f'{value:.10f}')

    return minimum, maximum, values


def generate_wave_table(wave_table):
    # Render and save template.
    environment = Environment(loader=FileSystemLoader(TEMPLATES_DIR))
    template = environment.get_template('wave_table_template.h')

    filename = f'{ wave_table.output_dir}/{wave_table.name.lower()}_table.h'

    content = template.render(
        name=wave_table.name,
        minimum=wave_table.minimum,
        maximum=wave_table.maximum,
        values=wave_table.values
    )

    with open(filename, mode="w", encoding="ascii") as f:
        f.write(content)


def generate_wave_table_include(wave_tables):
    # Render and save template.
    environment = Environment(loader=FileSystemLoader(TEMPLATES_DIR))
    template = environment.get_template('wave_table_include_template.h')

    content = template.render(
        wave_tables=wave_tables,
    )

    with open('src/synthesis/wave_tables/wave_tables.h',
              mode="w",
              encoding="ascii") as f:
        f.write(content)


@dataclass
class WaveTable:
    name: str
    output_dir: str
    expression: str
    minimum: float
    maximum: float
    values: list


def get_wave_tables(wave_table_config) -> List[WaveTable]:
    wave_table_list_json = None
    # Load wave table configuration file.
    with open(wave_table_config, 'r') as myfile:
        data = myfile.read()
        wave_table_list_json = json.loads(data)

    wave_tables: List[WaveTable] = []

    for wave_table in wave_table_list_json['wave_tables']:
        expression = wave_table['expression']
        minimum, maximum, values = evaluate_expression(expression)
        wave_tables.append(
            WaveTable(name=wave_table["name"],
                      output_dir='src/synthesis/wave_tables',
                      expression=expression,
                      minimum=minimum,
                      maximum=maximum,
                      values=values)
        )

    return wave_tables

wave_tables = get_wave_tables(WAVE_TABLE_CONFIG)

for wave_table in wave_tables:
    generate_wave_table(wave_table)

generate_wave_table_include(wave_tables)
