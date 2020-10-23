const util = require('util')

var config = {
	verbose: false
};

module.exports.config = config;

module.exports.PrintDebug = function(text)
{
	if (config.verbose)
		console.log(text);
}

module.exports.InspectObjectDebug = function(text)
{
	if (config.verbose)
		console.log(util.inspect(text, false, null, true));
}