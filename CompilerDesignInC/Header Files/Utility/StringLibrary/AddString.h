#pragma once

/**
 * \brief a function to check whether the character is of other type(for e.g. should not come with keywords or identifiers)
 * \param ch character for checking other types of characters that should not allow with alphabets
 * \return if the character is of other type, returns 1, else 0
 */
inline int recognize_other_types(const char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '<' || ch == '>' || ch == '=' || ch ==
	       '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == ',' || ch == ' ' || ch == ':' ||
	       ch == ';' || ch == '\n' ? 1 : 0;
}

inline int index_of(const char arr[], const int n, const char element)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == element)
			return i;
	}

	return -1;
}