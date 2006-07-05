
project(kcachegrind)

set( KCACHEGRIND_VERSION "0.4.6kde")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-kcachegrind.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-kcachegrind.h )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/version.h )
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/kcachegrind.spec.cmake ${CMAKE_CURRENT_BINARY_DIR}/kcachegrind.spec )
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/kcachegrind.lsm.cmake ${CMAKE_CURRENT_BINARY_DIR}/kcachegrind.lsm )

macro_additional_clean_files( 
	${CMAKE_CURRENT_BINARY_DIR}/version.h 
	${CMAKE_CURRENT_BINARY_DIR}/kcachegrind.lsm 
	${CMAKE_CURRENT_BINARY_DIR}/kcachegrind.spec)


add_subdirectory( kcachegrind ) 
add_subdirectory( pics ) 
add_subdirectory( converters ) 




########### install files ###############





#original Makefile.am contents follow:

#SUBDIRS = kcachegrind pics converters
#
#EXTRA_DIST = \
#	AUTHORS COPYING NEWS ChangeLog INSTALL README TODO \
#	kcachegrind.lsm kcachegrind.spec version.h 
#