if test -d ./build/; then rm -rf build/; fi
mkdir build
cd build
cmake ..
make
make test
test/json2sql/json2sql_test
