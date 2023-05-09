#include "BitcoinExchange.hpp"

int  main(int argc, char **argv)
{
		if (argc != 2)
		{
			std::cout << FILEOPEN_ERR << std::endl;
			exit (EXIT_FAILURE);
		}
		
		BitcoinExchange exchange(argv[1], "data.csv");
		exchange.execute();
	
		return 0;
}