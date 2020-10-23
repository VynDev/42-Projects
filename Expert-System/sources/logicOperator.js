var operator = { // ENUM
	AND: 1,
	OR: 2,
	XOR: 3
}

var state = { // ENUM
	FALSE: false,
	TRUE: true
}

var associativeLogicStrOperator = [
	{str: "+", logicOperator: operator.AND},
	{str: "|", logicOperator: operator.OR},
	{str: "^", logicOperator: operator.XOR}
]

function StrToLogic(operator)
{
	for (let i = 0; i < associativeLogicStrOperator.length; ++i)
	{
		if (associativeLogicStrOperator[i].str === operator)
			return (associativeLogicStrOperator[i].logicOperator);
	}
	return (false);
}

function LogicToStr(operator)
{
	for (let i = 0; i < associativeLogicStrOperator.length; ++i)
	{
		if (associativeLogicStrOperator[i].logicOperator === operator)
			return (associativeLogicStrOperator[i].str);
	}
	return (false);
}

module.exports.operator = operator;
module.exports.state = state;
module.exports.StrToLogic = StrToLogic;
module.exports.LogicToStr = LogicToStr;