//
// Created by Divium on 09/09/2023.
//
#include <catch2/catch_test_macros.hpp>
#include <dynamic_array.hpp>
#include <memory>
#include <iostream>

struct Dummy {
    inline static size_t count;
    size_t id;
    Dummy() {
        id = count++;
        //std::cout << std::format("Dummy {} created", id) << std::endl;
    }
    explicit Dummy(size_t id) {
        this->id = id;
        //std::cout << std::format("Dummy {} created", id) << std::endl;
    }
    ~Dummy() {
        //std::cout << std::format("Dummy {} DELETED", id) << std::endl;
    }
};

typedef std::shared_ptr<Dummy> spd;

TEST_CASE("Sample test", "[dyn]") {
    REQUIRE(2 == 2);
}

SCENARIO("Dynamic array must resize correctly") {
    GIVEN("120 objects inside the array") {
        dvm::DynamicArray<Dummy> dynamic_array{};
        {
            for (int i = 1; i <= 120; i++)
                dynamic_array.push_back(std::make_shared<Dummy>());

            REQUIRE(dynamic_array.size() == 120);
        }

        WHEN("Removing 11 objects") {
            for (int i = 0; i < 11; i++)
                dynamic_array.pop_back();

            THEN("Size changes") {
                REQUIRE(dynamic_array.size() == 109);
            }
        }
    }
}