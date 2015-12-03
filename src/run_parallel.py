#!/usr/bin/python

from glob import glob
import subprocess
import os.path
from cStringIO import StringIO
import pandas as pd

# Returns a string representing the perf command to run for the given benchmark
# path
def perf_cmd(bench_path):
  PERF_CMD = "/usr/bin/perf stat "

  EVENTS = ("-e ref-cycles,branches,branch-misses,instructions,cpu-cycles," +
           "L1-dcache-load-misses,L1-dcache-load,L1-icache-load-misses," +
           "dTLB-load-misses,LLC-load-misses,'syscalls:sys_enter_*'," +
           "'block:*',minor-faults,power/energy-pkg/,power/energy-ram/ ")

  OPTIONS = "-a --per-core -x, "

  return (PERF_CMD + EVENTS + OPTIONS + bench_path).split()

# Run the benchmark at bench_path and return a pandas dataframe for it
# index: socket/core, columns = counter
def run(bench_path):
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
      names=['socket/core', 'raw-count', 'counter', 'percent-time'],
      usecols=[0,2,4,6])

  df = df.pivot(index='socket/core', columns='counter', values='raw-count')
  return df

def measure_bench(bench_path):

  print "Measuring " + bench_path
  bench_df = pd.DataFrame()
  for runx in xrange(10):
    print "Iteration: " + str(runx)
    run_df = run(bench_path)
    run_df['Run'] = runx
    run_df.set_index('Run', append=True, inplace=True)
    bench_df = bench_df.append(run_df.swaplevel('Run', 'socket/core'))

  return bench_df

def main():
  suite_paths = glob("/mnt/data/repos/bits_gk/NPB3.3.1/NPB3.3-OMP/bin/*")
  
  suite_df = pd.DataFrame()
  for path in suite_paths:
    bench_df = measure_bench(path)
    bench_df['App'] = os.path.basename(path)
    bench_df.set_index('App', append=True, inplace=True)
    suite_df = suite_df.append(bench_df.reorder_levels(['App', 'Run', 'socket/core']))

  suite_df.to_hdf('results.h5', 'suite_perf')

main()
