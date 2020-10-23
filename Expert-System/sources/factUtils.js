const Condition = require("./Condition");
const logicOperator = require("./logicOperator");

module.exports.IsFact = function(fact)
{
	var i = 0;
	if (fact instanceof Condition)
		return (true);
	if (fact.length < 1 || fact.length > 2)
		return (false);
	if (fact.charAt(i) === "!")
		++i;
	if (fact.charCodeAt(i) < 65 || fact.charCodeAt(i) > 90)
		return (false);
	return (true);
}

module.exports.GetFactName = function(fact)
{
	var i = 0;
	if (fact instanceof Condition)
		throw "GetFactName: fact is Condition";
	if (fact.length < 1 || fact.length > 2)
		throw "GetFactName: fact length is wrong";
	if (fact.charAt(i) === "!")
		++i;
	if (fact.charCodeAt(i) < 65 || fact.charCodeAt(i) > 90)
		throw "GetFactName: fact is not an uppercase letter";
	return (fact.charAt(i));
}

module.exports.GetFactState = function(fact)
{
	if (fact.length < 1 || fact.length > 2)
		throw "GetFactState: fact length is wrong";
	if (fact.charAt(0) === "!")
		return (logicOperator.state.FALSE);
	return (logicOperator.state.TRUE);
}