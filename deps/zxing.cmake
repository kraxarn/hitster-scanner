include(FetchContent)

FetchContent_Declare(zxing-cpp
	GIT_REPOSITORY https://github.com/zxing-cpp/zxing-cpp.git
	GIT_TAG v2.2.1
)

message(STATUS "Downloading: zxing-cpp")
FetchContent_MakeAvailable(zxing-cpp)