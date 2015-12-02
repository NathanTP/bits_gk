#!/usr/bin/python

import sys
import pandas as pd

def main():
  path = sys.argv[1]
  df = pd.read_hdf(path)
  print df

main()
exit()
