'use strict'

const express = require('express');
const bodyParser = require('body-parser');
const pgp = require('pg-promise')();

const db_user = 'docker' || process.env.DB_USERNAME;
const db_pass = 'docker' || process.env.DB_PASSWORD;
const db_host = 'postgres' || process.env.DB_HOST;
const db_port = '8082' || process.env.DB_PORT;
const db_database = 'docker' || process.env.DB_DATABASE;
const db_url = 'postgres://' + db_user + ':' + db_pass + '@' + db_host + ':' + db_port+'/'+db_database;

const app = express();
const port = process.env.PORT || 8085;

app.use(bodyParser.urlencoded({ extended: false}));
app.use(bodyParser.json());

const db = pgp(db_url);

app.get('/', (req, res) => res.send('api rest de laberinto'));

app.get('/users/:user/:pass', (req, res) => {
    let user = req.params.user;
    let pass = req.params.pass;
    db.any('SELECT count(1) FROM public."user" WHERE user_t = $1 AND password_t = $2 Limit 1;', [user, pass])
        .then((data) => res.send(data))
        .catch((error) => console.log(error));
});
app.get('/laberinto/:fila/:columna', (req, res) => {
  let fila = req.params.fila;
  let colunma = req.params.columna;
  if(( /^([0-9])*$/.test(fila))  || ( /^([0-9])*$/.test(colunma))){
    db.any('SELECT laberinto.valor FROM public.laberinto where laberinto.seccion_fila = $1 AND laberinto.seccion_columna = $2;',[fila, colunma])
        .then((data) => res.send(data))
        .catch((error) => console.log(error));
  }
  else{res.status(400).send({Error:"no es numero la fila o columna"});}
});

app.listen(8085, '0.0.0.0', () => console.log("api corriendo en el puerto "+port));
