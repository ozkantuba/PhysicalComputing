//Server side
var app = require('http').createServer(handler); //default setting

//modules for node
var url = require('url');
var fs = require('fs'); //write files
var socket = require('socket.io').listen(app); // open connection between client and server sites

app.listen(8000);
console.log("8000 opened");

//open the port for serial communication with arduino
const SerialPort = require('serialport');
const Readline = SerialPort.parsers.Readline;

//Change the serial port name if needed
const port = new SerialPort("/dev/tty.usbmodem1411", {
  baudRate: 9600,
  parser: new Readline("\n") //parsing the data to terminal
});

//recieve data from arduino
var receivedData = "";

//opening the port 8000
port.on("open", function() {

  console.log('open');


  port.on('data', function(data) {
    console.log(data);
    // transform data from buffer data to string
    receivedData += data.toString();
    console.log("recieveddata= " + receivedData);
    if (receivedData.indexOf('E') >= 0 && receivedData.indexOf('B') >= 0) {
      // save the data between 'B' and 'E'
      var sendData = receivedData.substring(receivedData.indexOf('B') + 1, receivedData.indexOf('E'));
      receivedData = '';
    }
    // send the incoming data to browser with websockets. communicating with script.js client sites-----------------------------------------------
    socket.emit('update', sendData); //send updated data to client site, update function was sent to client site script.js
    //console.log("sentdata= " + sendData); //send

  });
});

// Http handler function
function handler(req, res) {

  // Using URL to parse the requested URL
  var path = url.parse(req.url).pathname;

  // Managing the root route
  if (path == '/') {
    index = fs.readFile(__dirname + '/index.html',
      function(error, data) {

        if (error) {
          res.writeHead(500);
          return res.end("Error: unable to load html");
        }

        res.writeHead(200, {
          'Content-Type': 'text/html'
        });
        res.end(data);
      });

    // Managing the route for the javascript files
  }

   else if (/\.(js)$/.test(path)) {
    index = fs.readFile(__dirname + path,
      function(error, data) {

        if (error) {
          res.writeHead(500);
          return res.end("Error: unable to load " + path);
        }

        res.writeHead(200, {
          'Content-Type': 'text/plain'
        });
        res.end(data);
      });
  } else {
    res.writeHead(404);
    res.end("Error: 404 - File not found.");
  }

}




