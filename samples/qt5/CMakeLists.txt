add_definitions(-DTUCANODEBUG)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TUCANO_BINARY_DIR}/qt5)

# Tip: you can comment out the examples you don't want to compile.
add_subdirectory(simpleTexture)
add_subdirectory(simpleFbo)
add_subdirectory(phongViewer)
add_subdirectory(rendering)
add_subdirectory(parallaxMapping)
add_subdirectory(simpleTesselation)
add_subdirectory(terrainTesselation)




