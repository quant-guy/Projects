#!/bin/bash
for i in {1..100}; do ./run.sh >> $i.csv; done
paste *.csv > $1
rm *.csv
