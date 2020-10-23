const Condition = require("./Condition");
const logicOperator = require("./logicOperator");
const factUtils = require("./factUtils");
const utils = require("./utils");
const parser = require("./parser");
const analyzer = require("./analyzer");

module.exports.Process = function(content)
{
	utils.PrintDebug("================================ INITIAL STATE");
	utils.PrintDebug(content);
	var data = parser.ParseContent(content);
	utils.PrintDebug("================================ PARSING STATE");
	utils.InspectObjectDebug(data);
	utils.PrintDebug("================================ ANALYZING STATE");
	var result = analyzer.analyze(data);
	return (result);
}