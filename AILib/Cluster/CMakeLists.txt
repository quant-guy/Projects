cmake_minimum_required( VERSION 2.6 )

project( Cluster )

add_subdirectory( Cluster_2_0       )
add_subdirectory( ClusterAlgorithms )
add_subdirectory( TestCluster       )

enable_testing()
