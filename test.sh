#!/bin/bash

OUT=$(echo "-12.8946,45.1422->-12.7794,45.2274" | $1 data.csv)

(echo "$OUT" | awk '
  BEGIN {
    e[1]=36315; n[1]="Num nodes"
    e[2]=308646; n[2]="Num arcs"
    e[3]=612965.047217; n[3]="Sum of arc durations (seconds)";
    e[4]=6630.652873; n[4]="Answer to the query: -12.8946,45.1422->-12.7794,45.2274";
    error = 0
  }
  {
    num++;
    d=$1-e[FNR];
    printf("Testing %s", n[FNR]);
    if (d < -0.01 || d > 0.01) {
      print "ERROR: expected " e[FNR], " got: " $1;
      error++;
    } else print "OK";
  }
  END {
    if (num != 4) {
      error++;
      print "ERROR: Missing or unexpected output (expected 4 lines, got " num ").";
    }
    if (error > 0) exit 1;
  }') && echo "PASS" || echo "FAILED"
