#include "../header/Utils.hpp"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <regex>

using namespace std;

namespace Manage
{

	int Utils::str_length(char *s)
	{
		if (!s)
			return 0;
		int len = 0;
		while (*(s + len) != '\0')
			len++;
		return len;
	}

	char *Utils::to_upper_last_name(char *s)
	{
		if (!s)
			return s;
		int i = 0;
		while (*(s + i) != '\0')
		{
			*(s + i) = toupper(*(s + i));
			i++;
		}
		return s;
	}

	char *Utils::to_upper_first_name(char *s)
	{
		if (!s)
			return s;
		*s = toupper(*s);
		return s;
	}

	char *Utils::str_to_char(string s, char *ptr)
	{
		int n = s.length();
		ptr = (char *)malloc((n + 1) * sizeof(char));
		for (int i = 0; i < n; i++)
		{
			*(ptr + i) = s[i];
		}
		*(ptr + n) = '\0';
		return ptr;
	}

	char *Utils::to_char(std::string s, char *ptr)
	{
		int n = s.length();
		ptr = (char *)malloc((n + 1) * sizeof(char));
		for (int i = 0; i < n; i++)
		{
			*(ptr + i) = s[i];
		}
		*(ptr + n) = '\0';
		return ptr;
	}

	int Utils::str_to_int(std::string s)
	{
		int len = s.size();
		if (len == 0)
			return 0;
		try
		{
			return stoi(s.c_str());
		}
		catch (...)
		{
			Logger::log(2, "Erreur de conversion de string vers int " + s);
		}
		return -1;
	}

	int Utils::validate_sexe(string s)
	{
		cout << s << endl;
		int x = s.compare("F");
		if (x == 0)
			return 0;
		x = s.compare("M");
		if (x == 0)
			return 0;
		return 1;
	}

	int Utils::validate_statut(string s)
	{
		int x = s.compare("Marie");
		if (x == 0)
			return 0;
		x = s.compare("Mariee");
		if (x == 0)
			return 0;
		x = s.compare("Celibataire");
		if (x == 0)
			return 0;
		x = s.compare("Veuf");
		if (x == 0)
			return 0;
		x = s.compare("Veuve");
		if (x == 0)
			return 0;
		x = s.compare("Pasce");
		if (x == 0)
			return 0;
		x = s.compare("Pascee");
		if (x == 0)
			return 0;
		x = s.compare("Autres");
		if (x == 0)
			return 0;
		return 1;
	}

	int Utils::validate_entreprise_name(string s)
	{
		int x = s.compare("SARL");
		if (x == 0)
			return 0;
		x = s.compare("SA");
		if (x == 0)
			return 0;
		x = s.compare("SAS");
		if (x == 0)
			return 0;
		x = s.compare("EURL");
		if (x == 0)
			return 0;
		return 1;
	}

	bool Utils::validate_first_last_name(string s)
	{
		int n = s.length();
		if (n == 0 || n > 30)
			return false;
		return true;
	}

	bool Utils::validate_entreprise(string s)
	{
		int n = s.length();
		if (n == 0 || n > 50)
			return false;
		return true;
	}

	bool Utils::check_email(string email)
	{
		const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
		return regex_match(email, pattern);
	}
}
