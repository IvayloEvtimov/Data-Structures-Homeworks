#include "HashTable.h"

HashTable::HashTable(const int size):Array(size),size(size)
{
}

void HashTable::insert(const std::string& key, Horo::Data* data)
{
	int index = hashFunc(key,size);

	Array[index].push_back(data);

	if (Array[index].size() == maxChaningSize)
		rehash();
}

void HashTable::remove(const std::string& key)
{
	int index = hashFunc(key,size);

	Horo::Data* person = find(key);

	Array[index].remove(person);
}

Horo::Data*& HashTable::find(const std::string &key)
{
	int index = hashFunc(key,size);

	Horo::Data* temp = nullptr;
	
	if (Array[index].empty())
		return temp;
	else if (Array[index].front()->right != nullptr)
	{
		for (std::list<Horo::Data*>::iterator itr = Array[index].begin(); itr != Array[index].end(); ++itr)
			if ((*itr)->name == key)
				return (*itr);
		return temp;
	}
	else if (Array[index].front()->name == key)
		return Array[index].front();
	else
		return temp;	
}

int HashTable::hashFunc(const std::string &key,const int size) const
{
	int result = key.size();
	for (char ch : key)
		result += ch;

	return result % size;
}

void HashTable::rehash()
{
	std::vector<std::list<Horo::Data*>> newArray(size * 2);

	for (int count = 0; count < Array.size(); +count)
	{
		if (!Array[count].empty())
			for (std::list<Horo::Data*>::iterator itr = Array[count].begin(); itr != Array[count].end(); ++itr)
				newArray[hashFunc((*itr)->name, size * 2)].push_back((*itr));
	}

	Array = newArray;
	size *= 2;
}
