const utils = require("./utils");
const logicOperator = require("./logicOperator");
const factUtils = require("./factUtils");
const Condition = require("./Condition");
const parseError = require("./ParseError");
const ParseError = parseError.ParseError;

function findCloseParenthese(condition, i)
{
	var nbOpened = 0;
	for (i; i < condition.length; ++i)
	{
		if (condition[i] === "(")
			++nbOpened;
		if (condition[i] === ")" && nbOpened !== 0)
			--nbOpened;
		else if (condition[i] === ")")
			return (i);
	}
	return (-1);
}

function ProcessParentheses(condition, i)
{
	//var parentheseEnd = condition.indexOf(")", i + 1);
	var parentheseEnd = findCloseParenthese(condition, i + 1);
	if (parentheseEnd === -1)
	{
		throw new ParseError(parseError.errors.parentheseNotClosed);
	}
	var newCondition = condition.splice(i, (parentheseEnd - i) + 1);
	newCondition.splice(0, 1);
	newCondition.splice(-1, 1);
	var tmp = module.exports.ConvertCondition(newCondition)
	condition.splice(i, 0, tmp);
}

function CreateNewCondition(condition, i)
{
	var convertedCondition = new Condition
	if (condition[i - 1] instanceof Condition)
		convertedCondition.SetLeft(condition[i - 1], logicOperator.state.TRUE);
	else
		convertedCondition.SetLeft(factUtils.GetFactName(condition[i - 1]), factUtils.GetFactState(condition[i - 1]));
	if (condition[i + 1] instanceof Condition)
		convertedCondition.SetRight(condition[i + 1], logicOperator.state.TRUE);
	else
		convertedCondition.SetRight(factUtils.GetFactName(condition[i + 1]), factUtils.GetFactState(condition[i + 1]));
	convertedCondition.SetLogicOperator(logicOperator.StrToLogic(condition[i]));
	return (convertedCondition);
}

function CreateNewConditionOneFact(fact)
{
	var convertedCondition = new Condition;
	convertedCondition.SetLeft(factUtils.GetFactName(fact), factUtils.GetFactState(fact));
	convertedCondition.SetRight(factUtils.GetFactName(fact), factUtils.GetFactState(fact));
	convertedCondition.SetLogicOperator(logicOperator.operator.AND);
	return (convertedCondition);
}

function _ConvertCondition(condition, operator)
{
	var priority = [logicOperator.operator.AND, logicOperator.operator.OR, logicOperator.operator.XOR];
	for (let j = 0; j < priority.length; ++j)
	{
		for (let i = 0; i < condition.length && condition[i][0] !== '#'; ++i)
		{
			if (condition[i] === "(")
				ProcessParentheses(condition, i);
			if (condition[i] === ")")
				throw new ParseError(parseError.errors.parentheseNotOpened);
			if (logicOperator.StrToLogic(condition[i]) !== false && logicOperator.StrToLogic(condition[i]) == priority[j])
			{
				if (i === 0 || i === condition.length - 1)
					throw new ParseError(parseError.errors.missingFact);
				if (condition[i + 1] === "(")
					ProcessParentheses(condition, i + 1);
				if (factUtils.IsFact(condition[i - 1]) === false || factUtils.IsFact(condition[i + 1]) === false)
				{
					if (logicOperator.StrToLogic(condition[i - 1]) !== false || logicOperator.StrToLogic(condition[i + 1]) !== false)
						throw new ParseError(parseError.errors.missingFact);
					throw new ParseError(parseError.errors.factNameCondition);
				}
				var convertedCondition = CreateNewCondition(condition, i);
				condition.splice(i - 1, 3, convertedCondition);
				i = -1;
			}
		}
	}
	if (condition.length !== 1)
		throw "Error: (condition) tab length should be 1"; // This is not a syntax error (critical)
	condition = condition[0];
	return (condition);
}

module.exports.ConvertCondition = function(condition)
{
	utils.InspectObjectDebug(condition);
	if (condition.length < 1 || (condition.length === 1 && condition[0].length === 0))
		throw new ParseError(parseError.errors.noCondition);
	if (condition.length === 1)
		return (CreateNewConditionOneFact(condition[0]));
	return (_ConvertCondition(condition))
}

module.exports.ConvertConclusion = function(conclusion)
{
	utils.InspectObjectDebug(conclusion);
	for (let i = 0; i < conclusion.length && conclusion[i][0] !== '#'; ++i)
	{
		if (logicOperator.StrToLogic(conclusion[i]) !== false)
		{
			if (logicOperator.StrToLogic(conclusion[i]) !== logicOperator.operator.AND)
				throw new ParseError(parseError.errors.wrongOperatorConclusion);
		}
		else if (factUtils.IsFact(conclusion[i]) === true)
		{
			var tmp = {fact: factUtils.GetFactName(conclusion[i]), state: factUtils.GetFactState(conclusion[i])};
			conclusion[i] = tmp;
		}
		else
		{
			throw new ParseError(parseError.errors.factNameConclusion);
		}
	}
	return (conclusion);
}