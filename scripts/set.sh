test_fail () {
	clean
	echo Fail 🔥
	exit 1
}

clean () {
  rm -rf ft_set.txt std_set.txt
}

cd ../cmake-build-debug
./ft_container_set > ft_set.txt
./std_container_set > std_set.txt

if ! diff ft_set.txt std_set.txt
then
	test_fail
fi

clean
echo Test Pass ✅