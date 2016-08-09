{
  "targets": [
    {
        "target_name": "VixenAUV",
        "sources": [
            "swig_VixenAUV_wrap.cxx",
            "Peripherals.Arduino/Serial.cpp",
            "Peripherals.Arduino/PowerInterface.cpp"
        ],
        "include_dirs": [
            "Peripherals.Arduino",
            "Peripherals.IMU",
            "../../Libraries/Drivers/Include/System",
            "../../Libraries/Drivers/Include/Registers",
            "../../Libraries/Drivers/Include/Interfaces",
            "../../Libraries/Drivers/Include/Sensors"
        ],
        "cflags": [
            "-std=c++11",
            "-w",
            # "libraries" places this lib file in an awkward spot such that it
            # cannot be found, so we'll just explicitely add them here.
            "-L../../Libraries/Drivers/Build", "-lDrivers"
        ],
        "defines": [
            "NODE_MAJOR=<!(node -e \"console.log(process.versions.node.split('.')[0])\")",
            "NODE_MINOR=<!(node -e \"console.log(process.versions.node.split('.')[1])\")"
        ]
    }
  ]
}