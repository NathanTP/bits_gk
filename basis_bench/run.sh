#!/bin/bash

perf stat -e ref-cycles,branches,branch-misses,instructions,cpu-cycles,L1-dcache-load-misses,L1-dcache-load,L1-icache-load-misses,dTLB-load-misses,LLC-load-misses $1
