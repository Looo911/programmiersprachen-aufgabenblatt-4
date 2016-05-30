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
	REQUIRE(3 == list.size());
	REQUIRE(64 == list.front());
	REQUIRE(42 == list.back());

}

TEST_CASE("add an element with push_back", "[modifiers]")
{	

	List<int> list ;
	list.push_back (59);
	list.push_back (52);
	list.push_back (64);
	REQUIRE(3 == list.size());
	REQUIRE(64 == list.back());
	REQUIRE(59 == list.front());

}

TEST_CASE("delete first and last element with pop", "[modifiers]")
{	

	List<int> list;
	list.push_back (1);
	list.push_back (2);
	list.push_back (3);
	list.push_back (4);
	//list.pop_back();
	list.pop_front();
	list.pop_back();

	REQUIRE(2 == list.size());
	REQUIRE(2 == list.front());
	REQUIRE(3 == list.back());

	list.pop_front();
}

TEST_CASE("clear a list", "[modifiers]")
{	

	List<int> list;
	list.push_back (1);
	list.push_back (2);
	list.push_back (3);
	list.push_back (4);
	REQUIRE(list.size() == 4);


	list.clear();

	REQUIRE(list.empty() == true);

}

TEST_CASE (" should be an empty range after default construction ","[ iterators ]")
{
	List <int > list ;
	auto b = list.begin();
	auto e = list.end();
	REQUIRE (b == e);
}

TEST_CASE (" provide acces to the first element with begin ", "[ iterators ]") //kein guter Test!
{
	List<int> list ;
	list.push_front (42);
	REQUIRE (42 == *list.begin());
}


TEST_CASE ("compare two lists", "[operators]")
{
	List<int> list;
	List<int> poo;
	list.push_back (1);
	list.push_back (2);
	list.push_back (3);
	list.push_back (4);
	poo.push_back (1);
	poo.push_back (2);
	poo.push_back (3);
	poo.push_back (4);
	
	REQUIRE(list == poo);
	list.pop_front();
	REQUIRE((list == poo) == false);
}

TEST_CASE ("compare two lists of different size", "[operators]")
{
	List<int> list;
	List<int> poo;
	list.push_back (1);
	
	poo.push_back (1);
	poo.push_back (2);
	
	
	REQUIRE(list != poo);
}



TEST_CASE ("compare two lists with different ends", "[operators]")
{
	List<int> list;
	List<int> poo;
	list.push_back (1);
	list.push_back (2);
	list.push_back (3);
	list.push_back (6);
	poo.push_back (1);
	poo.push_back (2);
	poo.push_back (3);
	poo.push_back (5);
	
	REQUIRE((list == poo) == false);

}


TEST_CASE ("compare two lists with different ends with !=", "[operators]")
{
	List<int> list;
	List<int> poo;
	list.push_back (1);
	list.push_back (2);
	list.push_back (3);
	list.push_back (6);
	poo.push_back (1);
	poo.push_back (2);
	poo.push_back (3);
	poo.push_back (5);
	
	REQUIRE(list != poo);

}


TEST_CASE ("copy a list", "[operators]")
{
	List<int> list;
	
	list.push_back (1);
	list.push_back (2);
	list.push_back (3);
	list.push_back (6);
	
	List<int> poo(list);

	for (auto i = list.begin(); i != list.end(); ++i)
	{
		std::cout << "1: " << *i << "\n";
	}

	for (auto i = poo.begin(); i != poo.end(); ++i)
	{
		std::cout << "2: "<< *i << "\n";
	}
	
	REQUIRE(list == poo);

}

TEST_CASE ( " copy constructor " , " [ constructor ] " )
{
	List<int> list ;
	list.push_front (1);
	list.push_front (2);
	list.push_front (3);
	list.push_front (4);
	List<int> list2 {list};
	REQUIRE (list == list2);
}

TEST_CASE ( " copy constructor: empty list" , " [ constructor ] " )
{
	List<int> list;
	List<int> list2 {list};
	REQUIRE (list == list2);
}



int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
