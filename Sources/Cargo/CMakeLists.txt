add_library(Cargo SHARED
Cargo.cpp
)

target_include_directories(Cargo PUBLIC
	${ORBITER_SOURCE_SDK_INCLUDE_DIR}
)

target_link_libraries(Cargo
	${ORBITER_SDK_LIB}
)

set_target_properties(Cargo
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${ORBITER_BINARY_MODULE_DIR}/UCSO
	OUTPUT_NAME Cargo
)

install(TARGETS Cargo
#	RUNTIME
	DESTINATION ${ORBITER_INSTALL_MODULE_DIR}/UCSO
)
