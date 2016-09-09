var path = "./../Peripherals/build/Release"
var VixenAUV = require(path + "/VixenAUV");

var imu = new VixenAUV.IMU();

console.log("- BEGIN TEST -");

// ToDo: Function Tests
imu.debug_compass();
imu.debug_accelerometer();
imu.debug_gyroscope();
imu.debug_temperature();
imu.debug_pressure();

console.log("- END OF TEST -");