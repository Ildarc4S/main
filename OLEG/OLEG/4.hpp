#pragma once

#include <iostream> // std::cin, std::cout, std::endl
#include <string> // std::string
#include <fstream> // std::ifstream, std::ofstream
#include <map> // std::map
#include <stdexcept> // std::out_of_range

template<typename T> void out(const T& t) { std::cout « t « std::endl; }

//-< Data >-------------------------------------------------------------------—

template<typename T> class Data
{
protected:

	typedef T value_type;
	typedef unsigned int count_type;

	Data();
	~Data();

	bool _isNull();

	value_type* _t = nullptr;
	count_type _n = 0;
};

//---------------------------------------------------------------------< Data >-
//-< Prep >-------------------------------------------------------------------—

template<typename T> class Prep : virtual private Data<T>
{
protected:

	using typename Data<T>::value_type;
	using typename Data<T>::count_type;

	typedef std::string _Key;
	typedef void (Prep::* _Value)(std::ifstream&);
	typedef const std::map<_Key, _Value> _Cmds;

	Prep();
	~Prep();

	_Cmds _cmds;

private:

	void fill_(std::ifstream& input);
	void equate_(std::ifstream& input);
};

//---------------------------------------------------------------------< Prep >-
//-< Proc >-------------------------------------------------------------------—

template<typename T> class Proc : virtual private Data<T>
{
protected:

	using typename Data<T>::value_type;
	using typename Data<T>::count_type;

	typedef std::string _Key;
	typedef void (Proc::* _Value)(std::ifstream&);
	typedef const std::map<_Key, _Value> _Cmds;

	Proc();
	~Proc();

	_Cmds _cmds;
};

//---------------------------------------------------------------------< Proc >-
//-< Post >-------------------------------------------------------------------—

template<typename T> class Post : virtual private Data<T>
{
protected:

	using typename Data<T>::value_type;
	using typename Data<T>::count_type;

	typedef std::string _Key;
	typedef void (Post::* _Value)(std::ifstream&);
	typedef const std::map<_Key, _Value> _Cmds;

	Post();
	~Post();

	_Cmds _cmds;

private:

	void write_(std::ifstream& input);
};

//---------------------------------------------------------------------< Post >-
//-< Main >-------------------------------------------------------------------—

template<typename T> class Main : private Prep<T>, private Proc<T>,
private Post<T>
{
public:

	Main(const std::string& path);
	~Main();

private:

	template<template<typename> class C>
	void invoke_(std::ifstream& input, std::string& kw);
};

template<typename T>
Main<T>::Main(const std::string& path)
{
	std::ifstream input(path);
	if (input.is_open()) {
		std::string kw; // keyword
		while (input » kw) { // operator bool()
			try {
				if (kw == "prep") { this->invoke_<Prep>(input, kw); }
				else if (kw == "proc") { this->invoke_<Proc>(input, kw); }
				else if (kw == "post") { this->invoke_<Post>(input, kw); }
				else {
					std::cout « "Unable to identify Class Alias: " « kw
						« std::endl;
				}
			}
			catch (const std::out_of_range&) {
				std::cout « "Unable to identify Method Alias: " « kw « std::endl;
			}
		}
		input.close();
	}
	else { std::cout « "Unable to open file: " « path « std::endl; }
}

template<typename T>
Main<T>::~Main() {}

template<typename T>
template<template<typename> class C>
void Main<T>::invoke_(std::ifstream& input, std::string& kw)
{
	input » kw;
	(this->*this->C<T>::_cmds.at(kw))(input);
}

//---------------------------------------------------------------------< Main >-

int main()
{
	Main<int> m("log.txt");
	return 0;
}

// UNIX: LF (line feed)
// Mac OS: CR (carriage return)
// DOS and Windows: CR + LF