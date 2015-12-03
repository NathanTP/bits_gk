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
  means = df.mean(level='App')
  stds = df.std(level='App')
  stds.rename(columns=lambda x:  x+"_std", inplace=True)
  
  suite_df = pd.concat([means, stds], axis=1)

  print suite_df.index

  # Numpy matrix representing the suite
  suite = suite_df.as_matrix()
  sk.preprocessing.scale(suite, copy=False)

  print suite_df
  exit()  
  assn = pick.pick_kmeans(suite, 3)
  sub_suite = suite[assn]
  print suite_df.index[assn]
  
  print "Dimensionality Score: " + str(explain.dim_score(sub_suite))
  print "Distance Score: " + str(explain.dist_score(sub_suite))

main()
