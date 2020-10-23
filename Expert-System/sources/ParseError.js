module.exports.errors = {
	syntax: {
		code: 1,
		message: "Syntax error"
	},
	muchImply: {
		code: 2,
		message: "To much imply operator"
	},
	parentheseNotClosed: {
		code: 3,
		message: "Parenthese not closed"
	},
	parentheseNotOpened: {
		code: 4,
		message: "Parenthese not opened"
	},
	noCondition: {
		code: 5,
		message: "No condition found"
	},
	missingFact: {
		code: 6,
		message: "Fact missing near operator"
	},
	factNameCondition: {
		code: 7,
		message: "The fact name must be an uppercase letter (condition)"
	},
	factNameConclusion: {
		code: 8,
		message: "The fact name must be an uppercase letter (conclusion)"
	},
	circularConditionDependency: {
		code: 9,
		message: "Circular condition dependency"
	},
	contradiction: {
		code: 10,
		message: "Contradiction"
	},
	wrongOperatorConclusion: {
		code: 11,
		message: "Wrong operator in conclusion"
	}
}

var currentInfo = {
	lineNumber: null,
	line: null
}

module.exports.currentInfo = currentInfo;

class ParseError
{
	constructor(error, customMessage)
	{
		this.code = error.code;
		this.message = customMessage !== undefined ? customMessage : error.message;
		this.lineNumber = currentInfo.lineNumber;
		this.line = currentInfo.line;
	}
}

module.exports.ParseError = ParseError;