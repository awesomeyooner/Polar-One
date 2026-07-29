#!/bin/bash

# This makes it so that terminal immediately quits / shuts down the moment there's an error (that way containers don't stall)
set -e

# Source bashrc (optional)
if [ -f "$HOME/.bashrc" ]; then
    source "$HOME/.bashrc"
fi

# Source ros2
source /opt/ros/jazzy/setup.bash

# Source project
source /home/ubuntu/ros2_ws/install/setup.bash

# Run your command as executable to takeover terminal
# Make this the last line
exec "$@"