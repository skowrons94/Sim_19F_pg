#!/bin/bash

docker run -it --rm --network=host -v ./macros/:/workdir/macros -v ./rootfiles/:/workdir/rootfiles -v ./data:/data simluna $@