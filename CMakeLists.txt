cmake_minimum_required(VERSION 3.26)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")
project(${MAIN_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(APPLE)
    add_compile_definitions(_DARWIN_C_SOURCE)
    add_compile_options(-Wno-deprecated-declarations)
endif()

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)
include(cmake/Options.cmake)
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set (WARNINGS_AS_ERRORS ON)
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.11.0
        GIT_SHALLOW    1
)
FetchContent_MakeAvailable(cpr)
FetchContent_Declare(
        simsimd
        GIT_REPOSITORY https://github.com/ashvardanian/simsimd.git
        GIT_TAG        v6.4.0
        GIT_SHALLOW    1
)
FetchContent_GetProperties(simsimd)
if(NOT simsimd_POPULATED)
    FetchContent_Populate(simsimd)
    file(COPY cmake/simsimd-patches/CMakeLists.txt DESTINATION ${simsimd_SOURCE_DIR})
endif()
 find_package(Threads REQUIRED)
set(SOURCES
    source/AI.cpp
    source/AI.h
    source/Family.cpp
    source/Family.h
        source/gameClasses/Game.cpp
        source/gameClasses/Game.h
    source/Player.cpp
    source/Player.h
        source/questionClasses/Question.cpp
        source/questionClasses/Question.h
        source/roundClasses/Round.cpp
        source/roundClasses/Round.h
        source/questionClasses/QuestionKiller.cpp
        source/questionClasses/QuestionKiller.h
        source/questionClasses/QuestionOptional.cpp
        source/questionClasses/QuestionOptional.h
        source/questionClasses/QuestionRandBonus.cpp
        source/questionClasses/QuestionRandBonus.h
        source/gameClasses/SpecialGame.cpp
        source/gameClasses/SpecialGame.h
        source/gameClasses/NormalGame.cpp
        source/gameClasses/NormalGame.h
        source/roundClasses/SpecialRound.cpp
        source/roundClasses/SpecialRound.h
        source/exceptions/FileReadException.cpp
        source/exceptions/FileReadException.h
        source/exceptions/AITimeoutException.cpp
        source/exceptions/AITimeoutException.h
        source/exceptions/OutOfRangeException.cpp
        source/exceptions/OutOfRangeException.h
        source/ScoreManager.cpp
        source/ScoreManager.h
        source/ClipArts.cpp
        source/ClipArts.h
        source/questionClasses/QuestionMath.cpp
        source/questionClasses/QuestionMath.h
        source/App.cpp
        source/App.h
        source/AIConnectionPool.cpp
        source/AIConnectionPool.h
        source/questionClasses/QuestionFactory.cpp
        source/questionClasses/QuestionFactory.h
        source/RollDice.cpp
        source/RollDice.h
        source/Config.cpp
        source/Config.h

)
add_executable(${MAIN_EXECUTABLE_NAME}
        source/main.cpp
        ${SOURCES}

)
include(cmake/CompilerFlags.cmake)
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE generated/include)

target_include_directories(
        ${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE
        ext/include/json
        ${simsimd_SOURCE_DIR}/include
        source
)

target_link_libraries(
        ${MAIN_EXECUTABLE_NAME}
        Threads::Threads
        cpr::cpr
)

install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()
include(cmake/CopyHelper.cmake)
copy_files(FILES source/questionResources/QMresources.json COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
copy_files(FILES source/questionResources/QRBresources.json COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
copy_files(FILES source/questionResources/QOresources.json COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
copy_files(FILES source/questionResources/killerQresources.json COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
copy_files(FILES source/questionResources/intrebari.json COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
copy_files(FILES tastatura.txt scripts/run_llm.sh COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
copy_files(FILES configure.json COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
