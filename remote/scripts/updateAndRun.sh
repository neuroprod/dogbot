
cd dogbot
git pull
cd remote
cd build
cmake .. -DCINDER_TARGET_GL=es3-rpi
make -j3
./Debug/remote/remote
$SHELL