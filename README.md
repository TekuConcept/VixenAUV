
VixenAUV
===========

VixenAUV provides a simple hardware foundation for autonomous vehicles as a JavaScript node module. Current features include: 6-axis motor control with linear and angular blended modifiers, and per-motor trim, a 9-axis IMU, and an arming feature.

### Software Requirements

> - Node v0.12.x or later *(required to use the built-in C++ callback features)*.
> - Swig v3.0.11 with JavaScript native directive:
```bash
git clone https://github.com/TekuConcept/swig
cd swig
./autogen.sh
./configure --prefix=/usr --without-clisp --without-maximum-compile-warnings
make; make install
```
> - (optional) 'jquery-deferred' or 'Bluebird' for promise-based scripting: `npm install -g jquery-deferred`
> - *It is recommended, though not required, to disable HDMI and eMMC on the bone, and to boot from an SD card for more pins and disk space.*

### Supported Hardware

> - BeagleBone Black - Debian 8.4 Jessie
> - Arduino Due - IDE v1.6.7, SAM Cortex-M3 v1.6.7
> - IMU - (BMP085, MPU6050, HMC5883L)

### Getting Started
First start by compiling the code: `cd VixenAUV/Scripts; ./compile.sh` - you may need to change permissions. If everything compiled successfully, a new node module should have been created in `VixenAUV/BoneCentral/Peripherals/build/Release` called **VixenAUV.node**. This is the heart of the code providing hardware access to the JavaScript brain.

The basic hardware configuration for testing code:

![Basic hardware configuration for testing.](http://usub.cs.usu.edu/Basic_Configuration_S.png)

The blue wire is the interrupt wire (where the kill switch plugs into) and the white wire is the kill-switch controller's feedback (for on-the-spot troubleshooting). When working with just a Beaglebone Black and Arduino Due, the white wire is not required but the blue wire needs to be pulled high to avoid weird side effects in the software.

###Scripting with VixenAUV
```JavaScript
// this path will vary according to the executing location
var libpath = './Peripherals/build/Release';
var VixenAUV = require(libpath + '/VixenAUV');

// Connect to the Arduino
var factory = new VixenAUV.ArduinoFactory();
var grid = factory.getPowerGrid();
var engine = factory.getEngine();

// Wait for the signal and go!
var deferred_resolve = null;
var wait = new Promise(function(resolve, reject) { deferred_resolve = resolve; });
function callback(msg) {
	console.log(msg);
	deferred_resolve();
}
grid.waitForStartSignal(callback);
wait.then(function() {
	engine.dive(0.25);
	engine.move(0.50);
});
```

### List of Commands
####ArduinoFactory
> - **pingArduino** - *sends a byte and the Arduino responds with a string*
> - **getEngine** - *creates a new Drive engine for managing motors*
> - **getPowerGrid** - *create a new Power interface for managing power power related features*

####Engine
> - **move**, **move2**, and **dive** - *all linear modifiers*
> - **yaw**, **yaw2**, and **pitch** - *all angular modifiers*
> - **setForwardTrim**, **setDiveTrim**, **setStrafeTrim** - *per thruster pair trim setting*
> - **debug** and **verbose** - *used for analyzing execution during runtime*

####Power
> - **turnOnEscs** and **turnOffEscs** - *relay powered ESC control*
> - **turnOnHeadlights** and **turnOffHeadlights** - *relay powered lights*
> - **getBatteryVoltage** - *reads the battery's current voltage*
> - **waitForStartSignal** - *callback-driven hardware signal*
> - **verbose** - *used for analyzing execution during runtime*
