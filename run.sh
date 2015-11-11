#!/bin/bash
for BENCH in $1/*
do
  $BENCH >> res.log
done
