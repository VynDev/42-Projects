const fs = require("fs");
const engine = require("./sources/engine");
const config = require("./sources/utils").config;
const logicOperator = require("./sources/logicOperator");
const util = require("util");

const parseError = require("./sources/ParseError");
const ParseError = parseError.ParseError;

var nbTest = 0;
var nbTestOk = 0;
var nbTestError = 0;
var nbFatalError = 0;

function GetFact(results, fact)
{
	for (let i = 0; i < results.length; ++i)
	{
		if (results[i].query == fact)
			return (results[i]);
	}
	return (null);
}

function TestError(file, expectedErrorCode)
{
	console.log("Testing with file => " + file);
	var fileContent = fs.readFileSync(file, "utf8");
	++nbTest;
	try {
		var results = engine.Process(fileContent);	
	} catch (error) {
		if (error instanceof ParseError)
		{
			if (error.code === expectedErrorCode)
			{
				console.log("\x1b[32m" + "Expected error code: " + expectedErrorCode + ", got: " + error.code + "\x1b[0m");
				++nbTestOk;
			}
			else
			{
				console.log("\x1b[31m" + "Expected error code: " + expectedErrorCode + ", got: " + error.code + "\x1b[0m");
				++nbTestError;
			}
		}
		else
		{
			console.log("\x1b[31m" + "Expected object ParseError but got something else: " + error + "\x1b[0m");
			++nbFatalError;
		}
		return ;
	}
	console.log("\x1b[31mNo error throwed \x1b[0m");
	++nbTestError;
}

function Test(file, expectedResults)
{
	console.log("Testing with file => " + file);
	var fileContent = fs.readFileSync(file, "utf8");
	try {
		var results = engine.Process(fileContent);
	} catch (error) {
		console.log(error)
		++nbFatalError;
		return ;
	}
	expectedResults.forEach((expectedResult) => {
		var result = GetFact(results, expectedResult.query);
		++nbTest;
		if (result === null)
		{
			if (expectedResult.state === null)
				++nbTestOk;
			else
				++nbTestError;
			console.log((expectedResult.state === null ? "\x1b[32m" : "\x1b[31m") + expectedResult.query + " query, expected: " + expectedResult.state + ", got: " + result + "\x1b[0m");
		}
		else
		{
			if (result.state == expectedResult.state)
				++nbTestOk;
			else
				++nbTestError;
			console.log((result.state === expectedResult.state ? "\x1b[32m" : "\x1b[31m") + expectedResult.query + " query, expected: " + expectedResult.state + ", got: " + result.state + "\x1b[0m");
		}
	})
}

try {

	/*
	**	Testing empty state & query
	*/
	Test("tests/empty_initial_state", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/empty_query", [
		{query: "A", state: null},
		{query: "B", state: null},
		{query: "C", state: null},
		{query: "D", state: null}
	])

	/*
	**	Testing comments
	*/
	Test("tests/simple_comment_1", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_comment_2", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	/*
	**	Testing AND
	*/
	Test("tests/simple_AND_1", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_AND_2", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_AND_3", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_AND_4", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.TRUE}
	])

	Test("tests/simple_AND_5", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_AND_6", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_AND_not_1", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_AND_not_2", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_AND_not_3", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	/*
	**	Testing AND in conclusion
	*/
	Test("tests/simple_AND_conclusion_1", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_AND_conclusion_2", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.TRUE}
	])

	/*
	**	Testing OR
	*/
	Test("tests/simple_OR_1", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_OR_2", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_OR_3", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_OR_4", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.TRUE}
	])

	Test("tests/simple_OR_5", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_OR_6", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	/*
	**	Testing XOR
	*/
	Test("tests/simple_XOR_1", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_XOR_2", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_XOR_3", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_XOR_4", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.TRUE}
	])

	Test("tests/simple_XOR_5", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_XOR_6", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	/*
	**	Testing simple imply
	*/
	Test("tests/simple_imply_1", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_imply_2", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_imply_3", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_imply_4", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.TRUE}
	])

	Test("tests/simple_imply_5", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE}
	])

	/*
	**	Testing simple test
	*/
	Test("tests/simple_test_1", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE},
		{query: "R", state: logicOperator.state.TRUE}
	])

	Test("tests/simple_test_2", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE},
		{query: "R", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_test_3", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE},
		{query: "R", state: logicOperator.state.TRUE}
	])

	Test("tests/simple_test_4", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE},
		{query: "R", state: logicOperator.state.TRUE}
	])

	/*
	**	Testing simple parentheses test
	*/
	Test("tests/simple_test_parentheses_1", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE},
		{query: "R", state: logicOperator.state.FALSE}
	])

	Test("tests/simple_test_parentheses_2", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE},
		{query: "R", state: logicOperator.state.TRUE}
	])

	Test("tests/simple_test_parentheses_3", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.TRUE},
		{query: "R", state: logicOperator.state.TRUE}
	])
	Test("tests/simple_test_parentheses_4", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.TRUE},
		{query: "R", state: logicOperator.state.FALSE}
	])

	/*
	**	Testing logic test
	*/
	Test("tests/logic_test_1", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.TRUE},
		{query: "R", state: logicOperator.state.FALSE}
	])

	Test("tests/logic_test_2", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.TRUE},
		{query: "R", state: logicOperator.state.TRUE}
	])

	Test("tests/logic_test_3", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.FALSE},
		{query: "R", state: logicOperator.state.FALSE}
	])

	Test("tests/logic_test_4", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE},
		{query: "R", state: logicOperator.state.TRUE}
	])

		// part 2 (negative)

	Test("tests/logic_test_5", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "B", state: logicOperator.state.FALSE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.FALSE},
		{query: "R", state: logicOperator.state.TRUE}
	])

	Test("tests/logic_test_6", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.FALSE},
		{query: "D", state: logicOperator.state.TRUE},
		{query: "R", state: logicOperator.state.FALSE}
	])

	Test("tests/logic_test_7", [
		{query: "A", state: logicOperator.state.FALSE},
		{query: "B", state: logicOperator.state.TRUE},
		{query: "C", state: logicOperator.state.TRUE},
		{query: "D", state: logicOperator.state.TRUE},
		{query: "R", state: logicOperator.state.TRUE}
	])

	/*
	**	Testing correction
	*/
	Test("tests/correction_AND_condition_conclusion_1", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "F", state: logicOperator.state.TRUE},
		{query: "K", state: logicOperator.state.TRUE},
		{query: "P", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_AND_condition_conclusion_2", [
		{query: "A", state: logicOperator.state.TRUE},
		{query: "F", state: logicOperator.state.TRUE},
		{query: "K", state: logicOperator.state.FALSE},
		{query: "P", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_OR_1", [
		{query: "A", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_OR_2", [
		{query: "A", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_OR_3", [
		{query: "A", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_OR_4", [
		{query: "A", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_XOR_1", [
		{query: "A", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_XOR_2", [
		{query: "A", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_XOR_3", [
		{query: "A", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_XOR_4", [
		{query: "A", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_negation_1", [
		{query: "A", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_negation_2", [
		{query: "A", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_negation_3", [
		{query: "A", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_negation_4", [
		{query: "A", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_multiple_rules_1", [
		{query: "A", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_multiple_rules_2", [
		{query: "A", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_multiple_rules_3", [
		{query: "A", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_multiple_rules_4", [
		{query: "A", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_parentheses_1", [
		{query: "E", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_parentheses_2", [
		{query: "E", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_parentheses_3", [
		{query: "E", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_parentheses_4", [
		{query: "E", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_parentheses_5", [
		{query: "E", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_parentheses_6", [
		{query: "E", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_parentheses_7", [
		{query: "E", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_parentheses_8", [
		{query: "E", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_parentheses_9", [
		{query: "E", state: logicOperator.state.FALSE}
	])

	Test("tests/correction_parentheses_10", [
		{query: "E", state: logicOperator.state.TRUE}
	])

	Test("tests/correction_parentheses_11", [
		{query: "E", state: logicOperator.state.TRUE}
	])

	/*
	**	Testing errors
	*/
	TestError("tests/simple_line_error_1", parseError.errors.syntax.code);
	TestError("tests/error_muchImply", parseError.errors.muchImply.code);
	TestError("tests/error_parentheseNotClosed_1", parseError.errors.parentheseNotClosed.code);
	TestError("tests/error_parentheseNotClosed_2", parseError.errors.parentheseNotClosed.code);
	TestError("tests/error_parentheseNotOpened_1", parseError.errors.parentheseNotOpened.code);
	TestError("tests/error_noCondition_1", parseError.errors.noCondition.code);
	TestError("tests/error_missingFact_1", parseError.errors.missingFact.code);
	TestError("tests/error_missingFact_2", parseError.errors.missingFact.code);
	TestError("tests/error_missingFact_3", parseError.errors.missingFact.code);
	TestError("tests/error_factNameCondition_1", parseError.errors.factNameCondition.code);
	TestError("tests/error_factNameCondition_2", parseError.errors.factNameCondition.code);
	TestError("tests/error_factNameCondition_3", parseError.errors.factNameCondition.code);
	TestError("tests/error_factNameCondition_4", parseError.errors.factNameCondition.code);
	TestError("tests/error_factNameConclusion_1", parseError.errors.factNameConclusion.code);
	TestError("tests/error_factNameConclusion_2", parseError.errors.factNameConclusion.code);
	TestError("tests/error_wrongOperatorConclusion_1", parseError.errors.wrongOperatorConclusion.code);
	TestError("tests/error_circularDependency_1", parseError.errors.circularConditionDependency.code);
	TestError("tests/error_circularDependency_2", parseError.errors.circularConditionDependency.code);
	TestError("tests/error_circularDependency_3", parseError.errors.circularConditionDependency.code);
	TestError("tests/error_contradiction_1", parseError.errors.contradiction.code);
	TestError("tests/error_contradiction_2", parseError.errors.contradiction.code);
	TestError("tests/error_contradiction_3", parseError.errors.contradiction.code);

	console.log("================ done ================")
	console.log("Total: " + nbTest);
	console.log("Success: " + nbTestOk);
	console.log("Error: " + (nbTestError !== 0 ? "\x1b[31m" : "") + nbTestError + "\x1b[0m");
	console.log("Fatal error: " + (nbFatalError !== 0 ? "\x1b[31m" : "") + nbFatalError + "\x1b[0m");

} catch (error) {
	console.log(error)
}