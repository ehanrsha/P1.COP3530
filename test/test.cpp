#include <catch2/catch_test_macros.hpp>
#include <iostream>

// uncomment and replace the following with your own headers
#include <algorithm>

#include "AVL.h"

//Ehan Shah - UF ID 188750044

using namespace std;

// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
TEST_CASE("Example Test Name - Change me!", "[flag]"){
	// instantiate any class members that you need to test here
	int one = 1;

	// anything that evaluates to false in a REQUIRE block will result in a failing test 
	REQUIRE(one == 1); // fix me!

	// all REQUIRE blocks must evaluate to true for the whole test to pass
	REQUIRE(false); // also fix me!
}

TEST_CASE("Test 2", "[flag]"){
	// you can also use "sections" to share setup code between tests, for example:
	int one = 1;

	SECTION("num is 2") {
		int num = one + 1;
		REQUIRE(num == 2);
	};

	SECTION("num is 3") {
		int num = one + 2;
		REQUIRE(num == 3);
	};

	// each section runs the setup code independently to ensure that they don't affect each other
}

// you must write 5 unique, meaningful tests for credit on the testing portion of this project!

// the provided test from the template is below.

TEST_CASE("Example BST Insert", "[flag]"){
	/*
		MyAVLTree tree;   // Create a Tree object
		tree.insert(3);
		tree.insert(2);
		tree.insert(1);
		std::vector<int> actualOutput = tree.inorder();
		std::vector<int> expectedOutput = {1, 2, 3};
		REQUIRE(expectedOutput.size() == actualOutput.size());
		REQUIRE(actualOutput == expectedOutput);
	*/
}

//these are my test cases but the code in my AVL tree function has not been implemented yet, so these tests will currently fail.
TEST_CASE("5 Incorrect Commands", "[flag]") {
	AVL tree;
	REQUIRE(tree.insert("A11y", 3474423) == false);
	REQUIRE(tree.insert("bigbest.3", 94850959) == false);
	REQUIRE(tree.insert("heyboy.3.4", 01) == false);
	REQUIRE(tree.insert("welcomehelow34", 33) == false);
	REQUIRE(tree.insert("SERIus-sd8d", 25652369) == false);
}

//this case works, but since the functions have not been implemented an empty vector is pushed back, which causes the test to work but fail.
TEST_CASE("Insert Command and 4 Rotations", "[flag]") {
	AVL t;
	std::vector<std::pair<std::string, int>> data3;
	data3.push_back(std::make_pair("Ethan", 20000000));
	data3.push_back(std::make_pair("Kalie", 10000000));
	data3.push_back(std::make_pair("Jacob", 30000000));

	//LL
	t.insert("Jacob", 30000000);
	t.insert("Ethan", 20000000);
	t.insert("Kalie", 10000000);
	REQUIRE(t.preorder() == data3);

	//RR
	AVL t2;
	t2.insert("Kalie", 10000000);
	t2.insert("Ethan", 20000000);
	t2.insert("Jacob", 30000000);

	REQUIRE(t2.preorder() == data3);

	//LR
	AVL t3;
	t3.insert("Jacob", 30000000);
	t3.insert("Kalie", 10000000);
	t3.insert("Ethan", 20000000);

	REQUIRE(t3.preorder() == data3);

	//RL
	AVL t4;
	t4.insert("Kalie", 10000000);
	t4.insert("Jacob", 30000000);
	t4.insert("Ethan", 20000000);

	REQUIRE(t4.preorder() == data3);
}

//used the setup example provided, with alterations for current code
TEST_CASE("Insert 100 Nodes", "[flag]") {
	AVL inputTree;
	std::vector<std::pair<std::string, int>> expectedOutput, actualOutput;
	std::vector<int> input;

	for(int i = 0; i < 110; i++)
	{
		int randomInput = rand();
		if (i < 10) {
			input.push_back(randomInput);
		}

		expectedOutput.emplace_back("Name", randomInput);
		inputTree.insert("Name", randomInput);
	}

	//remove 10 nodes
	for (int i = 0; i < 10; i++) {
		inputTree.remove(input[i]);
		expectedOutput.erase(expectedOutput.begin());
	}

	actualOutput = inputTree.inorder();
	REQUIRE(expectedOutput.size() == actualOutput.size());
	std::sort(expectedOutput.begin(), expectedOutput.end());
	REQUIRE(expectedOutput == actualOutput);
}



