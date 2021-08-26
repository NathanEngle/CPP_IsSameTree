/*
Nathan Engle
8/25/2021
Program Description: Implements binary tree data structure. Within the data structure is a function called bool isSameTree(Tree *) that takes an argument of a tree.  It returns true if the argument is the equivalent tree. Structure is ignored
*/

#pragma once
#include <stdexcept>
#include <string>


class NotFoundException : public std::runtime_error
{
public:
	NotFoundException(const std::string& message = "")
		: std::runtime_error("Not Found Exception: " + message)
	{
	}
};