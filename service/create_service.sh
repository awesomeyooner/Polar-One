#!/bin/bash

SCRIPT_DIR="$(dirname "$(realpath "$0")")"

FILE_NAME="polarone.service"

USER="$(whoami)"

echo "Creating file ${FILE_NAME}"

# Create the file
touch ${SCRIPT_DIR}/${FILE_NAME}

# Use > to OVERWRITE
# Use >> to APPEND

# Populate file contents
cat << EOF > ${FILE_NAME}
[Unit]
Description=Main Executable for running Polar One
Wants=network-online.target docker.service
After=network-online.target docker.service
StartLimitBurst=5

[Service]
User=${USER}
WorkingDirectory=${SCRIPT_DIR}
ExecStartPre=/bin/sleep 10
ExecStart=${SCRIPT_DIR}/run.sh
Restart=always
RestartSec=5s
Type=simple

[Install]
WantedBy=multi-user.target
EOF

# Print the file contents
echo "The file: ${FILE_NAME} contains the following"
echo "===== START ====="
cat ${SCRIPT_DIR}/${FILE_NAME}
echo "===== END ====="