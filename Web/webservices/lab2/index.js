const express = require('express');
const bodyParser = require('body-parser');
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

app.post('/users', function(req, res){
	var username = req.body.username;
	var query = "INSERT INTO users (username) VALUES('"
		+ username + "')";

	/*db.query(query, funtion(err, result, fields) {
		if(err) throw err;

		res.send(JSON.stringify("Success"));
	});*/
	db.query(query);
});

app.get('/users', function(req, res) {
	res.send(JSON.stringify("Read"));
});

app.get('/users/:id', function(req, res) {
	res.send(JSON.stringify("Read"));
});

app.put('/users/:id', function(req, res) {
	res.send(JSON.stringify("Update"));
});

app.delete('/users', function(req, res) {
	res.send(JSON.stringify("Delete"));
});

app.delete('/users/:id', function(req, res) {
	res.send(JSON.stringify("Delete"));
});

app.listen(3000, function() {
	console.log('Example app listening on port 3000');

	db.connect(function(err){
		if (err) throw err;
		console.log('Connection to database successful ! ');
	});
});
