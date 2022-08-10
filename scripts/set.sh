test_fail () {
	clean
	echo Fail 🔥
	exit 1
}

clean () {
  rm -rf set_test
  cd tests
  rm -rf std_set_test.cp
}

cd ..

clean

sed 's/ft::/std::/g' set_test.cpp > std_set_test_tmp.cpp
sed 's/#include "set.hpp"/#include <set>/g' std_set_test_tmp.cpp > std_set_test.cpp
rm -rf std_set_test_tmp.cpp
cd ..

mkdir set_test
cd set_test
cmake ..
make

./ft_container_set > ft_set.txt
./std_container_set > std_set.txt

if ! diff ft_set.txt std_set.txt
then
	test_fail
fi

echo Test Pass ✅