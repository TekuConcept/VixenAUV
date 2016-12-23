{
  "targets": [
    {
        "target_name": "VixenAUV",
        "sources": [
            "swig_VixenAUV_wrap.cxx",
            "Peripherals.Arduino/Serial.cpp",
            "../../Libraries/Drivers/Src/System/I2C.cpp",
            "../../Libraries/Drivers/Src/Sensors/BMP085.cpp",
            "../../Libraries/Drivers/Src/Sensors/HMC5883L.cpp",
            "../../Libraries/Drivers/Src/Sensors/MPU6050.cpp",
        ],
        "include_dirs": [
            "Peripherals.Arduino",
            "Peripherals.IMU",
            "../../Libraries/Drivers/Include/System",
            "../../Libraries/Drivers/Include/Registers",
            "../../Libraries/Drivers/Include/Interfaces",
            "../../Libraries/Drivers/Include/Sensors",
            "/usr/include/node"
            #avoid node-gyp confusion between ./node and ./nodejs
        ],
        "cflags": [
            "-std=c++11",
            "-w"
        ],
        "defines": [
            "NODE_MAJOR=<!(node -e \"console.log(process.versions.node.split('.')[0])\")",
            "NODE_MINOR=<!(node -e \"console.log(process.versions.node.split('.')[1])\")"
        ]
    }
  ]
}