#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include<ctime>
#include <chrono>
#include <cstdlib>
#include <exception>
#include "Patient.cpp"


using namespace std;

class Compare
{
public:
    bool operator() (const Patient& z, const Patient& y)
    {
        return z.getPriority() > y.getPriority();
    }
};

class User {

private:
    string access;
    bool debug;
    priority_queue<Patient, vector<Patient>, Compare> patients, treated;
    ofstream outFileLogger;
    ofstream outFileReport;

public:
    void separatePatients() {
        priority_queue<Patient, vector<Patient>, Compare> list = patients;
        vector<Patient> listSave;
        int i = 0;
        while(!list.empty()) {
            if(list.top().getTreated() == 1) {
                treated.push(list.top());
                patients.pop();
            }
            else {
                listSave.push_back(list.top());
            }
            list.pop();
        }
        while(!patients.empty())
            patients.pop();
        for(Patient& p: listSave)
            patients.push(p);

    }
    void clearReport() {
        string fileName;
        cout << "PLEASE ENTER FILE NAME YOU WOULD LIKE TO CLEAR:";
        cin.ignore();
        getline(cin,fileName);

        outFileReport.open(fileName);
        if (!outFileReport.is_open()) {
            cout << "\nERROR OPENING FILE\n";
            return;
        }

        string s;
        while(!outFileReport.eof() && outFileReport.bad()) {
            outFileReport << "";
        }
        outFileReport.close();
        cout << "\nFILE SUCCESSFULLY CLEARED!\n";
    }
    void clearLogger() {
        outFileLogger.open(R"(C:\Users\Girma Admasu\Desktop\NKU_CSC\Hospital\example.txt)");
        string s;
        while(!outFileLogger.eof() && outFileLogger.bad()) {
            outFileLogger << "";
        }
        outFileLogger.close();
    }

    void setAccess(string a) {
        try {
            int x = stoi(a);
        }
        catch (exception e) {
            cout << "\nPLEASE ENTER A NUMBER!\n" << endl;
            return;
        }
        access = a;
        methodCalled(this->access);
        logger(debug);
    }

    void methodCalled(string bb) {
        int b = stoi(bb);
        switch (b) {
            default:
                cout << "-----PLEASE ENTER A NUMBER PRESENT IN THIS LIST----\n\n";
                break;
            case -3:
                clearReport();
                break;
            case -2:
                break;
            case -1:
                clearLogger();
                break;
            case 0:
                clearLogger();
                break;
            case 1:
                add();
                break;
            case 2:
                addFromFile();
                break;
            case 3:
                treat();
                break;
            case 4:
                patientReport();
                break;
            case 5:
                allPatientsReport();
                break;
            case 6:
                treatedPatientsReport();
                break;
            case 7:
                next();
                break;
            case 8:
                treatAll();
                break;
            case 9:
                printByDoc();
                break;
            case 10:
                debugMode();
                break;
        }
    }

    ///FUNCTION: * SLEEP FOR SOME SECONDS * ADD PATIENT TO TREATED * POP PATIENT
    void logger(bool b = false) {
        int i = 0;
        int a = stoi(access);
        outFileLogger.open(R"(C:\Users\Girma Admasu\Desktop\NKU_CSC\Hospital\example.txt)", ios::app);
        vector<string> addStr = {
                "METHOD CALL: add()\n", "INSIDE add() METHOD\n"
                "***THE METHOD WORKS LIKE THIS***\n"
                  "\t- IT CREATES VECTOR OF STRINGS TO HOLD THE PROMPTS(firstname, middlename, ...) \n"
                  "\t\tAND ANOTHER VECTOR TO HOLD PATIENT-INFO\n"
                  "\t- THEN IT ITERATES THROUGH THAT VECTOR OF PROMPTS, PROMPTING THE USER TO GIVE AN ANSWER TO THE PROMPT\n"
                  "\t- IT THEN TAKES THE PROMPT ADDS IN A ':' AND THEN ADDS THE ANSWER TO CREATE A SINGLE STRING\n"
                  "\t- STRING IS PASSED INTO PATIENT-INFO VECTOR\n"
                "***STEPS***\n",
                "\t* ASK USER FOR PATIENT INFORMATION\n",
                "\t* FOR EACH PROMPT\n",
                "\t* IF PROMPT IS 'AILMENT'\n"
                "\t\t\t>> ASK USER TO INPUT NUMBER OF AILMENTS,\n"
                "\t\t\t>> ENTER ANOTHER FOR LOOP TILL NO_OF_AILMENTS IS REACHED,\n"
                "\t\t\t>> EACH TIME TAKE IN AILMENT AS STRING AND PUSH BACK TO PATIENT-INFO VECTOR.\n",
                "\t* ELSE\n"
                "\t\t\t>> ASK USER TO INPUT ANSWER OF PROMPT,\n"
                "\t\t\t>> TAKE ANSWER AND PUSHBACK AFTER CONCATENATING IT WITH PROMPT AND ':' "
        };
        vector<string> addFromFileStr = {
             "METHOD CALL: addFromFile()\n", "INSIDE addFromFile() METHOD:\n", "\t* GET FILENAME FROM USER\n",
             "\t* PASS FILENAME TO THE ifstream() METHOD\n", "\t* CREATE VECTOR OF STRINGS TO HOLD PATIENT INFORMATION AS STRING\n",
             "\t* WHILE (CHECK FOR SUCCESS OF getline(...)) THE RETURN TYPE IS CONVERTED TO BOOL BY IMPLICIT CONVERSION\n"
             "\t\t\t>> READ A LINE USING GETLINE AND STORE IN STRING 'X'"
             "\n\t\t\t>> IF EMPTY LINE IS READ OR EOF:\n"
             "\t\t\t\tTHEN CREATE A NEW PATIENT WITH THE VECTOR AND PASS THAT INTO THE GLOBAL PATIENT LIST"
    };
    vector<string> treatStr = {
             "METHOD CALL: treat()\n", "INSIDE treat() METHOD:\n", "\t* CATCH ERROR IF QUEUE IS EMPTY\n",
           "\t* SLEEP FOR SOME SECONDS\n", "\t* GET THE PATIENT ON TOP AND set Treated to '1' \n",
           "\t* ADD PATIENT TO TREATED * POP PATIENT\n"
    };

    vector<string> patientReportStr = {
            "METHOD CALL: patientReport()\n", "INSIDE patientReport() METHOD:\n", "\t* CATCH ERROR IF QUEUE IS EMPTY\n",
            "\t* COPY PATIENT LIST\n", "\t* ASK FOR FULL NAME OF PATIENT THAT THE USER WANTS A REPORT OF (OFC USE A FOR LOOP TO BE FANCY)\n",
            "\t* GET THE FULL NAME OF PATIENT AT THE TOP OF QUEUE\n",
            "\t* WHILE(INPUT_NAME != QUEUE.TOP()_NAME) \n"
            "\t\t\t>> POP PATIENT FROM COPY QUEUE\n"
            "\t\t\t>> GET THE FULL NAME OF PATIENT AT THE TOP OF QUEUE\n",
            "\t* OUTSIDE WHILE() LOOP:\n",
            "\t* IF QUEUE IS EMPTY\n"
            "\t\tTHEN TELL USER THERE IS NO PATIENT WITH THAT NAME\n",
            "* ELSE\n"
            "\t\tCOUT << PATIENT NAME (FLEX A BIT HERE WITH THE PRINTING)\n"
    };
    vector<string> allPatientsReportStr = {
            "METHOD CALL: allPatientsReport()\n", "INSIDE allPatientsReport() METHOD:\n", "\t* CATCH ERROR IF QUEUE IS EMPTY\n",
            "\t* COPY PATIENT LIST\n", "\t* ASK USER FOR CONSOLE/FILE OUTPUT\n",
            "\t* IF CONSOLE\n"
            "\t** WHILE COPY_QUEUE IS NOT EMPTY\n"
            "\t\t>> GET TOP PATIENT, CALL 'toString' ON IT(FOR FANCY PRINT) AND COUT\n"
            "\t\t>> POP PATIENT\n",
            "\t* ELSE\n"
            "\t** ASK FOR FILE PATH AND OPEN FILE\n"
            "\t** WHILE COPY_QUEUE IS NOT EMPTY\n"
            "\t\t>> GET TOP PATIENT, CALL 'toString' ON IT(FOR FANCY PRINT) AND OUTSTREAM TO FILE\n"
            "\t\t>> POP PATIENT"
    };
    vector<string> treatedPatientsReportStr = {
            "METHOD CALL: treatedPatientsReport()\n", "INSIDE treatedPatientsReport() METHOD:\n", "\t* CATCH ERROR IF QUEUE IS EMPTY\n",
            "\t* COPY PATIENT LIST\n", "\t* ASK USER FOR CONSOLE/FILE OUTPUT\n",
            "\t* IF CONSOLE\n"
            "\t** WHILE COPY_QUEUE IS NOT EMPTY\n"
            "\t\t>> GET TOP PATIENT, CALL 'toString' ON IT(FOR FANCY PRINT) AND COUT\n"
            "\t\t>> POP PATIENT\n",
            "\t* ELSE\n"
            "\t** ASK FOR FILE PATH AND OPEN FILE\n"
            "\t** WHILE COPY_QUEUE IS NOT EMPTY\n"
            "\t\t>> GET TOP PATIENT, CALL 'toString' ON IT(FOR FANCY PRINT) AND OUTSTREAM TO FILE\n"
            "\t\t>> POP PATIENT"
    };
    vector<string> nextStr = {
            "METHOD CALL: next()\n", "INSIDE next() METHOD:\n", "\t* CATCH ERROR IF QUEUE IS EMPTY\n",
            "\t* COPY PATIENT-TRIAGE\n", "\t* GET TRIAGE.TOP() AND COUT WITH 'toString'\n","\t* POP PATIENT\n",
    };
    vector<string> treatAllStr = {
            "METHOD CALL: treatAll()\n", "INSIDE treatAll() METHOD:\n", "\t* CATCH ERROR IF QUEUE IS EMPTY\n",
            "\t* WHILE(GLOBAL PATIENT LIST IS NOT EMPTY)\n"
            "\t\t>> SLEEP FOR SOME SECONDS\n"
            "\t\t>> GET THE PATIENT ON TOP AND set Treated to '1'\n"
            "\t\t>> PUSH THE TOP PATIENT ONTO GLOBAL TREATED QUEUE\n"
            "\t\t>>  POP PATIENT\n"
    };
    vector<string> printByDocStr = {
                "METHOD CALL: printByDoc()\n", "INSIDE printByDoc() METHOD:\n", "\t* CATCH ERROR IF QUEUE IS EMPTY\n",
                "\t* CREATE A list<vector<string>> TO HOLD DOCTOR NAMES AND A vector<Patient> TO HOLD ALL PATIENT INFO\n"
                "\t* WHILE(PQ OF PATIENT LIST NOT EMPTY)\n"
                "\t\t\t>> ADD DOCTOR NAME TO list<vector<string> AND PATIENT INFO TO vector<Patient>\n"
                "\t\t\t>> POP PATIENT FROM PQ\n",
                "\t* ORDER LIST BY DOC NAME WITH A FUNCTOR\n",
                "\t* CALL THE SORT() METHOD ON LIST WITH BINARY PREDICATE WE DEFINED\n",
                "\t* CALL THE unique() METHOD ON LIST WITH BINARY PREDICATE WE DEFINED\n",
                "\t* INSIDE FOR LOOP THAT RUNS FROM list.begin till list.end WITH AN ITERATOR\n"
                "\t\t\t>> GET NAME OF DOCTOR FOR THE ITERATOR AND SAVE TO STRING 'doc' FOR INSTANCE\n"
                "\t\t\t>> INSIDE SECOND FOR EACH LOOP\n"
                "\t\t\t\t- IF DOC OF PATIENT IS SAME AS STRING 'doc'\n"
                "\t\t\t\t\t> THEN PUSHBACK PATIENT.TOSTRING TO THIS DOCTOR'S VECTOR\n",
                "\t* WHEN DONE PRINT EVERYTHING WITH A FOR EACH"
        };

        if(b) {
            switch (a) {
                case -3:
                    //USER MANUAL
                    break;
                case -2:
                    cout << "\nLOGGER SUCCESSFULLY SAVED!!!\n";
                    break;
                case -1:
                    cout << "LOGGER SUCCESSFULLY CLEARED!!!\n";
                    break;
                case 0:
                    break;
                case 1:
                    cout << endl;
                    for(const string& log: addStr)
                        cout << "LOG " << ++i << ": " << log;
                    cout << endl;
                    break;
                case 2:
                    cout << endl;
                    for(const string& log: addFromFileStr)
                        cout << "LOG " << ++i << ": " << log;
                    cout << endl;
                    break;
                case 3:
                    cout << endl;
                    for(const string& log: treatStr)
                        cout << "LOG " << ++i << ": " << log;
                    cout << endl;
                    break;
                case 4:
                    cout << endl;
                    for(const string& log: patientReportStr)
                        cout << "LOG " << ++i << ": " << log;
                    cout << endl;
                    break;
                case 5:
                    cout << endl;
                    for(const string& log: allPatientsReportStr)
                        cout << "LOG " << ++i << ": " << log;
                    cout << endl;
                    break;
                case 6:
                    cout << endl;
                    for(const string& log: treatedPatientsReportStr)
                        cout << "LOG " << ++i << ": " << log;
                    cout << endl;
                    break;
                case 7:
                    cout << endl;
                    for(const string& log: nextStr)
                        cout << "LOG " << ++i << ": " << log;
                    cout << endl;
                    break;
                case 8:
                    cout << endl;
                    for(const string& log: treatAllStr)
                        cout << "LOG " << ++i << ": " << log;
                    cout << endl;
                    break;
                case 9:
                    cout << endl;
                    for(const string& log:  printByDocStr)
                        cout << "LOG " << ++i << ": " << log;
                    cout << endl;
                    break;
                case 10:
                    cout << "IN DEBUG MODE!\n\n";
            }
        }
        else {
            switch (a) {
                default:
                    outFileLogger << "\nLOG 0: NO METHOD CALLED\n\n";
                    break;
                case -3:
                    outFileLogger << "\nCLEAR REPORT WAS CALLED\n\n";
                case -2:
                    outFileLogger << "\nLOGGER SUCCESSFULLY SAVED!!!\n";
                    break;
                case -1:
                    outFileLogger << "LOGGER SUCCESSFULLY CLEARED!!!\n";
                    break;
                case 0:
                    break;
                case 1:
                    outFileLogger << endl;
                    for(const string& log: addStr)
                        outFileLogger << "LOG " << ++i << ": " << log;
                    outFileLogger << endl;
                    break;
                case 2:
                    outFileLogger << endl;
                    for(const string& log: addFromFileStr)
                        outFileLogger << "LOG " << ++i << ": " << log;
                    outFileLogger << endl;
                    break;
                case 3:
                    outFileLogger << endl;
                    for(const string& log: treatStr)
                        outFileLogger << "LOG " << ++i << ": " << log;
                    outFileLogger << endl;
                    break;
                case 4:
                    outFileLogger << endl;
                    for(const string& log: patientReportStr)
                        outFileLogger << "LOG " << ++i << ": " << log;
                    outFileLogger << endl;
                    break;
                case 5:
                    outFileLogger << endl;
                    for(const string& log: allPatientsReportStr)
                        outFileLogger << "LOG " << ++i << ": " << log;
                    outFileLogger << endl;
                    break;
                case 6:
                    outFileLogger << endl;
                    for(const string& log: treatedPatientsReportStr)
                        outFileLogger << "LOG " << ++i << ": " << log;
                    outFileLogger << endl;
                    break;
                case 7:
                    outFileLogger << endl;
                    for(const string& log: nextStr)
                        outFileLogger << "LOG " << ++i << ": " << log;
                    outFileLogger << endl;
                    break;
                case 8:
                    outFileLogger << endl;
                    for(const string& log: treatAllStr)
                        outFileLogger << "LOG " << ++i << ": " << log;
                    outFileLogger << endl;
                    break;
                case 9:
                    outFileLogger << endl;
                    for(const string& log:  printByDocStr)
                        outFileLogger << "LOG " << ++i << ": " << log;
                    outFileLogger << endl;
                    break;
            }
        }
        outFileLogger.close();
    }

    void debugMode() {
        debug = true;
    }
    static bool compDoc(const Patient& a, const Patient& b)
    {
        return a.getDoctor() == b.getDoctor();
    }
    static bool compDocSort(const Patient& a, const Patient& b)
    {
        return a.getDoctor() == b.getDoctor();
    }
    ///FUNCTION: * CATCH ERROR
    void printByDoc() {
        try {
            if(patients.empty())
                throw -1;
        }
        catch (int n) {
            cout << "ERROR " << n << ": PRIORITY QUEUE IS EMPTY, PLEASE ADD PATIENTS FIRST\n\n";
            return;
        }
        priority_queue<Patient, vector<Patient>, Compare> triageByDoc = patients;
        list<vector<string>> doctorNames;
        vector<Patient> patientInfo;
        vector<string> last;

        while(!triageByDoc.empty()) {
            Patient top = triageByDoc.top();
            vector<string> docVector = {top.getDoctor()};
            if(triageByDoc.size() == 1)
                last = docVector;

            doctorNames.push_back(docVector);
            patientInfo.push_back(top);
            triageByDoc.pop();
        }
            doctorNames.sort(compDocSort);
            doctorNames.unique(compDoc);
            doctorNames.push_back(last);

        for (auto & doctorName : doctorNames) {
            string doc = doctorName.at(0);
            cout << "DOCTOR: "<< doc << endl;
            cout << "----------------------" << endl;
            for(const Patient& patient: patientInfo) {
                if(patient.getDoctor() == doc) {
                    cout << patient.toString() <<endl <<endl;
                }
            }
            cout << endl;
        }

    }



    ///FUNCTION: * CATCH ERROR IF QUEUE IS EMPTY * SLEEP FOR SOME SECONDS * ADD PATIENT TO TREATED * POP PATIENT
    void treat() {
        try {
            if(patients.empty()) {
                throw -1;
            }
        }
        catch(int n) {
            cout << "ERROR " << n << ": PRIORITY QUEUE IS EMPTY, PLEASE ADD PATIENTS FIRST\n\n";
            return;
        }

        srand(time(0));
        int random = (rand() % 3) + 1;
        this_thread::sleep_for(chrono::milliseconds (random * 1000));

        Patient top = patients.top();
        top.setTreated(1);
        treated.push(top);
        cout << patients.top().fullNameFancy() << " HAS BEEN TREATED!" << endl << endl;
        patients.pop();
    }

    ///FUNCTION: * SLEEP FOR SOME SECONDS * ADD PATIENT TO TREATED * POP PATIENT * LOOP TILL TRIAGE IS EMPTY
    void treatAll() {
        try {
            if(patients.empty()) {
                throw -1;
            }
        }
        catch(int n) {
            cout << "ERROR " << n << ": PRIORITY QUEUE IS EMPTY, PLEASE ADD PATIENTS FIRST\n\n";
            return;
        }

        srand(time(0));
        cout << "TREATING PATIENTS . . ." << endl;
        while (!patients.empty()) {
            int random = (rand() % 3) + 1;
            this_thread::sleep_for(chrono::milliseconds ((random) * 1000));

            Patient top = patients.top();
            top.setTreated(1);
            treated.push(top);
            patients.pop();
        }
        cout << "SUCCESS: ALL PATIENTS HAVE BEEN TREATED!!!" << endl << endl;

    }

    ///FUNCTION: * COPY TRIAGE * POP FROM 'FAKE' PATIENT LIST * COUT THE TOP PATIENT
    void next() {
        try {
            if(patients.empty()) {
                throw -1;
            }
        }

        catch(int n) {
            cout << "ERROR " << n << ": PRIORITY QUEUE IS EMPTY, PLEASE ADD PATIENTS FIRST\n\n";
            return;
        }

        priority_queue<Patient, vector<Patient>, Compare> triage = patients;
        cout << "NEXT PATIENT TO BE TREATED IS:" << endl;
        cout << "----------------------------" << endl;
        cout << triage.top().toString()  << endl << endl;
        triage.pop();
    }

    ///FUNCTION: * COPY PATIENT LIST * ASK FOR NAME OF PATIENT THAT THE USER WANTS A REPORT OF
    /// - IN LOOP * CHECK IF NAME OF PATIENT IN LIST IS THE NAME REQUIRED * IF YES RETURN - ELSE POP AND LOOP
    void patientReport() {
        try {
            if(patients.empty()) {
                throw -1;
            }
        }
        catch(int n) {
            cout << "ERROR " << n << ": PRIORITY QUEUE IS EMPTY, PLEASE ADD PATIENTS FIRST\n\n";
            return;
        }

        priority_queue<Patient, vector<Patient>, Compare> triage = patients;
        vector<string> labels {"firstName" , "middleName", "lastName"};

        cout << "PLEASE ENTER THE FULL NAME OF THE PATIENT YOU WANT:" <<endl;
        string fullName, answer, patientName;
        for(const string& label: labels) {
            cout << label <<":";
            cin >> answer;
            fullName += answer + " ";
            answer = "";
        }

        patientName = triage.top().fullName();
        while (fullName != patientName && !triage.empty()) {
            triage.pop();
            patientName = triage.top().fullName();
        }
        if(triage.empty())
            cout << "THERE IS NO PATIENT NAMED " << fullName << endl <<endl;
        else {
            cout << endl;
            cout << "HERE IS " << triage.top().fullNameFancy() << "s INFORMATION" << endl;
            cout << "--------------------------------------------" << endl;

            cout << triage.top().toString() << endl <<endl;
        }

    }

    ///FUNCTION: * COPY TRIAGE TO LOCAL TRIAGE * CHECK IF EMPTY * IF NOT PRINT THE INFORMAITON OF FIRST PATIENT * POP FROM LOCAL TRIAGE* LOOP
    void allPatientsReport() {
        try {
            if (patients.empty()) {
                throw -1;
            }
        }
        catch (int n) {
            cout << "ERROR " << n << ": PRIORITY QUEUE IS EMPTY, PLEASE ADD PATIENTS FIRST\n\n";
            return;
        }
        int onConsole;
        priority_queue<Patient, vector<Patient>, Compare> triage = patients;

        cout << "WOULD YOU LIKE THE OUTPUT ON CONSOLE(0/1)?:";
        cin >> onConsole;

        if (onConsole) {
            cout << "\nHERE IS A LIST OF ALL PATIENTS YOUR REQUESTED:" << endl;
            cout << "----------------------------------------------" << endl;
            while (!triage.empty()) {
                cout << triage.top().toString() << endl << endl;
                triage.pop();
            }
        }
        else {
            string fileName;
            cout << "PLEASE ENTER FILE PATH YOU WANT TO WRITE TO:";
            cin.ignore();
            getline(cin,fileName);
            cout << endl;

            ofstream file(fileName);
            if (!file.is_open()) {
                cout << "\nERROR OPENING FILE\n";
                return;
            }

            file << "HERE IS A LIST OF ALL PATIENTS YOUR REQUESTED: " << endl << endl;
            while (!triage.empty()) {
                file << triage.top().toString() << endl << endl;
                triage.pop();
            }

        }
    }
    ///FUNCTION: * COPY GLOBAL TREATED_PATIENT_LIST TO LOCAL TREATED LIST *PRINT PATIENT AT TOP *POP *LOOP TILL LOCAL TREATED IS EMPTY
    void treatedPatientsReport() {
        try {
            if(treated.empty()) {
                throw -1;
            }
        }
        catch(int n) {
            cout << "ERROR " << n << ": TREATED PATIENTS LIST IS EMPTY, PLEASE TREAT PATIENTS FIRST!!!\n\n";
            return;
        }

        int onConsoleT;
        priority_queue<Patient, vector<Patient>, Compare> localTreated = treated;

        cout << "WOULD YOU LIKE THE OUTPUT ON CONSOLE(0/1)?:";
        cin >> onConsoleT;

        if (onConsoleT) {
            cout << "\nHERE IS A LIST OF ALL TREATED PATIENTS YOUR REQUESTED:";
            cout << "\n----------------------------------------------------" << endl;
            while (!localTreated.empty()) {
                cout << localTreated.top().toString() << endl << endl;
                localTreated.pop();
            }
        }
        else {
            string fileName;
            cout << "PLEASE ENTER FILE PATH YOU WANT TO WRITE TO:";
            cin.ignore();
            getline(cin,fileName);

            ofstream fileT(fileName);
            if (!fileT.is_open()) {
                cout << "\nERROR OPENING FILE\n";
            }

            fileT << "HERE IS A LIST OF ALL TREATED PATIENTS YOUR REQUESTED: " << endl << endl;
            while (!localTreated.empty()) {
                fileT << localTreated.top().toString() << endl << endl;
                localTreated.pop();
            }

        }
    }

    ///FUNCTION: *
    void add() {
        int numAil;
        vector<string> patientInfo;
        vector<string> labels {"firstName" , "middleName", "lastName", "suffix", "doctor", "ailment", "treated[0/1]", "priority"};
        string answer, no_of_ailments;

        cout << "ENTER PATIENT INFORMATION BELOW\n";
        cin.ignore();
        for(string label: labels) {
            if(label =="ailment"){
                cout << "ENTER NUMBER OF AILMENTS(0-10):";
                bool except;
                do {
                    getline(cin, no_of_ailments);
                    try {
                        numAil = stoi(no_of_ailments);
                        except = false;
                    } catch (exception e) {cout << "\nPLEASE ENTER A NUMBER(0-10):"; except = true;}
                } while(except);

                for (int i = 0; i < numAil; i++) {
                    cout << label << " " << i << ":";
                    getline(cin, answer);
                    patientInfo.push_back(label + ":"  + answer);
                    answer = "";
                }
            }
            else {
                cout << label <<":";
                getline(cin, answer);
                patientInfo.push_back(label + ":"  + answer);
            }
        }
        ///call constructor on patient info
        /// push Patient object to GLOBAL patients array
        patients.push(*new Patient(patientInfo));
        cout << "\nSUCCESS: A PATIENT HAS BEEN ADDED\n\n";
        separatePatients();
    }

    ///FUNCTION: *
    void addFromFile() {
        ///take input from file-IO-infinite loop
        ///create vector of patients
        string fileName, x, afterColonTreated;
        cout << "PLEASE ENTER FILE DIRECTORY:";
        cin.ignore();
        getline(cin, fileName);

/*
C:\Users\Girma Admasu\Desktop\NKU_CSC\Hospital\patients.txt
 */
        ifstream myFile(fileName);

        if (!myFile.is_open()) {
            cout << "\nERROR OPENING FILE\n";
            return;
        }
        vector<string> patientInfo;

        while(getline(myFile, x)) {
            patientInfo.push_back(x);
            if(x.length()==0 || myFile.eof()) {
                ///call constructor on patient info
                /// push Patient object to patients array
                patients.push(*new Patient(patientInfo));
                patientInfo.clear();
            }
        }
        cout << "\nSUCCESS: ALL PATIENTS HAVE BEEN ADDED FROM FILE" << endl;
        cout << endl;
        separatePatients();
    }
};

/*
 Acceptance Criteria:

As any user, I want to be able to print out a guide on each command the system offers. (eg "help" functionality).

As a sys admin, I want some way to turn on debug mode.
As a sys admin, I want all operations of the system by each user to be logged to the console in debug mode.

*/