test_fail () {
  clean
	echo Fail 🔥
	exit 1
}

clean () {
  rm -rf vector_test
    cd tests
    rm -rf std_vector_test.cp
}

cd ..

clean

sed 's/ft::/std::/g' vector_test.cpp > std_vector_test_tmp.cpp
sed 's/#include "vector.hpp"/#include <vector>/g' std_vector_test_tmp.cpp > std_vector_test.cpp
rm -rf std_vector_test_tmp.cpp
cd ..

mkdir vector_test
cd vector_test
cmake ..
make

./ft_container_vector > ft_vector.txt
./std_container_vector > std_vector.txt

if ! diff ft_vector.txt std_vector.txt
then
	test_fail
fi

echo Test Pass ✅