#pragma once

int recognize_other_types(const char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '<' || ch == '>' || ch == '=' || ch ==
	       '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == ',' || ch == ' ' || ch == ':' ||
	       ch == ';' || ch == '\n' ? 1 : 0;
}