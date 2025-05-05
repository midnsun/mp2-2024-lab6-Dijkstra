set(target dijkstra_test)

#file(GLOB hdrs "*.h*" "../include/*.h" "../gtest/*.h")
file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp" "../src/*.cpp")
find_library(GVC_LIBRARY "../Graphviz/lib/gvc.lib")
find_library(CGRAPH_LIBRARY "../Graphviz/lib/cgraph.lib")

link_libraries(${GVC_LIBRARY} ${CGRAPH_LIBRARY})
add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${GVC_LIBRARY} ${CGRAPH_LIBRARY} ${target} gtest)
