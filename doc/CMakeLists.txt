set(DOXYFILE_LATEX "OFF")
set(DOXYFILE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/library/include/")

include(UseDoxygen)

get_target_property(LOC_EI EIToolkit LOCATION)

get_target_property(LOC_EI_CSHARP eitoolkit_csharp LOCATION)
get_property(LOC_EI_CSHARP_NET TARGET eitoolkit_csharp_net PROPERTY _assembly)
file(TO_CMAKE_PATH "${LOC_EI_CSHARP_NET}" LOC_EI_CSHARP_NET)

string(REGEX REPLACE "\\$\\\(Configuration\\\)" "\${BUILD_TYPE}" LOC_EI ${LOC_EI})
string(REGEX REPLACE "\\$\\\(Configuration\\\)" "\${BUILD_TYPE}" LOC_EI_CSHARP ${LOC_EI_CSHARP})

if(WIN32 AND ENABLE_CSHARP)
	install(FILES ${LOC_EI} DESTINATION doc/examples/csharp-vc10/)
	install(FILES ${LOC_EI_CSHARP} DESTINATION doc/examples/csharp-vc10/)
	install(FILES ${LOC_EI_CSHARP_NET} DESTINATION doc/examples/csharp-vc10/)
endif()

get_target_property(LOC_EI_JAVA eitoolkit_java LOCATION)
get_property(LOC_EI_JAVA_JAR TARGET eitoolkit_java_jni PROPERTY JAR_FILE)

string(REGEX REPLACE "\\$\\\(Configuration\\\)" "\${BUILD_TYPE}" LOC_EI_JAVA ${LOC_EI_JAVA})

if(ENABLE_JAVA)
	if(WIN32)
		install(FILES ${LOC_EI} DESTINATION doc/examples/java-idea/)
	endif()
	install(FILES ${LOC_EI_JAVA} DESTINATION doc/examples/java-idea/)
	install(FILES ${LOC_EI_JAVA_JAR} DESTINATION doc/examples/java-idea/)
endif()

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc DESTINATION .)

install(DIRECTORY "examples" DESTINATION doc)
