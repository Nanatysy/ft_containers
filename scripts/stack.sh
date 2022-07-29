test_fail () {
	clean
	echo Fail 🔥
	exit 1
}

clean () {
  rm -rf ft_stack.txt std_stack.txt
}

cd cmake-build-debug
./ft_container_stack > ft_stack.txt
./std_container_stack > std_stack.txt

if ! diff ft_stack.txt std_stack.txt
then
	test_fail
fi

clean
echo Test Pass ✅