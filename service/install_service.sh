#!/bin/bash

# Full path to script
SCRIPT_PATH="$(realpath "$0")"

# Full Folder Path
SCRIPT_DIR="$(dirname "$SCRIPT_PATH")"

# Path to where .service files go
SYSTEMD_DIR="/etc/systemd/system"

# Name of the .service file without the extension
SERVICE_NAME="polarone"

echo "Copying file into ${SYSTEMD_DIR}..."

# Copy the service file into the systemd folder
cp ${SCRIPT_DIR}/${SERVICE_NAME}.service ${SYSTEMD_DIR}/${SERVICE_NAME}.service

echo "Reloading daemon..."

# Reload systemctl
sudo systemctl daemon-reload

echo "Enabling service..."

# Enable the service
sudo systemctl enable ${SERVICE_NAME}

# Start the service
sudo systemctl start ${SERVICE_NAME}

# Print the status
sudo systemctl status ${SERVICE_NAME}