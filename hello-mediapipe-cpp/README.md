# hello-mediapipe-cpp

This example is based on [MediaPipe Hands](https://google.github.io/mediapipe/solutions/hands.html) and broadcast hand tracking data over UDP on port 8080.

## BUILD

```bash
GLOG_logtostderr=1 bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 main:hand_tracking_cpu
GLOG_logtostderr=1 bazel-bin/main/hand_tracking_cpu \
--calculator_graph_config_file=hand_tracking_desktop_live.pbtxt
```
