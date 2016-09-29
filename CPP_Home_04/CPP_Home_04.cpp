// CPP_Home_04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctype.h>

using namespace std;



char* gets()
{
	char c, *str = 0;
	int cnt = 1;
	while ((c = getchar()) != '\n')
	{
		str = (char*)realloc(str, ++cnt);
		str[cnt-2] = c;
	}
	if (cnt != 1)  str[cnt - 1] = 0;
	return str;
}

char** TextIn()
{
	char *s = 0, **text = 0;
	cout << "¬ведите текст" << endl;
	int cnt = 1, size = 1;
	while ((s = gets()) != 0)
	{
		size += strlen(s);
		text = (char**)realloc(text, size);
		text[++cnt - 2] = s;
	}
	if (*text) text[cnt - 1] = 0;
	return text;
}

int main()
{
	setlocale(0,"");
	
	
	
	getchar();
    return 0;
}

