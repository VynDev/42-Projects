/*
* @Author: Vyn
* @Date:   2019-01-07 14:45:47
* @Last Modified by:   Vyn
* @Last Modified time: 2019-01-07 14:49:52
*/

const Predict = require("./predict.js")

function CostFunction(thetas, data)
{
	var loss = 0;
	for (let i = 0; i < data.length; ++i)
	{
		let predicted = Predict(thetas, [data[i][0]]);
		loss += Math.pow(predicted - data[i][1], 2) / (data.length * 2)
	}
	return (loss);
}

function Train(data, nbIterations, thetas, learningRate)
{
	var lastCostValue = CostFunction(thetas, data);
	var currentCostValue;
	for (let currentIteration = 0; currentIteration < nbIterations; ++currentIteration)
	{
		var total = 0;
		var derivateResults = [0, 0];
		for (let i = 0; i < data.length; ++i)
		{
			let predicted = Predict(thetas, [data[i][0]]);
			derivateResults[0] += (predicted - data[i][1]) * data[i][0];
			derivateResults[1] += predicted - data[i][1];
		}
		for (let i = 0; i < derivateResults.length; ++i)
			derivateResults[i] = derivateResults[i] / data.length;
		thetas[0] -= learningRate * derivateResults[0]
		thetas[1] -= learningRate * derivateResults[1]
		currentCostValue = CostFunction(thetas, data);
		console.log("current loss: " + currentCostValue);
		if (lastCostValue - currentCostValue < 0)
		{
			learningRate = learningRate / 10
			console.log("new learning rate (down): " + learningRate);
		}
		lastCostValue = currentCostValue;
	}
}

module.exports = Train;