#include <iostream>
#include <vector>
#include <string>
#include<bits/stdc++.h>


using namespace std;

class Patient {
private:
    vector<string> ailment;
    string firstName, middleName, lastName, suffix, doctor;
    int treated, priority;

public:
        string toString() const {
            string ill;
            for(string ail: ailment) {
                auto iter= find(ailment.begin(), ailment.end(), ail);
                if(distance(ailment.begin(), iter) == ailment.size() - 1)
                    ill += ail;
                else
                    ill += ail + ", ";
            }

            return ("Name: " + firstName + " " + middleName + " " + lastName + "\n" +
                    "Suffix: " + suffix + "\n" +
                    "Doctor: " + doctor + "\n" +
                    "Ailment: " + ill + "\n" +
                    "Priority: " + to_string(priority) + "\n" +
                    "Treated: " +  to_string(treated)
            );
        }

        string fullName () const{
            return (firstName + " " + middleName + " " + lastName + " ");
        }
        string fullNameFancy () const{
            return ("Patient: \"" + firstName + " " + middleName + " " + lastName + "\"");
        }

        Patient(vector<string> patient) {
        ///search for variable name > set the corr info to this
        for(string info: patient) {
            string substring = info.substr(info.find(":") +1);
            switch (info.front()) {
                case 'f' :
                case 'F' :
                    firstName = substring;
                    break;
                case 'm' :
                case 'M' :
                    middleName = substring;
                    break;
                case 'l' :
                case 'L' :
                    lastName = substring;
                    break;
                case 's' :
                case 'S' :
                    if(substring.length() == 0)
                        suffix = "-";
                    else
                        suffix = substring;
                    break;
                case 'a' :
                case 'A' :
                    if(info.front() == 'a' || info.front() == 'A')
                        ailment.push_back(substring);
                    break;
                case 'd' :
                case 'D' :
                    doctor = substring;
                    break;
                case 't' :
                case 'T' :
                    try {
                        treated = stoi(info.substr(info.find(":") +1));
                    }
                    catch (const std::invalid_argument& ia) {
                        //std::cerr << "Invalid argument: " << ia.what() << '\n';
                    }
                    break;
                case 'p':
                case 'P':
                    try {
                        priority = stoi(info.substr(info.find(":") +1));
                    }
                    catch (const std::invalid_argument& ia) {
                        //std::cerr << "Invalid argument: " << ia.what() << '\n';
                    }
                    break;
            }
        }
    }
    const string &getFirstName() const {
        return firstName;
    }

    void setFirstName(const string &firstName) {
        Patient::firstName = firstName;
    }

    const string &getMiddleName() const {
        return middleName;
    }

    void setMiddleName(const string &middleName) {
        Patient::middleName = middleName;
    }

    const string &getLastName() const {
        return lastName;
    }

    void setLastName(const string &lastName) {
        Patient::lastName = lastName;
    }

    const string &getSuffix() const {
        return suffix;
    }

    void setSuffix(const string &suffix) {
        Patient::suffix = suffix;
    }

    const vector<string> &getAilment() const {
        return ailment;
    }

    void setAilment(const vector<string> &ailment) {
        Patient::ailment = ailment;
    }


    const string &getDoctor() const {
        return doctor;
    }

    void setDoctor(const string &doctor) {
        Patient::doctor = doctor;
    }

    int getTreated() const {
        return treated;
    }

    void setTreated(int treated)  {
        Patient::treated = treated;
    }

    int getPriority() const {
        return priority;
    }

    void setPriority(int priority) {
        Patient::priority = priority;
    }

};

