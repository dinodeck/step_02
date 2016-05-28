if [ -e "/opt/local/lib/libSDL-1.2.0.dylib" ]
then
  mv /opt/local/lib/libSDL-1.2.0.dylib /opt/local/lib/libSDL-1.2.0.dylib_
fi

make clean
rm ./dinodeck
make PLATFORM_DS=MAC

if [ -e "/opt/local/lib/libSDL-1.2.0.dylib_" ]
then
  mv /opt/local/lib/libSDL-1.2.0.dylib_ /opt/local/lib/libSDL-1.2.0.dylib
fi