test_fail () {
	clean
	echo Fail 🔥
	exit 1
}

clean () {
    rm -rf map_test
    cd tests
    rm -rf std_map_test.cp
}


cd ..

clean

sed 's/ft::/std::/g' map_test.cpp > std_map_test_tmp.cpp
sed 's/#include "map.hpp"/#include <map>/g' std_map_test_tmp.cpp > std_map_test.cpp
rm -rf std_map_test_tmp.cpp
cd ..

mkdir map_test
cd map_test
cmake ..
make

./ft_container_map > ft_map.txt
./std_container_map > std_map.txt

if ! diff ft_map.txt std_map.txt
then
	test_fail
fi

echo Test Pass ✅