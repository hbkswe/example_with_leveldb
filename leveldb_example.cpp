#include <iostream>
#include <string>
#include <assert.h>
#include <unistd.h>
#include "leveldb/db.h"

using namespace std;

// build the code with $ g++ -o leveldb_example leveldb_example.cpp -lleveldb
int main (void)
{
    leveldb::DB *db;
    leveldb::Options options;

    options.create_if_missing = true;
    //open
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    assert(status.ok());

    string key = "name";
    string value = "HenryLe";

    // write - PUT
    status = db->Put(leveldb::WriteOptions(), key, value);
    assert(status.ok());
    cout << "=== Write K:[" << key << "] V:[" << value << "] to DB"  << endl;

    // read - GET
    status = db->Get(leveldb::ReadOptions(), key, &value);
    assert(status.ok());
    cout << "=== Read K:["  << key << "] V:[" << value << "] from DB" << endl;

    // delete - DELETE
    status = db->Delete(leveldb::WriteOptions(), key);
    assert(status.ok());

    status = db->Get(leveldb::ReadOptions(), key, &value);
    if (!status.ok())
    {
        cerr << "=== Failed to read kv after deletion: [" << key << "] Status: " << status.ToString()  << endl;
    }
    else
    {
        cout << key << "===" << value << endl;
    }
    // usleep(20000000);

    // close
    delete db;

    return 0;
}