#include <CCSDSParser/Interface.h>
#include <iostream>


int main()
{
	Interface<std::vector<uint8_t>> interface;
	std::vector<uint8_t> vecInput;
	size_t lenVecInput = 0;
	std::vector<uint8_t> result;
	while(1)
	{
		std::cout << "For add CCSDS package, write '1'" << std::endl << "For add stop, write '2'" << std::endl << "For get result, write '3'" << std::endl;
		int command;
		std::cin >> command;
		switch(command)
		{
			case 1:
				std::cout << "Write len data: ";
				std::cin >> lenVecInput;
				std::cout << "Write package: ";
				for(size_t i = 0; i < lenVecInput; i++)
					{
						uint8_t c;
						std::cin >> c;
						vecInput.push_back(c);
					}
				interface.addVCDU(vecInput, lenVecInput);
				vecInput.clear();
				break;
			case 2:
				return 0;
			case 3:
				for(auto i: interface.getCCSDSPackages())
					{
						for(auto j: i)
							std::cout << j;
						std::cout << std::endl <<std::endl;
					}
			default:
				std::cout << "error command" << std::endl;
				break;
		}
	}
	return 0;
}
