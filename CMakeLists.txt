## set target project
file(GLOB APPLICATION_HEADERS
    "Application/*.hpp"
    "Application/*.h"
)

file(GLOB APPLICATION_SOURCE
    "Application/*.cpp"
)

file(GLOB COMPONENTS_HEADERS
    "Components/*.hpp"
    "Components/*.h"
)

file(GLOB COMPONENTS_SOURCE
    "Components/*.cpp"
)

file(GLOB GAME_HEADERS
    "Game/*.hpp"
    "Game/*.h"
)

file(GLOB GAME_SOURCE
    "Game/*.cpp"
)


file(GLOB MISC_HEADERS
    "Misc/*.hpp"
    "Misc/*.h"
)

file(GLOB MISC_SOURCE
    "Misc/*.cpp"
)

file(GLOB UTILITY_HEADERS
    "Utility/*.hpp"
    "Utility/*.h"
)

file(GLOB UTILITY_SOURCE
    "Utility/*.cpp"
)

file(GLOB EDITOR_HEADERS
    "Editor/*.hpp"
    "Editor/*.h"
)

file(GLOB EDITOR_SOURCE
    "Editor/*.cpp"
)

file(GLOB target_src "*.h" "*.cpp") # look for source files
file(GLOB target_shaders "shaders/*.vert" "shaders/*.frag") # look for shaders
add_executable(${subdir} 
${GAME_HEADERS} ${GAME_SOURCE} 
${APPLICATION_HEADERS} ${APPLICATION_SOURCE} 
${MISC_HEADERS} ${MISC_SOURCE} 
${RAPID_JSON} 
${COMPONENTS_HEADERS} ${COMPONENTS_SOURCE}
${UTILITY_HEADERS} ${UTILITY_SOURCE}
${EDITOR_HEADERS} ${EDITOR_SOURCE}
${target_src}
${target_shaders}

)

# list of libraries
set(libraries glad glfw imgui assimp)

if(APPLE)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OPENGL_LIBRARY OpenGL)
    find_library(COREVIDEO_LIBRARY CoreVideo)

    list(APPEND libraries
            ${OPENGL_LIBRARY}
            ${COCOA_LIBRARY}
            ${IOKIT_LIBRARY}
            ${COREVIDEO_LIBRARY}
            )
endif()




# Create sub-folders in visual studio
source_group("Header Files\\Application" FILES ${APPLICATION_HEADERS})
source_group("Source Files\\Application" FILES ${APPLICATION_SOURCE})
source_group("Header Files\\Components" FILES ${COMPONENTS_HEADERS})
source_group("Source Files\\Components" FILES ${COMPONENTS_SOURCE})
source_group("Header Files\\Game" FILES ${GAME_HEADERS})
source_group("Source Files\\Game" FILES ${GAME_SOURCE})
source_group("Header Files\\Utility" FILES ${UTILITY_HEADERS})
source_group("Source Files\\Utility" FILES ${UTILITY_SOURCE})
source_group("Header Files\\Misc" FILES ${MISC_HEADERS})
source_group("Source Files\\Misc" FILES ${MISC_SOURCE})
source_group("Header Files\\Editor" FILES ${EDITOR_HEADERS})
source_group("Source Files\\Editor" FILES ${EDITOR_SOURCE})
source_group("Header Files\\rapidjson" FILES ${RAPID_JSON})


## set link libraries
target_link_libraries(${subdir} ${libraries})

## add local source directory to include paths
target_include_directories(${subdir} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

## copy shaders folder to build folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

## copy models and textures
##file(COPY ${CMAKE_SOURCE_DIR}/common/models/car DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
##file(COPY ${CMAKE_SOURCE_DIR}/common/models/floor DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
##file(COPY ${CMAKE_SOURCE_DIR}/common/models/skybox DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

## copy again at the time the current target gets compiled
 add_custom_command(
         TARGET ${subdir} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory
         ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders
         COMMENT "Copying shaders" VERBATIM
 )