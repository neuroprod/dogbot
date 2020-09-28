
cd dogbot
cd remote
cd build
cmake .. -DCINDER_TARGET_GL=es3-rpi -DPI
make -j3
./Debug/remote/remote devIP
$SHELL