#ifndef UTIL_H
#define UTIL_H

#include "common_define.h"
#include <string>

std::string translateError(int aError);

template <typename T>
class Singleton
{
public:
	typedef T ObjectType;
	static ObjectType *instance()
	{
		static ObjectType obj;
		object_creator.do_nothing();
		return &obj;
	}

private:
	struct ObjectCreator
	{
		ObjectCreator()
		{
			Singleton<T>::instance();
		}

		inline void do_nothing() const {}
	};

	static ObjectCreator object_creator;
};

template <typename T>
typename Singleton<T>::ObjectCreator Singleton<T>::object_creator;

#endif // UTIL_H
