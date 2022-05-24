add_subdirectory(Sources/API)
add_subdirectory(Sources/API/CustomCargo)
add_subdirectory(Sources/Cargo)
add_subdirectory(Sources/Samples)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Orbiter/Config
    DESTINATION ${ORBITER_INSTALL_ROOT_DIR}/
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Orbiter/Meshes
    DESTINATION ${ORBITER_INSTALL_ROOT_DIR}/
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Orbiter/Scenarios
    DESTINATION ${ORBITER_INSTALL_ROOT_DIR}/
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Orbiter/Textures
    DESTINATION ${ORBITER_INSTALL_ROOT_DIR}/
)
