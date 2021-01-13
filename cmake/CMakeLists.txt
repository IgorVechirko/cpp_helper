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
set( Allocator ${CPP_HELPER_SRC_DIR}/Allocator.h ${CPP_HELPER_SRC_DIR}/Allocator.cpp )
set( FreeListAllocator ${CPP_HELPER_SRC_DIR}/FreeListAllocator.h ${CPP_HELPER_SRC_DIR}/FreeListAllocator.cpp )


source_group( allocator FILES 
	${Allocator}
	${FreeListAllocator}
)

source_group( examples\\extern_key_word FILES ${CPP_HELPER_SRC_DIR}/ExternKeyWordCU1.cpp
											  ${CPP_HELPER_SRC_DIR}/ExternKeyWordCU2.cpp
											  ${CPP_HELPER_SRC_DIR}/ExternKeyWord.h
											  )

source_group( examples\\main_stl FILES 
				${CPP_HELPER_SRC_DIR}/Containers.h
				${CPP_HELPER_SRC_DIR}/Iterators.h
				${CPP_HELPER_SRC_DIR}/Algorithms.h
				)

source_group( main FILES ${CPP_HELPER_SRC_DIR}/main.cpp )



set( Namespaces 
	${CPP_HELPER_SRC_DIR}/Namespaces.h
	${CPP_HELPER_SRC_DIR}/NamespacesTU1.cpp
	${CPP_HELPER_SRC_DIR}/NamespacesTU2.cpp)
)

set( Atributes 
	${CPP_HELPER_SRC_DIR}/Attributes.h
	${CPP_HELPER_SRC_DIR}/Attributes.cpp
)

set( ClassesAndStructures
	${CPP_HELPER_SRC_DIR}/ClassesAndStructures.h
	${CPP_HELPER_SRC_DIR}/ClassesAndStructures.cpp
)

set( FinalKeyWord
	${CPP_HELPER_SRC_DIR}/FinalKeyWord.h
)

set( FunctionsAndMethodsPointers 
	${CPP_HELPER_SRC_DIR}/FucnctionsAndMethodsPointers.h
)

set( InlineFunctions 
	${CPP_HELPER_SRC_DIR}/InlineFunctions.h
)

set( Lambdas 
	${CPP_HELPER_SRC_DIR}/Lambdas.h
)

set( RvalueLvalueSemantic
	${CPP_HELPER_SRC_DIR}/RvalueLvalueSemantic.h
	${CPP_HELPER_SRC_DIR}/RvalueLvalueSemantic.cpp
)

set( SmartPointers 
	${CPP_HELPER_SRC_DIR}/SmartPointers.h
	${CPP_HELPER_SRC_DIR}/SmartPointers.cpp
)

set( Templates
	${CPP_HELPER_SRC_DIR}/Templates.h
)

set( VirtualAndOverrideKeyWords 
	${CPP_HELPER_SRC_DIR}/VirtualAndOverrideKeyWords.h
)

set( ExplicitKeyWord 
	${CPP_HELPER_SRC_DIR}/ExplicitKeyWord.h
)

set( MutableKeyWord 
	${CPP_HELPER_SRC_DIR}/MutableKeyWord.h
)

set( ValotileRegisterKeyWords 
	${CPP_HELPER_SRC_DIR}/ValotileRegisterKeyWords.h
)

set( ParallelProgramming 
	${CPP_HELPER_SRC_DIR}/ParallelProgramming.h
	${CPP_HELPER_SRC_DIR}/ParallelProgramming.cpp
	${CPP_HELPER_SRC_DIR}/RecursiveLock.h
	${CPP_HELPER_SRC_DIR}/RecursiveLockResolve.h
	${CPP_HELPER_SRC_DIR}/ConditionVariables.h
	${CPP_HELPER_SRC_DIR}/ConditionVariables.cpp
)

set( NumericLimits
	${CPP_HELPER_SRC_DIR}/NumericLimits.h
)

set( MinMaxFuncs
	${CPP_HELPER_SRC_DIR}/MinMaxFuncs.h
	${CPP_HELPER_SRC_DIR}/MinMaxFuncs.cpp
)

set( Chrono
	${CPP_HELPER_SRC_DIR}/Chrono.h
	${CPP_HELPER_SRC_DIR}/Chrono.cpp
)

set( Random 
	${CPP_HELPER_SRC_DIR}/Random.h
	${CPP_HELPER_SRC_DIR}/Random.cpp
)

set( OperatorsOverrides
	${CPP_HELPER_SRC_DIR}/OperatorsOverrides.h
	${CPP_HELPER_SRC_DIR}/OperatorsOverrides.cpp
)

set( Exeptions
	${CPP_HELPER_SRC_DIR}/Exceptions.h
)

source_group( examples\\atributes FILES ${Atributes} )
source_group( examples\\classes_and_structures FILES ${ClassesAndStructures} )
source_group( examples\\final_key_word FILES ${FinalKeyWord} )
source_group( examples\\functions_and_methods_pointers FILES ${FunctionsAndMethodsPointers} )
source_group( examples\\inline_functions FILES ${InlineFunctions} )
source_group( examples\\lambdas FILES ${Lambdas} )
source_group( examples\\rvalue_lvalue_semantic FILES ${RvalueLvalueSemantic} )
source_group( examples\\smart_pointers FILES ${SmartPointers} )
source_group( examples\\templates FILES ${Templates} )
source_group( examples\\virtural_and_override_key_words FILES ${VirtualAndOverrideKeyWords} )
source_group( examples\\explicit_key_word FILES ${ExplicitKeyWord} )
source_group( examples\\mutable_key_word FILES ${MutableKeyWord} )
source_group( examples\\valotile_register_key_words FILES ${ValotileRegisterKeyWords} )
source_group( examples\\parallel_programming FILES ${ParallelProgramming} )
source_group( examples\\numeric_limits FILES ${NumericLimits} )
source_group( examples\\min_max_funcs FILES ${MinMaxFuncs} )
source_group( examples\\chrono FILES ${Chrono} )
source_group( examples\\random FILES ${Random} )
source_group( examples\\operators_overrides FILES ${OperatorsOverrides} )
source_group( examples\\exeptions FILES ${Exeptions} )
source_group( examples\\namespaces FILES ${Namespaces} )

source_group( examples FILES 
			${CPP_HELPER_SRC_DIR}/CommonInclude.h
			${CPP_HELPER_SRC_DIR}/DebugTools.h
			${CPP_HELPER_SRC_DIR}/MemoryAllocations.h
			${CPP_HELPER_SRC_DIR}/RTTIEmulation.h
			${CPP_HELPER_SRC_DIR}/StaticLibUsing.h
			${CPP_HELPER_SRC_DIR}/DynamicLibUsing.h
			)
 
set( CPP_HELPER_SRC 
	${Atributes}
	${ClassesAndStructures}
	${FinalKeyWord}
	${FunctionsAndMethodsPointers}
	${InlineFunctions}
	${Lambdas}
	${RvalueLvalueSemantic}
	${SmartPointers}
	${Templates}
	${VirtualAndOverrideKeyWords}
	${ExplicitKeyWord}
	${MutableKeyWord}
	${ValotileRegisterKeyWords}
	${ParallelProgramming}
	${NumericLimits}
	${MinMaxFuncs}
	${Chrono}
	${Random}
	${Exeptions}
	${OperatorsOverrides}
	${Namespaces}
	${Namespaces}
	${CPP_HELPER_SRC_DIR}/main.cpp
    ${CPP_HELPER_SRC_DIR}/CommonInclude.h
    ${CPP_HELPER_SRC_DIR}/DebugTools.h
    ${CPP_HELPER_SRC_DIR}/MemoryAllocations.h
    ${CPP_HELPER_SRC_DIR}/RTTIEmulation.h
	${CPP_HELPER_SRC_DIR}/StaticLibUsing.h
	${CPP_HELPER_SRC_DIR}/DynamicLibUsing.h
	${CPP_HELPER_SRC_DIR}/ExternKeyWordCU1.cpp
	${CPP_HELPER_SRC_DIR}/ExternKeyWordCU2.cpp
	${CPP_HELPER_SRC_DIR}/ExternKeyWord.h
	${CPP_HELPER_SRC_DIR}/Ratio.h
	${CPP_HELPER_SRC_DIR}/Containers.h
	${CPP_HELPER_SRC_DIR}/Iterators.h
	${CPP_HELPER_SRC_DIR}/Algorithms.h
	${CPP_HELPER_SRC_DIR}/Namespaces.h
	${CPP_HELPER_SRC_DIR}/NamespacesTU1.cpp
	${CPP_HELPER_SRC_DIR}/NamespacesTU2.cpp
	${Allocator}
	${FreeListAllocator}
    )


add_executable( cpp_helper ${CPP_HELPER_SRC} )
include_directories( ${CPP_HELPER_SRC_DIR} )
target_link_libraries( cpp_helper static_lib dynamic_lib )


find_library( PTHREAD_LIB pthread )

if ( PTHREAD_LIB )
	target_link_libraries( pthread )
endif()
