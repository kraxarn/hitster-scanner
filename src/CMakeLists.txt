add_subdirectory(qml)
add_subdirectory(entity)
add_subdirectory(model)

target_sources(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/urlresolver.cpp
)