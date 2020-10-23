# -*- coding: utf-8 -*-
# @Author: Vyn
# @Date:   2019-03-05 21:35:50
# @Last Modified by:   Vyn
# @Last Modified time: 2019-03-10 15:51:44

# 1: dataset
# 2: column1 (2 - 31)
# 3: column2 (2 - 31)

import sys
import csv
import matplotlib.pyplot as plt
import numpy as np

COLUMN_DIAGNOSIS = 1

COLUMN_1 = int(sys.argv[2]);
DELETE_DIRECTION_1 = sys.argv[3];
DELETE_VALUE_1 = float(sys.argv[4]);

COLUMN_2 = int(sys.argv[5]);
DELETE_DIRECTION_2 = sys.argv[6];
DELETE_VALUE_2 = float(sys.argv[7]);

DIAGNONSIS_VALUE = sys.argv[8];

XB = [];
YB = [];

XM = [];
YM = [];

NEW_CSV = [];

with open(sys.argv[1], "rt") as csvfile:
	csvreader = csv.reader(csvfile)
	for row in csvreader:
		if row[1] == DIAGNONSIS_VALUE and DELETE_DIRECTION_1 == "<" and float(row[COLUMN_1]) < DELETE_VALUE_1 and DELETE_DIRECTION_2 == "<" and float(row[COLUMN_2]) < DELETE_VALUE_2:
			print("deleted");
		elif row[1] == DIAGNONSIS_VALUE and DELETE_DIRECTION_1 == ">" and float(row[COLUMN_1]) > DELETE_VALUE_1 and DELETE_DIRECTION_2 == "<" and float(row[COLUMN_2]) < DELETE_VALUE_2:
			print("deleted");
		elif row[1] == DIAGNONSIS_VALUE and DELETE_DIRECTION_1 == "<" and float(row[COLUMN_1]) < DELETE_VALUE_1 and DELETE_DIRECTION_2 == ">" and float(row[COLUMN_2]) > DELETE_VALUE_2:
			print("deleted");
		elif row[1] == DIAGNONSIS_VALUE and DELETE_DIRECTION_1 == ">" and float(row[COLUMN_1]) > DELETE_VALUE_1 and DELETE_DIRECTION_2 == ">" and float(row[COLUMN_2]) > DELETE_VALUE_2:
			print("deleted");
		elif row[1] == "B":
			XB.append(float(row[COLUMN_1]));
			YB.append(float(row[COLUMN_2]));
			NEW_CSV.append(row);
		elif row[1] == "M":
			XM.append(float(row[COLUMN_1]));
			YM.append(float(row[COLUMN_2]));
			NEW_CSV.append(row);

with open('resources/data_clean.csv', mode='w') as csvfile:
    csvwriter = csv.writer(csvfile, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    for row in NEW_CSV:
    	csvwriter.writerow(row);

#plt.subplot(10, 10, 1);
plt.plot(XB, YB, 'ro', color = "blue");
plt.plot(XM, YM, 'ro', color = "red");
plt.title("Feature " + str(COLUMN_1) + " / " + str(COLUMN_2));
plt.xlabel("feature " + str(COLUMN_1));
plt.ylabel("feature " + str(COLUMN_2));
plt.show()