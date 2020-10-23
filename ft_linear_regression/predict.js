/*
* @Author: Vyn
* @Date:   2019-01-07 14:45:47
* @Last Modified by:   Vyn
* @Last Modified time: 2019-01-07 14:49:19
*/

/*
**	thethas: [features, ..., bias]
**	xs: [features]
*/
function Predict(thetas, xs)
{
	return (xs[0] * thetas[0] + thetas[1]);
}

module.exports = Predict;