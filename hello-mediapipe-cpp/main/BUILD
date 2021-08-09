load("@mediapipe//mediapipe/framework/port:build_config.bzl", "mediapipe_proto_library")

cc_binary(
    name = "hand_tracking_cpu",
    deps = [
        "@mediapipe//mediapipe/examples/desktop:demo_run_graph_main",
        ":desktop_tflite_calculators",
    ],
)

cc_library(
    name = "desktop_tflite_calculators",
    deps = [
        ":desktop_offline_calculators",
        ":my_pass_through_calculator",
        "@mediapipe//mediapipe/calculators/core:constant_side_packet_calculator",
        "@mediapipe//mediapipe/calculators/core:merge_calculator",
        "@mediapipe//mediapipe/graphs/hand_tracking/subgraphs:hand_renderer_cpu",
        "@mediapipe//mediapipe/modules/hand_landmark:hand_landmark_tracking_cpu",
    ],
)

cc_library(
    name = "desktop_offline_calculators",
    deps = [
        "@mediapipe//mediapipe/calculators/core:flow_limiter_calculator",
        "@mediapipe//mediapipe/calculators/core:gate_calculator",
        "@mediapipe//mediapipe/calculators/core:immediate_mux_calculator",
        "@mediapipe//mediapipe/calculators/core:packet_inner_join_calculator",
        "@mediapipe//mediapipe/calculators/core:previous_loopback_calculator",
        "@mediapipe//mediapipe/calculators/video:opencv_video_decoder_calculator",
        "@mediapipe//mediapipe/calculators/video:opencv_video_encoder_calculator",
    ],
)

cc_library(
    name = "my_pass_through_calculator",
    srcs = ["my_pass_through_calculator.cc"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/port:status",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
        "@mediapipe//mediapipe/framework/formats:rect_cc_proto",
        "@mediapipe//mediapipe/framework/formats:detection_cc_proto",
        ":wrapper_hand_tracking_cc_proto",
    ],
    alwayslink = 1,
)

mediapipe_proto_library(
    name = "wrapper_hand_tracking_proto",
    srcs = ["wrapper_hand_tracking.proto"],
    visibility = ["//visibility:public"],
    deps = [
      "@mediapipe//mediapipe/framework/formats:landmark_proto",
      "@mediapipe//mediapipe/framework/formats:detection_proto",
      "@mediapipe//mediapipe/framework/formats:rect_proto",
    ],
)
