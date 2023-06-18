//ALADDIN
//1) ABDUL AZIZ BIN MABENI
//2) MUHAMAD ZAIED AZIEM BIMN MOHD ZAIDI
//3) ABDUL ROHMAN BIN MAHMOOD

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

void printline(){
    
    for(int i=0;i<30;i++)
        cout<<"=";
    cout<<endl;
}

void emptyspace(){

    for(int i=0;i<30;i++)
        cout<<"\n";
}

class PayMethod {
    private: 
        string methodName[2];
        string accDetail;
        double totalCost;
        bool payStat;
    public:
        PayMethod() {
            methodName[0] = "COD";
            methodName[1] = "Online Banking (FPX)";
        }
        bool process(double costPay) {
            int actionOpt;
            cout << "Choose payment method: " << endl;
            printline();
            cout << "1. " << methodName[0] << endl;
            cout << "2. " << methodName[1] << endl;
            printline();
            do {
                cout << "Enter Action -> ";
                cin >> actionOpt;
                if (actionOpt == 1) 
                    cout << "COD method chosen." << endl;
                else if (actionOpt == 2) {
                    string tempAccDetail;
                    cout << "Insert bank account number -> ";
                    cin >> tempAccDetail;
                    if (tempAccDetail == accDetail) {
                        cout << "RM" << costPay << " has been deducted from your account." << endl;
                    }
                    else {
                        cout << "Bank account number not found." << endl;
                    }
                }
                else 
                    cout << "Invalid action. ";
            } while ( actionOpt < 1 || actionOpt > 2 );
            return true;
        }
};


class Product{
    
    string p_id;
    string p_name;
    string p_desc;
    double price;
    string seller;
    int quantity;

    public:

        friend class ShopCart;
        friend class Buyer;
};

class User{
    protected:
        string id;   
        string username;    //changeable
        string email;  
        string password;    //changeable    
        string address;     //changeable
        int paymentmethod;  //changeable
        Product item;
        string acctype; //ONLY 2 , BUYER&SELLER 

    public:

        User(){
            id="0";
            username="username"; 
            email="email";
            password="password";
            address="address";
            paymentmethod=0;
            acctype="BUYER";
        }
        void addproduct(Product *prod){
            item=*prod;
        }
        Product getproduc(){
            return item;
        }
        string getid(){
            return id;
        }   
        string getusername(){
            return username;
        }    
        string getpassword(){
            return password;
        }    
        string getemail(){
            return email;
        }      
        string getaddress(){
            return address;
        }     
        int getpaymentmethod(){
            return paymentmethod;
        } 
        string getacctype(){
            return acctype;
        }
        void changeusername(string newusername){
            
            bool status=true;
            string waste,userr;
            
            ifstream reading("accinfo.txt");
            while (reading >> waste >> userr >> waste>>waste) {
                getline(reading>>ws, waste, '\"');  //read from password to "
                getline(reading,waste,'\"');
                reading>>waste>>waste;
                if (newusername == userr) {
                    status = false;
                    emptyspace();
                    cout<<"Username taken"<<endl;
                    break;
                }
                
            }
            reading.close();

            if(status==true){
                
                ifstream reading1("accinfo.txt");
                string everything,singleline;
                while(getline(reading1,singleline)){
                    everything+=singleline+"\n";
                }
                
                everything=everything.replace(everything.find(" "+email+" "+password)-username.length(),username.length(),newusername);
                
                reading1.close();
                ofstream overwrite("accinfo.txt");
                overwrite<<everything;
                overwrite.close();

                username=newusername;
                emptyspace();
                cout<<"Username updated"<<endl;
            }

        }
        void changepassword(string newpass){
            
            ifstream reading("accinfo.txt"); 
            string everything,singleline;
            while(getline(reading,singleline)){
                everything+=singleline+"\n";
            }
            everything=everything.replace(everything.find(email+" "+password)+email.length()+1,password.length(),newpass);
            
            reading.close();
            ofstream overwrite("accinfo.txt");
            overwrite<<everything;
            overwrite.close();
            emptyspace();
            cout<<"Password updated"<<endl;
            password=newpass;

        }
        void changeaddress(string ad){
            
            
            ifstream reading("accinfo.txt");
            
            string everything,singleline;
            while(getline(reading,singleline)){
                everything+=singleline+"\n";
            }
            everything=everything.replace(everything.find(" "+email+" "+password)+1+email.length()+1+password.length()+1+1,address.length(),ad);
            reading.close();
            ofstream overwrite("accinfo.txt");
            overwrite<<everything;
            overwrite.close();

            address=ad;
            emptyspace();
            cout<<"Address updated"<<endl;

            
        }
        void changepaymentmethod(int a){
            
            ifstream reading("accinfo.txt");
            
            string everything,singleline;
            while(getline(reading,singleline)){
                everything+=singleline+"\n";
            }
            everything=everything.replace(everything.find(" "+email+" "+password)+1+email.length()+1+password.length()+1+1+address.length()+1+1,1,to_string(a));
            reading.close();
            ofstream overwrite("accinfo.txt");
            overwrite<<everything;
            overwrite.close();

            paymentmethod=a;
            emptyspace();
            cout<<"Payment Method updated"<<endl;
        }
        
        bool authenticateemail(){

            string tempEmail,waste;
            bool status = false;
            ifstream reading("accinfo.txt");

            
            while (reading >> waste >> waste >> tempEmail>>waste) {
                getline(reading>>ws, waste, '\"');  //read from password to "
                getline(reading,waste,'\"');
                reading>>waste>>waste;
                if (email == tempEmail) {
                    status = true;
                    break;
                }
            }
            

            reading.close();
            return status;
        }

        bool authenticatelogin(){
            string tempEmail, tempPassword;
            bool status = false;
            ifstream reading("accinfo.txt");
            
    
            while (reading >> id >> username >> tempEmail>>tempPassword) {
                getline(reading>>ws, address, '\"');  //read from password to "
                getline(reading,address,'\"');
                reading>>paymentmethod;
                reading>>acctype;
                if (email == tempEmail && password == tempPassword) {
                    status = true;
                    break;
                }
            }
            

            reading.close();
            return status;
        }

        void Register(){
            printline();
            cout<<"  REGISTER PAGE "<<endl;
            printline();
            cout<<"Email : ";
            cin>>email;
            cout<<"Password : ";
            cin>>password;
            string p;
            cout<<"Confirm Password : ";
            cin>>p;
            while(p!=password){
                emptyspace();
                cout<<"ERROR Password does not match , Type Again"<<endl;
                cout<<"Email : "<<email<<endl;
                cout<<"Password : ";
                cin>>password;
                cout<<"Confirm Password : ";
                cin>>p;
                
            }
            if(authenticateemail()==true){
                emptyspace();
                cout<<"EMAIL ALREADY EXIST"<<endl;
            }
            if(authenticateemail()==false){
                

                cout<<"Choose Account Type : "<<endl;
                cout<<"(1) Buyer\n(2) Seller"<<endl;
                cout<<"Action => ";
                int T;
                cin>>T;
                if(T==1){
                    acctype="BUYER";
                }
                if(T==2){
                    acctype="SELLER";
                }

                emptyspace();
                cout<<"USER ACCOUNT CREATED"<<endl;
               

                ifstream readID("accinfo.txt");
                ofstream createAcc("accinfo.txt",ios::app);
                string id,waste;
                while(readID>>id>>waste>>waste>>waste){
                    getline(readID>>ws, waste, '\"');  //read from password to "
                    getline(readID,waste,'\"');
                    readID>>waste>>waste;
                    
                }
                int tempid=stoi(id);
                tempid+=1;
                id=to_string(tempid);

                readID.close();

                createAcc<<id<<" "<<"username"+id+"alibabba"<<" "<<email<<" "<<password<<" \"Earth\""<<" "<<"0 "<<acctype<<endl;
                createAcc.close();
            }
            
        }

        bool Login(){
            printline();
            cout<<"  Login Page "<<endl;
            printline();
            cout<<"Email : ";
            cin>>email;
            cout<<"Password : ";
            cin>>password;
            bool status=authenticatelogin();
            if(status==false){
                emptyspace();
                cout<<"WRONG LOGIN CREDINTIALS"<<endl;
            }
            else{
                emptyspace();
                cout<<"LOGIN SUCCESSFUL"<<endl;
            }
            return status;
        }
        void AccountInfo(){
                
                printline();
                cout<<"Account Info"<<endl;
                printline();
                cout<<" Account Type : "<<acctype<<endl;
                cout<<"(1) ID : "<<id<<endl;
                cout<<"(2) Username : "<<username<<endl;
                cout<<"(3) Email : "<<email<<endl;
                cout<<"(4) Password : "<<password<<endl;
                cout<<"(5) Address : "<<address<<endl;
                cout<<"(6) Payment Method : "<<paymentmethod<<endl;
                cout<<"(99) Previous Page"<<endl;

                cout<<"\nNote : You can only change option 2,3,4,5"<<endl;

                printline();
                cout<<"Choose Action => ";
                int action;
                cin>>action;
                if(action==2){
                    string newusername;
                    cout<<"Note : Username is only 1 word long"<<endl;
                    cout<<"Enter new username : ";
                    cin>>newusername;
                    changeusername(newusername);
                    
                }
                else if(action==4){
                    string temppass,newpass;
                    cout<<"Enter current password : ";
                    cin>>temppass;
                    if(temppass!=password){
                        emptyspace();
                        cout<<"Password does not match."<<endl;
                    }
                    if(temppass==password){
                        cout<<"Enter New password : ";
                        cin>>newpass;
                        changepassword(newpass);
                        
                    }
                    
                }
                else if(action==5){
                    string newaddress;
                    cout<<"Enter new address : ";
                    cin.ignore();
                    getline(cin,newaddress);
                    changeaddress(newaddress);
                    
                }
                else if(action==6){
                    int newpaymentmethod;
                    //PUT PAYMENT METHOD CLASS HERE
                    cout<<"Enter new payment method : ";
                    cin>>newpaymentmethod;
                    changepaymentmethod(newpaymentmethod);
                    
                }
                else if(action==99){
                    emptyspace();
                }
                else
                    emptyspace();
                if(action!=99)
                    AccountInfo();
    
        }

        

};

class Buyer:public User{

    public:

    Buyer (const User &u):User(u){

       
    }

    void BrowseItem(Product &prod,int k=1){//k is for page number 
        printline();
        cout<<"Aladdin Marketplace"<<endl;
        printline();
        cout<<"Item List"<<endl;
        
        ProductListing(prod,k);
        
        cout<<"(10) Search Item"<<endl;

        if(k>1)
            cout<<"(90) Previous Page"<<endl;
        if(k<maxListingPage())
            cout<<"(91) Next Page"<<endl;
        cout<<"(99) Previous Page"<<endl;
        printline();
        int options;
        cout<<"Pick Action =>";
        cin>>options;
        if(options>=1&&options<=5){
            ItemInfo(prod,(5*(k-1))+options);
        }
        else if(options==10){
            emptyspace();
            SearchItem(prod);
        }
        else if(options==90&&k>1){
            emptyspace();
            BrowseItem(prod,k-1);
        }
        else if(options==91&&k<maxListingPage()){
            emptyspace();
            BrowseItem(prod,k+1); 
        }
        else{
            emptyspace();
            BrowseItem(prod);
        }
       
    }

    int maxListingPage(){
        ifstream reading("marketplace.txt");
        string waste;
        int item=0;
        while(getline(reading,waste)){
            item++;
        }
        int pages=ceil(item/5);


        reading.close();
        return pages;
    }

    void ProductListing(Product prod,int page){
        ifstream reading("marketplace.txt");
        string waste;
        getline(reading,waste);
        
        string id[5];
        for (int i=0;(i<((5*page)));i++ ) {
            
            

            reading >> prod.seller >> prod.p_id;
            getline(reading>>ws, prod.p_name, '\"');  //read from password to "
            getline(reading,prod.p_name,'\"');
            getline(reading>>ws, prod.p_desc, '\"');  //read from password to "
            getline(reading,prod.p_desc,'\"');
            reading>>prod.price>>prod.quantity;
            
            

            id[(i%5)]=prod.p_id;
            

            if(i>((5*page)-6)){
                
                cout<<"("<<(i%5+1)<<") "<<prod.p_name<<"  -RM "<<prod.price<<" ("<<to_string(prod.quantity)<<" left)"<<endl;
                
            }
        }
        reading.close();
    }

    void SearchItem(Product prod,string item$=" "){
        //item$ is any description/price/quantity/id of the item, no discrimination
        bool newitemvalue=false;
        
        if(item$==" "){
            printline();
            cout<<"Item Search"<<endl;
            printline();
            cout<<"Please enter anything related to the item\n(ID/Name/Desc./Price/Quantity)"<<endl;
            cout<<"Item Info : ";
            cin>>item$;
            newitemvalue=true;
        }
        ifstream reading("marketplace.txt"); 
        
        string waste;
        vector<Product> list;
        int totalfound=0;
        getline(reading,waste);    
        do{
            reading >> prod.seller >> prod.p_id;
            getline(reading>>ws, prod.p_name, '\"');  //read from password to "
            getline(reading,prod.p_name,'\"');
            getline(reading>>ws, prod.p_desc, '\"');  //read from password to "
            getline(reading,prod.p_desc,'\"');
            reading>>prod.price>>prod.quantity;
            //seller 0 "name" "desc" 00.00 0
            waste=prod.seller+" "+prod.p_id+" "+prod.p_name+" "+prod.p_desc+" "+to_string(prod.price)+" "+to_string(prod.quantity);
            if(waste.find(item$) != std::string::npos){
                list.push_back(prod);
                totalfound+=1;
            }

        }while(!reading.eof());
        if(list.capacity()>0){
            vector<Product>::iterator itr;
            
            if(newitemvalue)
                emptyspace();
            cout<<"FOUND "<<totalfound<<" ITEMS"<<" with prompts \""<<item$<<"\""<<endl;
            printline();
            
            for(itr=list.begin();itr!=list.end();itr++){
                cout<<"("<<itr->p_id<<")"<<itr->p_name<<"  -RM "<<itr->price<<" ("<<to_string(itr->quantity)<<" left)"<<endl;
            }
            string opt;
            
            cout<<"(-99) Previous Page"<<endl;
            printline();
            cout<<"Choose Action=>";
            cin>>opt;
            try
            {
                bool valid=false;
                if(stoi(opt)==-99){
                    BrowseItem(prod);
                }

                else{
                    for(itr=list.begin();itr!=list.end();itr++){
                        if(stoi(itr->p_id)==stoi(opt))
                            valid=true;
                    }
                    if(valid)
                        ItemInfo(prod,stoi(opt));
                    else
                        throw string("NOT VALID ID");
                }
                
            }
            catch(const std::exception& e)
            {
                
                emptyspace();
                cout<<"ERROR "<<e.what()<<endl;
                SearchItem(prod,item$);
                

            }
            catch(const string error){
                emptyspace();
                cout<<"ERROR "<< error<<endl;
                cin.ignore();
                SearchItem(prod,item$);
            }
            
            
        }
        else{
            emptyspace();
            cout<<"NO ITEM FOUND"<<endl;
            BrowseItem(prod);
        }
        
        

        reading.close();

    }

        
        
    

    void ItemInfo(Product prod,int index){
        
        
        ifstream reading("marketplace.txt");
        string waste;
        getline(reading,waste);
            
            for(int i=0;i<index;i++) {
                reading >> prod.seller;
                reading>>prod.p_id;
                getline(reading>>ws, prod.p_name, '\"');  //read from password to "
                getline(reading,prod.p_name,'\"');
                getline(reading>>ws, prod.p_desc, '\"');  //read from password to "
                getline(reading,prod.p_desc,'\"');
                reading>>prod.price>>prod.quantity;
                
            }

            emptyspace();
            printline();
            cout<<"Item Info"<<endl;
            printline();
            cout<<"Seller : "<<prod.seller+" "<<endl;
            cout<<"Product ID : "<<prod.p_id+" "<<endl;
            cout<<"Product Name : "<<prod.p_name<<endl;
            cout<<"Product Details : "<<prod.p_desc<<endl;
            cout<<"Price : RM"<<to_string(prod.price)<<endl;
            cout<<"Quantity : "<<to_string(prod.quantity)<<endl;
            printline();
            cout<<"1. Add to Cart(TBA)"<<endl;
            cout<<"99. Previous Page "<<endl;
            cout<<"Choose Action => ";
            int options;
            cin>>options;
            if(options)
                BrowseItem(prod);
            
            reading.close();
    }

    


};


class Order{
    string o_id;
    User *user;
    
};

class ShopCart {
    private:
        User user;
        Product *item;
        int cartLimit;
        double totalPayCost;
    public:
        ShopCart(User _user) {
            user = _user;
            item = new Product[5];
            int cartLimit = 5;
            totalPayCost = 0.0;
        }
        void addItem(Product _item) {
            item[0] = _item;
            item[cartLimit] = item[0];
            cartLimit--;
            if (cartLimit == 0)
                cout << "Shopping cart already full." << endl;
        }
        void removeItem(Product _item) {
            for (int i = 0; i < 5; i++) {
                if (item[i].p_name == _item.p_name)
                    item[i].p_id = "0"; //grab info from marketplace.txt
                    cartLimit++;
            }
        }
        void viewCart() {
            for (int i = 0; i < 5; i++) {
                cout << "Slot " << i << ": " << item[i].p_name << endl;
            }
        }
        void checkOut() {
            totalPayCost = 0.0;
            for (int i = 0; i < 5; i++) {
                totalPayCost += item[i].price;
            }
            delete [] item;
            cartLimit = 5;
        }
};


int Options1(){
    int opt=0;
    string ifnotnumber;
    bool digit=true;
    printline();
    cout<<"Main Page"<<endl;
    printline();
    cout<<"1. Register"<<endl;
    cout<<"2. Login"<<endl;
    cout<<"99. QUIT"<<endl;
    printline();
    cout<<"Choose Action => ";
    cin>>ifnotnumber;

    for(int i=0;i<ifnotnumber.length();i++){
        if(!isdigit(ifnotnumber[i]))
            digit=false;
    }
    if(!digit){
        opt=0;
    }
    else
        opt=stoi(ifnotnumber);
    
    return opt;
}

int Options2BUYER(){
    int opt=0;
    string ifnotnumber;
    bool digit=true;
    
    printline();
    cout<<"1. Account Info"<<endl;
    cout<<"2. Browse Item"<<endl;
    cout<<"99. QUIT"<<endl;
    printline();
    cout<<"Choose Action => ";
    cin>>ifnotnumber;

    for(int i=0;i<ifnotnumber.length();i++){
        if(!isdigit(ifnotnumber[i]))
            digit=false;
    }
    if(!digit){
        opt=0;
    }
    else
        opt=stoi(ifnotnumber);
    
    
    return opt;
}





int main(){

    ifstream file1("accinfo.txt");
    ifstream file2("marketplace.txt");
    if(!file1.is_open()){
        ofstream createfile1("accinfo.txt"); // ID USERNAME EMAIL PASSWORD ADDRESS PAYMENTMETHOD ACCTYPE
        createfile1<<"0 username email password \"address\" 0 acctype"<<endl;
        createfile1.close();
    }
    if(!file2.is_open()){
        ofstream createfile1("marketplace.txt");  //SELLER ITEMID ITEMNAME ITEMDESC PRICE QUANTITY
        createfile1<<"seller 0 \"name\" \"desc\" 00.00 0"<<endl;
        createfile1.close();
    }
    file1.close();
    file2.close();

    User localuser;
    int options;
    Product *item=new Product;
    localuser.addproduct(item);
    
    //MAINPAGE
    

    options=Options1();
    
    
    //PAGE 1 , LOOP until or login
    bool QUIT=false;
    bool loginstatus=false;
    do{

        emptyspace();
        if(options==1){
            localuser.Register();
        }
        if(options==2){
            loginstatus=localuser.Login();
        }
        
        
        if(options==99)
            QUIT=true;
            
        if(options!=99&&loginstatus==false)
            options=Options1();

    }while(QUIT==false&&loginstatus==false);


    //OPTIONS2 when already login,
    if(localuser.getacctype()=="BUYER"){
    
        Buyer localbuyer(localuser);
        options=Options2BUYER();
    
        do{
            emptyspace();
            if(options==1){
                
                localbuyer.AccountInfo();
            }
            if(options==2){
                localbuyer.BrowseItem(*item);
                
            }

            if(options==3){
                
            }

            if(options!=99){
                options=Options2BUYER();
            }
            if(options==99){
                QUIT=true;
            }
        
        }while(QUIT==false&&(options>0 && options<4));


    }

    if(localuser.getacctype()=="SELLER"){

    }

    return 0;
}
