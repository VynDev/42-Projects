# -*- coding: utf-8 -*-
# @Author: Vyn
# @Date:   2019-03-05 21:35:50
# @Last Modified by:   Vyn
# @Last Modified time: 2019-03-06 18:43:37

# 1: dataset
# 2: column1 (2 - 31)
# 3: column2 (2 - 31)

import sys
import csv
import matplotlib.pyplot as plt
import numpy as np

COLUMN_DIAGNOSIS = 1

def couple(a, b):
	COLUMN_1 = a;
	COLUMN_2 = b;

	XB = [];
	YB = [];

	XM = [];
	YM = [];

	with open(sys.argv[1], "rt") as csvfile:
		csvreader = csv.reader(csvfile)
		for row in csvreader:
			if row[1] == "B":
				XB.append(float(row[COLUMN_1]));
				YB.append(float(row[COLUMN_2]));
			if row[1] == "M":
				XM.append(float(row[COLUMN_1]));
				YM.append(float(row[COLUMN_2]));

	#plt.subplot(10, 10, 1);
	plt.plot(XB, YB, 'ro', color = "blue");
	plt.plot(XM, YM, 'ro', color = "red");
	plt.title("Feature " + str(COLUMN_1) + " / " + str(COLUMN_2));
	plt.xlabel("feature " + str(COLUMN_1));
	plt.ylabel("feature " + str(COLUMN_2));
	plt.show()

if len(sys.argv) == 4:
	couple(int(sys.argv[2]), int(sys.argv[3]));
elif len(sys.argv) == 2:
	for i in range(2, 30): #start a 11
		for j in range(2, 30): #start a 2
			couple(i, j);
else:
	exit();