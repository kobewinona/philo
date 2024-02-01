#!/bin/bash

if [ ! -d "logs" ]; then
    mkdir logs
fi

if ./philo "$@" > logs/sim_logs.txt; then
    sort -n < logs/sim_logs.txt | grep . > logs/sim_logs_sorted.txt
else
    echo "Program failed to run successfully"
    exit 1
fi
