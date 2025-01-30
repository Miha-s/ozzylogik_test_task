# Static text analysis client
## Dependencies
`CPP 17`  
`Qt5::Core`, `Qt5::Network`

## build (linux)
```bash
mkdir build
cd build
cmake ..
make
```

After that, the `client` executable will be available in `<source-dir>/build/bin/client`

## run (linux)
```
./server <host> <port> <file>
```
 - `<host>` - server ip address
 - `<port>` - server port address
 - `<file>` - path to file which will be sent to server for parsing