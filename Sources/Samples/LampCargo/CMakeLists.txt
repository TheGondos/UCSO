add_library(LampCargo SHARED
LampCargo.cpp
)

target_include_directories(LampCargo PUBLIC
	${ORBITER_SOURCE_SDK_INCLUDE_DIR}
	${ORBITER_BINARY_SDK_DIR}/include
)

target_link_libraries(LampCargo
	${ORBITER_SDK_LIB}
	UCSO_API
)

set_target_properties(LampCargo
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${ORBITER_BINARY_MODULE_DIR}/UCSO
	OUTPUT_NAME LampCargo
)

install(TARGETS LampCargo
#	RUNTIME
	DESTINATION ${ORBITER_INSTALL_MODULE_DIR}/UCSO
)

add_dependencies(LampCargo
	${OrbiterTgt}
	Orbitersdk
	UCSO_API
)
