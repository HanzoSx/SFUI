#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;
int main(){
    bool flag =true;
    ifstream fout;
        fout.open("data.CSV",ios::in);

        string b[40],c[40];
        string line;
        while(getline(fout,line)){
            stringstream ss(line);
            int k = 0;
            ss>>k;
            ss>>b[k]>>c[k];
        }
        fout.close();
    ofstream out;
    out.open("out.txt",ios::out);
    while(flag){
        cout<<"plesase choose the item follows"<<endl;
        cout<<"1.sword 2.pickaxe 3.shovel 4.axe 5.helmet 6.chestplate 7.leggings 8.boots 9.others"<<endl;
        int item = 0;
        cin>>item;
        if(item==0){break;}
        string name=" ";
        if (item==9){
            cout<<"please input the name of this item"<<endl;
            cin>>name;
        }
        string a[10] = {"","sword","pickaxe","shovel","axe","helmet","chestplate","leggings","boots",name};
        cout<<"please choose the needed one"<<endl;
        if(item==1){
            for(int i=12;i<19;i++){
                cout<<i<<" "<<b[i]<<" "<<c[i]<<endl;
            }
            cout<<"33"<<" "<<b[33]<<" "<<c[33]<<endl;
            cout<<"37"<<" "<<b[37]<<" "<<c[37]<<endl;
        }
        else if(item<4){
            for(int i=33;i<38;i++){
                cout<<i<<" "<<b[i]<<" "<<c[i]<<endl;
            }
        }
        else if(item==5){
            cout<<"0"<<" "<<b[0]<<c[0]<<endl;
            cout<<"1"<<" "<<b[1]<<c[1]<<endl;
            for(int i=3;i<7;i++){
                cout<<i<<" "<<b[i]<<" "<<c[i]<<endl;
            }
            cout<<"8"<<" "<<b[8]<<c[8]<<endl;
            cout<<"33"<<" "<<b[33]<<" "<<c[33]<<endl;
            cout<<"37"<<" "<<b[37]<<" "<<c[37]<<endl;
        }
        else if(item==6){
            cout<<"0"<<" "<<b[0]<<c[0]<<endl;
            cout<<"1"<<" "<<b[1]<<c[1]<<endl;
            for(int i=3;i<6;i++){
                cout<<i<<" "<<b[i]<<" "<<c[i]<<endl;
            }
            cout<<"33"<<" "<<b[33]<<" "<<c[33]<<endl;
            cout<<"37"<<" "<<b[37]<<" "<<c[37]<<endl;
        }
        else if(item ==7){
            cout<<"0"<<" "<<b[0]<<c[0]<<endl;
            cout<<"1"<<" "<<b[1]<<c[1]<<endl;
            for(int i=3;i<6;i++){
                cout<<i<<" "<<b[i]<<" "<<c[i]<<endl;
            }
            cout<<"11"<<" "<<b[11]<<c[11]<<endl;
            cout<<"33"<<" "<<b[33]<<" "<<c[33]<<endl;
            cout<<"37"<<" "<<b[37]<<" "<<c[37]<<endl;
        }
        else if(item==8){
            for(int i=0;i<6;i++){
                cout<<i<<" "<<b[i]<<" "<<c[i]<<endl;
            }
            cout<<"7"<<" "<<b[7]<<c[7]<<endl;
            cout<<"9"<<" "<<b[9]<<" "<<c[9]<<endl;
            cout<<"10"<<" "<<b[10]<<" "<<c[10]<<endl;
            cout<<"11"<<" "<<b[11]<<c[11]<<endl;
            cout<<"33"<<" "<<b[33]<<" "<<c[33]<<endl;
            cout<<"37"<<" "<<b[37]<<" "<<c[37]<<endl;
        }
        else{
            for(int i=0;i<40;i++){
                cout<<i<<" "<<b[i]<<" "<<c[i]<<endl;
            }
        }
        int magicname=0;
        string magicpower;



        if(item<9){
            out<<"/give @p minecraft:netherite_";
            out<<a[item];
            out<<"{Enchantments:[";
            cin.ignore();
            getline(cin,line);
            stringstream sw(line);
            sw>>magicname;
            sw>>magicpower;
            out<<"{id:";
            out<<b[magicname];
            out<<",lvl:";
            out<<magicpower;
            out<<"s}";
            while(sw>>magicname){
                out<<",";
                sw>>magicpower;
                out<<"{id:";
                out<<b[magicname];
                out<<",lvl:";
                out<<magicpower;
                out<<"s}";
            }
            out<<"]} 1";
        }
        if(item==9){
            out<<"/give @p minecraft:";
            out<<a[item];
            out<<"{Enchantments:[";
            cin.ignore();
            getline(cin,line);
            stringstream sw(line);
            sw>>magicname;
            sw>>magicpower;
            out<<"{id:";
            out<<b[magicname];
            out<<",lvl:";
            out<<magicpower;
            out<<"s}";
            while(sw>>magicname){
                out<<",";
                sw>>magicpower;
                out<<"{id:";
                out<<b[magicname];
                out<<",lvl:";
                out<<magicpower;
                out<<"s}";
            }
            out<<"]} 1";
        }

    }
    out.close();
    return 0;
}