cmake_minimum_required( VERSION 2.6 )

add_subdirectory( Metrics     )
add_subdirectory( TestMetrics )

enable_testing()
add_test( test_levenshtein python Levenshtein/Levenshtein.py )
