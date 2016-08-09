scripts=$(pwd)

cd ../Libraries/Drivers
git submodule update --recursive

cd ../BoneCentral/Peripherals
V8=$(node -e "var V8A=process.versions.v8.split('.');console.log('0x0'+V8A[0]+V8A[1]+V8A[2]);")
swig -c++ -javascript -node -DV8_VERSION=$V8 swig_BoneCentral.i
node-gyp configure
node-gyp build

echo "- FINISHED -"
cd $scripts