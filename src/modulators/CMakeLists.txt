add_library(modulators
    clipper.cc
    dry_wet.cc
    ring_mod.cc
)

target_link_libraries(modulators
    unit-utils
)