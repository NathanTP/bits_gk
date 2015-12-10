#!/usr/bin/env python

# A standalone program to read results and create figures.
# Little effort was made at software engineering, it's intended as an
# interactive script.
# Call it in a directory containing results to analyze.

import sys
import pandas as pd
import numpy as np
import sklearn as sk
import matplotlib
import matplotlib.pyplot as plt
import data_model as dm
import explain

def plot_feat(dim_df, feat):
    dim_df.loc[2:].plot(linewidth=4.0)
    plt.xlabel("K", fontsize=20)
    plt.ylabel(feat, fontsize=20)
    plt.xticks(fontsize=20)
    plt.yticks(fontsize=20)
    plt.legend(fontsize=20, loc='lower right')
    plt.show()

def plot_assn(assn_df, dat):
    for x in range(len(assn_df)):
        algo = assn_df.iloc[x]
        assn = algo['choice'].split(':')
        sub = dat.loc[assn]
        explain.plot_coverage(sub, algo.name)
    
def main():
#     matplotlib.style.use('ggplot')
#     feat = 'ulik_rep'
#     dim_df = dm.get_feature("basis_kgraph/", feat)
#     plot_feat(dim_df, feat)

    assn = dm.get_assn("nas_k5/nas_k5_results.csv")
    dat = dm.get_dat("../nas_results.h5")
    plot_assn(assn, dat)
    


main()