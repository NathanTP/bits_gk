#!/usr/bin/env python

import sys
import pandas as pd
import numpy as np
import sklearn as sk
import pick
import explain

# Replace some raw counters with derived metrics (like IPC or miss-rate)
def derive_features(suite):
    # IPC
    suite['ipc'] = suite['instructions'] / suite['cpu-cycles']  
     
    # Branch Miss-rate (misses/branch)
    suite['branch-miss-rate'] = suite['branch-misses'] / suite['branches']
    
    # L1-D$ Miss Rate
    suite['L1-dcache-miss-rate'] = suite['L1-dcache-load-misses'] / suite['L1-dcache-load']
    
    # exclusive dTLB metrics
    suite['dTLB-miss-rate'] = suite['dTLB-load-misses'] / suite['dTLB-loads']  
    
    # Re-write system calls to be on a log scale (dynamic range is too high)
    suite['syscalls'] = suite['syscalls'].apply(np.log10)
    
    # Remove no-longer needed features (do this after all derived features are
    # caluclated)
    suite.drop(['instructions', 'cpu-cycles', 'branch-misses', 'branches',
                'L1-dcache-load-misses', 'L1-dcache-load',
                'dTLB-load-misses', 'dTLB-loads'], axis=1, inplace=True)
    
    return suite
    
def main():
    path = sys.argv[1]
    df = pd.read_hdf(path)
    
    # Transform the suite to be the mean/std of all runs per-app
    suite = df.mean(level='App')
    
    suite = derive_features(suite)

    # Ignore standard deviations for now (for simplicity)
#     stds = df.std(level='App')
#     stds.rename(columns=lambda x:  x+"_std", inplace=True)
#     suite = pd.concat([means, stds], axis=1)

    print "Candidate Benchmarks: " + str(list(suite.index))
    
    # Normalize Data (center to be >=0 range=1)
    # Interpretation is counter=% of max value
    suite = (suite - suite.min()) / (suite.max() - suite.min())

#     assn = pick.pick_dim_dist_greedy(suite, 5)
#     assn = pick.pick_dim_dist_exh(suite, 5)
    assn = pick.pick_ic_greedy(suite, 5)
#     assn = pick.pick_kmeans(suite, 5)
#     assn = pick.pick_rand(suite, 5)
#     assn = [1,4,8,16,19] # max unlikelihood k=5
    sub_suite = suite.iloc[assn]
    print "Selected Subset: " + str(list(sub_suite.index))

    print "Dimensionality Score: " + str(explain.score_dim(sub_suite))
    print "Distance Score: " + str(explain.score_dist(sub_suite))
    print "Unlikelihood: " + str(explain.score_unlik(sub_suite, suite))
    print "Information: " + str(explain.score_ic(sub_suite, suite))
    explain.plot_coverage(sub_suite)

main()
