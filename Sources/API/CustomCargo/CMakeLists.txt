add_library(CustomCargo SHARED
    CustomCargo.cpp
)

target_include_directories(CustomCargo PUBLIC
	${ORBITER_SOURCE_SDK_INCLUDE_DIR}
)

target_link_libraries(CustomCargo
	${ORBITER_SDK_LIB}
)

set_target_properties(CustomCargo
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${ORBITER_BINARY_MODULE_DIR}/UCSO
	OUTPUT_NAME CustomCargo
)

install(TARGETS CustomCargo
#	RUNTIME
	DESTINATION ${ORBITER_INSTALL_MODULE_DIR}/UCSO
)

#install(FILES CustomCargo.h
#	DESTINATION ${ORBITER_BINARY_SDK_DIR}/UCSO
#)
add_custom_command(TARGET CustomCargo
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${ORBITER_BINARY_SDK_DIR}/include/UCSO
#	COMMAND ${CMAKE_COMMAND} -E make_directory ${ORBITER_BINARY_SDK_DIR}/lib/Lua
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/CustomCargo.h ${ORBITER_BINARY_SDK_DIR}/include/UCSO
#	COMMAND ${CMAKE_COMMAND} -E copy ${LUAINTERPRETER_LIB} ${ORBITER_BINARY_SDK_DIR}/lib/Lua/
)

