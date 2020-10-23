/*
* @Author: Vyn
* @Date:   2019-01-03 21:46:08
* @Last Modified by:   Vyn
* @Last Modified time: 2019-01-07 17:36:29
*/

const fs = require("fs");
const csv = require("csv");
const chart = require("./chart.js");

const scaler = require("./scaler.js");
const Train = require("./train.js")
const Predict = require("./predict.js")

var isTraining = false;
var trainingDataset = null;
var xs = [];
var modelFile = "./model.json";
var generateChart = false;

for (let i = 2; i < process.argv.length; ++i)
{
	if (process.argv[i] == "--train")
	{
		if (i + 1 < process.argv.length)
		{
			isTraining = true;
			trainingDataset = process.argv[i + 1];
			++i;
		}
		else
		{
			console.log("Missing file after '--train' argument")
			return PrintUsage();
		}
	}
	else if (process.argv[i] == "--model")
	{
		if (i + 1 < process.argv.length)
		{
			modelFile = "./" + process.argv[i + 1];
			++i;
		}
		else
		{
			console.log("Missing file after '--model' argument")
			return PrintUsage();
		}
	}
	else if (process.argv[i] == "--chart")
	{
		generateChart = true;
	}
	else
	{
		xs.push(process.argv[i]);
	}
}

if (isTraining)
{
	DoTraining(trainingDataset);
}
else
{
	if (xs.length == 0)
	{
		console.log("Missing inputs");
		return PrintUsage();
	}
	DoPrediction(modelFile, xs);
}

function DoTraining(file)
{
	csv.parse(fs.readFileSync(file, "utf8"), function(err, data) {
		if (err)
			console.log(err);
		else
		{
			let thetas = [0, 0];
			data.splice(0, 1);
			for (let i = 0; i < data.length; ++i)
			{
				data[i][0] = parseInt(data[i][0]);
				data[i][1] = parseInt(data[i][1]);
				if (data[i][0] === NaN || data[i][1] === NaN)
				{
					console.log("dataset has errors (only CSV are accepted)");
					return ;
				}

			}
			console.log(data);
			if (data.length == 0)
			{
				console.log("dataset is empty or has errors (only CSV are accepted)");
				return ;
			}
			let ln = 0.1
			let scaledData = scaler.Scale(data);
			Train(scaledData, 1000, thetas, ln);
			scaler.RescaleThetas(thetas, data, scaledData);
			console.log("Thetas: " + thetas);
			fs.writeFileSync(modelFile, JSON.stringify(thetas));
			console.log("Model saved to " + modelFile);
			if (generateChart)
				chart.SavePlotChart("chart.png", data.slice(), thetas);
		}
	})
}

function DoPrediction(modelFile, xs)
{
	try {
		var thetas = require(modelFile);
	} catch (e) {
		console.log("The model '" + modelFile + "' is not valid or doesn't exist");
		return ;
	}
	console.log(thetas);
	console.log(Predict(thetas, xs));
}

function PrintUsage()
{
	let usage = "usage: " + process.argv[0] + " " + process.argv[1] + " input [--model FILE] [--train FILE] [--chart]\n";
	usage += "--train FILE => Enable the TRAINING mode, don't forget the FILE dataset (csv)\n";
	usage += "--model FILE => The model FILE to use if PREDICTION (default) mode is enabled or model FILE to save in if TRAINING mode is enabled\n";
	usage += "--chart => Generate a chart (PNG) with the plots and the linear regression";
	console.log(usage)
}