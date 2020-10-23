var logicOperator = require("./logicOperator.js");

class Condition
{
	constructor()
	{
		this.left = {fact: null, state: null};
		this.right = {fact: null, state: null};
		this.logicOperator = null;
	}

	SetLeft(fact, state)
	{
		this.left.fact = fact;
		this.left.state = state;
	}
	SetRight(fact, state)
	{
		this.right.fact = fact;
		this.right.state = state;
	}
	SetLogicOperator(operator)
	{
		this.logicOperator = operator;
	}
	GetLeft()
	{
		return (this.left);
	}
	GetRight()
	{
		return (this.right);
	}
	GetLogicOperator()
	{
		return (this.logicOperator);
	}
}

module.exports = Condition;