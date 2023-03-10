#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <unordered_map>


using namespace std;



struct Stock
{
    int lts;            // Last trade TimeStamp
    string sym;         // Symbol
    int tol_p = 0;      // Total Price
    int max_tg = 0;     // Maximum Time gap
    int tol_vol = 0;    // Total Volume traded
    int wa_p;           // Weighted Average Price   
    int max_p = 0;      // Max Trade price


};

int main(int argc, char **argv)
{  
     // basic parameter
    string ip_file;     // input cvs file
    string op_file;     // output cvs file
    ip_file = argv[1];
    op_file = argv[2];
    // check reading
    // cout << "input file:" << ip_file << endl;
    // cout << "output file:" << op_file << endl;
    
    vector<Stock> stocks;   //  store all presented stocks

    cout << "Part I:" << endl;
    // reading and operating
    ifstream file(ip_file);
    file.rdbuf()->pubsetbuf(0, 1024 * 1024);
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        vector<string> record;
        string cell;
        // get all data from a row as a piece of trade record
        while(getline(ss, cell, ',')){
            record.push_back(cell);
        }
        // judge if the stock has been in the stock set
        bool newone = true;
        for(auto& cur_stock : stocks ){
            // the stock exists in the set
            if(cur_stock.sym == record[1]){
                newone = false;
                cur_stock.max_tg = max(cur_stock.max_tg, (stoi(record[0]) - cur_stock.lts)  );
                cur_stock.lts = stoi( record[0] );
                cur_stock.tol_vol += stoi( record[2] );
                cur_stock.max_p = max( cur_stock.max_p, stoi(record[3]) );
                cur_stock.tol_p += stoi(record[2]) * stoi(record[3]);
                break;
            }
        }
        // it is a new one
        if(newone==true){
            Stock newstock;
            newstock.lts = stoi(record[0]);
            newstock.sym = record[1];
            newstock.tol_vol = stoi(record[2]);
            newstock.max_p = stoi(record[3]);
            newstock.tol_p = stoi(record[2]) * stoi(record[3]);
            stocks.push_back(newstock);     // add the new one into stock set
        }            
    }
    //read over

    // data calculation
    for (auto& cur_stock : stocks){
        cur_stock.wa_p = cur_stock.tol_p / cur_stock.tol_vol;
        // cout << cur_stock.sym<<",";
    }
    cout<<"Data Processing Over"<<endl;
    // cal over

    
    // output
    ofstream opfile(op_file);
    for(auto& cur_stock: stocks){
        opfile << cur_stock.sym << ',';
        opfile << cur_stock.max_tg << ",";
        opfile << cur_stock.tol_vol << ",";
        opfile << cur_stock.wa_p << ",";
        opfile << cur_stock.max_p << endl;
    }
    opfile.close();
    // output over

    return 0;
}

