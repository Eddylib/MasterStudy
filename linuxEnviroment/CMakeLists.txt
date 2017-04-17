
MESSAGE(STATUS "Linux Enviroment Beginning...")

#add_executable(thread_linux thread.c)
#target_link_libraries(thread_linux pthread)


add_executable(apue_network_client_linux network/network_client.c )
add_executable(apue_network_server_linux network/network_server.c )

add_executable(apue_network_select_server network_select/network_select_server.c)
add_executable(apue_network_select_client network_select/network_select_client.c)

MESSAGE(STATUS "Linux Enviroment End...")
