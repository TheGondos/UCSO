add_library(XR2_Platform SHARED
XR2_Platform.cpp
)

target_include_directories(XR2_Platform PUBLIC
	${ORBITER_SOURCE_SDK_INCLUDE_DIR}
    ${ORBITER_BINARY_SDK_DIR}/include
    ${ORBITER_BINARY_SDK_DIR}/XRSound
    ../../../../XRVessels/XRVessels/framework/framework
)

target_link_libraries(XR2_Platform
	${ORBITER_SDK_LIB}
    XRSound_dll
)

set_target_properties(XR2_Platform
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${ORBITER_BINARY_MODULE_DIR}/UCSO
	OUTPUT_NAME XR2_Platform
)

install(TARGETS XR2_Platform
#	RUNTIME
	DESTINATION ${ORBITER_INSTALL_MODULE_DIR}/UCSO
)

add_dependencies(XR2_Platform
	${OrbiterTgt}
	Orbitersdk
	UCSO_API
)
