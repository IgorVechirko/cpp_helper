CMAKE_MINIMUM_REQUIRED( VERSION 3.8 )

project( cpp_helper VERSION 0.1.0.0 LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set( CPP_HELPER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.. )
set( CPP_HELPER_SRC_DIR ${CPP_HELPER_DIR}/src )

#static lib
set( STATIC_LIB_SRC ${CPP_HELPER_SRC_DIR}/StaticLib.cpp
					${CPP_HELPER_SRC_DIR}/StaticLib.h
					)

add_library( static_lib STATIC ${STATIC_LIB_SRC} )

target_include_directories( static_lib PUBLIC ${CPP_HELPER_SRC_DIR} )
target_include_directories( static_lib PRIVATE ${CPP_HELPER_SRC_DIR} )

#dynamic lib
set( DYNAMIC_LIB_SRC ${CPP_HELPER_SRC_DIR}/DynamicLib.cpp
					 ${CPP_HELPER_SRC_DIR}/DynamicLib.h
					 )

add_library( dynamic_lib SHARED ${DYNAMIC_LIB_SRC} )

target_include_directories( dynamic_lib PUBLIC ${CPP_HELPER_SRC_DIR} )
target_include_directories( dynamic_lib PRIVATE ${CPP_HELPER_SRC_DIR} )	
target_compile_definitions( dynamic_lib PRIVATE DYNAMIC_LIB_EXPORT )

#sources

source_group( examples\\extern_key_word FILES ${CPP_HELPER_SRC_DIR}/ExternKeyWordCU1.cpp
											  ${CPP_HELPER_SRC_DIR}/ExternKeyWordCU2.cpp
											  ${CPP_HELPER_SRC_DIR}/ExternKeyWord.h
											  )

source_group( examples FILES ${CPP_HELPER_SRC_DIR}/main.cpp
							 ${CPP_HELPER_SRC_DIR}/ClassesAndStructures.h
							 ${CPP_HELPER_SRC_DIR}/CommonInclude.h
							 ${CPP_HELPER_SRC_DIR}/DebugTools.h
						 	 ${CPP_HELPER_SRC_DIR}/FinalKeyWord.h
						 	 ${CPP_HELPER_SRC_DIR}/FucnctionsAndMethodsPointers.h
						 	 ${CPP_HELPER_SRC_DIR}/InlineFunctions.h
						 	 ${CPP_HELPER_SRC_DIR}/Lambdas.h
						 	 ${CPP_HELPER_SRC_DIR}/MemoryAllocations.h
						 	 ${CPP_HELPER_SRC_DIR}/RTTIEmulation.h
						 	 ${CPP_HELPER_SRC_DIR}/RvalueLvalueSemantic.h
							 ${CPP_HELPER_SRC_DIR}/SmartPointers.h
							 ${CPP_HELPER_SRC_DIR}/Templates.h
							 ${CPP_HELPER_SRC_DIR}/VirtualAndOverrideKeyWords.h
							 ${CPP_HELPER_SRC_DIR}/StaticLibUsing.h
							 ${CPP_HELPER_SRC_DIR}/DynamicLibUsing.h
							 ${CPP_HELPER_SRC_DIR}/ExplicitKeyWord.h
							 ${CPP_HELPER_SRC_DIR}/MutableKeyWord.h
							 ${CPP_HELPER_SRC_DIR}/ValotileRegisterKeyWords.h
							 ${CPP_HELPER_SRC_DIR}/ParallelProgramming.h
							 ${CPP_HELPER_SRC_DIR}/NumericLimits.h
							 ${CPP_HELPER_SRC_DIR}/MinMaxFuncs.h
							 ${CPP_HELPER_SRC_DIR}/Ratio.h
							 ${CPP_HELPER_SRC_DIR}/Chrono.h
							 ${CPP_HELPER_SRC_DIR}/Random.h
							 )
 
set( CPP_HELPER_SRC ${CPP_HELPER_SRC_DIR}/main.cpp
                    ${CPP_HELPER_SRC_DIR}/ClassesAndStructures.h
                    ${CPP_HELPER_SRC_DIR}/CommonInclude.h
                    ${CPP_HELPER_SRC_DIR}/DebugTools.h
                    ${CPP_HELPER_SRC_DIR}/FinalKeyWord.h
                    ${CPP_HELPER_SRC_DIR}/FucnctionsAndMethodsPointers.h
                    ${CPP_HELPER_SRC_DIR}/InlineFunctions.h
                    ${CPP_HELPER_SRC_DIR}/Lambdas.h
                    ${CPP_HELPER_SRC_DIR}/MemoryAllocations.h
                    ${CPP_HELPER_SRC_DIR}/RTTIEmulation.h
                    ${CPP_HELPER_SRC_DIR}/RvalueLvalueSemantic.h
                    ${CPP_HELPER_SRC_DIR}/SmartPointers.h
                    ${CPP_HELPER_SRC_DIR}/Templates.h
                    ${CPP_HELPER_SRC_DIR}/VirtualAndOverrideKeyWords.h
					${CPP_HELPER_SRC_DIR}/StaticLibUsing.h
					${CPP_HELPER_SRC_DIR}/DynamicLibUsing.h
					${CPP_HELPER_SRC_DIR}/ExplicitKeyWord.h
					${CPP_HELPER_SRC_DIR}/MutableKeyWord.h
					${CPP_HELPER_SRC_DIR}/ValotileRegisterKeyWords.h
					${CPP_HELPER_SRC_DIR}/ExternKeyWordCU1.cpp
					${CPP_HELPER_SRC_DIR}/ExternKeyWordCU2.cpp
					${CPP_HELPER_SRC_DIR}/ExternKeyWord.h
					${CPP_HELPER_SRC_DIR}/ParallelProgramming.h
					${CPP_HELPER_SRC_DIR}/NumericLimits.h
					${CPP_HELPER_SRC_DIR}/MinMaxFuncs.h
					${CPP_HELPER_SRC_DIR}/Ratio.h
					${CPP_HELPER_SRC_DIR}/Chrono.h
					${CPP_HELPER_SRC_DIR}/Random.h
                    )


add_executable( cpp_helper ${CPP_HELPER_SRC} )
include_directories( ${CPP_HELPER_SRC_DIR} )
target_link_libraries( cpp_helper static_lib dynamic_lib )
