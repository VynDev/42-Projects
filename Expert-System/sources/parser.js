const converter = require("./converter");
const utils = require("./utils");
const parseError = require("./ParseError");
const ParseError = parseError.ParseError;

function ParseRules(data, line)
{
	var lineTmp = line.split("=>");
	if (lineTmp[0].trim().split(/\s+/)[0][0] === '#')
		return ;
	if (lineTmp.length === 1)
	{
		if (lineTmp[0].trim().split(/\s+/)[0] !== "")
			throw new ParseError(parseError.errors.syntax);
	}
	if (lineTmp.length > 2)
		throw new ParseError(parseError.errors.muchImply);
	var condition = lineTmp[0].trim().split(/\s+/);
	var conclusion = lineTmp[1].trim().split(/\s+/);
	var rule = {condition: converter.ConvertCondition(condition), conclusion: converter.ConvertConclusion(conclusion)};
	data.rules.push(rule);
}

function ParseInitialState(line)
{
	return (line.split("#")[0].split(""));
}

function ParseQueries(line)
{
	return (line.split("#")[0].split(""));
}

module.exports.ParseContent = function(content)
{
	var data = {rules: []};
	content = content.replace(/\(|\)/g, " $& ");
	contentLines = content.trim().split(/\n+/);
	contentLines.forEach((line, lineNumber) => {
		parseError.currentInfo.line = line;
		parseError.currentInfo.lineNumber = lineNumber;
		if (line[0] === "=" && line[1] !== ">")
			data.initialState = ParseInitialState(line.substr(1));
		else if (line[0] === "?")
			data.queries = ParseQueries(line.substr(1));
		else
			ParseRules(data, line);
	})
	return (data);
}