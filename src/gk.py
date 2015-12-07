#!/usr/bin/env python

import sys
import pandas as pd
import numpy as np
import sklearn as sk
import pick
import explain

def main():
    path = sys.argv[1]
    df = pd.read_hdf(path)

    # Transform the suite to be the mean/std of all runs per-app
    suite = df.mean(level='App')
    
    # Ignore standard deviations for now (for simplicity)
#     stds = df.std(level='App')
#     stds.rename(columns=lambda x:  x+"_std", inplace=True)
#     suite = pd.concat([means, stds], axis=1)

    print "Candidate Benchmarks: " + str(list(suite.index))

    # Normalize Data
    suite = (suite - suite.mean()) / (suite.max() - suite.min())

    assn = pick.pick_kmeans(suite.as_matrix(), 5)
    sub_suite = suite.iloc[assn]

    print "Selected Subset: " + str(list(sub_suite.index))

    print "Dimensionality Score: " + str(explain.score_dim(sub_suite))
    print "Distance Score: " + str(explain.score_dist(sub_suite))
    explain.plot_coverage(sub_suite)

main()
