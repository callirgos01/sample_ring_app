cc_inc_library(
    name = "testplatform",
    hdrs = ["source/platform/testplatform/typedefs.h"],
    prefix = "source/platform/testplatform",
    
)
cc_inc_library(
    name = "hal",
    hdrs = glob(["source/functional/hal/**/*.h"]),
    prefix = "source/functional/hal"
)

cc_library(
    name = "config",
    srcs = glob(["source/config/**/*.c",
                "source/config/**/*.h",
                "source/functional/**/*.h"]),
    deps = [":testplatform",":hal"],
    includes = ["source/functional/lib",
                "source/functional/lib/**/src",]            
)


cc_binary(
    name = "main_testplatform",
    srcs = glob([   
                    "source/functional/lib/**/*.c",
                    "source/functional/os/**/*.h",
            ]),
    deps = [":testplatform", ":hal", ":config"],
    includes = ["source/functional", 
                "source/config"]
)