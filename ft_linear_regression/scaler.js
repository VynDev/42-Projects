/*
* @Author: Vyn
* @Date:   2019-01-07 14:45:47
* @Last Modified by:   Vyn
* @Last Modified time: 2019-01-07 17:20:03
*/

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

function RescaleThetas(thetas, data, scaledData)
{
	let newTheta2 = thetas[0] * ((0 - GetMin(data, 0)) /(GetMax(data, 0) - GetMin(data, 0))) + thetas[1];
	let newTheta1 = (thetas[0] * scaledData[2][0] + thetas[1] - newTheta2) / data[2][0];
	thetas[0] = newTheta1;
	thetas[1] = newTheta2;
}

function Scale(data)
{
	scaledData = [];
	for (let i = 0; i < data.length; ++i)
	{
		scaledData[i] = []
		scaledData[i][0] = data[i][0];
		scaledData[i][1] = data[i][1];
	}
	scaledData.forEach((elem) => {
		elem[0] = (elem[0] - GetMin(data, 0)) / (GetMax(data, 0) - GetMin(data, 0));
	})
	return (scaledData);
}

module.exports.RescaleThetas = RescaleThetas;
module.exports.Scale = Scale;