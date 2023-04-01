#!/bin/bash

set -e

docker run \
  --rm \
  -v $(pwd):/src \
  -u $(id -u):$(id -g) \
  main \
  -it /bin/bash
