#!/usr/bin/python

import sys
import pandas as pd
import numpy as np
import pick

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

  assn = pick.pick_kmeans(suite, 5)
  print suite_df.index[assn]

main()
