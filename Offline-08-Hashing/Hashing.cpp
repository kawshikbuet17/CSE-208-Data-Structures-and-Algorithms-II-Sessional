#include<bits/stdc++.h>
using namespace std;

#define C1 5
#define C2 7

class HashWithChaining
{
    int N;
    vector<pair<string, int>> *hashTable;
    int collision;
    int probe;
    int tableSize;
public:
    HashWithChaining(int N)
    {
        hashTable = new vector<pair<string, int>>[N];
        this->N = N;
        tableSize = N;
        collision = 0;
        probe = 0;
    }
    int hashFunction1(string str)
    {
        int hashVal = 0;
        for(int i=0; i<str.length(); i++)
        {
            hashVal = (17 * hashVal + str[i])%tableSize;
        }
        hashVal = hashVal%tableSize;
        return hashVal;
    }

    int hashFunction2(string str)
    {
        int hashVal = 0;
        for(int i=0; i<str.length(); i++)
        {
            hashVal = (29 * hashVal + str[i])%tableSize;
        }
        hashVal = 44497 - (hashVal % 44497);
        return hashVal;
    }
    void hashTableInsert(string str, int value, int which_hash)
    {
        int hash1 = hashFunction1(str);
        int hash2 = hashFunction2(str);

        if(which_hash==1)
        {
            hashTable[hash1%N].push_back(make_pair(str, value));
            collision = collision + hashTable[hash1%N].size()-1;
        }
        else
        {
            hashTable[hash2%N].push_back(make_pair(str, value));
            collision = collision + hashTable[hash2%N].size()-1;
        }
    }

    bool hashTableSearch(string str, int value, int which_hash)
    {
        int flag = 0;

        int hash1 = hashFunction1(str);
        int hash2 = hashFunction2(str);
        int loc;

        if(which_hash == 1)
            loc = hash1;
        else
            loc = hash2;

        for(int i=0; i<hashTable[loc].size(); i++)
        {
            probe = i;
            if(value == hashTable[loc][i].second)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            return true;//cout<<"search "<<value<<" successful"<<endl;
        else
            return false;//cout<<"search "<<value<<" NOT successful"<<endl;
    }
    void hashTableDelete(string str, int value, int which_hash)
    {
        int hash1 = hashFunction1(str);
        int hash2 = hashFunction2(str);
        int loc;

        if(which_hash == 1)
            loc = hash1;
        else
            loc = hash2;
        for(int i=0; i<hashTable[loc].size(); i++)
        {
            if(value == hashTable[loc][i].second)
            {
                swap(hashTable[loc][i], hashTable[loc][hashTable[loc].size()-1]);
                hashTable[loc].pop_back();
                //cout<<"delete "<<value<<" successful"<<endl;
                break;
            }
        }
    }

    int collisionCount()
    {
        return collision;
    }

    int probeCount(string str, int value, int which_hash)
    {
        probe = 0;
        hashTableSearch(str, value, which_hash);
        return probe;
    }

    void hashTablePrint()
    {
        int x = 0;
        for(int i=0; i<N; i++)
        {
            cout<<i<<" :";
            for(auto j : hashTable[i])
            {
                cout<<" --> ("<<j.first<<", "<<j.second<<")";
            }
            cout<<endl;
        }
    }
};


class DoubleHashing
{
    int N;
    vector<pair<string, int>> hashTable;
    int collision;
    int probe;
    int tableSize;
public:
    DoubleHashing(int N)
    {
        tableSize = N;
        hashTable.resize(N);
        for(int i=0; i<tableSize; i++)
        {
            hashTable[i].first = "-1";
            hashTable[i].second = -1;
        }
        collision = 0;
        probe = 0;
    }
    int hashFunction1(string str)
    {
        int hashVal = 0;
        for(int i=0; i<str.length(); i++)
        {
            hashVal = (17 * hashVal + str[i])%tableSize;
        }
        hashVal = hashVal%tableSize;
        return hashVal;
    }

    int hashFunction2(string str)
    {
        int hashVal = 0;
        for(int i=0; i<str.length(); i++)
        {
            hashVal = (29 * hashVal + str[i])%tableSize;
        }
        hashVal = 44497 - (hashVal % 44497);
        return hashVal;
    }
    int auxHash(string str)
    {
        unsigned long aux = 5381;
        char c;
        for(int i=0; i<str.size(); i++)
        {
            c=str[i];
            aux = ((aux << 5) + aux) + c;
        }
        return aux%tableSize;
    }

    void insertedQuantity()
    {
        int cnt = 0;
        for(auto i : hashTable)
        {
            if(i.first != "-1" and i.second != -1)
                cnt++;
        }
        cout<<"Inserted Quantity = "<<cnt<<endl;

    }
    void hashTableInsert(string str, int value, int which_hash)
    {
        int i = 0;
        int location;

        while(1)
        {
            int hash1 = hashFunction1(str);
            int hash2 = hashFunction2(str);
            int aux = auxHash(str);
            if(which_hash==1)
                location = (hash1 + aux*i)%tableSize;
            else
                location = (hash2 + aux*i)%tableSize;

            if((hashTable[location].first == "-1" || hashTable[location].first == "DEL") and  hashTable[location].second == -1)
            {
                hashTable[location].first = str;
                hashTable[location].second = value;

                collision += i;
                break;
            }
            else
                i++;

            if(i>=tableSize)
            {
                collision += i;
                break;
            }
        }
    }

    bool hashTableSearch(string str, int value, int which_hash)
    {
        int flag = 0;
        int i = 0;
        int location;

        while(1)
        {
            int hash1 = hashFunction1(str);
            int hash2 = hashFunction2(str);
            int aux = auxHash(str);
            if(which_hash==1)
                location = (hash1 + aux*i)%tableSize;
            else
                location = (hash2 + aux*i)%tableSize;

            if(hashTable[location].first == str and  hashTable[location].second == value)
            {
                flag = 1;
                probe = i;
                break;
            }
            else if(hashTable[location].first == "-1" and  hashTable[location].second == -1)
            {
                flag = 0;
                probe = i;
                break;
            }
            else
                i++;
            if(i>=tableSize)
            {
                probe = i;
                break;
            }
        }

        if(flag == 1)
            return true;//cout<<"search "<<value<<" successful"<<endl;
        else
            return false;//cout<<"search "<<value<<" NOT successful"<<endl;
    }
    void hashTableDelete(string str, int value, int which_hash)
    {
        int i = 0;
        int location;

        while(1)
        {
            int hash1 = hashFunction1(str);
            int hash2 = hashFunction2(str);
            int aux = auxHash(str);
            if(which_hash==1)
                location = (hash1 + aux*i)%tableSize;
            else
                location = (hash2 + aux*i)%tableSize;

            if(hashTable[location].first == str and  hashTable[location].second == value)
            {
                hashTable[location].first = "DEL";
                hashTable[location].second = -1;
                break;
            }
            else if(hashTable[location].first == "-1" and  hashTable[location].second == -1)
            {
                break;
            }
            else
                i++;

            if(i>=tableSize)
                break;
        }
    }

    int collisionCount()
    {
        return collision;
    }

    int probeCount(string str, int value, int which_hash)
    {
        probe = 0;
        hashTableSearch(str, value, which_hash);
        return probe;
    }

    void hashTablePrint()
    {
        for (auto i : hashTable)
            cout<<"-->("<<i.first<<", "<<i.second<<") ";
        cout<<endl;
    }
};




class CustomProbing
{
    vector<pair<string, int>> hashTable;
    int collision;
    int probe;
    int tableSize;
    int currentSize;
public:
    CustomProbing(int N)
    {
        tableSize = N;
        hashTable.resize(N);
        for(int i=0; i<tableSize; i++)
        {
            hashTable[i].first = "-1";
            hashTable[i].second = -1;
        }
        collision = 0;
        probe = 0;
    }
    int hashFunction1(string str)
    {
        int hashVal = 0;
        for(int i=0; i<str.length(); i++)
        {
            hashVal = (17 * hashVal + str[i])%tableSize;
        }
        hashVal = hashVal%tableSize;
        return hashVal;
    }

    int hashFunction2(string str)
    {
        int hashVal = 0;
        for(int i=0; i<str.length(); i++)
        {
            hashVal = (29 * hashVal + str[i])%tableSize;
        }
        hashVal = 44497 - (hashVal % 44497);
        return hashVal;
    }

    int auxHash(string str)
    {
        unsigned long aux = 5381;
        char c;
        for(int i=0; i<str.size(); i++)
        {
            c=str[i];
            aux = ((aux << 5) + aux) + c;
        }
        return aux%tableSize;
    }

    bool insertQuantity()
    {
        int cnt = 0;
        for(auto i : hashTable)
        {
            if(i.first != "-1")
                cnt++;
        }
        cout<<"Inserted Quantity "<<cnt<<endl;

    }
    void hashTableInsert(string str, int value, int which_hash)
    {
        int i = 0;
        int location;

        while(1)
        {
            int hash1 = hashFunction1(str);
            int hash2 = hashFunction2(str);
            int aux = auxHash(str);
            if(which_hash==1)
                location = (hash1 + C1*i*aux + C2*i*i)%tableSize;
            else
                location = (hash2 + C1*i*aux + C2*i*i)%tableSize;

            if((hashTable[location].first == "-1"||hashTable[location].first == "DEL") and  hashTable[location].second == -1)
            {
                hashTable[location].first = str;
                hashTable[location].second = value;

                collision += i;

                break;
            }
            else
                i++;
            if(i>=tableSize)
            {
                collision += i;
                break;
            }
        }
    }

    bool hashTableSearch(string str, int value, int which_hash)
    {
        int flag = 0;
        int i = 0;
        int location;

        while(1)
        {
            int hash1 = hashFunction1(str);
            int hash2 = hashFunction2(str);
            int aux = auxHash(str);
            if(which_hash==1)
                location = (hash1 + C1*i*aux + C2*i*i)%tableSize;
            else
                location = (hash2 + C1*i*aux + C2*i*i)%tableSize;

            if(hashTable[location].first == str and  hashTable[location].second == value)
            {
                flag = 1;
                probe = i;
                break;
            }
            else if(hashTable[location].first == "-1" and  hashTable[location].second == -1)
            {
                flag = 0;
                probe = i;
                break;
            }
            else
                i++;
            if(i>=tableSize)
            {
                probe = i;
                break;
            }
        }

        if(flag == 1)
            return true;//cout<<"search "<<value<<" successful"<<endl;//
        else
            return false;//cout<<"search "<<value<<" NOT successful"<<endl;//
    }
    void hashTableDelete(string str, int value, int which_hash)
    {
        int i = 0;
        int location;

        while(1)
        {
            int hash1 = hashFunction1(str);
            int hash2 = hashFunction2(str);
            int aux = auxHash(str);
            if(which_hash==1)
                location = (hash1 + C1*i*aux + C2*i*i)%tableSize;
            else
                location = (hash2 + C1*i*aux + C2*i*i)%tableSize;
            if(hashTable[location].first == str and  hashTable[location].second == value)
            {
                hashTable[location].first = "DEL";
                hashTable[location].second = -1;
                break;
            }
            else if(hashTable[location].first == "-1" and  hashTable[location].second == -1)
            {
                break;
            }
            else
                i++;
            if(i>=tableSize)
                break;
        }
    }

    int collisionCount()
    {
        return collision;
    }

    int probeCount(string str, int value, int which_hash)
    {
        probe = 0;
        hashTableSearch(str, value, which_hash);
        return probe;
    }

    void hashTablePrint()
    {
        for (auto i : hashTable)
            cout<<"-->("<<i.first<<", "<<i.second<<") ";
        cout<<endl;
    }
};



int32_t main()
{
    ///Random String Generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1000000);

    string tmp_s="";
    static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
    int len = 7;
    set<string>s;
    for(int i=0; i<11000; i++)
    {
        if(i>=10000)
            break;
        for (int i = 0; i < len; ++i)
        {
            tmp_s += alphanum[dis(gen) % (sizeof(alphanum) - 1)];
        }
        s.insert(tmp_s);
        tmp_s = "";
    }

    vector<string>word(s.begin(), s.end());
    vector<pair<string, int>> words;
    for(int i=0; i<word.size(); i++)
        words.push_back(make_pair(word[i], i+1));
    cout<<"Generated "<<words.size()<<" Strings"<<endl;



    ///Input from user
    int N;
    cout<<"Input HashTable Size : ";
    cin>>N;
    cout<<"For Testing press '1' \nFor Report generation press '2'\n";
    int choice;
    cin>>choice;
    if(choice == 1)
    {
        cout<<"How many string you want to insert = ";
        int how_many;
        cin>>how_many;

        cout<<"\n-------------CHAINING METHOD (HASH 1)--------------"<<endl;
        HashWithChaining hwc(N);
        for(int i=0; i<how_many; i++)
        {
            hwc.hashTableInsert(words[i].first, words[i].second, 1);
        }
        hwc.hashTablePrint();

        cout<<"\n-------------CHAINING METHOD (HASH 2)--------------"<<endl;
        HashWithChaining hwc2(N);
        for(int i=0; i<how_many; i++)
        {
            hwc2.hashTableInsert(words[i].first, words[i].second, 2);
        }
        hwc2.hashTablePrint();



        cout<<"\n-------------DOUBLE HASHING (HASH 1)--------------"<<endl;
        DoubleHashing dh(N);
        for(int i=0; i<how_many; i++)
        {
            dh.hashTableInsert(words[i].first, words[i].second, 1);
        }
        dh.insertedQuantity();
        cout<<"Collision 1 = "<<dh.collisionCount()<<endl;
        dh.hashTablePrint();


        cout<<"\n-------------DOUBLE HASHING (HASH 2)--------------"<<endl;
        DoubleHashing dh2(N);
        for(int i=0; i<how_many; i++)
        {
            dh2.hashTableInsert(words[i].first, words[i].second, 2);
        }
        dh2.insertedQuantity();
        cout<<"Collision 2 = "<<dh2.collisionCount()<<endl;
        dh2.hashTablePrint();



        cout<<"\n-------------CUSTOM PROBING (HASH 1)--------------"<<endl;
        CustomProbing cb(N);
        for(int i=0; i<how_many; i++)
        {
            cb.hashTableInsert(words[i].first, words[i].second, 1);
        }
        cb.insertQuantity();
        cout<<"Collision 1 = "<<cb.collisionCount()<<endl;
        cb.hashTablePrint();

        cout<<"\n-------------CUSTOM PROBING (HASH 2)--------------"<<endl;
        CustomProbing cb2(N);
        for(int i=0; i<how_many; i++)
        {
            cb2.hashTableInsert(words[i].first, words[i].second, 2);
        }
        cb2.insertQuantity();
        cout<<"Collision 2 = "<<cb2.collisionCount()<<endl;
        cb2.hashTablePrint();

        ///Custom Probing Ends
    }
    else
    {
        int lenInsert;
        if(N>10000)
            lenInsert = 10000;
        else
            lenInsert = N;

        cout<<"-------------CHAINING METHOD (HASH 1)--------------"<<endl;
        HashWithChaining hwc(N);
        for(int i=0; i<min(N, 10000); i++)
        {
            hwc.hashTableInsert(words[i].first, words[i].second, 1);
        }
        cout<<"Collision 1= "<<hwc.collisionCount()<<endl;

        double prb = 0;
        for(int i=0; i<N/10; i++)
        {
            int rgen = dis(gen);
            string str = words[rgen%(N)].first;
            int value = words[rgen%(N)].second;
            prb+=hwc.probeCount(str, value, 1);
            //cout<<rgen%(N/10)<<" --- "<<dh.probeCount(str, value)<<endl;
        }
        prb = prb/(N/10);
        cout<<"Avg Probe 1= "<<prb<<endl;



        cout<<"-------------CHAINING METHOD (HASH 2)--------------"<<endl;
        HashWithChaining hwc2(N);
        for(int i=0; i<min(N, 10000); i++)
        {
            hwc2.hashTableInsert(words[i].first, words[i].second, 2);
        }

        cout<<"Collision 2= "<<hwc2.collisionCount()<<endl;

        prb = 0;
        for(int i=0; i<N/10; i++)
        {
            int rgen = dis(gen);
            string str = words[rgen%(N)].first;
            int value = words[rgen%(N)].second;
            prb+=hwc2.probeCount(str, value, 1);
            //cout<<rgen%(N/10)<<" --- "<<dh.probeCount(str, value)<<endl;
        }
        prb = prb/(N/10);
        cout<<"Avg Probe 1= "<<prb<<endl;



        ///Double Hashing Starts///
        cout<<"\n-------------DOUBLE HASHING (HASH 1)--------------"<<endl;
        DoubleHashing dh(N);
        for(int i=0; i<min(N, 10000); i++)
        {
            dh.hashTableInsert(words[i].first, words[i].second, 1);
        }
        dh.insertedQuantity();
        //dh.hashTablePrint();
        cout<<"Collision 1= "<<dh.collisionCount()<<endl;

        prb = 0;
        for(int i=0; i<N/10; i++)
        {
            int rgen = dis(gen);
            string str = words[rgen%(N)].first;
            int value = words[rgen%(N)].second;
            prb+=dh.probeCount(str, value, 1);
            //cout<<rgen%(N/10)<<" --- "<<dh.probeCount(str, value)<<endl;
        }
        prb = prb/(N/10);
        cout<<"Avg Probe 1= "<<prb<<endl;

        cout<<"\n-------------DOUBLE HASHING (HASH 2)--------------"<<endl;
        DoubleHashing dh2(N);
        for(int i=0; i<min(N, 10000); i++)
        {
            dh2.hashTableInsert(words[i].first, words[i].second, 2);
        }
        dh2.insertedQuantity();
        cout<<"Collision 2= "<<dh2.collisionCount()<<endl;

        prb = 0;
        for(int i=0; i<N/10; i++)
        {
            int rgen = dis(gen);
            string str = words[rgen%(N)].first;
            int value = words[rgen%(N)].second;
            prb+=dh2.probeCount(str, value, 2);
            //cout<<rgen%(N/10)<<" --- "<<dh2.probeCount(str, value)<<endl;
        }
        prb = prb/(N/10);
        cout<<"Avg Probe 2= "<<prb<<endl;


        ///Double Hashing Ends///




        ///Custom Probing Starts
        cout<<"\n-------------CUSTOM PROBING (HASH 1)--------------"<<endl;
        CustomProbing cb(N);
        for(int i=0; i<min(N, 10000); i++)
        {
            cb.hashTableInsert(words[i].first, words[i].second, 1);
        }
        cb.insertQuantity();

        cout<<"Collision 1= "<<cb.collisionCount()<<endl;

        prb = 0;
        for(int i=0; i<N/10; i++)
        {
            int rgen = dis(gen);
            string str = words[rgen%(N)].first;
            int value = words[rgen%(N)].second;
            prb+=cb.probeCount(str, value, 1);
            //cout<<rgen%(N/10)<<" --- "<<dh.probeCount(str, value, 1)<<endl;
        }
        prb = prb/(N/10);
        cout<<"Avg Probe 1= "<<prb<<endl;


        cout<<"\n-------------CUSTOM PROBING (HASH 2)--------------"<<endl;
        CustomProbing cb2(N);
        for(int i=0; i<min(N, 10000); i++)
        {
            cb2.hashTableInsert(words[i].first, words[i].second, 2);
        }
        cb2.insertQuantity();
        cout<<"Collision 2= "<<cb2.collisionCount()<<endl;

        prb = 0;
        for(int i=0; i<N/10; i++)
        {
            int rgen = dis(gen);
            string str = words[rgen%(N)].first;
            int value = words[rgen%(N)].second;
            prb+=cb2.probeCount(str, value, 2);
            //cout<<rgen%(N/10)<<" --- "<<dh2.probeCount(str, value)<<endl;
        }
        prb = prb/(N/10);
        cout<<"Avg Probe 2= "<<prb<<endl;


        ///Custom Probing Ends
    }
}
