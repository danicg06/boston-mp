touch tests//.timeout
CMD="valgrind --leak-check=full /home/daniel06/Documentos/MP/Prácticas/Boston2/dist/Debug/GNU-Linux/boston2  data/input09.b2in  tests/output/output.crm 1> tests//.out11 2>&1"
eval $CMD
rm tests//.timeout
