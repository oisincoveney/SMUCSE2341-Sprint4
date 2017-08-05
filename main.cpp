#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <output.h>
using namespace std;

int runCatchTests(int argc, char* const argv[])
{
    return Catch::Session().run(argc, argv);
    return 0;
}


int main(int argc, char* argv[])
{

    if(argc != 5)
        runCatchTests(argc, argv);
    else
    {
        Output o(argv[2], argv[3], argv[4]);
        o.print();
    }
    return 0;
}
