# CMakeList.txt : CMake project for Matching_Game, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("MatchingGame")

# Add source to this project's executable.
add_executable (MatchingGame "Source/MatchingGame.cpp" "Header/MatchingGame.h" "Header/Game.h" "Header/Card.h" "Header/Image.h" )

# Include the NANA library
target_include_directories(MatchingGame PUBLIC "C:\\aa\\nana\\include")
target_link_directories(MatchingGame PUBLIC "C:\\aa\\nana\\build\\bin")
target_link_directories(MatchingGame PUBLIC "C:\\aa\\nana\\extrlib\\vc2019\\jpeg-9c")

# Define compiler variable
add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
add_definitions(-DNANA_ENABLE_AUDIO)
#add_definitions(-DNANA_ENABLE_JPEG)

# Link NANA libraries
target_link_libraries(MatchingGame "nana_v142_debug_x64")
target_link_libraries(MatchingGame "libjpeg.MDd.x64")
