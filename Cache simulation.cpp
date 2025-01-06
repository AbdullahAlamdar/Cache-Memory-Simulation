#include<iostream>
#include<fstream>
#include<string>
using namespace std;
string intToHex(int num);
int hexToInt(const string& hexStr);
class node{
    public:
    string adress;// to store hexadecimal adress
    int data;
    bool dirtybit;
    node*next;
    node(string adrr,int val){
        adress=adrr;
        data=val;
        dirtybit=false;
        next=NULL;
    }
};
class cacheList{
    public:
    node*head;
    int capacity;
    int size;
    cacheList(int capacity){
        this->capacity=capacity;
        size=0;
        head=NULL;
    }
    node* search(int adrr){
        node*temp=head;
        while(temp!=NULL){
            //string int_to_string_adrr=intToHex(adrr);
            if(hexToInt(temp->adress)==adrr/*int_to_string_adrr*/){
                return temp;
            }
            temp=temp->next;
        }
        return nullptr;
    }
    void write(int adress,string data,bool writeAllocate){
        int maxLines=100;
        string*lines=new string[maxLines];
        int lineCount=0;
        ifstream file;
        file.open("Memory.csv");
        if(!file.is_open()){
            cout<<"Error in opening the file !"<<endl;
            return;
        }
        string line;
        while(getline(file,line)){
            lines[lineCount++]=line;// storing each line in string array
        }
        file.close();// closing the file after storing each line in string array

        // exgtracting adress and data part and then matching the adress and overwriting the cache linked list

        for(int i=1;i<lineCount;i++){
            int commapos=lines[i].find(',');
            string adressPart=lines[i].substr(0,commapos);
            string dataPart=lines[i].substr(commapos+1,4);
            //int dataprt=stoi(dataPart);
            int currentAdress=stoi(adressPart);
            string int_to_str_current_adress=intToHex(currentAdress);
            int str_to_hexint_data=hexToInt(dataPart);
            if(currentAdress==adress){
                //lines[i]=adressPart+","+to_string(value);
                if(size>=capacity){
                    cout<<"Cache memory is full can not add more data ! "<<endl;
                }
                else{
                    if(writeAllocate){
                        addNodeAtHead(int_to_str_current_adress,hexToInt(data));
                    }
                    addNodeAtHead(int_to_str_current_adress,str_to_hexint_data);
                    size++;
                    break;
                }

            }
        }
        //OPENING THE FILE AGAIN in write mode
        /*
        ofstream ofile;
        ofile.open("Memory.csv");
        if(!ofile.is_open()){
            cout<<"Error opening the file !";
        }
        for(int i=0;i<lineCount;i++){
            ofile << lines[i]<<endl;
        }
        ofile.close();
        */
    }
    void writeDatatoFile(){
        node*temp=head;
        while(temp!=NULL){
            int cacheData=temp->data;
            string hex_data=intToHex(cacheData);
            string cacheAdress=temp->adress;
            int dec_adress=hexToInt(cacheAdress);
            string line=to_string(dec_adress)+","+hex_data;
            // opening the file in write mode
            ofstream ofile;
            ofile.open("Memory.csv",ios::app);
            if(!ofile.is_open()){
                cout<<"error opening the file ! "<<endl;
                return;
            }
            else{
                ofile<<line<<endl;
                ofile.close();
                temp=temp->next;
            }
        }
    }
    void addNodeAtHead(string adrr,int val){
        node*nn=new node(adrr,val);
        if(size>=capacity){
            cout<<"Not enough space in cache , can not add any other node ! "<<endl;
            return;
        }
        if(head!=NULL){
            nn->next=head;
            head=nn;
        }
        head=nn;
        size++;
    }

    void display(){
        cout<<"----------DATA FROM CACHE LIST----------"<<endl;
        node*temp=head;
        int index=1;
        while(temp!=NULL){
            cout<<"###  index : "<<index<<"  ###"<<endl;
            cout<<"adress : "<<temp->adress<<"   data : "<<temp->data<<"  Dirtybit : "<<temp->dirtybit<<endl;
            temp=temp->next;
            index++;

        }
    }
    void displayDataFromFile(){
        cout<<"--------DATA FROM FILE-----------"<<endl;
        int maxLines=100;
        string*lines=new string[maxLines];
        int lineCount=0;
        ifstream file;
        file.open("Memory.csv");
        if(!file.is_open()){
            cout<<"Error in opening the file !"<<endl;
            return;
        }
        string line;
        while(getline(file,line)){
            lines[lineCount++]=line;// storing each line in string array
        }
        for(int i=0;i<lineCount;i++){
            cout<<lines[i]<<endl;
        }
        file.close();// closing the file after storing each line in string array
     
    }
};
    string intToHex(int num) {
        // hexadecimal characters
        const char hexChars[] = "0123456789ABCDEF";
        string hexString;
        if (num == 0) {
            return "0";
        }
        bool isNegative = false;
        if (num < 0) {
            isNegative = true;
            num = -num; //positive conversion
        }
        while (num > 0) {
            int remainder = num % 16;
            hexString = hexChars[remainder] + hexString;
            num /= 16;
        }
        if (isNegative) {
            hexString = "-" + hexString;
        }
        return hexString;
    }
    //independent functins
    int hexToInt(const string& hexStr) {
        int decimalValue = 0;
        int base = 1; // represents 16^0 
        // Loop  from the end to the last
        for (int i = hexStr.length() - 1; i >= 0; i--) {
            char c = hexStr[i];
            if (c >= '0' && c <= '9') {
                decimalValue += (c - '0') * base;
            } else if (c >= 'A' && c <= 'F') {
                decimalValue += (c - 'A' + 10) * base;
            } else if (c >= 'a' && c <= 'f') {
                decimalValue += (c - 'a' + 10) * base;
            } else {
                cout << "Invalid hexadecimal character detected!" << endl;
                return -1;
            }

            base *= 16; //next power of 16
        }
        return decimalValue;
    }
int main(){
    cout<<"Cache hit policy : "<<endl<<"1.Write through"<<endl<<"2.Write Back"<<endl;
    int choice1;
    cin>>choice1;
    cout<<"Cache miss policy : "<<endl<<"1.Write Allocate"<<endl<<"2.Write Around"<<endl;
    int choice2;
    cin>>choice2;
    cout<<"Enter size of cache : ";
    int size;
    cin>>size;
    cacheList x(size);
    //dummy data
    x.addNodeAtHead("FFA",12);
    x.addNodeAtHead("23F",13);
    x.addNodeAtHead("2A6",14);
    x.addNodeAtHead("2B7",15);
    x.display();
    bool quit=true;
    while(quit){
        cout<<"1.Load operation"<<endl<<"2.Save operation"<<endl;
        int choice3;
        cin>>choice3;
        cout<<"Adress(Hexadecimal) : ";
        string adress;
        cin>>adress;
        int dec_adress=hexToInt(adress);
        node*adres=x.search(dec_adress);
        if(choice3==1){
            if(adres){
                cout<<"Found(cache hit) ! "<<endl;
            }
            else{
                cout<<"Not found(cache miss) ! "<<endl;
                x.write(dec_adress,"",false);
                x.displayDataFromFile();
                x.display();
                char q;
                cout<<"Enter q to quit or c to continue"<<endl;
                cin>>q;
                if(q=='q'||q=='Q'){
                    quit=false;
                    break;
                }
            }
        }
        if(choice3==2){
            // if the operation is store
            string data;
            cout<<"Enter data(hexadecimal) : ";
            cin>>data;
            if(adres){
                cout<<"found !(cache hit)!"<<endl;
                if(choice1==1){
                    //write through condition
                    adres->data=hexToInt(data);
                    x.display();
                    //writin data in csv 
                    x.writeDatatoFile();
                    x.displayDataFromFile();
                        char q;
                        cout<<"Enter q to quit or c to continue"<<endl;
                        cin>>q;
                        if(q=='q'||q=='Q'){
                        quit=false;
                        break;
                    }
                }
                else if(choice1==2){
                    //write back condition
                adres->data=hexToInt(data);
                adres->dirtybit=1;
                x.display(); 
                    char q;
                    cout<<"Enter q to quit or c to continue"<<endl;
                    cin>>q;
                    if(q=='q'||q=='Q'){
                        quit=false;
                        break;
                    }
                }
                else{
                    cout<<"Invalid policies entered ! "<<endl;
                    char q;
                    cout<<"Enter q to quit or c to continue"<<endl;
                    cin>>q;
                    if(q=='q'||q=='Q'){
                        quit=false;
                        break;
                    }
                }

            }
            else{
                //write allocate condition
                cout<<"not found !(cache miss)!"<<endl;
                if(choice2==1){

                    x.write(dec_adress,data,true);
                    x.writeDatatoFile();
                    //adres->data=hexToInt(data);
                    x.display();
                    x.displayDataFromFile();
                    char q;
                    cout<<"Enter q to quit or c to continue"<<endl;
                    cin>>q;
                    if(q=='q'||q=='Q'){
                        quit=false;
                        break;
                    }
                }
                if(choice2==2){
                    //write around condition
                    ofstream ofile;
                    ofile.open("Memory.csv",ios::app);
                    if(!ofile.is_open()){
                        cout<<"error in opening file ! "<<endl;
                    }
                    else{
                        string line=to_string(dec_adress)+","+data;
                        ofile<<line<<endl;
                    }
                    x.displayDataFromFile();
                    char q;
                    cout<<"Enter q to quit or c to continue"<<endl;
                    cin>>q;
                    if(q=='q'||q=='Q'){
                        quit=false;
                        break;
                    }
                }

            }
        }
    }




}