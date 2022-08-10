test_fail () {
	clean
	echo Fail 🔥
	exit 1
}

clean () {
    rm -rf stack_test
    cd tests
    rm -rf std_stack_test.cp
}

cd ..

clean

sed 's/ft::/std::/g' stack_test.cpp > std_stack_test_tmp.cpp
sed 's/#include "stack.hpp"/#include <stack>/g' std_stack_test_tmp.cpp > std_stack_test.cpp
rm -rf std_stack_test_tmp.cpp
cd ..

mkdir stack_test
cd stack_test
cmake ..
make

./ft_container_stack > ft_stack.txt
./std_container_stack > std_stack.txt

if ! diff ft_stack.txt std_stack.txt
then
	test_fail
fi

echo Test Pass ✅