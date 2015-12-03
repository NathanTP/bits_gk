# This module has routines to explain the choices made by the gatekeeper.
# It can also evaluate how "good" of a choice was made

import numpy as np
import sklearn as sk
import sklearn.decomposition

# Score a suite based on its dimensionality (bigger better)
def dim_score(suite):
    # The basic idea here is to do PCA and count how many dimensions it takes
    # to account of 90% of the variability in our data (more dimensions means
    # more intrinsic dimensionality in the dataset)
    analyzer = sk.decomposition.PCA(n_components=0.9)
    analyzer.fit(suite)
    
    return analyzer.n_components_

# Score a suite based on the sum of squared distances (bigger is better)
def dist_score(suite):
    mean = suite.mean(axis=0)
    diff = np.linalg.norm(mean - suite, axis=1)
    diff = np.square(diff)
    return diff.sum()