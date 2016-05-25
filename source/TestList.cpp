#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Lists.hpp"



TEST_CASE("test empty list", "[modifiers]")
{	

	List <int> list;
	REQUIRE (list.size()==0);
	REQUIRE (list.empty() == true);

}


TEST_CASE("add an element with push_front", "[modifiers]")
{	

	List<int> list ;
	list.push_front (42);
	list.push_front (52);
	list.push_front (64);
	REQUIRE(64 == list.front());
	REQUIRE(42 == list.back());

}

TEST_CASE("add an element with push_back", "[modifiers]")
{	

	List<int> list ;
	list.push_back (59);
	list.push_back (52);
	list.push_back (64);
	REQUIRE(64 == list.back());
	REQUIRE(59 == list.front());

}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
