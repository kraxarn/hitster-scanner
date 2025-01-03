include(FetchContent)

FetchContent_Declare(android_openssl
	DOWNLOAD_EXTRACT_TIMESTAMP true
	URL https://github.com/KDAB/android_openssl/archive/refs/heads/master.zip
)

FetchContent_MakeAvailable(android_openssl)
include(${android_openssl_SOURCE_DIR}/android_openssl.cmake)