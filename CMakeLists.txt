# CMakeList.txt : CMake project for Matching_Game, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Matching_Game")

# Add source to this project's executable.
add_executable (Matching_Game "Source/MatchingGame.cpp" "Header/MatchingGame.h" "Header/Game.h" "Header/Card.h" "Header/Image.h")

# Include the NANA library
target_include_directories(Matching_Game PUBLIC "nana\\include")

# Define compiler variable
add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
add_definitions(-DNANA_ENABLE_AUDIO)
add_definitions(-DNANA_ENABLE_JPEG)

# Link NANA libraries
target_link_libraries(Matching_Game "nana_v142_Debug_x64")

target_link_directories(Matching_Game PUBLIC "nana\\build\\bin")
