//READ ARDUINO INPUTS
var data;
var newData;

// Connect to socket.io
var socket = io.connect('http://localhost:8000');
console.log('socket connected to:8000');
runSocket();

// Receive arduino data from server side (from app.js)
function runSocket() {
  socket.on('update', function(data) { //receiving updated data from server site app.js
    console.log(data);
    showData(data);
  });
}

function showData(data) {
  // data = 1;
  console.log('data is coming');
  // var showText = document.createElememt('p');
  if (data > 1) {
    // debugging part for data receiving==================================
    var divData = document.getElementById('show');
    var node = document.createTextNode( "serial is sending " + data);
    divData.appendChild(node);
    newData = parseInt(data);
  }
}

// NOW WE CAN USE "data" VARIABLE TO MANIPULATE P5 OBJECTS OR BEHAVIOUR

function setup() {
  var width = 255
  var height =255
  createCanvas(width, height);
  textSize(20);
}

function draw() {

  background(240, 40, 90);
  text("data=" + newData, 10, 240);

  noStroke();
  fill(50, 40, 250);
  ellipse(width/2, height/2, newData, newData);

}




