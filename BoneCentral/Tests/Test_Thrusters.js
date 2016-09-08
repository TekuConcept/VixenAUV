var path = "./../Peripherals/build/Release"
var VixenAUV = require(path + "/VixenAUV");
var factory = new VixenAUV.ArduinoFactory();
var engine = factory.getEngine();

console.log("- BEGIN TEST -");

// test initialization was successful
engine.debug();
engine.verbose(true);

// test linear modifiers
engine.move(1.0);
engine.dive(1.0);
engine.move2(1.0);
engine.debug();

// reset
engine.kill();

// test angular modifiers
engine.yaw(1.0);
engine.pitch(1.0);
engine.yaw2(1.0);
engine.debug();

// reset
engine.kill();

// test modifier blending
engine.move(1.0);
engine.yaw(1.0);
engine.dive(1.0);
engine.pitch(1.0);
engine.move2(1.0);
engine.yaw2(1.0);
engine.debug();

// automatically kills engine when node ends
console.log("- END OF TEST -");