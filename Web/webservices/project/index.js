const express = require('express');
const mysql = require('mysql');
const bodyParser = require('body-parser');
const app = express();

app.use(bodyParser.urlencoded({ extended: true }));

var db = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "zoo",
    port: "3306"
});

/* ANIMALS */
app.get('/animals', function(req, res) {
    var query = "SELECT * FROM animals"
    db.query(query, function(err, result, fields) {
        if (err) throw err;
        res.send(JSON.stringify(result));
    });
});

app.get('/animals/:id', function(req, res) {
    var id = req.params.id;
    var query = "SELECT * FROM animals WHERE id=" + id;
    db.query(query, function(err, result, fields) {
        if (err) throw err;
        res.send(JSON.stringify(result));
    });
});

app.post('/animals', function(req, res) {
    var id              = req.body.id;
    var name            = req.body.name;
    var race            = req.body.race;
    var food_per_day    = req.body.food_per_day;
    var birth_date      = req.body.birth_date;
    var entry_date      = req.body.entry_date;
    var cage_id         = req.body.cage_id;    
    var query = "INSERT INTO `animals`(`id`, `name`, `race`, `food_per_day`, `birth_date`, `entry_date`, `cage_id`) VALUES ("+id+",'"+name+"','"+race+"',"+food_per_day+",'"+birth_date+"','"+entry_date+"',"+cage_id+")";
    db.query(query, function(err, result, fields) {
        if (err) throw err;
        res.send(JSON.stringify("Success"));
    });
});

app.put('/animals/:id', function(req, res) {
    var id = req.params.id;
    var name = req.body.name;
    var race = req.body.race;
    var food_per_day = req.body.food_per_day;
    var birth_date = req.body.birth_date;
    var entry_date = req.body.entry_date;
    var cage_id = req.body.cage_id;

    var query = "UPDATE animals SET name = '" + name + "' , race = '" + race + "' , food_per_day = " + food_per_day + " , birth_date = '" + birth_date + "' , entry_date = '" + entry_date + "' , cage_id = " + cage_id + " WHERE id="
    + id;
    db.query(query, function(err, result, fields) {
        if (err) throw err;
        res.send(JSON.stringify("Success"));
    });
});

app.delete('/animals', function(req, res) {
    var query = "DELETE FROM animals";
    db.query(query, function(err, result, fields) {
        if (err) throw err;
        res.send(JSON.stringify("Success"));
    });
});

app.delete('/animals/:id', function(req, res) {
    var id = req.params.id;
    var query = "DELETE FROM animals WHERE id=" + id;
    db.query(query, function(err, result, fields) {
        if (err) throw err;
        res.send(JSON.stringify("Success"));
    });
});

/*CAGES*/
app.get('/cages', function(req, res) {
    var query = "SELECT * FROM cages"
    db.query(query, function(err, result, fields) {
        if (err) throw err;
        res.send(JSON.stringify(result));
    });
});

/*FOOD*/
app.get('/food', function(req, res) {
    var query = "SELECT * FROM food"
    db.query(query, function(err, result, fields) {
        if (err) throw err;
        res.send(JSON.stringify(result));
    });
});

/*STAFF*/
app.get('/staff', function(req, res) {
    var query = "SELECT * FROM staff"
    db.query(query, function(err, result, fields) {
        if (err) throw err;
        res.send(JSON.stringify(result));
    });
});

/* Listen - database */
app.listen(3000, function() {
    db.connect(function(err) {
        if (err) throw err;
        console.log('Connection to database successful!');
    });
    console.log('Example app listening on port 3000!');
});
