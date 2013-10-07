#pragma once
#ifndef MARKOV_UNIT
#define MARKOV_UNIT

#include <map>
#include <cstdlib>

template<class T>
class MarkovUnit
{
	public:
		T data;
		std::map<MarkovUnit<T>*,int> Links;
		int Pdenom;
		MarkovUnit( T d );
		MarkovUnit();
		MarkovUnit<T>* GiveLink();
		MarkovUnit<T>* Add( MarkovUnit<T>* d, int i );
};

template <class T>
MarkovUnit<T>::MarkovUnit( T d )
{
	data = d;
	Pdenom = 0;
}

template <class T>
MarkovUnit<T>::MarkovUnit()
{
	
}

template <class T>
MarkovUnit<T>* MarkovUnit<T>::GiveLink()
{
	if(!Pdenom)
		return (MarkovUnit<T>*)0;
	typename std::map<MarkovUnit<T>*, int>::iterator it;
	int rnum = rand()%Pdenom;
	for(it=Links.begin(); it!=Links.end(); ++it)
	{
		rnum -= it->second;
		if(rnum<1)
			return it->first;
	}
	return (MarkovUnit<T>*)0;
}

template <class T>
MarkovUnit<T>* MarkovUnit<T>::Add( MarkovUnit<T>* d, int i )
{
	typename std::map<MarkovUnit<T>*, int>::iterator it = Links.find(d);
	if( it!=Links.end() )
	{
		it->second += i;
	}
	else
	{
		Links[d] = i;
	}
	Pdenom +=i;
	return d;
}

#endif