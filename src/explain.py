# This module has routines to explain the choices made by the gatekeeper.
# It can also evaluate how "good" of a choice was made

import numpy as np
import sklearn as sk
import sklearn.decomposition
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
    

def plot_coverage(suite):

    # Column labels, first half are means, second are standard deviations
    clbl = list(suite)
    tot = suite.max()

    # Plot Means
    print "Plotting means to suite_coverage_means.svg"
    plot = pg.Radar(fill=True)
    plot.title = "Suite Coverage (Feature Means)"
    plot.x_labels = clbl
    for bench in suite.iterrows():
        plot.add(bench[0], list(bench[1]))
        
#     plot.add("Total", list(tot))
    plot.render_to_file("suite_coverage.svg")
