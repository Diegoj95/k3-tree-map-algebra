FILE(REMOVE_RECURSE
  "CMakeFiles/clean-test"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/clean-test.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
