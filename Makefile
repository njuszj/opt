default:
	g++ src/main.cpp -o a.out
	./a.out

test_time:
	g++ test/currTimeTester.cpp -o a.out
	./a.out