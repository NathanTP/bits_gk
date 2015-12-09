import numpy as np
import sklearn as sk
import sklearn.cluster
import itertools
import pandas as pd
import random
import explain

# Picking functions (pick_*(dat, k)):
# Given an (N, M) matrix of N benchmarks and M features, return the k best
# bencharmks (k,).

# Creates k clusters (using k-means) and then returns the applications closest
# to the cluster centers. Note: It's possible that an application could appear
# multiple times, we'll try and fix this later.
def pick_kmeans(dat, k):
    classifier = sk.cluster.KMeans(n_clusters=k)

    dist = classifier.fit_transform(dat.as_matrix())
    assn = np.argmin(dist, axis=0)
    return assn

# Return a random selection (just for verification purposes)
def pick_rand(dat, k):
    return np.array(random.sample(range(len(dat)), k))

# Create a sub-test using a greedy algorithm
def _test_greedy(dat, k, scorer, param):
    # Pick the single benchmark with the highest score
    seed = None
    seed_score = float('-inf')
    for idx in range(len(dat)):
        bench = dat.iloc[idx:idx+1]
        score = scorer(bench, param)
        if score > seed_score:
            seed_score = score
            seed = idx

    assert (seed != None),"Couldn't Score Candidates"
    sub = [seed]
    cand = list(range(len(dat)))
    cand.remove(seed)
    for subx in range(1,k):
        best = None
        best_score = float('-inf')
        for bx in cand:
            cand_sub = list(sub)
            cand_sub.append(bx)
            score = scorer(dat.iloc[cand_sub], param)
            if score > best_score:
                best_score = score
                best = bx
        
        assert (best != None),"Couldn't Score Candidates"
        sub.append(best)
        cand.remove(best)
        
    return sub

# Exhaustively test all possible k subsets of dat and return the subset ranked
# highest by the function "scorer" (float scorer(pandas.dataframe, param))
def _test_exhaustive(dat, k, scorer, param):
    best = []
    best_score = float('-inf')
    for idx in itertools.combinations(range(len(dat)), k):
        sub = dat.iloc[list(idx)]
        score = scorer(sub, param)
        if score > best_score:
            best_score = score
            best = list(idx)
    
    return best

def _dim_dist_scorer(df, param):
    return explain.score_dist(df)*param[0] + explain.score_dim(df)*param[1]

def _unlik_scorer(sub, full):
    return explain.score_unlik(sub, full)

def _unlik_loo_scorer(sub, full):
    return explain.score_unlik_loo(sub, full)

def _ic_scorer(sub, full):
    return explain.score_ic(sub, full)

def _ic_loo_scorer(sub, full):
    return explain.score_ic_loo(sub, full)

# Brute-force searches for best subset of data according to
# dimension and distance
def pick_dim_dist_exh(dat, k):
    # Weight given to distance vs dimensionality (must sum to 1.0)
    wdist = 0.1
    wdim = 0.9
 
    return _test_exhaustive(dat, k, _dim_dist_scorer, [wdist, wdim])

# Greedy searches for best subset of data according to
# dimension and distance
def pick_dim_dist_greedy(dat, k):
    # Weight given to distance vs dimensionality (must sum to 1.0)
    wdist = 0.1
    wdim = 0.9
 
    return _test_greedy(dat, k, _dim_dist_scorer, [wdist, wdim])

def pick_unlik_exh(dat, k):
    return _test_exhaustive(dat, k, _unlik_scorer, dat)

def pick_unlik_greedy(dat, k): 
    return _test_greedy(dat, k, _unlik_scorer, dat)

def pick_unlik_loo_exh(dat, k):
    return _test_exhaustive(dat, k, _unlik_loo_scorer, dat)

def pick_unlik_loo_greedy(dat, k):
    return _test_greedy(dat, k, _unlik_loo_scorer, dat)

def pick_ic_loo_greedy(dat, k):
    return _test_greedy(dat, k, _ic_loo_scorer, dat)

def pick_ic_exh(dat, k):
    return _test_exhaustive(dat, k, _ic_scorer, dat)

def pick_ic_greedy(dat, k):
    return _test_greedy(dat, k, _ic_scorer, dat)
