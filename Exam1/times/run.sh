#!/bin/bash
echo "___________________________________________________________"
echo "Here is the average time for files data transfer:"
gcc time_files.c -o files
chmod +x files
./files
echo "___________________________________________________________"
echo "Here is the average time for pipelines data transfer:"
gcc time_pipelines.c -o pipes
chmod +x pipes
./pipes
echo "___________________________________________________________"
echo "Here is the average time for shared memory data transfer:"
gcc time_shm.c -o shm
chmod +x shm
./shm
echo "___________________________________________________________"

