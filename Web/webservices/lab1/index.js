const express = require('express');
const app = express();
const mysql = require('mysql');

// Connection to the database
var db = mysql.createConnection({
	host: "localhost",
	user: "korax",
	password: "pass",
	database: "ML1",
	port: "3306"
});

// All the get responses
app.get('/', function(req, res) {
	db.query("SELECT * FROM AIRCRAFTS", function(err, result, fields){
		if(err) throw err;

		var response = {"page": "home", "result": result};
		res.send(JSON.stringify(response));
	})
});

app.get('/users', function(req, res){
	var response = {"page": "users"};
	res.send(JSON.stringify(response));
});

app.get('/users/:id(\\d+)', function(req, res){
	var response = {"page": "users", "parameters": req.params};
	res.send(JSON.stringify(response));
});

app.get('/users/message', function(req, res){
	var response = {"page": "message"};
	res.send(JSON.stringify(response));
});

app.listen(3000, function() {
	console.log('Example app listening on port 3000!');

	db.connect(function(err){
		if (err) throw err;
		console.log('Connection to database successful ! ');
	});
});
