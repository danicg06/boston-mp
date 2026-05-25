touch tests//.timeout
CMD="valgrind --leak-check=full /home/daniel06/Documentos/MP/Prácticas/Boston4/dist/Debug/GNU-Linux/boston4  -c 1> tests//.out16 2>&1"
eval $CMD
rm tests//.timeout
