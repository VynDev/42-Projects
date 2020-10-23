const logicOperator = require("./logicOperator");
const utils = require("./utils");
const Condition = require("./Condition");
const parseError = require("./ParseError");
const ParseError = parseError.ParseError;

function IsFactInInitialState(data, query)
{
	for (let i = 0; i < data.initialState.length; ++i)
	{
		if (data.initialState[i] === query)
			return (true);
	}
	return (false);
}
function FindFactRule(data, query)
{
	var results = [];
	utils.PrintDebug("Finding rules for fact:");
	utils.InspectObjectDebug(query);
	for (let i = 0; i < data.rules.length; ++i)
	{
		let conclusion = data.rules[i].conclusion;
		for (let j = 0; j < conclusion.length; ++j)
		{
			if (conclusion[j].fact === query)
				results.push({rule: data.rules[i], factIndex: j});
		}
	}
	return (results);
}

function IsFactIn(lastCheck, fact)
{
	for (var i = 0; i < lastCheck.length; ++i)
	{
		if (lastCheck[i] === fact)
			return (true);
	}
	return (false);
}

function IsConditionTrue(data, condition, lastCheck)
{
	utils.PrintDebug("Checking condition")
	utils.InspectObjectDebug(condition);
	var leftState;
	var rightState;

	if (condition.left.fact instanceof Condition)
		leftState = IsConditionTrue(data, condition.left.fact, lastCheck);
	else
		leftState = IsFactTrue(data, condition.left.fact, lastCheck);
	if (condition.right.fact instanceof Condition)
		rightState = IsConditionTrue(data, condition.right.fact, lastCheck);
	else
		rightState = IsFactTrue(data, condition.right.fact, lastCheck);
	if (condition.logicOperator === logicOperator.operator.AND)
	{
		if (leftState === condition.left.state && rightState === condition.right.state)
			return (logicOperator.state.TRUE);
	}
	else if (condition.logicOperator === logicOperator.operator.OR)
	{
		if (leftState === condition.left.state || rightState === condition.right.state)
			return (logicOperator.state.TRUE);
	}
	else if (condition.logicOperator === logicOperator.operator.XOR)
	{
		if (leftState === condition.left.state && rightState !== condition.right.state
			|| leftState !== condition.left.state && rightState === condition.right.state)
			return (logicOperator.state.TRUE);
	}
	return (logicOperator.state.FALSE);
}

function IsFactTrue(data, query, lastCheck)
{
	lastCheck = lastCheck.slice(0, lastCheck.length);
	if (IsFactIn(lastCheck, query))
		throw new ParseError(parseError.errors.circularConditionDependency, "Circular condition dependency for fact " + query);
	lastCheck.push(query);
	utils.PrintDebug("Checking query:");
	utils.InspectObjectDebug(query);
	var rules = FindFactRule(data, query);
	var state = null;
	for (let i = 0; i < rules.length; ++i)
	{
		if (IsConditionTrue(data, rules[i].rule.condition, lastCheck))
		{
			if (state !== null && rules[i].rule.conclusion[rules[i].factIndex].state !== state)
				throw new ParseError(parseError.errors.contradiction);
			state = rules[i].rule.conclusion[rules[i].factIndex].state;
		}
	}
	let isInitialFact = IsFactInInitialState(data, query);
	if (isInitialFact && state !== null && state !== isInitialFact)
		throw new ParseError(parseError.errors.contradiction);
	else if (isInitialFact)
		return (logicOperator.state.TRUE);
	return (state === true ? logicOperator.state.TRUE : logicOperator.state.FALSE);
}

module.exports.analyze = function(data)
{	
	let result = [];
	data.queries.forEach((query) => {
		var lastCheck = [];
		var isTrue = IsFactTrue(data, query, lastCheck);
		utils.PrintDebug("[QUERY] " + query + ": " + isTrue);
		utils.PrintDebug("=======================");
		result.push({query: query, state: isTrue});
	})
	return (result);
}