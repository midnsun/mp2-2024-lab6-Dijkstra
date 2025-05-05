set(GVC "gvc")
set(CGRAPH "cgraph")

add_library(${GVC} PUBLIC STATIC /lib/gvc.lib)
add_library(${CGRAPH} PUBLIC STATIC /lib/cgraph.lib)

target_link_libraries(${GVC} ${CGRAPH})