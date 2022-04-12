#include <iostream>
#include <string>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <stdexcept>

struct Pass
{
	template <typename... Ts>
	Pass(const Ts &...) {}
};

template <typename... Ts>
void out(const Ts &...ts)
{
	Pass{ (std::cout « ts « ' ', 1)... };
}

template <typename... Ts>
class Database
{
public:
	static constexpr std::size_t N = sizeof...(Ts);

	typedef std::string Arg;
	template <typename T>
	using ConvFunc = T(*)(const Arg&);

	Database(const char(&signs)[N], const ConvFunc<Ts>... convFuncs);
	~Database();

	void set(const Arg& name, const Arg& value);
	void out(const Arg& name) const noexcept(false);

	bool exists(const Arg& name) const;

private:
	std::string signs_;
	std::tuple<ConvFunc<Ts>...> convFuncs_;

	struct Unit_
	{
		void* data = nullptr;
		std::type_index index = typeid(void);
		void release(const Database* const db) const;
	};

	std::unordered_map<Arg, Unit_> library_;

	template <typename T>
	void set_(const Arg& name, const T& value);

	template <const std::size_t I = 0, class Func, class Cond>
	typename std::enable_if<I == Database<Ts...>::N, void>::type
		forEachConvFunc_(const Func& func, const Cond& cond) const {}

	template <const std::size_t I = 0, class Func, class Cond>
	typename std::enable_if < I<Database<Ts...>::N, void>::type
		forEachConvFunc_(const Func& func, const Cond& cond) const
	{
		auto cf = std::get<I>(this->convFuncs_);
		if (cond(cf))
		{
			func(cf);
		}
		else
		{
			this->forEachConvFunc_<I + 1>(func, cond);
		}
	}
};

template <typename... Ts>
Database<Ts...>::Database(const char(&signs)[N], const ConvFunc<Ts>... convFuncs) : signs_(signs, N), convFuncs_(convFuncs...) {}

template <typename... Ts>
Database<Ts...>::~Database()
{
	for (const auto& i : this->library_)
	{
		i.second.release(this);
	}
}

template <typename... Ts>
void Database<Ts...>::set(const Arg& name, const Arg& value)
{
	const char sign = value.back();
	Arg::const_iterator sign_ci = this->signs_.cbegin();
	auto func = [&](auto cf) -> void
	{ this->set_(name, (*cf)(value)); };
	auto cond = [&](auto) -> bool
	{ return (sign == *(sign_ci++)); };
	this->forEachConvFunc_(func, cond);
}

template <typename... Ts>
void Database<Ts...>::out(const Arg& name) const noexcept(false)
{
	if (this->exists(name))
	{
		const Unit_& u = this->library_.at(name);
		auto func = [&]<typename D>(ConvFunc<D>) -> void
		{
			std::cout «* (D*)u.data « std::endl;
		};
		auto cond = [&]<typename D>(ConvFunc<D>) -> bool
		{
			return (u.index == typeid(D));
		};
		this->forEachConvFunc_(func, cond);
	}
	else
	{
		throw std::out_of_range("The name " + name + "does not exist.");
	}
}

template <typename... Ts>
bool Database<Ts...>::exists(const Arg& name) const
{
	try
	{
		this->library_.at(name);
	}
	catch (const Unit_&)
	{
		return true;
	}
	catch (const std::out_of_range&)
	{
		return false;
	}
}

template <typename... Ts>
void Database<Ts...>::Unit_::release(const Database* const db) const
{
	auto func = [this]<typename D>(ConvFunc<D>) -> void
	{
		delete (D*)this->data;
	};
	auto cond = [this]<typename D>(ConvFunc<D>) -> bool
	{
		return (this->index == typeid(D));
	};
	db->forEachConvFunc_(func, cond);
}

template <typename... Ts>
template <typename T>
void Database<Ts...>::set_(const Arg& name, const T& value)
{
	const std::type_index ind = typeid(T);
	if (!this->exists(name))
	{
		this->library_.insert({ name, Unit_{new T(value), ind} });
	}
	else
	{
		Unit_& u = this->library_[name];
		if (u.index == ind)
		{
			*(T*)u.data = value;
		}
		else
		{
			u.release(this);
			u.data = new T(value);
			u.index = ind;
		}
	}
}

int stoi(const std::string& line)
{
	return std::stoi(std::string(line.begin(), —line.end()));
}

float stof(const std::string& line)
{
	return std::stof(std::string(line.begin(), —line.end()));
}

std::string stos(const std::string& line)
{
	return std::string(++line.begin(), —line.end());
}

int main()
{
	// set x 42i
	// set y 12.3f

	// set l "hello, world!"
	Database<int, float, std::string> db({ 'i', 'f', '"' }, &::stoi, &::stof, &::stos);
	db.set("x", "42i");
	db.out("x");
	system("pause");
	return 0;
}