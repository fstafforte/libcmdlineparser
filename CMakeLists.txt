cmake_minimum_required (VERSION 2.8.12.2)


set (TARGETBASENAME "cmdlineparser")

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  project (libcmdlineparser_d)
  set(LIBTARGETNAME ${TARGETBASENAME}_d)
else()
  project (libcmdlineparser)
  set(LIBTARGETNAME ${TARGETBASENAME})
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")


# version number

set(libcmdlineparser_VERSION_MAJOR 1)
set(libcmdlineparser_VERSION_MINOR 0)


set(LIBSRCDIR source) 
set(EXAMPLESRCDIR examples)

file(GLOB LIBSRCS ${LIBSRCDIR}/*.cpp)

foreach(s IN ITEMS ${LIBSRCS})
  file(RELATIVE_PATH s ${CMAKE_CURRENT_SOURCE_DIR} ${s})
  list (APPEND LIBSRCFILES ${s})
endforeach(s)

file(GLOB EXAMPLESRCS ${EXAMPLESRCDIR}/*.cpp)

foreach(s IN ITEMS ${EXAMPLESRCS})
  file(RELATIVE_PATH s ${CMAKE_CURRENT_SOURCE_DIR} ${s})
  list (APPEND EXAMPLESRCFILES ${s})
endforeach(s)


if (${LIBFMT} STREQUAL "STATIC")
set (BUILDTYPE static)
else()
set (BUILDTYPE shared)
endif(${LIBFMT} STREQUAL "STATIC")

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY dist/${BUILDTYPE})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY dist/${BUILDTYPE})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY dist/${BUILDTYPE})


add_library (${LIBTARGETNAME} ${LIBFMT} ${LIBSRCFILES})

add_executable(test_${BUILDTYPE}_${LIBTARGETNAME} ${EXAMPLESRCFILES})
target_link_libraries(test_${BUILDTYPE}_${LIBTARGETNAME} ${LIBTARGETNAME})


include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Werror")
  message (STATUS "CMAKE_CXX_FLAGS:" ${CMAKE_CXX_FLAGS})
endif()
 

install(TARGETS ${LIBTARGETNAME} test_${BUILDTYPE}_${LIBTARGETNAME}
        RUNTIME DESTINATION lib${TARGETBASENAME}/example
        LIBRARY DESTINATION lib${TARGETBASENAME}/lib
        ARCHIVE DESTINATION lib${TARGETBASENAME}/lib/static)

install(DIRECTORY include/ DESTINATION lib${TARGETBASENAME}/include)
install(DIRECTORY docs/html DESTINATION lib${TARGETBASENAME}/docs)


