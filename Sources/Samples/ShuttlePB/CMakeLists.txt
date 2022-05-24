add_library(UCSOShuttlePB SHARED
ShuttlePB.cpp
)

target_include_directories(UCSOShuttlePB PUBLIC
	${ORBITER_SOURCE_SDK_INCLUDE_DIR}
    ${ORBITER_BINARY_SDK_DIR}/include
)

target_link_libraries(UCSOShuttlePB
	${ORBITER_SDK_LIB}
    UCSO_API
)

set_target_properties(UCSOShuttlePB
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${ORBITER_BINARY_MODULE_DIR}/UCSO
	OUTPUT_NAME ShuttlePB
)

install(TARGETS UCSOShuttlePB
#	RUNTIME
	DESTINATION ${ORBITER_INSTALL_MODULE_DIR}/UCSO
)

add_dependencies(UCSOShuttlePB
	${OrbiterTgt}
	Orbitersdk
	UCSO_API
)
