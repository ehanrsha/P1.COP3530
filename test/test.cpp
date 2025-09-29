/*
#include <catch2/catch_test_macros.hpp>
#include <iostream>

// uncomment and replace the following with your own headers
#include <algorithm>
#include <functional>
#include <random>
#include <sstream>
#include <unordered_map>

#include "AVL.h"

//Ehan Shah - UF ID 188750044

using namespace std;

// referenced from https://stackoverflow.com/questions/4191089/how-to-unit-test-function-writing-to-stdout-stdcout
static std::string capture(std::function<void()> fn) {
	std::ostringstream oss;
	std::streambuf* old = std::cout.rdbuf(oss.rdbuf());  // redirect cout -> string
	fn();                                                // run the code that prints
	std::cout.rdbuf(old);                                // restore cout
	return oss.str();                                    // captured output
}

//referenced from onlineGDB example provided in the instructions for test case 5
static std::vector<std::string> split_names(const std::string& s) {
	// input looks like: "Alice, Bob, Carol\n"
	std::vector<std::string> out;
	if (s.empty()) return out;
	std::string line = s;
	if (!line.empty() && line.back() == '\n') line.pop_back();

	std::istringstream iss(line);
	std::string name;
	while (std::getline(iss, name, ',')) {
		// trim leading space
		if (!name.empty() && name.front() == ' ') name.erase(name.begin());
		out.push_back(name);
	}
	return out;
}


// test1 — Five incorrect commands (each prints "unsuccessful\n")
TEST_CASE("5 Incorrect Commands", "[test]") {
	auto discard = [](const std::function<void()>& f){ (void)capture(f); };

	SECTION("Duplicate insert of same UFID") {
		AVL t;
		discard([&]{ t.insert("Alice", 12345678); });
		std::string out = capture([&]{ t.insert("Bob", 12345678); }); // duplicate ID
		REQUIRE(out == "unsuccessful\n");
	}

	SECTION("remove on non-existent ID") {
		AVL t;
		discard([&]{ t.insert("Alice", 12345678); });
		std::string out = capture([&]{ t.remove(87654321); });
		REQUIRE(out == "unsuccessful\n");
	}

	SECTION("search by ID not found") {
		AVL t; // empty
		std::string out = capture([&]{ t.search(11112222); });
		REQUIRE(out == "unsuccessful\n");
	}

	SECTION("search by NAME not found") {
		AVL t;
		discard([&]{
			t.insert("Alice", 12345678);
			t.insert("Brian", 22345678);
		});
		std::string out = capture([&]{ t.search(std::string("Zoe")); });
		REQUIRE(out == "unsuccessful\n");
	}

	SECTION("removeInorder invalid index (out-of-range and negative)") {
		AVL t;
		// Out of range
		discard([&]{ t.insert("Alice", 12345678); t.insert("Brian", 22345678); });
		std::string out1 = capture([&]{ t.removeInorder(5); });
		REQUIRE(out1 == "unsuccessful\n");

		// Negative
		std::string out2 = capture([&]{ t.removeInorder(-1); });
		REQUIRE(out2 == "unsuccessful\n");
	}
}

//test 2
TEST_CASE("Edge cases across functions", "[edges]") {
	// 1) remove on non-existent ID -> "unsuccessful\n"
	{
		AVL t;
		(void)capture([&] {
			t.insert("A", 10000000);
		});  // ignore this "successful\n"
		std::string out = capture([&]{ t.remove(99999999); });
		REQUIRE(out == "unsuccessful\n");
	}

	// 2) removeInorder with n out of range -> "unsuccessful\n"
	{
		AVL t;
		(void)capture([&]{
			t.insert("A", 10000000);
			t.insert("B", 20000000);
		});
		std::string out = capture([&]{ t.removeInorder(5); }); // only indices 0..1 exist
		REQUIRE(out == "unsuccessful\n");
	}

	// 3) search by ID on empty tree -> "unsuccessful\n"
	{
		AVL t;
		std::string out = capture([&]{ t.search(12345678); });
		REQUIRE(out == "unsuccessful\n");
	}
}

//test3
TEST_CASE("Testing All 4 Rotation Cases") {
	auto discard = [](const std::function<void()>& f){ (void)capture(f); };

	// Expected preorder after rebalancing: root=Ethan, left=Kalie, right=Jacob
	const std::string expected = "Ethan, Kalie, Jacob\n";

	SECTION("LL rotation") {
		AVL t;
		discard([&]{
			t.insert("Jacob", 30000000);
			t.insert("Ethan", 20000000);
			t.insert("Kalie", 10000000);
		});
		std::string out = capture([&]{ t.preOrder(); });
		REQUIRE(out == expected);
	}

	SECTION("RR rotation") {
		AVL t;
		discard([&]{
			t.insert("Kalie", 10000000);
			t.insert("Ethan", 20000000);
			t.insert("Jacob", 30000000);
		});
		std::string out = capture([&]{ t.preOrder(); });
		REQUIRE(out == expected);
	}

	SECTION("LR rotation") {
		AVL t;
		discard([&]{
			t.insert("Jacob", 30000000);
			t.insert("Kalie", 10000000);
			t.insert("Ethan", 20000000);
		});
		std::string out = capture([&]{ t.preOrder(); });
		REQUIRE(out == expected);
	}

	SECTION("RL rotation") {
		AVL t;
		discard([&]{
			t.insert("Kalie", 10000000);
			t.insert("Jacob", 30000000);
			t.insert("Ethan", 20000000);
		});
		std::string out = capture([&]{ t.preOrder(); });
		REQUIRE(out == expected);
	}
}

//test4
TEST_CASE("Testing All 3 Deletion Cases (no child, one child, two children)", "[deletes]") {
    auto discard = [](const std::function<void()>& f){ (void)capture(f); };

    SECTION("Delete leaf") {
        AVL t;
        discard([&]{
            t.insert("Nathan", 50000000);
            t.insert("William", 20000000);
            t.insert("Jake",    80000000);
            t.insert("Arnold",  15000000); // leaf
            t.insert("Louis",   25000000);
            t.insert("Smith",   60000000);
            t.insert("Brian",   90000000);
            t.insert("Ethan",   22000000); // child of Louis
        });

        std::string rem = capture([&]{ t.remove(15000000); });
        REQUIRE(rem == "successful\n");

        std::string inorder = capture([&]{ t.inOrder(); });
        REQUIRE(inorder == "William, Ethan, Louis, Nathan, Smith, Jake, Brian\n");
    }

    SECTION("Delete node with one child") {
        AVL t;
        discard([&]{
            t.insert("Nathan", 50000000);
            t.insert("William", 20000000);
            t.insert("Jake",    80000000);
            t.insert("Arnold",  15000000);
            t.insert("Louis",   25000000); // one child
            t.insert("Smith",   60000000);
            t.insert("Brian",   90000000);
            t.insert("Ethan",   22000000); // child of Louis
        });

        std::string rem = capture([&]{ t.remove(25000000); });
        REQUIRE(rem == "successful\n");

        std::string inorder = capture([&]{ t.inOrder(); });
        REQUIRE(inorder == "Arnold, William, Ethan, Nathan, Smith, Jake, Brian\n");
    }

    SECTION("Delete node with two children") {
        AVL t;
        discard([&]{
            t.insert("Nathan", 50000000);  // root with two children
            t.insert("William", 20000000);
            t.insert("Jake",    80000000);
            t.insert("Arnold",  15000000);
            t.insert("Louis",   25000000);
            t.insert("Smith",   60000000);
            t.insert("Brian",   90000000);
            t.insert("Ethan",   22000000);
        });

        std::string rem = capture([&]{ t.remove(50000000); });
        REQUIRE(rem == "successful\n");

        std::string inorder = capture([&]{ t.inOrder(); });
        REQUIRE(inorder == "Arnold, William, Ethan, Louis, Smith, Jake, Brian\n");
    }
}

//test 5 - referenced from the OnlineGDB example provided by the instructions
TEST_CASE("Insert 100 Nodes", "[avl_bulk]") {
	//auto discard = [](const std::function<void()>& f){ (void)capture(f); };
	AVL t;

	// Build 100 unique 8-digit UFIDs and shuffle deterministically
	std::vector<int> ids(100);
	for (int i = 0; i < 100; ++i) ids[i] = 10000000 + i;

	std::mt19937 rng(42); // fixed seed -> deterministic test
	std::shuffle(ids.begin(), ids.end(), rng);

	// Alphabetic names pool
	const std::vector<std::string> pool = {
		"Alice","Bob","Carol","David","Eve","Frank","Grace","Hank","Ivy","Jack",
		"Kara","Liam","Mia","Noah","Olivia","Paul","Quinn","Rita","Sam","Tina"
	};
	unordered_map<int,std::string> id2name;

	// Insert all 100
	std::string outIns = capture([&]{
		for (int i = 0; i < 100; ++i) {
			int id = ids[i];
			const std::string& nm = pool[i % pool.size()];
			id2name[id] = nm;
			t.insert(nm, id);
		}
	});

	// 100 lines printed
	REQUIRE(std::count(outIns.begin(), outIns.end(), '\n') == 100);

	// Remove 10 "random"
	std::string outRem = capture([&]{
		for (int i = 0; i < 10; ++i) t.remove(ids[i]);
	});
	REQUIRE(std::count(outRem.begin(), outRem.end(), '\n') == 10);

	// Expected inorder names from remaining 90 (IDs sorted ascending)
	std::vector<int> remaining(ids.begin() + 10, ids.end());
	std::sort(remaining.begin(), remaining.end());

	std::vector<std::string> expectedNames;
	expectedNames.reserve(remaining.size());
	for (int id : remaining) expectedNames.push_back(id2name[id]);

	// Actual inorder
	std::string printed = capture([&]{ t.inOrder(); });
	std::vector<std::string> actualNames = split_names(printed);

	REQUIRE(expectedNames.size() == actualNames.size());
	REQUIRE(actualNames == expectedNames);
}
*/




