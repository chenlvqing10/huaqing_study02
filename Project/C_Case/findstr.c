#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* findstr(char* str,char* substr)
{
	int i = 0;
	int size_substr = 0;//¿¿¿¿¿¿¿
	int index_str = 0;//¿¿¿¿¿¿¿¿¿¿¿

	while (*(str +i) != '\0')//¿¿¿¿¿¿¿¿
	{
		if (*(str + i) == *(substr + size_substr))
		{
			i++;
			size_substr++;
			index_str = i - size_substr;
			continue;
		}
		i++;
	}
	if (size_substr >= 5)
		return (str + index_str);
	else
		return NULL;
}
int main()
{
	char str[100] = {0};
	char substr[50] = "hello";
	char* p;
	printf("Please input a String:");
	scanf("%s",str);

	if ((p=findstr(str, substr)) == NULL)
	{
		printf("there is not have sub string in str");
	}
	else
	{
		printf("there is have sub string in str\n");
		printf("the address is :%p",p);
	}

	return 0;
}
