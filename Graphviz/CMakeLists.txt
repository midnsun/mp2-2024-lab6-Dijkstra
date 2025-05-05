set(GVC "gvc")
set(CGRAPH "cgraph")

add_library(${GVC} STATIC "/lib/gvc.lib")
add_library(${CGRAPH} STATIC "/lib/cgraph.lib")

target_link_libraries(${GVC} ${CGRAPH})