test_fail () {
	clean
	echo Fail 🔥
	exit 1
}

clean () {
  rm -rf ft_map.txt std_map.txt
}

cd cmake-build-debug
./ft_container_map > ft_map.txt
./std_container_map > std_map.txt

if ! diff ft_map.txt std_map.txt
then
	test_fail
fi

clean
echo Test Pass ✅