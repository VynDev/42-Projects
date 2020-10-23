/*
* @Author: Vyn
* @Date:   2019-01-07 14:45:47
* @Last Modified by:   Vyn
* @Last Modified time: 2019-01-07 17:16:39
*/

const vega = require('vega')
const fs = require("fs");

var chart = require('./chart.json');

function GetMin(tab, key)
{
	var max = null;
	tab.forEach((elem) => {
		if (max == null || elem[key] < max)
			max = elem[key];
	})
	return (max);
}

function GetMax(tab, key)
{
	var max = null;
	tab.forEach((elem) => {
		if (max == null || elem[key] > max)
			max = elem[key];
	})
	return (max);
}

module.exports.SavePlotChart = function(fileName, data, thetas)
{
	for (let i = 0; i < data.length; ++i)
		data[i] = {km: data[i][0], price: data[i][1]};
	chart.data[0].values = data;
	chart.marks.push({
		"type": "line",
		"from": {"data": "linear_regression"},
		"encode": {
			"enter": {
				"x": {"scale": "x", "field": "x"},
				"y": {"scale": "y", "field": "y"},
				"interpolate": {"value": "linear"}            
			}
		}
	});
	chart.data.push({
		"name": "linear_regression",
		"values": [{x: 0, y: thetas[0] * 0 + thetas[1]}, {x: GetMax(data, "km"), y: thetas[0] * GetMax(data, "km") + thetas[1]}]
	})
	var view = new vega.View(vega.parse(chart)).renderer('none').initialize();

	// generate static PNG file from chart
	view.toCanvas().then(function (canvas) {
		console.log('Writing PNG to file...')
		fs.writeFileSync(fileName, canvas.toBuffer())
	})
	.catch(function (err) {
		console.log("Error writing PNG to file:")
		console.error(err)
	});
}