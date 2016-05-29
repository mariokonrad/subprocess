#include "subprocess.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("single", "")
{
	utils::subprocess p{{"ls", "-a", "subprocess.hpp"}};

	std::ostringstream os;

	p.exec();
	p.out() >> std::noskipws;
	std::copy(std::istream_iterator<char>{p.out()}, std::istream_iterator<char>{},
		std::ostream_iterator<char>{os});
	p.wait();

	REQUIRE("subprocess.hpp\n" == os.str());
}

TEST_CASE("single_repeated_execution_failure", "")
{
	utils::subprocess p{{"ls", "-a", "subprocess.hpp"}};

	std::ostringstream os;

	p.exec();
	REQUIRE_THROWS(p.exec());

	p.out() >> std::noskipws;
	std::copy(std::istream_iterator<char>{p.out()}, std::istream_iterator<char>{},
		std::ostream_iterator<char>{os});
	p.wait();

	REQUIRE("subprocess.hpp\n" == os.str());
}

TEST_CASE("single_repeated_execution", "")
{
	utils::subprocess p{{"ls", "-a", "subprocess.hpp"}};

	std::ostringstream os0;
	p.exec();
	p.out() >> std::noskipws;
	std::copy(std::istream_iterator<char>{p.out()}, std::istream_iterator<char>{},
		std::ostream_iterator<char>{os0});
	p.wait();
	REQUIRE("subprocess.hpp\n" == os0.str());

	std::ostringstream os1;
	p.exec();
	p.out() >> std::noskipws;
	std::copy(std::istream_iterator<char>{p.out()}, std::istream_iterator<char>{},
		std::ostream_iterator<char>{os1});
	p.wait();
	REQUIRE("subprocess.hpp\n" == os1.str());
}

TEST_CASE("two_subprocesses_exec", "")
{
	utils::subprocess p0{{"cat"}};
	utils::subprocess p1{{"sort", "-r"}};

	p0.exec(p1.exec());

	p0.in() << "a"
			<< "\n"
			<< "b"
			<< "\n"
			<< "c"
			<< "\n";
	p0.close_in();

	p0.out() >> std::noskipws;
	std::copy(std::istream_iterator<char>{p0.out()}, std::istream_iterator<char>{},
		std::ostream_iterator<char>{p1.in()});

	std::ostringstream os;
	p1.out() >> std::noskipws;
	std::copy(std::istream_iterator<char>{p1.out()}, std::istream_iterator<char>{},
		std::ostream_iterator<char>{os});
	p1.wait();

	REQUIRE("c\nb\na\n" == os.str());
}

TEST_CASE("two_subprocesses_stream", "")
{
	utils::subprocess p0{{"cat"}};
	utils::subprocess p1{{"sort", "-r"}};

	p0 >> p1;

	p0.in() << "a"
			<< "\n"
			<< "b"
			<< "\n"
			<< "c"
			<< "\n";
	p0.close_in();

	p0.out() >> std::noskipws;
	std::copy(std::istream_iterator<char>{p0.out()}, std::istream_iterator<char>{},
		std::ostream_iterator<char>{p1.in()});

	std::ostringstream os;
	p1.out() >> std::noskipws;
	std::copy(std::istream_iterator<char>{p1.out()}, std::istream_iterator<char>{},
		std::ostream_iterator<char>{os});
	p1.wait();

	REQUIRE("c\nb\na\n" == os.str());
}

TEST_CASE("two_subprocesses_function_operator", "")
{
	utils::subprocess p0{{"cat"}};
	utils::subprocess p1{{"sort", "-r"}};

	p0(p1());

	p0.in() << "a"
			<< "\n"
			<< "b"
			<< "\n"
			<< "c"
			<< "\n";
	p0.close_in();

	p0.out() >> std::noskipws;
	std::copy(std::istream_iterator<char>{p0.out()}, std::istream_iterator<char>{},
		std::ostream_iterator<char>{p1.in()});

	std::ostringstream os;
	p1.out() >> std::noskipws;
	std::copy(std::istream_iterator<char>{p1.out()}, std::istream_iterator<char>{},
		std::ostream_iterator<char>{os});
	p1.wait();

	REQUIRE("c\nb\na\n" == os.str());
}
