cmake_minimum_required (VERSION 2.6)
set(PROJECTNAME SuperLoloBross)
project (${PROJECTNAME})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECTNAME} ${SOURCES})

include(FindPkgConfig)
pkg_search_module(SDL REQUIRED sdl)
pkg_search_module(SDLIMAGE REQUIRED SDL_image)
pkg_search_module(SDLMIXER REQUIRED SDL_mixer)

include_directories(${SDL_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIRS} ${SDLMIXER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL_LIBRARIES} ${SDLIMAGE_LIBRARIES} ${SDLMIXER_LIBRARIES})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

# install(FILES ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY images/ DESTINATION images)
install(DIRECTORY audio/ DESTINATION audio)
install(DIRECTORY level/ DESTINATION level)