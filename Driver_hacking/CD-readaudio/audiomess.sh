#!/bin/bash

for i in `seq 3 13`;
  do
    aplay output.wav -r 44100 -c $i
  done
