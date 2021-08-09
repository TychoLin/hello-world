# hello-openFrameworks

This example is based on [madelinegannon](https://github.com/madelinegannon)'s [example-mediapipe-udp](https://github.com/madelinegannon/example-mediapipe-udp).

![hand tracking gif](assets/hello-my-hand.gif)

## Build

```bash
projectGenerator -o"/path/to/openFrameworks/" -a"ofxNetwork" hello-openFrameworks
protoc --proto_path=. --cpp_out=./libs PROTO_FILE

make
make run
```

Your libs directory should look like this:

```bash
libs
└── mediapipe
    └── framework
        └── formats
            ├── annotation
            │   ├── rasterization.pb.cc
            │   └── rasterization.pb.h
            ├── detection.pb.cc
            ├── detection.pb.h
            ├── landmark.pb.cc
            ├── landmark.pb.h
            ├── location_data.pb.cc
            ├── location_data.pb.h
            ├── rect.pb.cc
            ├── rect.pb.h
            ├── wrapper_hand_tracking.pb.cc
            └── wrapper_hand_tracking.pb.h
```
