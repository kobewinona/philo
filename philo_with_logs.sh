#!/bin/bash

if [ ! -d "logs" ]; then
    mkdir logs
fi

if ./philo "$@" > logs/sim_logs.txt; then
    valgrind --leak-check=full --show-reachable=yes --log-file=logs/valgrind_report.txt ./philo "$@"
else
    echo "Program failed to run successfully"
    exit 1
fi
