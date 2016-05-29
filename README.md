# subprocess

License: MIT

Execute subprocesses from C++, communicate with them through
`stdin`/`stdout`/`stderr`.

Example: read from subprocess

~~~{.cpp}
utils::subprocess p{{"ls", "-l", "-a"}};
p.exec();
p.out() >> std::noskipws;
std::copy(
    std::istream_iterator<char>{p.out()},
    std::istream_iterator<char>{},
    std::ostream_iterator<char>{std::cout});
p.wait();
~~~


# Requirements

- Supported OS: Linux
- Supported Compiler: GCC 5

