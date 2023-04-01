#!/bin/bash
set -e -x
docker pull ubuntu:20.04
cd docker && docker build -t main .
