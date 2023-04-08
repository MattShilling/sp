#!/bin/bash

set -e

docker run \
  --rm \
  -v $(pwd):/src \
  -it \
  main \
  /bin/bash
