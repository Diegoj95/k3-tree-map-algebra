FILE(REMOVE_RECURSE
  "CMakeFiles/compile-test"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/compile-test.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
