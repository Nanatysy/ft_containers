test_fail () {
  clean
	echo Fail 🔥
	exit 1
}

clean () {
  rm -rf ft_vector.txt std_vector.txt
}

cd ../cmake-build-debug
./ft_container_vector > ft_vector.txt
./std_container_vector > std_vector.txt

if ! diff ft_vector.txt std_vector.txt
then
	test_fail
fi

clean
echo Test Pass ✅