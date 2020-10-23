const fs = require("fs");
const engine = require("./sources/engine");
const config = require("./sources/utils").config;
const logicOperator = require("./sources/logicOperator");

var fileName;

function ParseArgs()
{
	for (let i = 2; i < process.argv.length; ++i)
	{
		if (process.argv[i] === "-v")
			config.verbose = true;
		else
			fileName = process.argv[i];
	}
}

if (process.argv.length < 3)
{
	console.log("Usage:\n" + process.argv[0] + " " + process.argv[1] + " FILE [-v]");
	return ;
}


try {
	ParseArgs();
	var fileContent = fs.readFileSync(fileName, "utf8");
	var results = engine.Process(fileContent);
	results.forEach((res) => {
		console.log((res.state == logicOperator.state.TRUE ? "\x1b[32m" : "\x1b[31m") + res.query + " is " + res.state + "\x1b[0m");
	})
} catch (error) {
	console.log(error)
}