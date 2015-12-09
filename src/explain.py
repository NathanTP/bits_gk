# This module has routines to explain the choices made by the gatekeeper.
# It can also evaluate how "good" of a choice was made

import numpy as np
import sklearn as sk
import sklearn.decomposition
import sklearn.mixture
import scipy.stats
import pygal as pg

# Score a suite based on its dimensionality (bigger better)
def score_dim(suite):
    smat = suite.as_matrix()
    
    # The basic idea here is to do PCA and count how many dimensions it takes
    # to account of 90% of the variability in our data (more dimensions means
    # more intrinsic dimensionality in the dataset)
    analyzer = sk.decomposition.PCA(n_components=0.9)
    analyzer.fit(smat)
    
    return analyzer.n_components_

# Score a suite based on the average distance from the mean
def score_dist(suite):
    smat = suite.as_matrix()
    mean = smat.mean(axis=0)
    diff = np.linalg.norm(mean - smat, axis=1)
    return np.fabs(diff).mean()

# Score based on the area enclosed by data
# (should account for both dim and dist)
def score_area(suite):
    # XXX This turns out to be trickier than I thought. The idea is to model a
    # polyhedron with suite points and the origin as the vertices and then
    # measure its volume
    pass

# Leave-one-out scoring (bigger is better)
# The score for a subset of 1 is a bit skrewy (not comparable to other scores) 
def score_unlik_loo(sub, full):
    if(len(sub) == 1):
        model = sk.mixture.DPGMM(n_components=len(full), covariance_type='full')
        model.fit(full)
        return -1 * model.score(sub)[0]

    unlik = 0.0
    for bx in xrange(len(sub)):
        bench = sub.iloc[bx:bx+1]
        loo_sub = sub.drop(sub.index[bx])
        
        model = sk.mixture.DPGMM(n_components=len(loo_sub), covariance_type='full')
        model.fit(loo_sub)
        unlik -= model.score(bench)[0]
        
    return unlik / len(sub)

# Leave-one-out scoring (bigger is better)
# The score for a subset of 1 is a bit skrewy (not comparable to other scores) 
def score_ic_loo(sub, full):
    if(len(sub) == 1):
        model = sk.mixture.DPGMM(n_components=len(full), covariance_type='full')
        model.fit(full)
        return model.aic(sub)

    unlik = 0.0
    for bx in xrange(len(sub)):
        bench = sub.iloc[bx:bx+1]
        loo_sub = sub.drop(sub.index[bx])
        
        model = sk.mixture.DPGMM(n_components=len(loo_sub), covariance_type='full')
        model.fit(loo_sub)
        unlik = model.aic(bench)
        
    return unlik / len(sub)

# Score based on the information criterion of a gaussian mixture model
def score_unlik(sub_suite, full_suite):
    model = sk.mixture.DPGMM(n_components=len(sub_suite), covariance_type='full')
    model.fit(sub_suite)
    # We want to maximize the negative log-liklihood
    return (model.score(full_suite)).sum()

def score_ic(sub_suite, full_suite):
    model = sk.mixture.DPGMM(n_components=len(sub_suite), covariance_type='full')
    model.fit(sub_suite)
    # Return the negative because we would like our subset to model the full
    # suite well.
    return (model.aic(full_suite))

def plot_coverage(suite, name):
    # Column labels, first half are means, second are standard deviations
    clbl = list(suite)
    tot = suite.max()
    
    # Plot Means
    plot = pg.Radar(fill=True)
    plot.title = name + " Coverage"
    plot.x_labels = clbl
    for bench in suite.iterrows():
        plot.add(bench[0], list(bench[1]))
        
#     plot.add("Total", list(tot))
    fname = name + "_coverage.svg"
    print "Plotting coverage to " + fname
    plot.render_to_file(fname)
