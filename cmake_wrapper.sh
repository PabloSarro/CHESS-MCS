#!/bin/bash

# Change to the project root directory first (where settings.ini is)
cd /home/pablo/CHESS-MCS/fprime-workspace/CHESS-SIM || exit 1

# 1. Activate the Venv, then immediately execute the CMake command.
# The '&&' ensures the second command only runs if the source is successful.
source fprime-venv/bin/activate && exec fprime-venv/bin/cmake "$@"