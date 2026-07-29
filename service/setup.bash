#!/bin/bash

SCRIPT_DIR="$(dirname "$(realpath "$0")")"

run()
{
    local script=$1

    echo "Running script: ${script}..."

    sudo chmod +x ${SCRIPT_DIR}/$script && ${SCRIPT_DIR}/$script

    echo "Done!"

} # run()

run create_service.sh
run install_service.sh

echo "Finished!"