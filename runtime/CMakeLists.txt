cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE RUNTIME_STATIC_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cc")
set(RUNTIME_SOURCES ${RUNTIME_STATIC_SOURCES})

###############################################################################################
## Converts every castel source file into an object file in order to link them into the library

file(GLOB_RECURSE RUNTIME_CASTEL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.ct")
foreach(CASTEL_SOURCE ${RUNTIME_CASTEL_SOURCES})
    file(RELATIVE_PATH RELATIVE_CASTEL_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}" "${CASTEL_SOURCE}")
    string(REGEX REPLACE "\\.ct$" ".o" RELATIVE_OBJ_SOURCE "${RELATIVE_CASTEL_SOURCE}")

    set(GENERATED_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/temporary/sources/${RELATIVE_OBJ_SOURCE}")
    get_filename_component(GENERATION_NAME "${GENERATED_SOURCE}" NAME_WE)
    get_filename_component(GENERATION_PATH "${GENERATED_SOURCE}" PATH)
    list(APPEND RUNTIME_SOURCES "${GENERATED_SOURCE}")

    get_property(MICROCASTEL_LOCATION TARGET microcastel PROPERTY LOCATION)
    add_custom_command(OUTPUT "${GENERATED_SOURCE}"
      COMMAND mkdir -p "${GENERATION_PATH}"
      COMMAND cat "${CASTEL_SOURCE}"
            | "${MICROCASTEL_LOCATION}" "prototypeInitializer_${GENERATION_NAME}" | llc
            | clang -x assembler -c -o "${GENERATED_SOURCE}" -
      DEPENDS "${MICROCASTEL_LOCATION}" "${CASTEL_SOURCE}")
endforeach(CASTEL_SOURCE)

###############################################################
## Copies every header file into the build's /include directory

file(GLOB_RECURSE RUNTIME_CPP_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.hh" "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.def")
foreach(CPP_HEADER ${RUNTIME_CPP_HEADERS})
    file(RELATIVE_PATH RELATIVE_CPP_HEADER "${CMAKE_CURRENT_SOURCE_DIR}" "${CPP_HEADER}")

    set(COPIED_HEADER "${CMAKE_BINARY_DIR}/${RELATIVE_CPP_HEADER}")
    get_filename_component(COPY_PATH "${COPIED_HEADER}" PATH)
    list(APPEND RUNTIME_SOURCES "${COPIED_HEADER}")

    add_custom_command(OUTPUT "${COPIED_HEADER}"
        COMMAND mkdir -p "${COPY_PATH}"
        COMMAND cp "${CPP_HEADER}" "${COPIED_HEADER}"
        DEPENDS "${CPP_HEADER}")
endforeach(CPP_HEADER)

############################
## Final library description

add_library(CastelRuntime STATIC ${RUNTIME_HEADERS} ${RUNTIME_SOURCES})
add_dependencies(CastelRuntime CastelParse CastelCompile microcastel)
