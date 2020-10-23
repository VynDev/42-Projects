import csv
from pylab import *

batchSize = 0;
size = 0;

X = [];
Y = [];
YTotal = 0
XMean = [];
YMean = [];
currentX = 0;

with open(sys.argv[1], "rt") as csvfile:
	csvreader = csv.reader(csvfile)
	for i, row in enumerate(csvreader):
		if i == 0:
			size = float(row[0]);
		elif i == 1:
			batchSize = float(row[0]);
		else:
			X.append(currentX);
			Y.append(float(row[0]));
			YTotal += float(row[0]);
			currentX += 1;
			if currentX % (size / batchSize) == 0:
				XMean.append(currentX);
				YMean.append(YTotal / (size / batchSize));
				YTotal = 0;

print("files: ", sys.argv[1]);
print("size: ", size, ", batch size: ", batchSize);
plot(XMean, YMean, color = "blue");

currentXDiff = (size / batchSize);

batchSize = 0;
size = 0;

X = [];
Y = [];
YTotal = 0
XMean = [];
YMean = [];
currentX = 0;

with open(sys.argv[2], "rt") as csvfile:
	csvreader = csv.reader(csvfile)
	for i, row in enumerate(csvreader):
		if i == 0:
			size = float(row[0]);
		elif i == 1:
			batchSize = float(row[0]);
		else:
			X.append(currentX);
			Y.append(float(row[0]));
			YTotal += float(row[0]);
			currentX += currentXDiff;
			if currentX % (size / batchSize) == 0:
				XMean.append(currentX);
				YMean.append(YTotal / (size / batchSize));
				YTotal = 0;

print("files: ", sys.argv[2]);
print("size: ", size, ", batch size: ", batchSize);
plot(XMean, YMean, color = "red");

#plot(X, Y, "ro", markersize=1);
show();