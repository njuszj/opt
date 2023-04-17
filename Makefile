default:
	g++ src/main.cpp -o a.out
	./a.out

test_time:
	g++ test/currTimeTester.cpp -o a.out
	./a.out
test_print:
	g++ src/utils/printer.cpp test/printTester.cpp -o a.out
	./a.out