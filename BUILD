#include for the test platform type def
cc_inc_library(
    name = "testplatform",
    hdrs = ["source/platform/testplatform/typedefs.h"],
    prefix = "source/platform/testplatform",
)
#public include for OS
cc_inc_library(
    name = "os",
    hdrs = glob(["source/functional/os/**/*.h"]),
    prefix = "source/functional",
    deps = [":os_impl"]
)
#private implementation of OS
cc_library(
    name = "os_impl",
    srcs = glob(include = ["source/functional/os/**/*.c",
                           "source/functional/os/**/*.h"],
                exclude = ["source/functional/os/**/test_*.c"]),
    deps = [":testplatform",":hal"],      
    includes = ["source/functional"],
)
#public inlcudes for hal independent of implementation
cc_inc_library(
    name = "hal",
    hdrs = glob(["source/functional/hal/**/*.h"]),
    prefix = "source/functional",
    deps = [":hal_testplat_impl"],      
)
#private implementation of hal for the test platform
cc_library(
    name = "hal_testplat_impl",
    srcs = glob(["source/platform/testplatform/**/*.c",
                 "source/platform/testplatform/**/*_p.h",
                 "source/functional/hal/**/*.h"] ),     
    deps = [":testplatform", ":os"],      
)
#config includes for the libraries
cc_inc_library(
    name = "libs_config",
    hdrs = glob(["source/functional/lib/**/*.h"]),
    prefix = "source/functional/lib",
    deps = [":libs_impl"],
)
#public includes for the libraries
cc_inc_library(
    name = "libs",
    hdrs = glob(["source/functional/lib/**/*.h"]),
    prefix = "source/functional/lib",
    deps = [":libs_impl"],
)
#private implementation of the libraries
cc_library(
    name = "libs_impl",
    srcs = glob(include = ["source/functional/lib/**/*.c",
                           "source/functional/lib/**/*.h"],
                exclude = ["source/functional/lib/**/test_*.c"] ),     
    deps = [":testplatform", ":hal", ":os"], 
    includes = ["source/functional/lib"]
)
#building config this might end up being the entry point for the build
cc_library(
    name = "config",
    srcs = glob(include = [ "source/config/**/*.c",
                            "source/config/**/*.h" ],
                exclude = [ "source/config/**/test_*.c" ]),
    deps = [ ":testplatform",":hal", ":libs_config" ]        
)

#building the main application
cc_binary(
    name = "main_testplatform",
    srcs = glob([   
                    "source/functional/lib/**/*.c",
                    "source/functional/lib/**/*.h",
                    "source/functional/os/**/*.h",
                    "source/functional/os/**/*.c",
            ]),
    deps = [":testplatform", ":hal", ":config"],
    includes = ["source/functional", 
                "source/config"]
)