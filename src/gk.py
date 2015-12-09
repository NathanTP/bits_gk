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

def run_and_report(algo, k, suite, name):
    assn = algo(suite, k)
    sub_suite = suite.iloc[assn]
    sub_name = ':'.join(map(str, list(sub_suite.index)))
    dim = explain.score_dim(sub_suite)
    dist = explain.score_dist(sub_suite)
    ic = explain.score_ic_loo(sub_suite, suite)
    ulik = explain.score_unlik_loo(sub_suite, suite)
    explain.plot_coverage(sub_suite, name)
    
    return ("{},{},{},{},{},{}\n".format(name,sub_name,dim,dist,ic,ulik)) 

def run_interactive(algo, k, suite):
    assn = algo(suite, k)
    sub_suite = suite.iloc[assn]
    print "Selected Subset: " + str(list(sub_suite.index))
    print "Dimensionality Score: " + str(explain.score_dim(sub_suite))
    print "Distance Score: " + str(explain.score_dist(sub_suite))
    print "LOO IC: " + str(explain.score_ic_loo(sub_suite, suite))
    print "LOO Unlikelihood: " + str(explain.score_unlik_loo(sub_suite, suite))
    
    return sub_suite
    
def run_battery(suite, k, name):
    csv = "algo,choice,dim,dist,ic,unlik\n"
    csv += run_and_report(pick.pick_rand, k, suite, "rand")
    csv += run_and_report(pick.pick_kmeans, k, suite, "kmeans")
    csv += run_and_report(pick.pick_dim_dist_greedy, k, suite, "dimdist_greedy")
    csv += run_and_report(pick.pick_dim_dist_exh, k, suite, "dimdist_exh")
    csv += run_and_report(pick.pick_ic_greedy, k, suite, "ic")
    csv += run_and_report(pick.pick_ic_loo_greedy, k, suite, "ic_loo")
    csv += run_and_report(pick.pick_unlik_greedy, k, suite, "unlik")
    csv += run_and_report(pick.pick_unlik_loo_greedy, k, suite, "unlik_loo")
    
    fname = name + "_k" + str(k) + "_results.csv"
    print "Writing file to " + fname
    file = open(fname, 'w')
    file.write(csv)
    file.close()
    
    print csv


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

#     run_battery(suite, 8, "basis")
    run_interactive(pick.pick_ic_greedy, 3, suite)
#     explain.plot_coverage(sub_suite)

main()
