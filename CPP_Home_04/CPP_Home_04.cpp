// CPP_Home_04.cpp  Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctype.h>

using namespace std;
typedef unsigned char byte;

char* gets()
{
	char c, *str = 0;
	int cnt = 1;
	while ((c = getchar()) != '\n')
	{
		str = (char*)realloc(str, ++cnt);
		str[cnt-2] = c;
	}
	if (str) str[cnt - 1] = 0;
	return str;
}

//Сдвигает циклически символы вправо
void rCircleMove(char * str)
{
	if (!str) return; //ы
	int len = strlen(str);
	char c = str[len - 1];	
	for (int i = len - 1; i > 0; --i)
		str[i] = str[i - 1];
	str[0] = c;
}

//Изменить порядок символов в строке на обратный
void ReverseCharOrder(char* str)
{
	int len = strlen(str);
	for (int i = 0; i < len/2; ++i)
	{
		char cbuf = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = cbuf;
	}
}

//Переставить все цифры в начало строки
void MoveDigits(char * str)
{
	int len = strlen(str), digcnt = 0;
	for (int i = 0; i < len; ++i)
	{
		if (isdigit(str[i]))
		{			
			char dig = str[i];
			for (int j = i; j > digcnt; j--)
				str[j] = str[j - 1];
			str[digcnt++] = dig;
		}
	}
}

//Удалить из строки всё, что находится в скобках
void DelFocusArea(char* str)
{
	char * p = str+1;
	bool aredeleting = false;
	while (*str++)
	{
		if (*(str-1) == '(') aredeleting = true;
		if (*str == ')') aredeleting = false;
		if (!aredeleting)
			*(p++) = *(str);		
	}
	if (p) *p = 0;
}

//создает копию первой найденной сущности от пробела до пробела
char * cpyfrstw(const char * str)
{
	char * dup = 0;
	int cnt = 1;
	bool fwordstarted = false, fwordended = false;
	while (*str && !fwordended)
	{
		if (isspace(*str))
		{
			if (fwordstarted) fwordended = true;
		}
		else
		{
			fwordstarted = true;
			dup = (char*)realloc(dup, ++cnt);
			dup[cnt - 2] = *str;
		}
		str++;
	}
	//проверка на пустую строку
	if (dup) dup[cnt - 1] = 0;
	return dup;
}

//Переставить первое слово в конец строки
void FirstWordToEnd(char *str)
{
	if (!str) return; 
	char* firstword = cpyfrstw(str), *p = str;
	//пропускаю пробелы
	while (*p == ' ')
	{		
		p++;
	}
	str = p;
	int lenfw = strlen(firstword);
	//Пропускаю первое слово и пробел за ним
	for (int i = 0; i < lenfw + 1; i++)
		p++;
	//смещаю ост. строку в начало, к пробелам
	while (*p)
		*(str++) = *(p++);
	//вставил пробел, чтобы слова не слиплись
	*(str++) = ' ';
	p = firstword;
	//вставил первое слово в конец строки
	while (*str)
		*(str++) = *(p++);
	free(firstword);
}

//Удалить из строки лишние пробелы
void EraseExtraSpaces(char* str)
{
	char * p = str;
	bool spacefound = false, firletfound = false;
	//удаляет все пробелы, пока не нашел первый символ
	 //и оставляет 1 пробел между непробелами(читай - словами)
	while (*str)
	{		
		if (isspace(*str))
			if (spacefound || !firletfound)
				str++;
			else
			{				
				*(p++) = *(str++);
				spacefound = true;
			}
		else
		{			
			firletfound = true; 
			spacefound = false;
			*(p++) = *(str++);
		}
	}
	//удаляет последний пробел в конце
	if (p) isspace(*(p-1))? *(p-1)=0 : *p = 0;
}

char** TextIn()
{
	char *s = 0, **text = 0;
	//cout << "Введите текст" << endl;
	int cnt = 1, size = 1;
	while ((s = gets()) != 0)
	{
		size += strlen(s);
		text = (char**)realloc(text, size);
		text[++cnt - 2] = s;		
	}
	if (text) text[cnt - 1] = 0;
	return text;
}


//крутая функция с лекции
void test(const char * fn, void(*f)(char *), const char * str) 
{
	char * buf = _strdup(str);
	f(buf);
	printf("%15s : \"%s\"\n", fn, str);
	printf("%15s : \"%s\"\n", "=>", buf);
	free(buf);
}

void freetext(char ** text)
{
	while (text && *text)
		free(*text++);	
}

void printtext(char **text)
{
	while (text && *text)
		puts(*text++);
}

int main()
{
	setlocale(0,"");	
	cout << "Введите текст" << endl;	
	char** text = TextIn();
	/*cout << "вывод текста" << endl;
	printtext(text);*/
	freetext(text);	
	getchar();
    return 0;
}

