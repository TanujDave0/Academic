const express = require("express");
const bodyParser = require("body-parser");
const app = express();
const mysql2 = require("mysql2");

const cors = require("cors");

app.use(cors({ origin: "*" }));

/*------------------------------------------
--------------------------------------------
parse application/json
--------------------------------------------
--------------------------------------------*/
app.use(bodyParser.json());

/*------------------------------------------
--------------------------------------------
Database Connection
--------------------------------------------
--------------------------------------------*/
const conn = mysql2.createConnection({
  host: process.env["host"],
  user: process.env["user"] /* MySQL User */,
  password: process.env["password"] /* MySQL Password */,
  database: process.env["database"] /* MySQL Database */,
});

/*------------------------------------------
--------------------------------------------
Shows Mysql Connect
--------------------------------------------
--------------------------------------------*/
conn.connect((err) => {
  if (err) throw err;
  console.log("Mysql Connected with App...");
});


app.get("/api/v1/actors", (req, res) => {
  let sqlQuery = "SELECT * FROM actor";

  let query = conn.query(sqlQuery, (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/films", (req, res) => {
  let sqlQuery = "SELECT * FROM film";

  const { query } = req.query;

  if (query) {
    sqlQuery += ` WHERE LOWER(title) LIKE '%${query.toLowerCase()}%'`;
  }

  conn.query(sqlQuery, (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/customers", (req, res) => {
  let sqlQuery = "SELECT * FROM customer";

  let query = conn.query(sqlQuery, (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/stores", (req, res) => {
  let sqlQuery = "SELECT * FROM store";

  let query = conn.query(sqlQuery, (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/staff", (req, res) => {
  let sqlQuery = "SELECT * FROM staff";

  let query = conn.query(sqlQuery, (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/actors/:id", (req, res) => {
  let data = req.params.id;

  let sqlQuery = "SELECT * FROM actor WHERE actor_id = ?";

  let query = conn.query(sqlQuery, [data], (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/films/:id", (req, res) => {
  let data = req.params.id;

  let sqlQuery = "SELECT * FROM film WHERE film_id = ?";

  let query = conn.query(sqlQuery, [data], (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/customers/:id", (req, res) => {
  let data = req.params.id;

  let sqlQuery = "SELECT * FROM customer WHERE customer_id = ?";

  let query = conn.query(sqlQuery, [data], (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/staff/:id", (req, res) => {
  let data = req.params.id;

  let sqlQuery = "SELECT * FROM staff WHERE staff_id = ?";

  let query = conn.query(sqlQuery, [data], (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/stores/:id", (req, res) => {
  let data = req.params.id;

  let sqlQuery = "SELECT * FROM store WHERE store_id = ?";

  let query = conn.query(sqlQuery, [data], (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/inventory/:id", (req, res) => {
  let data = req.params.id;

  let sqlQuery = "SELECT * FROM inventory WHERE inventory_id = ?";

  let query = conn.query(sqlQuery, [data], (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/inventory-in-stock/:film_id/:store_id", (req, res) => {
  const { film_id, store_id } = req.params;

  let sqlQuery = "CALL film_in_stock(?,?,@count)";

  conn.query(sqlQuery, [film_id, store_id], (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results[0]);
    }
  });
});

app.get("/api/v1/actors/:id/films", (req, res) => {
  let data = req.params.id;

  let sqlQuery =
    "SELECT f.* FROM film f INNER JOIN film_actor fa ON f.film_id = fa.film_id WHERE fa.actor_id = ?;";

  let query = conn.query(sqlQuery, [data], (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/films/:id/actors", (req, res) => {
  let data = req.params.id;

  let sqlQuery =
    "SELECT a.* FROM actor a INNER JOIN film_actor fa ON a.actor_id = fa.actor_id INNER JOIN film f ON fa.film_id = f.film_id WHERE f.film_id = ?;";

  let query = conn.query(sqlQuery, [data], (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/films/:id/detail", (req, res) => {
  let data = req.params.id;

  let sqlQuery = "SELECT * FROM film_list WHERE FID = ?;";

  let query = conn.query(sqlQuery, [data], (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/customers/:id/detail", (req, res) => {
  let data = req.params.id;

  let sqlQuery = "SELECT * FROM customer_list WHERE ID = ?;";

  let query = conn.query(sqlQuery, [data], (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

app.get("/api/v1/actors/:id/detail", (req, res) => {
  let data = req.params.id;

  let sqlQuery = "SELECT * FROM actor_info WHERE actor_id = ?;";

  let query = conn.query(sqlQuery, [data], (err, results) => {
    if (err) {
      res.send("An Error has occured");
      console.log("An Error has occured");
    } else {
      res.send(results);
    }
  });
});

// --------------------MONGO----------------------------

const { MongoClient, ServerApiVersion, ObjectId } = require("mongodb");
const uri =
  "mongodb+srv://cs480apim:CS480wProfHayes@cluster0.qeipn8n.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0";

// Create a MongoClient with a MongoClientOptions object to set the Stable API version
const client = new MongoClient(uri, {
  serverApi: {
    version: ServerApiVersion.v1,
    strict: true,
    deprecationErrors: true,
  },
});

app.get("/api/v1/movies", async (req, res) => {
  try {
    const db = client.db("sample_mflix");
    const collection = db.collection("movies");

    const { query } = req.query;

    if (query) {
      const result = await collection
        .find({ genres: query })
        .limit(10)
        .toArray();
      res.send(result);
    } else {
      const result = await collection.find({}).limit(10).toArray();
      res.send(result);
    }
  } catch (err) {
    console.error("Error: ", err);
    res.send(["An Error has occured."]);
  }
});

app.get("/api/v1/colors", async (req, res) => {
  try {
    const db = client.db("cs480-project2");
    const collection = db.collection("colors");

    const result = await collection.find({}).toArray();

    res.send(result);
  } catch (err) {
    console.error("Error: ", err);
    res.send(["An Error has occured."]);
  }
});

app.post("/api/v1/colors", async (req, res) => {
  try {
    const db = client.db("cs480-project2");
    const collection = db.collection("colors");

    const newColor = req.body ;

    const result = await collection.insertOne(newColor);

    res.send(result);
  } catch (err) {
    console.error("Error: ", err);
    res.send(["An Error has occured."]);
  }
});

app.get("/api/v1/colors/:id", async (req, res) => {
  try {
    const db = client.db("cs480-project2");
    const collection = db.collection("colors");

    let objectID = new ObjectId(req.params.id);

    const result = await collection.find({ _id: objectID }).toArray();

    res.send(result);
  } catch (err) {
    console.error("Error: ", err);
    res.send(["An Error has occured."]);
  }
});

app.delete("/api/v1/colors/:id", async (req, res) => {
  try {
    const db = client.db("cs480-project2");
    const collection = db.collection("colors");
    let objectID = new ObjectId(req.params.id);

    const result = await collection.deleteMany({ _id: objectID });

    res.send(result);
  } catch (err) {
    console.error("Error: ", err);
    res.send(["An Error has occured."]);
  }
});

// async function run() {
//   try {
//     // Connect the client to the server	(optional starting in v4.7)
//     await client.connect();
//     // Send a ping to confirm a successful connection
//     await client.db("admin").command({ ping: 1 });
//     console.log(
//       "Pinged your deployment. You successfully connected to MongoDB!",
//     );
//   } finally {
//     // Ensures that the client will close when you finish/error
//     await client.close();
//   }
// }
// run().catch(console.dir);

/**
 * API Response
 *
 * @return response()
 */
// function apiResponse(results) {
//   return JSON.stringify({ status: 200, error: null, response: results });
// }

/*------------------------------------------
--------------------------------------------
Server listening
--------------------------------------------
--------------------------------------------*/
app.listen(3000, () => {
  console.log("Server started on port 3000...");
});
