# ft_linear_regression

## Installation
*You must have **Node.js** and **npm** installed*
```
npm install
```
## Usage
To train the model from a file 'dataset.csv':
```
node index.js --train dataset.csv
```
To use the model and get the output for the input '42':
```
node index.js 42
```
You can specify the model to use with the '--model FILE' parameter (default is model.json)  
You can save a PNG chart of the model with the '--chart' parameter  
Just type 'node index.js' to get the full usage
