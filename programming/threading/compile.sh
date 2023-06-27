#!/bin/bash
gcc -o tcp_clients tcp_clients.c
gcc -o tcp_server_threads tcp_server_threads.c -lpthread