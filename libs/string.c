#include <os/string.h>

int kstrlen(char *src)
{
	int i;
	for (i = 0; src[i] != '\0'; i++)
	{
	}
	return i;
}

void kmemcpy(uint8_t *dest, uint8_t *src, uint32_t len)
{
	for (; len != 0; len--)
	{
		*dest++ = *src++;
	}
}

void kmemset(void *dest, uint8_t val, uint32_t len)
{
	uint8_t *dst = (uint8_t *)dest;

	for (; len != 0; len--)
	{
		*dst++ = val;
	}
}

void kbzero(void *dest, uint32_t len)
{
	kmemset(dest, 0, len);
}

int kstrcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && (*str1++ == *str2++))
	{
	};

	if (*str1 == '\0' && *str2 == '\0')
	{
		return 0;
	}

	if (*str1 == '\0')
	{
		return -1;
	}

	return 1;
}

char *kstrcpy(char *dest, char *src)
{
	char *tmp = dest;

	while (*src)
	{
		*dest++ = *src++;
	}

	*dest = '\0';

	return tmp;
}
