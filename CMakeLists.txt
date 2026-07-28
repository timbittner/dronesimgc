cmake_minimum_required(VERSION 3.21)
project(dronesimgc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Widgets Network Test)
qt_standard_project_setup()

qt_add_library(gcs_core STATIC
    src/geo.cpp
    src/mavlink_listener.cpp
    src/entity_model.cpp
    src/world_state.cpp
    src/detail_pane.cpp
    src/event_log.cpp
    src/command_sender.cpp
    src/map_view.cpp
)
target_include_directories(gcs_core PUBLIC src third_party/mavlink)
target_link_libraries(gcs_core PUBLIC Qt6::Widgets Qt6::Network)
qt_add_resources(gcs_core "assets" PREFIX "/" BASE assets FILES
    assets/sebexen/albedo.png
    assets/sebexen/map.json
)

qt_add_executable(dronesimgc src/main.cpp)
target_link_libraries(dronesimgc PRIVATE gcs_core)

enable_testing()
foreach(t geo_test decode_test)
    qt_add_executable(${t} tests/${t}.cpp)
    target_link_libraries(${t} PRIVATE gcs_core Qt6::Test)
    target_compile_definitions(${t} PRIVATE
        VECTORS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/tests/mavlink_vectors.json")
    add_test(NAME ${t} COMMAND ${t})
endforeach()
