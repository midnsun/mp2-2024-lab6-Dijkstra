set(target dijkstra_test)

#file(GLOB hdrs "*.h*" "../include/*.h" "../gtest/*.h")
file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp" "../src/*.cpp")
add_library(gvc "../Graphviz/lib/gvc.lib")
add_library(cgraph "../Graphviz/lib/cgraph.lib")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest gvc cgraph)
