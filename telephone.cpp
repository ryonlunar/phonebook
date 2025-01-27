#include <iostream>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "style.h"

using namespace std;

class Contact {
    public:
        Contact() : name(""), number(""), address(""), power("") {}
        Contact(string namaKontak, string nomorKontak, string alamatKontak, string powerKontak) : name(namaKontak), number(nomorKontak), address(alamatKontak), power(powerKontak) {}
        string getName() { return name; } 
        string getNumber() { return number; }
        string getAddress() { return address; }
        string getPower() { return power; }

        void setName(string newName) { name = newName; }
        void setNumber(string newNumber) { number = newNumber; }
        void setAddress(string newAddress) { address = newAddress; }
        void setPower(string newPower) { power = newPower; }
    private:
        string name;
        string number;
        string address;
        string power;
};

class PhoneBook {
    public:
        PhoneBook() {};
        void displayContacts(){
            cout << "Menampilkan daftar kontak.." << endl;
            const string border(50, '-');
            cout << YELLOW "+" << border << "+\n" << RESET;
            if(contact_count == 0){
                cout << "Kontak kosong" << endl;
            } else{
                for(int i = 0; i < contact_count; i++){
                    string name = to_string(i+1) + ". Nama : " + contact_list[i].getName();
                    string number = "Nomor :" + contact_list[i].getNumber();

                    int nameWidth = 30; 
                    int numberWidth = 60 - nameWidth - 2; 

                    cout << left << setw(nameWidth) << name
                         << left << setw(numberWidth) << number << endl;
                }
            }
            cout << YELLOW << "+" << border << "+\n" << RESET;
        };

        void addContact(){
            cout << "Menambahkan kontak.." << endl;
            string name, number, address, power;
            cout << "Silahkan tambahkan kontak yang ingin anda muat" << endl;
            userInput("Masukkan Nama kontak : ", &name, "name");
            userInput("Masukkan Nomor kontak : ", &number, "num");
            userInput("Masukkan Alamat kontak : ", &address, "addr");
            userInput("Masukkan Power kontak : ", &power, "power"); // asumsi power bisa berupa apa saja

            if(contact_count > 7) {
                string ans;
                cout << "Daftar kontak anda sudah penuh apakah anda ingin tetap menambah kontak? (y/n)" << endl;
                getline(cin,ans);
                if(ans == "y"){
                    deleteEarliestContact();
                    cout << "Kontak terlama telah dihapus" << endl;
                }
                else if (ans == "n"){
                    cout << "Tambah kontak dibatalkan" << endl;
                    return;
                }
                else {
                    cout << "Input tidak valid, Tambah kontak dibatalkan" << endl;
                    return;
                }
            }
            Contact tempContact(name,number,address,power);
            contact_list[contact_count] = tempContact;
            contact_count++;
            cout << BGREEN << "Kontak berhasil ditambahkan!" << RESET << endl;

        };

        void searchContact(){
            string name;
            if(contact_count == 0){
                cout << "Tidak ada yang bisa dicari" << endl;
            } else {
                cout << "Masukkan nama kontak yang ingin dicari : ";
                getline(cin,name);
                bool found = false;
                for(int i = 0; i < contact_count; i++){
                    if(contact_list[i].getName() == name){
                        displaySpecificContact(contact_list[i]);
                        found = true;
                    }
            }
            if(found == false){
                cout << "Tidak ada kontak dengan nama " << name << endl;
            }
            }
        };
        void deleteContact() {
            string name;
            if(contact_count == 0){
                cout << "Tidak ada yang bisa dihapus" << endl;
            }
            else {
                cout << "Masukkan nama kontak yang ingin dihapus : ";
                getline(cin,name);
                bool found = false;
                int del_index;
                for(int i = 0; i < contact_count; i++){
                    if(contact_list[i].getName() == name){
                        found = true;
                        del_index = i;
                    }
                }
        
                if(found){
                    for(int i = del_index; i < contact_count-1; i++){
                        contact_list[i] = contact_list[i+1];
                    }
                    contact_count--;
                    cout << BGREEN << "Kontak berhasil dihapus" << RESET << endl;
                }
                else {
                    cout << "Kontak tidak ditemukan" << endl;
                }
            }
        }

        void editContact(){
            string name;
            if(contact_count == 0){
                cout << "Tidak ada yang bisa diedit" << endl;
            }
            else {
                bool found = false;
                int index;
                for(int i = 0; i < contact_count; i++){
                    if(contact_list[i].getName() == name){
                        found = true;
                        index = i;
                    }
                }
        
                if(found){
                    string name, number, address, power;
                    displaySpecificContact(contact_list[index]);
                    cout << "Silahkan ubah atribut kontak anda" << endl;
                    userInput("Masukkan Nama kontak : ", &name, "name");
                    userInput("Masukkan Nomor kontak : ", &number, "num");
                    userInput("Masukkan Alamat kontak : ", &address, "addr");
                    userInput("Masukkan Power kontak : ", &power, "power"); // asumsi power bisa berupa apa saja

                    contact_list[index].setName(name);
                    contact_list[index].setNumber(number);
                    contact_list[index].setAddress(address);
                    contact_list[index].setPower(power);

                    cout << BGREEN << "Kontak berhasil diedit" << RESET << endl;
                }
                else {
                    cout << "Kontak tidak ditemukan" << endl;
                }
            }
        }

    private:
        Contact contact_list[8];
        int contact_count = 0;

        void displaySpecificContact(Contact contact){
            const string border(50, '-');

            cout << YELLOW << "+" << border << "+\n" << RESET;
            cout << "Nama : " << contact.getName() << endl;
            cout << "Nomor : " << contact.getNumber() << endl;
            cout << "Alamat : " << contact.getAddress() << endl;
            cout << "Power : " << contact.getPower() << endl;
            cout << YELLOW << "+" << border << "+\n" << RESET;
        };

        void userInput(string messages, string *input, string type){
            cout << messages;
            getline(cin, *input);
            if(type == "num"){
                while (!checkValidNumber(*input) || !checkLengthInput(*input, "num"))
                {
                    userInput(messages, input, "num");
                }
            }
            else if (type == "name"){
                while(!checkValidName(*input) || !checkLengthInput(*input, "name")){
                    userInput(messages, input, "name");
                }
            }
            else if(type == "power") {
                while(!checkEmptyInput(*input) || !checkLengthInput(*input, "power")){
                    userInput(messages, input, "power");
                }
            }
            else if(type == "addr") {
                while(!checkEmptyInput(*input) || !checkLengthInput(*input, "addr")){
                    userInput(messages, input, "addr");
                }
            }
        };

        bool checkLengthInput(string input, string type) {
            if(type == "name"  && input.length() > 20){
                cout << BRED << "Error : input nama tidak boleh lebih dari 20 karakter" << RESET << endl;
                return false;
            }
            else if(type == "num"  && (input.length() > 14 || input.length() < 8)){
                cout << BRED << "Error : input nomor hanya 8 hingga 13 karakter" << RESET << endl;
                return false;
            }
            else if(type == "addr" && input.length() > 50) {
                cout << BRED << "Error : input nomor tidak boleh lebih dari 50 karakter" << RESET << endl;
                return false;
            }
            else if(type == "power" && input.length() > 20) {
                cout << BRED << "Error : input power tidak lebih dari 20 karakter" << RESET << endl;
                return false;
            }
            return true;
        }

        bool checkEmptyInput(string input){
            if(input.empty()){
                cout << BRED << "Error : input tidak boleh kosong" << RESET << endl;
                return false;
            }
            return true;
        }

        bool checkValidName(string input){
            if(checkEmptyInput(input)){
                for(int i = 0; i < contact_count; i++){
                    if(contact_list[i].getName() == input){
                        cout << BRED << "Error : nama kontak sudah ada" << RESET << endl;
                        return false;
                    }
                }
                return true;
            }
            else{
                return false;
            }
        };

        bool isNumber(const string& str) {
            for (char c : str) {
                if (!isdigit(c)) {
                    cout << BRED << "Error : input harus berupa angka!" << RESET << endl;
                    return false;
                }
            }
            return true;
        }

        bool checkValidNumber(string input){
            return isNumber(input) && checkEmptyInput(input);
        };

        void deleteEarliestContact() {
            for(int i = 0; i < contact_count-1; i++){
                contact_list[i] = contact_list[i+1];
            }

            contact_count--;
        }
};

void displayMenu() {
    const string menuOptions[][2] = {
        {"ADD", "Untuk menambahkan Kontak"},
        {"SHOW", "Untuk melihat Kontak"},
        {"SEARCH", "Untuk mencari Kontak"},
        {"DELETE", "Untuk menghapus Kontak"},
        {"EDIT", "Untuk mengedit Kontak"},
        {"EXIT", "Untuk keluar dari program"}
    };

    const int menuWidth = 50; 
    const string border(menuWidth, '-');

    string paddingr(menuWidth / 2 - 4, ' ');
    string paddingl(menuWidth / 2 - 6, ' ');

    cout << YELLOW << "+" << border << "+\n" << RESET;
    cout << YELLOW << "|" << paddingl << WHITE << BLINK << BOLD << "PHONE BOOK" << RESET << YELLOW << paddingr << "|\n" << RESET;
    cout << YELLOW << "+" << border << "+\n" << RESET;

    for (int i = 0; i < 6; ++i) {
        string option = WHITE + to_string(i + 1) + ". " + menuOptions[i][0];
        string explanation = menuOptions[i][1] + YELLOW;

        int optionWidth = 22; 
        int explanationWidth = 60 - optionWidth - 2; 

        cout << YELLOW << "| " 
             << left << setw(optionWidth) << option
             << left << setw(explanationWidth) << explanation 
             << " |\n" << RESET;
    }

    cout << YELLOW << "+" << border << "+\n" << RESET;
    cout << "Masukkan pilihan Anda (contoh: ADD): ";
}

void menuTitle(string name){
    int totalLength = 50;
    int paddingTotal = totalLength - 2 - name.length();
    int paddingl = paddingTotal / 2;
    int paddingr = paddingTotal - paddingl;

    string paddingLeft(paddingl, '-');
    string paddingRight(paddingr, '-');

    cout << YELLOW << "<" << paddingLeft << WHITE << BOLD << ' ' << name << ' '<< RESET << YELLOW << paddingRight << ">\n" << RESET;
}

int main(){
    PhoneBook phonebook;
    string input;
    while(true){
        displayMenu();
        getline(cin,input);
        cout << endl;
        if(input == "ADD"){
            menuTitle("ADD");
            phonebook.addContact();
        }
        else if(input == "SEARCH"){
            menuTitle("SEARCH");
            phonebook.displayContacts();
            phonebook.searchContact();
        }
        else if(input == "DELETE"){
            menuTitle("DELETE");
            phonebook.displayContacts();
            phonebook.deleteContact();
        }
        else if(input == "SHOW"){
            menuTitle("SHOW");
            phonebook.displayContacts();
        }
        else if(input == "EDIT"){
            menuTitle("EDIT");
            phonebook.displayContacts();
            phonebook.editContact();
        }
        else if(input == "EXIT"){
            cout << BYELLOW << BLACK << BLINK <<  " Terima kasih telah menggunakan PhoneBook! " << RESET << endl;
            break;
        }
        else{
            cout << "Input tidak valid" << endl;
        }
        
        string temp;
        cout << "Ketik apapun untuk melanjutkan" << endl;
        getline(cin,temp);
        system("cls");
    }
}
