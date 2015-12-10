#!/usr/bin/env python

import sys
import pandas as pd
import numpy as np
import sklearn as sk
import data_model as dm
import pick
import explain

def run_and_report(algo, k, suite, name):
    assn = algo(suite, k)
    sub_suite = suite.iloc[assn]
    sub_name = ':'.join(map(str, list(sub_suite.index)))
    dim = explain.score_dim(sub_suite)
    dist = explain.score_dist(sub_suite)
    ic_rep = explain.score_ic_rep(sub_suite, suite)
    ic_loo = explain.score_ic_loo(sub_suite, suite)
    ulik_rep = explain.score_unlik_rep(sub_suite, suite)
    ulik_loo = explain.score_unlik_loo(sub_suite, suite)
    explain.plot_coverage(sub_suite, name)
    
    return ("{},{},{},{},{},{},{},{}\n".format(name,sub_name,dim,dist,ic_rep,ic_loo,ulik_rep,ulik_loo)) 

def run_interactive(algo, k, suite):
    assn = algo(suite, k)
    sub_suite = suite.iloc[assn]
    print "Selected Subset: " + str(list(sub_suite.index))
    print "Dimensionality Score: " + str(explain.score_dim(sub_suite))
    print "Distance Score: " + str(explain.score_dist(sub_suite))
    print "LOO IC: " + str(explain.score_ic_loo(sub_suite, suite))
    print "LOO Unlikelihood: " + str(explain.score_unlik_loo(sub_suite, suite))
    
    return sub_suite
    
def run_battery(suite, k, name):
    csv = "algo,choice,dim,dist,ic_rep,ic_loo,unlik_rep,unlik_loo\n"
    csv += run_and_report(pick.pick_rand, k, suite, "rand")
    csv += run_and_report(pick.pick_kmeans, k, suite, "kmeans")
    csv += run_and_report(pick.pick_dd_gre, k, suite, "dd_greedy")
    csv += run_and_report(pick.pick_dd_exh, k, suite, "dimdist_exh")
    csv += run_and_report(pick.pick_ic_rep_gre, k, suite, "ic_rep")
    csv += run_and_report(pick.pick_ic_loo_gre, k, suite, "ic_loo")
    csv += run_and_report(pick.pick_unlik_rep_gre, k, suite, "unlik_rep")
    csv += run_and_report(pick.pick_unlik_loo_gre, k, suite, "unlik_loo")
    
    fname = name + "_k" + str(k) + "_results.csv"
    print "Writing file to " + fname
    file = open(fname, 'w')
    file.write(csv)
    file.close()
    
    print csv

def run_kgraph(algo, max_k, suite, name):
    csv = "k,dim,dist,ic_rep,ic_loo,ulik_rep,ulik_loo\n"
    for k in range(1,max_k+1):
        assn = algo(suite, k)
        sub_suite = suite.iloc[assn]
                
        dim = explain.score_dim(sub_suite)
        dist = explain.score_dist(sub_suite)
        ic_rep = explain.score_ic_rep(sub_suite, suite)
        ic_loo = explain.score_ic_loo(sub_suite, suite)
        ulik_rep = explain.score_unlik_rep(sub_suite, suite)
        ulik_loo = explain.score_unlik_loo(sub_suite, suite)
        csv += ("{},{},{},{},{},{},{}\n".format(k,dim,dist,ic_rep,ic_loo,ulik_rep,ulik_loo))
    
    fname = name + "_kgraph.csv"
    print "Writing file to " + fname
    file = open(fname, 'w')
    file.write(csv)
    file.close()
    return csv

def run_kgraph_battery(max_k, suite):
    run_kgraph(pick.pick_rand, max_k, suite, "rand")
    run_kgraph(pick.pick_kmeans, max_k, suite, "kmeans")
    run_kgraph(pick.pick_dd_gre, max_k, suite, "dd_gre")
    run_kgraph(pick.pick_dd_exh, max_k, suite, "dd_exh")
    run_kgraph(pick.pick_ic_gre, max_k, suite, "ic")
    run_kgraph(pick.pick_ic_loo_gre, max_k, suite, "ic_loo")
    run_kgraph(pick.pick_unlik_gre, max_k, suite, "unlik")
    run_kgraph(pick.pick_unlik_loo_gre, max_k, suite, "unlik_loo")
    return

def main():
    suite = dm.get_dat(sys.argv[1])

    print "Candidate Benchmarks: " + str(list(suite.index))

    run_battery(suite, 8, "nas")
#     run_kgraph_battery(8, suite)
#     run_interactive(pick.pick_dimdist_exh, 5, suite)
#     explain.plot_coverage(sub_suite)

main()
