#include<bits/stdc++.h>
using namespace std;


bool prime(int n)
{
    if(n%2==0)
        return false;
    else
    {
        for(int i=3; i*i<=n;i++)
        {
            if(n%i==0) return false;
        }
        return true;
    }
}

class Hashing
{
    int hashSize;
    vector<list<pair<string, int> > > hashTable;
    int hash1(string key);
    int hash2(string key);
    int auxHash(string key);

    int collisionMethod;
    ///collisionMethod==1 -> chaining method
    ///collisionMethod==2 -> double hashing
    ///collisionMethod==3 -> custom probing

    int hashF;
    ///hashF==1 -> hash1()
    ///hashF==2 -> hash2()

    int no_collision;
    int no_probe;

public:
    Hashing(int n, int collM, int hashf);
    void hash_insert(string key, int value);
    int hash_search(string key);
    void hash_delete(string key);
    void printHashTable();
    void printData();
};


Hashing::Hashing(int n, int collM, int hashf)
{
    if(n%2==0) n=n+1;
    while(1)
    {
        if(prime(n)==true)
            break;
        else
            n=n+2;
    }

    hashSize = n;
    collisionMethod = collM;
    hashF = hashf;
    no_collision=0;
    no_probe = 0;

    hashTable.resize(n);

}

int Hashing::hash1(string key)
{
    long long int hashIdx = 0;
    int max_prime = 1e9 + 9;
    for(int i=0; i<key.length(); i++)
    {
        hashIdx = ((hashIdx*37) + key[i])% max_prime;

    }
    return int(hashIdx%hashSize);
}

int Hashing::hash2(string key) ///polynomial rolling hash function
{
    long long int hashIdx = 0;

    int primeP = 31;
    long long int powerP = 1;
    int max_prime = 1e9 + 9;

    for(int i=0; i<key.length(); i++)
    {
        hashIdx = (hashIdx+ (key[i]-'a'+1)*powerP)%max_prime;
        powerP = (powerP*primeP)%max_prime;
    }
    return int(hashIdx%hashSize);
}


int Hashing::auxHash(string key)
{
    long long int hashIdx = 0;
    for(int i=0; i<key.length(); i++)
    {
        hashIdx = hashIdx + key[i];
    }
    return int(hashIdx%hashSize);
}

void Hashing::hash_insert(string key, int value)
{
    if(hashF == 1)
    {
        if(collisionMethod == 1)
        {
            int hashIdx = hash1(key);
            int listSize = hashTable[hashIdx].size();
            if(listSize>=1)
            {
                no_collision++;
            }
            pair<string, int> tempPair;
            tempPair = make_pair(key, value);
            hashTable[hashIdx].push_back(tempPair);
        }
        else if(collisionMethod == 2)
        {

            for(int i=0; i<=hashSize; i++)
            {
                int hashIdx = (hash1(key) + i*auxHash(key))%hashSize;
                int listSize = hashTable[hashIdx].size();
                if(listSize>=1)
                {
                    no_collision++;
                }
                else
                {
                    pair<string, int> tempPair;
                    tempPair = make_pair(key, value);
                    hashTable[hashIdx].push_back(tempPair);
                    break;
                }
            }
        }
        else if(collisionMethod == 3)
        {
            for(int i=0; i<=hashSize; i++)
            {
                int hashIdx = (hash1(key) + (4*i*auxHash(key)) + 7*i*i) % hashSize;
                int listSize = hashTable[hashIdx].size();
                if(listSize>=1)
                {
                    no_collision++;
                }
                else
                {
                    pair<string, int> tempPair;
                    tempPair = make_pair(key, value);
                    hashTable[hashIdx].push_back(tempPair);
                    break;
                }
            }
        }
    }
    else if(hashF == 2)
    {
        if(collisionMethod == 1)
        {
            int hashIdx = hash2(key);
            int listSize = hashTable[hashIdx].size();
            if(listSize>=1)
            {
                no_collision++;
            }
            pair<string, int> tempPair;
            tempPair = make_pair(key, value);
            hashTable[hashIdx].push_back(tempPair);
        }
        else if(collisionMethod == 2)
        {

            for(int i=0; i<=hashSize; i++)
            {
                int hashIdx = (hash2(key) + i*auxHash(key))%hashSize;
                int listSize = hashTable[hashIdx].size();
                if(listSize>=1)
                {
                    no_collision++;
                }
                else
                {
                    pair<string, int> tempPair;
                    tempPair = make_pair(key, value);
                    hashTable[hashIdx].push_back(tempPair);
                    break;
                }
            }
        }
        else if(collisionMethod == 3)
        {
            for(int i=0; i<=hashSize; i++)
            {
                int hashIdx = (hash2(key) + (4*i*auxHash(key)) + 7*i*i) % hashSize;
                int listSize = hashTable[hashIdx].size();
                if(listSize>=1)
                {
                    no_collision++;
                }
                else
                {
                    pair<string, int> tempPair;
                    tempPair = make_pair(key, value);
                    hashTable[hashIdx].push_back(tempPair);
                    break;
                }
            }
        }
    }
}

int Hashing::hash_search(string key)
{
    if(hashF==1)
    {
        if(collisionMethod==1)
        {
            int hashIdx = hash1(key);
            list<pair<string, int> > temp = hashTable[hashIdx];
            list<pair<string, int> >::iterator it;
            for(it=temp.begin(); it!=temp.end(); it++)
            {
                no_probe++;
                pair<string, int> t= *it;
                if(t.first==key)
                    return t.second;
            }
        }
        else if(collisionMethod==2)
        {
            for(int i=0; i<=hashSize; i++)
            {
                no_probe++;
                int hashIdx = (hash1(key) + i*auxHash(key))%hashSize;
                int listSize = hashTable[hashIdx].size();
                if(listSize!=0)
                {
                    list<pair<string, int> >::iterator it;
                    it = hashTable[hashIdx].begin();
                    if((*it).first==key)
                    {
                        return (*it).second;
                    }
                }
            }
        }
        else if(collisionMethod==3)
        {
            for(int i=0; i<=hashSize; i++)
            {
                no_probe++;
                int hashIdx = (hash1(key) + (4*i*auxHash(key)) + 7*i*i) % hashSize;
                int listSize = hashTable[hashIdx].size();
                if(listSize!=0)
                {
                    list<pair<string, int> >::iterator it;
                    it = hashTable[hashIdx].begin();
                    if((*it).first==key)
                    {
                        return (*it).second;
                    }
                }
            }
        }
    }
    else if(hashF==2)
    {
        if(collisionMethod==1)
        {
            int hashIdx = hash2(key);
            list<pair<string, int> > temp = hashTable[hashIdx];
            list<pair<string, int> >::iterator it;
            for(it=temp.begin(); it!=temp.end(); it++)
            {
                no_probe++;
                pair<string, int> t= *it;
                if(t.first==key)
                    return t.second;
            }
        }
        else if(collisionMethod==2)
        {
            for(int i=0; i<=hashSize; i++)
            {
                no_probe++;
                int hashIdx = (hash2(key) + i*auxHash(key))%hashSize;
                int listSize = hashTable[hashIdx].size();
                if(listSize!=0)
                {
                    list<pair<string, int> >::iterator it;
                    it = hashTable[hashIdx].begin();
                    if((*it).first==key)
                    {
                        return (*it).second;
                    }
                }
            }
        }
        else if(collisionMethod==3)
        {
            for(int i=0; i<=hashSize; i++)
            {
                no_probe++;
                int hashIdx = (hash2(key) + (4*i*auxHash(key)) + 7*i*i) % hashSize;
                int listSize = hashTable[hashIdx].size();
                if(listSize!=0)
                {
                    list<pair<string, int> >::iterator it;
                    it = hashTable[hashIdx].begin();
                    if((*it).first==key)
                    {
                        return (*it).second;
                    }
                }
            }
        }
    }
}

void Hashing::hash_delete(string key)
{
    if(hashF==1)
    {
        if(collisionMethod==1)
        {
            int hashIdx = hash1(key);
            list<pair<string, int> > temp = hashTable[hashIdx];
            list<pair<string, int> >::iterator it;
            for(it=temp.begin(); it!=temp.end(); it++)
            {
                pair<string, int> t= *it;
                if(t.first==key)
                {
                    temp.erase(it);
                    return;
                }

            }
        }
        else if(collisionMethod==2)
        {
            for(int i=0; i<=hashSize; i++)
            {
                int hashIdx = (hash1(key) + i*auxHash(key))%hashSize;
                int listSize = hashTable[hashIdx].size();
                if(listSize!=0)
                {
                    list<pair<string, int> >::iterator it;
                    it = hashTable[hashIdx].begin();
                    if((*it).first==key)
                    {
                        hashTable[hashIdx].clear(); ///ektai element ache list e
                        return;
                    }
                }
            }
        }
        else if(collisionMethod==3)
        {
            for(int i=0; i<=hashSize; i++)
            {
                int hashIdx = (hash1(key) + (4*i*auxHash(key)) + 7*i*i) % hashSize;
                int listSize = hashTable[hashIdx].size();
                if(listSize!=0)
                {
                    list<pair<string, int> >::iterator it;
                    it = hashTable[hashIdx].begin();
                    if((*it).first==key)
                    {
                        hashTable[hashIdx].clear(); ///ektai element ache list e
                        return;
                    }
                }
            }
        }
    }
    else if(hashF==2)
    {
        if(collisionMethod==1)
        {
            int hashIdx = hash2(key);
            list<pair<string, int> > temp = hashTable[hashIdx];
            list<pair<string, int> >::iterator it;
            for(it=temp.begin(); it!=temp.end(); it++)
            {
                pair<string, int> t= *it;
                if(t.first==key)
                {
                    temp.erase(it);
                    return;
                }

            }
        }
        else if(collisionMethod==2)
        {
            for(int i=0; i<=hashSize; i++)
            {
                int hashIdx = (hash2(key) + i*auxHash(key))%hashSize;
                int listSize = hashTable[hashIdx].size();
                if(listSize!=0)
                {
                    list<pair<string, int> >::iterator it;
                    it = hashTable[hashIdx].begin();
                    if((*it).first==key)
                    {
                        hashTable[hashIdx].clear(); ///ektai element ache list e
                        return;
                    }
                }
            }
        }
        else if(collisionMethod==3)
        {
            for(int i=0; i<=hashSize; i++)
            {
                int hashIdx = (hash2(key) + (4*i*auxHash(key)) + 7*i*i) % hashSize;
                int listSize = hashTable[hashIdx].size();
                if(listSize!=0)
                {
                    list<pair<string, int> >::iterator it;
                    it = hashTable[hashIdx].begin();
                    if((*it).first==key)
                    {
                        hashTable[hashIdx].clear(); ///ektai element ache list e
                        return;
                    }
                }
            }
        }
    }
}


void Hashing::printHashTable()
{
    for(int i=0; i<hashTable.size(); i++)
    {
        cout<<i<<": ";
        list<pair<string, int> > temp = hashTable[i];
        list<pair<string, int> >::iterator it;
        for(it=temp.begin(); it!=temp.end(); it++)
        {
            pair<string, int> t= *it;
            cout<<t.first<<"("<<t.second<<"), ";
        }
        cout<<endl;
    }
}

void Hashing::printData()
{
    cout<<"Number of collisions: "<<no_collision<<endl;
    double avg_probe = double(no_probe)/1000.00;
    cout<<"Average Probes: "<<avg_probe<<endl;
}

int main()
{
    srand(time(NULL));

    int n;
    cin>>n;


    /// Generate random words

    vector<string>  allwords;
    set<string> duplicateHandler;
    set<string> ::iterator it;

    for(int i=0; i<n; i++)
    {
        string s = "";
        for(int j=0; j<7; j++)
        {
            s = s+ char((rand()%26) + 97);
        }
        duplicateHandler.insert(s);
    }

    for(it=duplicateHandler.begin(); it!=duplicateHandler.end(); it++)
    {
        allwords.push_back(*it);
    }

    vector<string>  wordSearch;
    set<string> searchDuplicate;
    set<string>::iterator it2;
    for(int i=0; i<allwords.size(); i++)
    {
        int randIdx =  rand()%allwords.size();
        string ss = allwords[randIdx];
        searchDuplicate.insert(ss);
        if(searchDuplicate.size()==1000) break;
    }
    for(it2=searchDuplicate.begin(); it2!=searchDuplicate.end(); it2++)
    {
        wordSearch.push_back(*it2);
    }



    /// end of word generation

    int collMethod =3;
    int hashF =1;
    ///collisionMethod==1 -> chaining method
    ///collisionMethod==2 -> double hashing
    ///collisionMethod==3 -> custom probing

    ///hashF==1 -> hash1()
    ///hashF==2 -> hash2()

    Hashing h = Hashing(allwords.size(),collMethod, hashF);
    for(int i=1; i<=allwords.size(); i++)
    {
        h.hash_insert(allwords[i-1], i);
    }

    for(int i=0; i<wordSearch.size(); i++)
    {
        h.hash_search(wordSearch[i]);
    }

    /*
    for(int i=1; i<=allwords.size()-5; i++)
    {
        h.hash_delete(allwords[i-1]);
    }
    */
    //h.printHashTable();
    h.printData();
}
