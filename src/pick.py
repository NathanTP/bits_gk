import numpy as np
import sklearn as sk
import sklearn.cluster
import random

# Picking functions (pick_*(dat, k)):
# Given an (N, M) matrix of N benchmarks and M features, return the k best
# bencharmks (k,).

# Creates k clusters (using k-means) and then returns the applications closest
# to the cluster centers. Note: It's possible that an application could appear
# multiple times, we'll try and fix this later.
def pick_kmeans(dat, k):
  classifier = sk.cluster.KMeans(n_clusters=k)

  dist = classifier.fit_transform(dat)
  assn = np.argmin(dist, axis=0)
  return assn

# Return a random selection (just for verification purposes)
def pick_rand(dat, k):
  return np.array(random.sample(range(dat.shape[0]), k))

 
