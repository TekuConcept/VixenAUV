// setup variables, functions, and libraries
var libpath = './Peripherals/build/Release';
var VixenAUV = require(libpath + '/VixenAUV');
var $ = require('jquery-deferred');
var SECONDS = 1000;

function timeout(ms) {
	var res = $.Deferred();
	setTimeout(res.resolve, ms);
	return res.promise();
}



// Connect to the Arduino
var factory = new VixenAUV.ArduinoFactory();
var grid = factory.getPowerGrid();
var engine = factory.getEngine();



// Wait for the signal...
var wait = $.Deferred();
function callback(msg) {
    console.log(msg);
    wait.resolve();
}
grid.waitForStartSignal(callback);



// ...and BEGIN!
wait
.then(function() {
    engine.move(0.50);
})
.then(timeout(1*SECONDS))
.then(function() {
	engine.yaw(0.50);
})
.then(timeout(5*SECONDS))
.then(function() {
	engine.yaw(0.00);
})
.then(timeout(1*SECONDS))
.then(function() {
	engine.yaw(-0.50);
})
.then(timeout(5*SECONDS))
.done(function() {
	engine.kill();
});