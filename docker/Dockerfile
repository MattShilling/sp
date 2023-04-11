FROM ubuntu:20.04

RUN apt update && apt install -y --no-install-recommends \
    ninja-build \
    cmake \
    clang-format-11 \
    python3 \
    pip

RUN pip install \
    ipympl \
    Jinja2 \
    numpy \
    librosa \
    matplotlib \
    pandas \
    sympy \
    "textual[dev]"

WORKDIR src/