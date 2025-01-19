file(REMOVE_RECURSE
  "libgiflib.a"
  "libgiflib.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/giflib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
