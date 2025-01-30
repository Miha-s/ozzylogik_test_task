# Static text analysis server
## Dependencies
`CPP 17`  
`Boost::system`, `Boost::json`

## build (linux)
```bash
mkdir build
cd build
cmake ..
make
```

After that, the `server` executable will be available in `<source-dir>/build/bin/server`

## run (linux)
The only command line parameter is `port` on which server will run
```
./server <port>
```
