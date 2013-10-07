#ifndef MARKOV_MANAGER
#define MARKOV_MANAGER

#include <map>
#include <vector>
#include "MarkovUnit.h"

template <class T>
class MarkovManager
{
	public:
		~MarkovManager<T>();
		std::map<T, MarkovUnit<T>*> LinkMap;
		MarkovUnit<T>* Add( T base, T b, int i);
		MarkovUnit<T>* Add( T base, T b );
		std::vector<T> Build( T d );
		std::vector<T> Build( T d, int i);
		std::vector<T> Build();
		std::vector<T> Build( int i );
		MarkovUnit<T>* GetRand();
};


template <class T>
MarkovManager<T>::~MarkovManager()
{
	typename std::map<T, MarkovUnit<T>*>::iterator it;
	for(it=LinkMap.begin(); it!=LinkMap.end(); ++it)
	{
    	delete it->second;
	}
}

template <class T>
MarkovUnit<T>* MarkovManager<T>::Add( T base, T b, int i)
{
	MarkovUnit<T>* mu;
	if( !(mu=LinkMap[base]) )
		mu=LinkMap[base]=new MarkovUnit<T>(base);
	MarkovUnit<T>* mb;
	if( !(mb=LinkMap[b]) )
		mb=LinkMap[b]=new MarkovUnit<T>(b);
	return mu->Add(mb,i);
}

template <class T>
MarkovUnit<T>* MarkovManager<T>::Add( T base, T b )
{
	return Add( base, b, 1);
}

template <class T>
std::vector<T> MarkovManager<T>::Build( T d, int i )
{
	std::vector<T> results;
	MarkovUnit<T>* mu = LinkMap[d];
	while( mu && i>0 )
	{
		results->push_back(mu->data);
		mu = mu->GiveLink();
		i--;
	}
	return results;
}

template <class T>
std::vector<T> MarkovManager<T>::Build( T d )
{
	std::vector<T> results;
	MarkovUnit<T>* mu = LinkMap[d];
	while( mu )
	{
		results->push_back(mu->data);
		mu = mu->GiveLink();
	}
	return results;
}

template <class T>
std::vector<T> MarkovManager<T>::Build()
{
	std::vector<T> results;
	MarkovUnit<T>* mu = GetRand();
	while( mu )
	{
		results->push_back(mu->data);
		mu = mu->GiveLink();
	}
	return results;
}

template <class T>
std::vector<T> MarkovManager<T>::Build( int i )
{
	std::vector<T> results;
	MarkovUnit<T>* mu = GetRand();
	while( mu && i>0 )
	{
		results->push_back(mu->data);
		mu = mu->GiveLink();
		i--;
	}
	return results;
}

template <class T>
MarkovUnit<T>* MarkovManager<T>::GetRand()
{
	int num = rand()%LinkMap.size();
	typename std::map<T, MarkovUnit<T>*>::iterator it;
	for(it=LinkMap.begin(); it!=LinkMap.end(); ++it)
	{
    	num--;
    	if(num==0)
    		return it->second;
	}
}

#endif