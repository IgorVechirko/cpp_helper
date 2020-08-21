CMAKE_MINIMUM_REQUIRED( VERSION 3.8 )

project( cpp_helper VERSION 0.1.0.0 LANGUAGES CXX )

set( CPP_HELPER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.. )
set( CPP_HELPER_SRC_DIR ${CPP_HELPER_DIR}/src )

#sources
set( CPP_HELPER_SRC ${CPP_HELPER_SRC_DIR}/main.cpp
                    ${CPP_HELPER_SRC_DIR}/ClassesAndStructures.h
                    ${CPP_HELPER_SRC_DIR}/CommonInclude.h
                    ${CPP_HELPER_SRC_DIR}/DebugTools.h
                    ${CPP_HELPER_SRC_DIR}/FinalKeyWord.h
                    ${CPP_HELPER_SRC_DIR}/FunctionsAndMethodsPointers.h
                    ${CPP_HELPER_SRC_DIR}/InlineFunctions.h
                    ${CPP_HELPER_SRC_DIR}/Lambdas.h
                    ${CPP_HELPER_SRC_DIR}/MemoryAllocations.h
                    ${CPP_HELPER_SRC_DIR}/RTTIEmulation.h
                    ${CPP_HELPER_SRC_DIR}/RvalueLvalueSemantic.h
                    ${CPP_HELPER_SRC_DIR}/SmartPointers.h
                    ${CPP_HELPER_SRC_DIR}/Templates.h
                    ${CPP_HELPER_SRC_DIR}/VirtualAndOverrideKeyWords.h
                    )


add_executable( cpp_helper ${CPP_HELPER_SRC} )
include_directories( ${CPP_HELPER_SRC_DIR} )
