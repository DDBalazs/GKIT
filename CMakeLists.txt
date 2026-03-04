cmake_minimum_required(VERSION 3.30.5)
project(CLionGraphicsKit)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(include)
link_directories(lib)

# 1. Létrehozzuk a közös grafikus könyvtárat CSAK a graphics.cpp-ből
add_library(graphics graphics.cpp)

# 2. Hozzálinkeljük az SDL-t a grafikus könyvtárhoz
target_link_libraries(graphics SDL2 SDL2.dll SDL2main SDL2_ttf SDL2_ttf.dll)

# 3. Létrehozzuk a futtatható programokat, és mindhez hozzálinkeljük a graphics könyvtárat
add_executable(hazi01 hazi1.cpp)
target_link_libraries(hazi01 graphics)

add_executable(Hoeses Hoeses.cpp)
target_link_libraries(Hoeses graphics)

add_executable(MozgoCsirke MozgoCs.cpp)
target_link_libraries(MozgoCsirke graphics)

add_executable(CsirkeKep Csirke.cpp)
target_link_libraries(CsirkeKep graphics)

# A részecskés programod:
add_executable(Reszecskerendszer reszecske.cpp)
target_link_libraries(Reszecskerendszer graphics)