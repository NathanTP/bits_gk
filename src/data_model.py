import numpy as np
import pandas as pd

algos = ['rand', 'km', 'dd', 'ic_rep', 'ic_loo', 'lik_rep', 'lik_loo']
algo_fname = ['rand_kgraph.csv', 'kmeans_kgraph.csv', 'dd_gre_kgraph.csv', 
              'ic_kgraph.csv', 'ic_loo_kgraph.csv',
              'unlik_kgraph.csv', 'unlik_loo_kgraph.csv']
feat_names = ['dim', 'dist', 'ic_rep', 'ic_loo', 'ulik_rep', 'ulik_loo']

# Replace some raw counters with derived metrics (like IPC or miss-rate)
def get_dat(path):
    df = pd.read_hdf(path)
    
    # Transform the suite to be the mean/std of all runs per-app
    suite = df.mean(level='App')
    
    #==
    # Derive Features
    #==
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
         
    # Normalize Data (center to be >=0 range=1)
    # Interpretation is counter=% of ma value
    suite = (suite - suite.min()) / (suite.max() - suite.min())
    
    return suite

def get_assn(path):
    return pd.read_csv(path, index_col=0)

def get_feature(path, feat):
    afeat = []
#     for x in range(len(algos) / 2, len(algos)):
#     for x in range(0, len(algos) / 2):
#     for x in [1, 2, 4, 5]:
    for x in range(len(algos)):
#         print x
        adf = pd.read_csv("basis_kgraph/" + algo_fname[x], index_col=0)
        adf /= 10 
        afeat.append(adf[feat])
        afeat[-1].name = algos[x]
    
    feat_df = pd.concat(afeat, axis=1)
    print feat_df
    return feat_df