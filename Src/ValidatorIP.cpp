#include "ValidatorIP.h"
#include <sstream>
#include <string.h>
	bool PNet::Validator::isValidPart(const std::string& address) 
    {
		size_t countdigit = address.size();
		if (countdigit > 3) { return false; }
		for (int i = 0; i < countdigit; i++)
		{
			if ((address[i] >= '0' && address[i] <= '9') == false) { return false; }
		}
		if (address.find('0') == 0 && countdigit > 1) { std::cerr << "index out of range!" << std::endl; }
		std::stringstream strStream{ address };
		int bufferNumber = 0;
		strStream >> bufferNumber;
		return (bufferNumber >= 0 && bufferNumber <= 255);
    }

    int PNet::Validator::isValidIp (const std::string& address) 
    {
		int dots = 0;
		size_t lenghIPaddr = address.length();
		try
		{
			if (lenghIPaddr == 0 || typeid(address).name() != typeid(std::string).name())
				throw 0;
		}
		catch (int exe)
		{
			std::cerr << "Lenght of Ipaddress is wrong || ipaddress != std::string " << exe << std::endl;
		}
		int counter = 0;
		for (int i = 0; i < lenghIPaddr; i++)
			if (address[i] == '.') { counter++; }
		if (counter != 3) { std::cerr << "counter !=3 " << std::endl;  }
		//buffer token  for strtok_s ,otherwise i could use strtok,but my compiler trhow error
		char* token;
		const char* convertedIp = address.c_str();
		char* ptrIp = strtok_r(const_cast<char*>(convertedIp), ".", &token);
		while (ptrIp)
		{
			if (Validator::isValidPart(ptrIp))
			{
				ptrIp = strtok_r(nullptr, ".", &token);
				if (ptrIp != nullptr)
				{
					++dots;
				}
			}
			else
			{
				break;
			}
		}
		if (dots != 3) { return 0; }
		return 1;
	}

