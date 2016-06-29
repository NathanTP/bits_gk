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
import pygal as pg

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

# Just a sandbox to play with plotting ideas
def plot_sand(suite, name):
    clbl = ['LLC', 'SysCalls', 'IPC', 'Branch', 'Cache', 'TLB']
    
    cust_style = pg.style.Style(value_font_size=1, label_font_size=20, legend_font_size=20)

    # Plot Means
#     plot = pg.Radar(fill=True, style=cust_style, legend_at_bottom=True,
#                     legend_at_bottom_columns=3, legend_box_size=10,
#                     margin_bottom=60, margin_left=0, margin_right=10)
    plot = pg.Radar(fill=True, style=cust_style, show_legend=False)
#     plot = pg.Radar(fill=True, hide_legend=True, )
#     plot.title = name + " Coverage"
    plot.x_labels = clbl
    for bench in suite.iterrows():
        plot.add(bench[0], list(bench[1]))
        
#     plot.add("Total", list(tot))
    fname = name + "_coverage.png"
    print "Plotting coverage to " + fname
    plot.render_to_png(fname)
#     plot.render_to_file(fname)
    
def main():
#     matplotlib.style.use('ggplot')
#     feat = 'ulik_rep'
#     dim_df = dm.get_feature("basis_kgraph/", feat)
#     plot_feat(dim_df, feat)

#     assn = dm.get_assn("basis_k5/basis_k5_results.csv")
    dat = dm.get_dat("../basis_results.h5")
    sub = dat.iloc[14:15]
#     sub.drop([[1]], )
#     sub = pd.DataFrame([[0,0,0,0,0,0]])
    sub = pd.DataFrame([[0.1,0.1,0.1,0.1,1.0,0.1]], index=['dummy'])
#     sub = pd.DataFrame([[0.1,0.1,0.1,0.1,0.1,1.0],
#                         [0.1,0.1,0.1,0.1,1.0,0.1],
#                         [0.1,0.1,0.1,1.0,0.1,0.1],
#                         [0.1,0.1,1.0,0.1,0.1,0.1],
#                         [0.1,1.0,0.1,0.1,0.1,0.1],
#                         [1.0,0.1,0.1,0.1,0.1,0.1],
#                         ], index=['d1', 'd2', 'd3', 'd4', 'd5', 'd6'])
    print dat
    print sub
#     exit()
    plot_sand(sub, "test")
#     plot_assn(assn, dat)
    


main()