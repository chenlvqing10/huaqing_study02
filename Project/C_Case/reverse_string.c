#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//change two value from two address
void swap_string(char* str1, char* str2)
{
	char temp;
	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

//Reverse string between begin and end address
void reverse_string(char* begin, char* end, int length)
{
	for (int i = 0; i < length; i++)
	{
		end--;
		swap_string(end, begin);
		begin++;
	}
}

int main()
{
	char b[100];
	printf("Please input a String(with space):");
	scanf("%[^\n]",b);//input the string
	if(*b=='\0')
	{
		printf("The string is not null\n");
		return 0;
	}
	//call the reverse function(all string reverse)
	reverse_string(b,b+strlen(b),strlen(b)/2);
	printf("the first revesed string is:%s\n",b);

	//reverse string by space
	int count_ptr = 0;//ptr index
	int count_space= 0;//space index
	char* p = b, * q = b;//p:string end by space  q:string begin by space

	while (*p)//select all string
	{
		if ((*p == ' ')||(*(p+1) == '\0'))//when string is space or the next char is \0
		{
			if (*(p + 1) == '\0')//if the next char is \0 then made the ptr direct to \0
				p++;
			reverse_string(q,p,(count_ptr- count_space)/2);//call fun
			count_space = count_ptr;//space index set to current index
			p = b + count_space;//p ptr direct to space address
			q = p + 1;//q ptr direct to space next address to judge next char
		}
		p++;//next p ptr
		count_ptr++;//next index
	}
	//print the final reverse string
	printf("the second reverded String is: %s",b);

	return 0;
}

