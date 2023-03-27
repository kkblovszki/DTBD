file(REMOVE_RECURSE
  "../../../build/lib/libns3.38-wave-debug.pdb"
  "../../../build/lib/libns3.38-wave-debug.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/libwave.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
