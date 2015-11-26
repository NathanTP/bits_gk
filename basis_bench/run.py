#!/usr/bin/python

import sys
from glob import glob
import subprocess
import os.path
from cStringIO import StringIO
import pandas as pd

# Returns a string representing the perf command to run for the given benchmark
# path
def perf_cmd(bench_path):
  PERF_CMD = "/usr/bin/perf stat "

  EVENTS = ("-e ref-cycles,branches,branch-misses,instructions,cpu-cycles,"
    "L1-dcache-load-misses,L1-dcache-load,L1-icache-load-misses," +
          "dTLB-load-misses,LLC-load-misses,'syscalls:sys_enter_*'," +
          "'block:*' ")

  OPTIONS = " -x, "

  return (PERF_CMD + EVENTS + OPTIONS + bench_path).split()

# Run the benchmark at bench_path and return a pandas dataframe for it
# columns = raw_count, counter
def run(bench_path, run_id):
  cmd = perf_cmd(bench_path)
  
  try:
    proc = subprocess.Popen(cmd,
                     stdout=subprocess.PIPE,
                     stderr=subprocess.PIPE)
  except:
    print "Error running command: " + cmd
    exit()
 
  out = proc.communicate(input=None)[1]
  if proc.returncode != 0:
    print "Perf Command Failed: " + " ".join(cmd)
    print out
    exit()

  df = pd.read_csv(StringIO(out), header=None,
      names=['raw-count', 'counter'],
      usecols=[0,2])

  df['Run'] = run_id
  df = df.pivot(index='Run', columns='counter', values='raw-count')

  cols = list(df)

  # Merge block-io columns
  block_cols = [col for col in cols if col.startswith("block")]
  df['block_op'] = df[block_cols].sum(axis=1)
  df.drop(block_cols, axis=1, inplace=True)

  # Merge system-call columns
  sys_cols = [col for col in cols if col.startswith("syscall")]
  df['syscalls'] = df[sys_cols].sum(axis=1)
  df.drop(sys_cols, axis=1, inplace=True)

  return df

def measure_bench(bench_path):

  print "Measuring " + bench_path
  bench_df = pd.DataFrame()
  for runx in xrange(10):
    print "Iteration: " + str(runx)
    run_df = run(bench_path, runx)
    bench_df = bench_df.append(run_df)

  return bench_df

def main():
  suite_paths = glob(sys.argv[1] + "*")
  
  suite_df = pd.DataFrame()
  for path in suite_paths:
    bench_df = measure_bench(path)
    bench_df['App'] = os.path.basename(path)
    bench_df.set_index('App', append=True, inplace=True)
    suite_df = suite_df.append(bench_df.reorder_levels(['App', 'Run']))

  # Normalize all columns based on reference cycles
  suite_df = suite_df.div(suite_df['ref-cycles'], axis='index')*10E6
  suite_df.drop('ref-cycles', axis=1, inplace=True)  
  suite_df.to_hdf('results.h5', 'suite_perf')

main()
