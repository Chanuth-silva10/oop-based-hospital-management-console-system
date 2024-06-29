#include <string>
#include <vector>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ios>
#include <limits>

using namespace std;

extern int yearDetails;
int pow(int *no = nullptr, int *e = nullptr);
int stringToNumber(std::string str, int *response = nullptr);

int yearDetails;

// Typedef for function pointers
typedef int (*PowFunction)(int *, int *);
typedef int (*StringToNumberFunction)(std::string, int *);

// Function to compute power
int pow(int *no, int *e)
{
    if (no == nullptr || e == nullptr)
        return -1; // Error handling if pointers are null

    int response = 1;
    while (*e)
    {
        if (*e & 1)
            response *= *no, (*e)--;
        else
            *no *= *no, (*e) >>= 1;
    }
    return response;
}

// Function to convert string to number
int stringToNumber(std::string str, int *response)
{
    if (response == nullptr)
        return -1; // Error handling if pointer is null

    *response = 0;
    for (int i = 0; i < str.size(); i++)
    {
        int *power = new int(10);                                                // Dynamically allocate memory for power variable
        *response += ((str[str.size() - 1 - i] - '0') * pow(power, new int(i))); // Pass the pointer to pow function
        delete power;                                                            // Free dynamically allocated memory
    }

    return *response;
}

// Base class with virtual methods demonstrating polymorphism
// Uisng prtected demonstrating Encapsulation
class person
{
protected: // Access specifier and Information Hiding
    int pid;
    string fName, lName;
    char sex;
    int pAge;
    string mobile;
    string perT;
    int personType;

public:
    // Constructor
    person();
    virtual void createPerson(int minmumAge = 0, int maximumAge = 1000);
    virtual void displayDetails();
    virtual void displayDetailsFromHistory();
    virtual void retrieveDetails(int record1 = 0) = 0;
    virtual void retrieveDetailsFromHistory() = 0; // Achieving abstraction using pure virtual function
    virtual void deletePerson() = 0;
};

// Derived class demonstrating inheritance (Concrete class implementing person)
class appointment;
class doctor : public person
{
private:
    string type;
    int appointmentsBooked;
    friend class appointment; // friendship between doctor and appointment classes

public:
    doctor();
    void createPerson();
    void displayDetails();
    void displayDetailsFromHistory(string additionalDetails = ""); //  virtual methods overridden in subclasses doctor, it would demonstrate polymorphic behavior.
    void retrieveDetails(int record1 = 0);
    void retrieveDetailsFromHistory();
    void deletePerson();
};

class appointment;
class patient : public person
{
private:
    int h;
    int w;
    bool hospitalized;
    bool alive;
    friend class appointment;

public:
    patient();
    void createPerson();
    void displayDetails();
    void displayDetailsFromHistory(string additionalDetails = "");
    void retrieveDetails(int record1 = 0);
    void retrieveDetailsFromHistory();
    void hospitalize();
    void reportADeath();
    void deletePerson();
};

class nurse : public person
{
private:
    string type;

public:
    nurse();
    void createPerson();
    void displayDetails();
    void displayDetailsFromHistory(string additionalDetails = "");
    void retrieveDetails(int record1 = 0);
    void retrieveDetailsFromHistory();
    void deletePerson();
};

// Class demonstrating composition
class appointment
{
private:
    int appID;
    doctor doc;
    patient P;
    int hourFormat;

public:
    appointment();
    ~appointment();
    void displayDetails();
    void book();
    void retrieveDetails();
};

// Class demonstrating static variables and methoda
class hospital
{
private:
    static map<int, doctor> doctorDetailList;
    static map<int, patient> patientDetailList;
    static map<int, nurse> nurseDetailList;
    static map<int, appointment> appointmentDetailList;

    static const int doctorDetailsLimit;
    static const int nurseDetailsLimit;
    static const int appointmentDetailsLimit;

    friend class doctor;
    friend class patient;
    friend class nurse;
    friend class appointment;

public:
    // Definition of static methods
    static void retriveDoctorDetails();
    static void retrivePatientDetails();
    static void retriveNursesDetails();
    static void retriveAppointmentsDetail();
};
// used constructor
person::person()
{
    pid = -1;
}

void person::createPerson(int minmumAge, int maximumAge)
{
    cout << endl
         << "Input person name: " << endl
         << "Input First name:" << endl;
    getline(cin >> ws, fName);
    cout << "\nInput Last name:\n";
    getline(cin, lName);

    cout << "\nInput pAge: \n";
    cin >> pAge;
    while (pAge <= 0)
        cout << "Please enter only positive value \nInput again!\n", cin >> pAge;
    if (personType != 2)
    {
        if (pAge < minmumAge)
            return void(cout << "Apologies, the person must be at least " << minmumAge << " years old to add as a " << perT << "." << endl);
        else if (pAge > maximumAge)
            return void(cout << "Apologies, we are unable to add a person older than " << maximumAge << " years as a " << perT << "." << endl);
    }

    cout << "\nSex (M || F ): \n";
    cin >> sex;
    while (sex != 'M' && sex != 'F')
        cout << "M or F?\n", cin >> sex;
    cout << "\nInput your mobile number: \n";
    getline(cin >> ws, mobile);
    return;
}
void person::displayDetails()
{
    if (pid == -1)
        return;
    cout << "\nDetails:\n";
    cout << "Person ID              : " << pid << "\n";
    cout << "Person Full Name       : " << fName << " " << lName << "\n";
    cout << "Sex                    : " << sex << "\n";
    cout << "Age                    : " << pAge << "\n";
    cout << "Mobile No              : " << mobile << "\n";
    return;
}
void person::displayDetailsFromHistory()
{
    if (pid == -1)
        return;
    cout << "\nHistory Details :\n";
    cout << "Person Full Name       : " << fName << " " << lName << "\n";
    cout << "Sex                    : " << sex << "\n";
    cout << "Age                    : " << pAge << "\n";
    cout << "Mobile                 : " << mobile << "\n";
    return;
}

map<int, doctor> hospital::doctorDetailList;
map<int, patient> hospital::patientDetailList;
map<int, nurse> hospital::nurseDetailList;
map<int, appointment> hospital::appointmentDetailList;

const int hospital::doctorDetailsLimit = 20;
const int hospital::nurseDetailsLimit = 30;
const int hospital::appointmentDetailsLimit = 100;

void hospital::retriveDoctorDetails()
{
    for (auto i1 : doctorDetailList)
        i1.second.displayDetails(), cout << "\n";
    return;
}
void hospital::retrivePatientDetails()
{
    for (auto i1 : patientDetailList)
        i1.second.displayDetails(), cout << "\n";
    return;
}
void hospital::retriveNursesDetails()
{
    for (auto i1 : nurseDetailList)
        i1.second.displayDetails(), cout << "\n";
    return;
}
void hospital::retriveAppointmentsDetail()
{
    for (auto i1 : appointmentDetailList)
        i1.second.displayDetails(), cout << "\n";
    return;
}

// used default constructor
appointment::appointment()
{
    appID = -1;
    doc.pid = -1;
    P.pid = -1;
}
// Reset the object's data members to default values when the object is destroyed
appointment::~appointment()
{
    appID = -1;
    doc.pid = -1;
    P.pid = -1;
    return;
}

void appointment::displayDetails() // Methods to access private members
{
    if (appID == -1)
        return;
    cout << endl
         << endl
         << "Appointment Details:" << endl
         << "ID                 : " << appID << endl
         << "Patient's Name     : " << P.fName << " " << P.lName << "(ID = " << P.pid << ")" << endl
         << "Doctor's Name      : " << doc.fName << " " << doc.lName << "(ID = " << doc.pid << ")" << endl
         << "Time : " << hourFormat << ":00 Hrs to " << hourFormat + 1 << ":00 Hrs" << endl
         << endl;
    return;
}

void appointment::book()
{
    if (hospital::appointmentDetailList.size() >= 8 * hospital::doctorDetailList.size())
    {
        cout << endl
             << endl
             << "We regret to inform you that there are no doctors available for appointments today." << endl
             << endl;
        return;
    }
    cout << endl
         << endl
         << "Has the patient been previously added? (Y or N)" << endl;
    char answer;
    cin >> answer;
    while (answer != 'Y' && answer != 'N')
    {
        cout << "Y or N?\n";
        cin >> answer;
    }
    if (answer == 'N')
    {
        cout << "Please add the patient:" << endl;
        P.createPerson();
    }
    else
    {
        cout << "Begin search for the specified patient:" << endl
             << endl;
        answer = 'Y';
        while (answer == 'Y')
        {
            P.retrieveDetails();
            answer = 'K';
            if (P.pid == -1)
            {
                cout << "Would you like to try again? (Y || N)\n";
                cin >> answer;
                while (answer != 'Y' && answer != 'N')
                {
                    cout << "Y or N?\n";
                    cin >> answer;
                }
            }
        }
        if (answer == 'N')
        {
            return;
        }
    }
    cout << endl
         << endl
         << "Proceeding to locate the requested physician:" << endl;
    answer = 'Y';
    while (answer == 'Y')
    {
        doc.retrieveDetails();
        answer = 'K';
        if (doc.pid == -1)
        {
            cout << "Would you like to try again? (Y || N)\n";
            cin >> answer;
            while (answer != 'Y' && answer != 'N')
            {
                cout << "Y or N?\n";
                cin >> answer;
            }
        }
        else if (doc.appointmentsBooked >= 8)
        {
            cout << "Unfortunately, the chosen doctor is fully booked for the day!" << endl;
            cout << "Would you like to search again? (Y: Yes || N: No)" << endl;
            cin >> answer;
            while (answer != 'Y' && answer != 'N')
            {
                cout << "Y or N?\n";
                cin >> answer;
            }
        }
    }
    if (answer == 'N')
    {
        return;
    }
    if (hospital::appointmentDetailList.rbegin() != hospital::appointmentDetailList.rend())
        appID = ((hospital::appointmentDetailList.rbegin())->first) + 1;
    else
        appID = 1;
    hourFormat = 9 + doc.appointmentsBooked;
    hospital::appointmentDetailList[appID] = *this;

    hospital::doctorDetailList[doc.pid].appointmentsBooked++;
    cout << endl
         << "Appointment for patient " + P.fName + " " + P.lName + " with doctor "
         << doc.fName << " " << doc.lName << " has been successfully booked." << endl;
    displayDetails();
    return;
}
void appointment::retrieveDetails()
{
    cout << "\nInput appointment ID:\n";
    cin >> appID;
    if (hospital::appointmentDetailList.find(appID) == hospital::appointmentDetailList.end())
    {
        cout << "\nInvalid appointment ID!\n";
        appID = -1;
        return;
    }
    *this = hospital::appointmentDetailList[appID];
    return;
}

nurse::nurse()
{
    pid = -1;
    type = "";
    perT = "nurse";
    personType = 3;
}

void nurse::createPerson()
{
    if (hospital::nurseDetailList.size() == hospital::nurseDetailsLimit)
    {
        cout << endl
             << endl
             << "Maximum number of nurses reached. Unable to add more!" << endl
             << endl;
        return;
    }

    person::createPerson(18, 65);
    if ((pAge < 18) || (pAge > 65))
        return;
    cout << "\nInput the type of the nurse:  " << endl;
    getline(cin >> ws, type);
    if (hospital::nurseDetailList.rbegin() != hospital::nurseDetailList.rend())
        pid = ((hospital::nurseDetailList.rbegin())->first) + 1;
    else
        pid = 1;
    hospital::nurseDetailList[pid] = *this;

    fstream fst;
    fst.open("./csvFile/nursesHistory.csv", ios::app);
    fst << fName << "," << lName << "," << sex << "," << pAge << "," << mobile << "," << type << ",N,NA" << endl;
    fst.close();

    cout << "\n"
         << fName << " " << lName << " added successfully!\n";
    cout << "added nurseing ID is: " << pid << "\n";

    return;
}
void nurse::displayDetails()
{
    if (pid == -1)
        return;
    person::displayDetails();
    cout << "Person Type            : " << type << "\n";
    return;
}
void nurse::displayDetailsFromHistory(string additionalDetails)
{
    if (pid == -1)
        return;
    person::displayDetailsFromHistory();
    stringstream k(additionalDetails);
    string str1, str2;
    getline(k, str1, ',');
    getline(k, str2, ',');
    if (additionalDetails == "")
    {
        fstream fst;
        fst.open("./csvFile/nursesHistory.csv", ios::in);
        string strTemp;

        getline(fst >> ws, strTemp);

        while (getline(fst >> ws, strTemp))
        {
            nurse nur;

            stringstream s(strTemp);
            string str4, str5, str7;

            getline(s, nur.fName, ',');
            getline(s, nur.lName, ',');
            getline(s, str4, ',');
            getline(s, str5, ',');
            getline(s, nur.mobile, ',');

            if (nur.fName == fName && nur.lName == lName && nur.mobile == mobile)
            {

                getline(s, str7, ',');
                getline(s, nur.type, ',');
                getline(s, str1, ',');
                getline(s, str2, ',');
            }
        }
        fst.close();
    }
    cout << "Employee Type   : " << type << endl;
    cout << "On Leave?       : " << str1 << endl;
    if (str1 == "Y")
        cout << "Reason for the leave         : " << str2 << "\n";
    return;
}
void nurse::retrieveDetails(int record1)
{
    int retriveOpt = 0;
    cout << endl
         << "OPTIONS:" << endl
         << "(1): Filter by ID" << endl
         << "(2): Filter by Name" << endl
         << "(3): Filter by Type" << endl
         << endl;
    cin >> retriveOpt;
    while (retriveOpt != 1 && retriveOpt != 2 && retriveOpt != 3)
        cout << "option 1, 2 or 3?\n", cin >> retriveOpt;

    if (retriveOpt == 1)
    {
        int requesID;
        cout << "\nInput ID:\n";
        cin >> requesID;
        if (hospital::nurseDetailList.find(requesID) != hospital::nurseDetailList.end())
            *this = hospital::nurseDetailList[requesID];
        else
            cout << endl
                 << "No records matching your search were found." << endl;
    }

    else if (retriveOpt == 2)
    {
        string requesFName, requesLName;
        cout << "First Name:\n";
        getline(cin >> ws, requesFName);
        cout << "\nLast Name:\n";
        getline(cin, requesLName);
        vector<nurse> checkingRecords;
        for (auto i1 : hospital::nurseDetailList)
        {
            if (i1.second.fName == requesFName && i1.second.lName == requesLName)
                checkingRecords.push_back(i1.second);
        }
        cout << "\n";
        cout << checkingRecords.size() << " input record exist\n";
        for (auto i1 : checkingRecords)
            i1.displayDetails();
        char hospitalizedStatus = 'N';
        if (checkingRecords.size() > record1)
        {
            do
            {
                int requesID;
                cout << endl
                     << "Please enter the ID of the nurse you need to find:" << endl;
                cin >> requesID;
                if (hospital::nurseDetailList.find(requesID) != hospital::nurseDetailList.end())
                    *this = hospital::nurseDetailList[requesID];
                else
                {
                    cout << "\nInvalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> hospitalizedStatus;
                    while (hospitalizedStatus != 'Y' || hospitalizedStatus != 'N')
                        cout << "Y or N?\n", cin >> hospitalizedStatus;
                }
            } while (hospitalizedStatus == 'Y');
        }
    }

    else if (retriveOpt == 3)
    {
        string requesType;
        cout << "Input the type of nurse required:\n";
        getline(cin >> ws, requesType);
        vector<nurse> checkingRecords;
        for (auto i1 : hospital::nurseDetailList)
        {
            if (i1.second.type == requesType)
                checkingRecords.push_back(i1.second);
        }
        cout << "\n";
        cout << checkingRecords.size() << " input record exist\n";
        for (auto i1 : checkingRecords)
            i1.displayDetails();
        char hospitalizedStatus = 'N';
        if (checkingRecords.size() > 0)
            do
            {
                int requesID;
                cout << endl
                     << "Please enter the ID of the nurse you need to find:" << endl;
                cin >> requesID;
                if (hospital::nurseDetailList.find(requesID) != hospital::nurseDetailList.end())
                    *this = hospital::nurseDetailList[requesID];
                else
                {
                    cout << "\nInvalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> hospitalizedStatus;
                    while (hospitalizedStatus != 'Y' || hospitalizedStatus != 'N')
                        cout << "Y or N?\n", cin >> hospitalizedStatus;
                }
            } while (hospitalizedStatus == 'Y');
    }
    return;
}
// Implementing the abstract functions
void nurse::retrieveDetailsFromHistory()
{
    int retriveOpt = 0;
    cout << "\nOPTIONS:\n(1): Filter by Name\n(2): Filter by Type\n\n";
    cin >> retriveOpt;
    while (retriveOpt != 1 && retriveOpt != 2)
        cout << "option 1 or 2?\n", cin >> retriveOpt;

    if (retriveOpt == 1)
    {
        string requesFName, requesLName;
        cout << "First Name:\n";
        getline(cin >> ws, requesFName);
        cout << "\nLast Name:\n";
        getline(cin, requesLName);
        vector<nurse> checkingRecords;
        vector<string> additionalDetails;
        fstream fst;
        fst.open("./csvFile/nursesHistory.csv", ios::in);
        string strTemp;

        getline(fst >> ws, strTemp);

        while (getline(fst >> ws, strTemp))
        {
            nurse nur;

            stringstream s(strTemp);
            string str4, str5, str7, str9;

            getline(s, nur.fName, ',');
            getline(s, nur.lName, ',');

            if (nur.fName == requesFName && nur.lName == requesLName)
            {
                getline(s, str4, ',');
                getline(s, str5, ',');
                getline(s, nur.mobile, ',');
                getline(s, str7, ',');
                getline(s, nur.type, ',');
                getline(s, str9);
                nur.pid = 0;
                nur.sex = str4[0];
                nur.pAge = stringToNumber(str5);
                checkingRecords.push_back(nur);
                additionalDetails.push_back(str9);
            }
        }
        fst.close();
        cout << "\n";
        cout << checkingRecords.size() << " input record exist\n";
        for (int i = 0; i < checkingRecords.size(); i++)
            checkingRecords[i].displayDetailsFromHistory(additionalDetails[i]);
    }

    else if (retriveOpt == 2)
    {
        string requesType;
        cout << "Input the type of nurse required:\n";
        getline(cin >> ws, requesType);
        vector<nurse> checkingRecords;
        vector<string> additionalDetails;
        fstream fst;
        fst.open("./csvFile/nursesHistory.csv", ios::in);
        string strTemp;

        getline(fst >> ws, strTemp);

        while (getline(fst >> ws, strTemp))
        {
            nurse nur;

            stringstream s(strTemp);
            string str4, str5, str7, str9;

            getline(s, nur.fName, ',');
            getline(s, nur.lName, ',');
            getline(s, str4, ',');
            getline(s, str5, ',');
            getline(s, nur.mobile, ',');
            getline(s, str7, ',');
            getline(s, nur.type, ',');
            if (nur.type == requesType)
            {
                getline(s, str9);
                nur.pid = 0;
                nur.sex = str4[0];
                nur.pAge = stringToNumber(str5);
                checkingRecords.push_back(nur);
                additionalDetails.push_back(str9);
            }
        }
        fst.close();
        cout << endl;
        cout << checkingRecords.size() << " Input record(s) exist!" << endl;
        for (int i = 0; i < checkingRecords.size(); i++)
            checkingRecords[i].displayDetailsFromHistory(additionalDetails[i]);
    }
    return;
}
void nurse::deletePerson()
{
    cout << "\nSearch for the nurse you want to remove.\n";
    retrieveDetails();
    if (pid == -1)
        return;
    hospital::nurseDetailList.erase(pid);

    string s, strTemp;
    stringstream str;
    fstream fst, fout;
    string reason;
    cout << "\nReason?\n";
    getline(cin >> ws, reason);
    str << fName << "," << lName << "," << sex << "," << pAge
        << "," << mobile << "," << type << ",N,NA\n";
    getline(str, s);
    fst.open("./csvFile/nursesHistory.csv", ios::in);
    fout.open("./csvFile/strTemp.csv", ios::out);
    while (getline(fst, strTemp))
    {
        if (strTemp == s)
        {
            fout << fName << "," << lName << "," << sex << "," << pAge
                 << "," << mobile << "," << type << ",Y," << reason << "\n";
        }
        else
            fout << strTemp << "\n";
    }
    fst.close();
    fout.close();
    s.erase();
    strTemp.erase();
    remove("./csvFile/nursesHistory.csv");
    rename("./csvFile/strTemp.csv", "./csvFile/nursesHistory.csv");
    cout << fName << " " << lName << " removed successfully!\n";
    return;
}

doctor::doctor()
{
    pid = -1;
    type = "";
    appointmentsBooked = 0;
    perT = "doctor";
    personType = 1;
}

void doctor::createPerson()
{
    if (hospital::doctorDetailList.size() == hospital::doctorDetailsLimit)
    {
        cout << endl
             << endl
             << "Maximum doctor capacity reached. No further additions possible." << endl
             << endl;
        return;
    }

    person::createPerson(18, 65);
    if ((pAge < 18) || (pAge > 65))
        return;
    cout << "\nInput the type of the doctor: \n";
    getline(cin >> ws, type);
    if (hospital::doctorDetailList.rbegin() != hospital::doctorDetailList.rend())
        pid = ((hospital::doctorDetailList.rbegin())->first) + 1;
    else
        pid = 1;
    hospital::doctorDetailList[pid] = *this;

    fstream fst;

    fst.open("./csvFile/doctorsHistory.csv", ios::app);
    fst << fName << "," << lName << "," << sex << "," << pAge << "," << mobile << "," << type << ",N,NA" << endl;
    fst.close();

    cout << "\n"
         << fName << " " << lName << " added success!\n";
    cout << "Their ID is: " << pid << "\n";

    return;
}
void doctor::displayDetails()
{
    if (pid == -1)
        return;
    person::displayDetails();
    cout << "Type            : " << type << "\n";
    cout << "Appointments Scheduled for Today: " << appointmentsBooked << " out of 8 (appointments booked for today)" << endl;
    return;
}
void doctor::displayDetailsFromHistory(string additionalDetails)
{
    if (pid == -1)
        return;
    person::displayDetailsFromHistory();
    stringstream k(additionalDetails);
    string str1, str2;
    getline(k, str1, ',');
    getline(k, str2, ',');
    if (additionalDetails == "")
    {
        fstream fst;
        fst.open("./csvFile/doctorsHistory.csv", ios::in);
        string strTemp;
        getline(fst >> ws, strTemp);

        while (getline(fst >> ws, strTemp))
        {
            doctor doc1;

            stringstream s(strTemp);
            string str4, str5, str7;

            getline(s, doc1.fName, ',');
            getline(s, doc1.lName, ',');
            getline(s, str4, ',');
            getline(s, str5, ',');
            getline(s, doc1.mobile, ',');

            if (doc1.fName == fName && doc1.lName == lName && doc1.mobile == mobile)
            {

                getline(s, str7, ',');
                getline(s, doc1.type, ',');
                getline(s, str1, ',');
                getline(s, str2, ',');
            }
        }
        fst.close();
    }
    cout << "Type            : " << type << "\n";
    cout << "On Leave?      : " << str1 << "\n";
    if (str1 == "Y")
        cout << "Reason for the leave         : " << str2 << "\n";
    return;
}
void doctor::retrieveDetails(int record1)
{
    int retriveOpt = 0;
    cout << endl
         << "OPTIONS:" << endl
         << "(1): Filter by ID" << endl
         << "(2): Filter by Name" << endl
         << "(3): Filter by Type" << endl
         << endl;
    cin >> retriveOpt;
    while (retriveOpt != 1 && retriveOpt != 2 && retriveOpt != 3)
        cout << "option 1, 2 or 3?\n", cin >> retriveOpt;

    if (retriveOpt == 1)
    {
        int requesID;
        cout << "\nInput ID:\n";
        cin >> requesID;
        if (hospital::doctorDetailList.find(requesID) != hospital::doctorDetailList.end())
            *this = hospital::doctorDetailList[requesID];
        else
            cout << endl
                 << "No records matching your search were found." << endl;
    }

    else if (retriveOpt == 2)
    {
        string requesFName, requesLName;
        cout << "First Name:\n";
        getline(cin >> ws, requesFName);
        cout << "\nLast Name:\n";
        getline(cin, requesLName);
        vector<doctor> checkingRecords;
        for (auto i1 : hospital::doctorDetailList)
        {
            if (i1.second.fName == requesFName && i1.second.lName == requesLName)
                checkingRecords.push_back(i1.second);
        }
        cout << "\n";
        cout << checkingRecords.size() << " input record exist\n";
        for (auto i1 : checkingRecords)
            i1.displayDetails();
        char hospitalizedStatus = 'N';
        if (checkingRecords.size() > record1)
        {
            do
            {
                int requesID;
                cout << endl
                     << "Please enter the ID of the doctor you need to find:" << endl;
                cin >> requesID;
                if (hospital::doctorDetailList.find(requesID) != hospital::doctorDetailList.end())
                    *this = hospital::doctorDetailList[requesID];
                else
                {
                    cout << "\nInvalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> hospitalizedStatus;
                    while (hospitalizedStatus != 'Y' || hospitalizedStatus != 'N')
                        cout << "Y or N?\n", cin >> hospitalizedStatus;
                }
            } while (hospitalizedStatus == 'Y');
        }
    }
    // 3: Filter by type;
    else if (retriveOpt == 3)
    {
        string requesType;
        cout << "Input the type of doctor required:\n";
        getline(cin >> ws, requesType);
        vector<doctor> checkingRecords;
        for (auto i1 : hospital::doctorDetailList)
        {
            if (i1.second.type == requesType)
                checkingRecords.push_back(i1.second);
        }
        cout << "\n";
        cout << checkingRecords.size() << " input record exist\n";
        for (auto i1 : checkingRecords)
            i1.displayDetails();
        char hospitalizedStatus = 'N';
        if (checkingRecords.size() > 0)
            do
            {
                int requesID;
                cout << endl
                     << "Please enter the ID of the doctor you need to find:" << endl;
                cin >> requesID;
                if (hospital::doctorDetailList.find(requesID) != hospital::doctorDetailList.end())
                    *this = hospital::doctorDetailList[requesID];
                else
                {
                    cout << "\nInvalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> hospitalizedStatus;
                    while (hospitalizedStatus != 'Y' || hospitalizedStatus != 'N')
                        cout << "Y or N?\n", cin >> hospitalizedStatus;
                }
            } while (hospitalizedStatus == 'Y');
    }
    return;
}
void doctor::retrieveDetailsFromHistory()
{
    int retriveOpt = 0;
    cout << "\nOPTIONS:\n(1): Filter by Name\n(2): Filter by Type\n\n";
    cin >> retriveOpt;
    while (retriveOpt != 1 && retriveOpt != 2)
        cout << "Input option 1 or 2?\n", cin >> retriveOpt;

    if (retriveOpt == 1)
    {
        string requesFName, requesLName;
        cout << "First Name:\n";
        getline(cin >> ws, requesFName);
        cout << "\nLast Name:\n";
        getline(cin, requesLName);
        vector<doctor> checkingRecords;
        vector<string> additionalDetails;
        fstream fst;
        fst.open("./csvFile/doctorsHistory.csv", ios::in);
        string strTemp;

        getline(fst >> ws, strTemp);
        while (getline(fst >> ws, strTemp))
        {
            doctor doc1;

            stringstream s(strTemp);
            string str4, str5, str7, str9;

            getline(s, doc1.fName, ',');
            getline(s, doc1.lName, ',');

            if (doc1.fName == requesFName && doc1.lName == requesLName)
            {
                getline(s, str4, ',');
                getline(s, str5, ',');
                getline(s, doc1.mobile, ',');
                getline(s, str7, ',');
                getline(s, doc1.type, ',');
                getline(s, str9);
                doc1.pid = 0;
                doc1.sex = str4[0];
                doc1.pAge = stringToNumber(str5);

                checkingRecords.push_back(doc1);
                additionalDetails.push_back(str9);
            }
        }
        fst.close();
        cout << "\n";
        cout << checkingRecords.size() << " input record exist\n";
        for (int i = 0; i < checkingRecords.size(); i++)
            checkingRecords[i].displayDetailsFromHistory(additionalDetails[i]);
    }

    else if (retriveOpt == 2)
    {
        string requesType;
        cout << "Input the type of doctor required:\n";
        getline(cin >> ws, requesType);
        vector<doctor> checkingRecords;
        vector<string> additionalDetails;
        fstream fst;
        fst.open("./csvFile/doctorsHistory.csv", ios::in);
        string strTemp;

        getline(fst >> ws, strTemp);

        while (getline(fst >> ws, strTemp))
        {
            doctor doc1;

            stringstream s(strTemp);
            string str4, str5, str7, str9;

            getline(s, doc1.fName, ',');
            getline(s, doc1.lName, ',');
            getline(s, str4, ',');
            getline(s, str5, ',');
            getline(s, doc1.mobile, ',');
            getline(s, str7, ',');
            getline(s, doc1.type, ',');
            if (doc1.type == requesType)
            {
                getline(s, str9);
                doc1.pid = 0;
                doc1.sex = str4[0];
                doc1.pAge = stringToNumber(str5);
                checkingRecords.push_back(doc1);
                additionalDetails.push_back(str9);
            }
        }
        fst.close();
        cout << endl;
        cout << checkingRecords.size() << " input record exist\n";
        for (int i = 0; i < checkingRecords.size(); i++)
            checkingRecords[i].displayDetailsFromHistory(additionalDetails[i]);
    }
    return;
}
void doctor::deletePerson()
{
    cout << "\nSearch for the doctor you want to remove.\n";
    retrieveDetails();
    if (pid == -1)
        return;
    if (appointmentsBooked > 0)
    {
        cout << endl
             << "The chosen doctor currently has appointments scheduled for today and cannot be removed." << endl
             << endl;
        return;
    }
    hospital::doctorDetailList.erase(pid);

    string s, strTemp;
    stringstream str;
    fstream fst, fout;
    string reason;
    cout << "\nRemove Reason?\n";
    getline(cin >> ws, reason);
    str << fName << "," << lName << "," << sex << "," << pAge
        << "," << mobile << "," << type << ",N,NA\n";
    getline(str, s);
    fst.open("./csvFile/doctorsHistory.csv", ios::in);
    fout.open("./csvFile/strTemp.csv", ios::out);
    while (getline(fst, strTemp))
    {
        if (strTemp == s)
        {
            fout << fName << "," << lName << "," << sex << "," << pAge
                 << "," << mobile << "," << type << ",Y," << reason << "\n";
        }
        else
            fout << strTemp << "\n";
    }
    fst.close();
    fout.close();
    s.erase();
    strTemp.erase();
    remove("./csvFile/doctorsHistory.csv");
    rename("./csvFile/strTemp.csv", "./csvFile/doctorsHistory.csv");
    cout << fName << " " << lName << " removed successfully!\n";
    return;
}

patient::patient()
{
    pid = -1;
    hospitalized = 0;
    alive = 1;
    perT = "patient";
    personType = 2;
}
void patient::createPerson()
{
    person::createPerson();

    cout << "\nInput the h of the patient (in cms):\n";
    cin >> h;
    cout << "\nInput the w of the patient (in pounds):\n";
    cin >> w;
    char hospitalizedStatus;
    cout << "\nIs the patient being hospitalized? (Y = Yes || N = No)\n";
    cin >> hospitalizedStatus;
    while (hospitalizedStatus != 'Y' && hospitalizedStatus != 'N')
        cout << "Y or N?\n", cin >> hospitalizedStatus;
    hospitalized = (hospitalizedStatus == 'Y');
    if (hospital::patientDetailList.rbegin() != hospital::patientDetailList.rend())
        pid = ((hospital::patientDetailList.rbegin())->first) + 1;
    else
        pid = 1;
    hospital::patientDetailList[pid] = *this;

    fstream fst;

    fst.open("./csvFile/patientsHistory.csv", ios::app);
    fst << fName << "," << lName << "," << sex << "," << pAge
        << "," << mobile << "," << h << ","
        << w << "," << ((hospitalized) ? "Y" : "N")
        << ","
        << "Y"
        << ","
        << "N"
        << "\n";
    fst.close();

    cout << "\n"
         << fName << " " << lName << " added success.\n";
    cout << "Person ID is: " << pid << "\n";

    return;
}
void patient::displayDetails()
{
    if (pid == -1)
        return;
    person::displayDetails();
    cout << "Height (in centimeters): " << h << endl;
    cout << "Weight (in pounds): " << w << endl;
    cout << "History of Hospitalization: " << ((hospitalized) ? "Yes" : "No") << endl;
    cout << "Currently Alive: " << ((alive) ? "Yes" : "No") << endl;
    return;
}
void patient::displayDetailsFromHistory(string additionalDetails)
{
    if (pid == -1)
        return;
    person::displayDetailsFromHistory();
    stringstream k(additionalDetails);
    string str1;
    getline(k, str1, ',');
    if (additionalDetails == "")
    {
        fstream fst;
        fst.open("./csvFile/patientsHistory.csv", ios::in);
        string strTemp;

        getline(fst >> ws, strTemp);

        while (getline(fst >> ws, strTemp))
        {
            patient pat;
            stringstream s(strTemp);
            string str3, str4, str6, str7, str8, str9, str10;

            getline(s, pat.fName, ',');
            getline(s, pat.lName, ',');
            getline(s, str3, ',');
            getline(s, str4, ',');
            getline(s, pat.mobile, ',');

            if (pat.fName == fName && pat.lName == lName && pat.mobile == mobile)
            {

                getline(s, str6, ',');
                getline(s, str7, ',');
                getline(s, str8, ',');
                getline(s, str9, ',');
                getline(s, str10, ',');
                getline(s, str1, ',');
            }
        }
        fst.close();
    }
    cout << "Height (in centimeters): " << h << endl;
    cout << "Weight (in pounds): " << w << endl;
    cout << "History of Hospitalization: " << ((hospitalized) ? "Yes" : "No") << endl;
    cout << "Currently Alive: " << ((alive) ? "Yes" : "No") << endl;
    cout << "Is the person discharged? : " << str1 << endl;
    return;
}
void patient::retrieveDetails(int record1)
{
    int retriveOpt = 0;
    cout << "\nOPTIONS:\n(1): Filter by ID\n(2): Filter by Name\n\n";
    cin >> retriveOpt;
    while (retriveOpt != 1 && retriveOpt != 2)
        cout << "option 1 or 2?\n", cin >> retriveOpt;

    if (retriveOpt == 1)
    {
        int requesID;
        cout << "\nInput ID:\n";
        cin >> requesID;
        if (hospital::patientDetailList.find(requesID) != hospital::patientDetailList.end())
            *this = hospital::patientDetailList[requesID];
        else
            cout << endl
                 << "No records matching your search were found." << endl;
    }

    else if (retriveOpt == 2)
    {
        string requesFName, requesLName;
        cout << "First Name:\n";
        getline(cin >> ws, requesFName);
        cout << "\nLast Name:\n";
        getline(cin, requesLName);
        vector<patient> checkingRecords;
        for (auto i1 : hospital::patientDetailList)
        {
            if (i1.second.fName == requesFName && i1.second.lName == requesLName)
                checkingRecords.push_back(i1.second);
        }
        cout << "\n";
        cout << checkingRecords.size() << " input record exist\n";
        for (auto i1 : checkingRecords)
            i1.displayDetails();
        char hospitalizedStatus = 'N';
        if (checkingRecords.size() > record1)
        {
            do
            {
                int requesID;
                cout << endl
                     << "Please enter the ID of the patient you need to find:" << endl;
                cin >> requesID;
                if (hospital::patientDetailList.find(requesID) != hospital::patientDetailList.end())
                    *this = hospital::patientDetailList[requesID];
                else
                {
                    cout << "\nInvalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> hospitalizedStatus;
                    while (hospitalizedStatus != 'Y' || hospitalizedStatus != 'N')
                        cout << "Y or N?\n", cin >> hospitalizedStatus;
                }
            } while (hospitalizedStatus == 'Y');
        }
    }
    return;
}
void patient::retrieveDetailsFromHistory()
{
    int retriveOpt = 0;
    cout << "\nOPTIONS:\n(1): Filter by Name\n(2): Filter by Mobile Number\n\n";
    cin >> retriveOpt;
    while (retriveOpt != 1 && retriveOpt != 2)
        cout << "option 1 or 2?\n", cin >> retriveOpt;

    if (retriveOpt == 1)
    {
        string requesFName, requesLName;
        cout << "First Name:\n";
        getline(cin >> ws, requesFName);
        cout << "\nLast Name:\n";
        getline(cin, requesLName);
        vector<patient> checkingRecords;
        vector<string> additionalDetails;
        fstream fst;
        fst.open("./csvFile/patientsHistory.csv", ios::in);
        string strTemp;
        getline(fst >> ws, strTemp);

        while (getline(fst >> ws, strTemp))
        {
            patient pat;

            stringstream s(strTemp);
            string str3, str4, str6, str7, str8, str9, str10, str12;

            getline(s, pat.fName, ',');
            getline(s, pat.lName, ',');

            if (pat.fName == requesFName && pat.lName == requesLName)
            {
                getline(s, str3, ',');
                getline(s, str4, ',');
                getline(s, pat.mobile, ',');
                getline(s, str6, ',');
                getline(s, str7, ',');
                getline(s, str8, ',');
                getline(s, str9, ',');
                getline(s, str10, ',');
                getline(s, str10, ',');
                getline(s, str12);
                pat.pid = 0;
                pat.sex = str3[0];
                pat.pAge = stringToNumber(str4);
                pat.h = stringToNumber(str7);
                pat.w = stringToNumber(str8);
                pat.hospitalized = (str9 == "Y");
                pat.alive = (str10 == "Y");
                checkingRecords.push_back(pat);
                additionalDetails.push_back(str12);
            }
        }
        fst.close();
        cout << "\n";
        cout << checkingRecords.size() << " input record exist\n";
        for (int i = 0; i < checkingRecords.size(); i++)
            checkingRecords[i].displayDetailsFromHistory(additionalDetails[i]);
    }

    else if (retriveOpt == 2)
    {
        string requsetMobile;
        cout << "Input mobile number:\n";
        cin >> requsetMobile;
        vector<patient> checkingRecords;
        vector<string> additionalDetails;
        fstream fst;
        fst.open("./csvFile/patientsHistory.csv", ios::in);
        string strTemp;
        getline(fst >> ws, strTemp);

        while (getline(fst >> ws, strTemp))
        {
            patient pat;
            stringstream s(strTemp);
            string str3, str4, str6, str7, str8, str9, str10, str12;

            getline(s, pat.fName, ',');
            getline(s, pat.lName, ',');
            getline(s, str3, ',');
            getline(s, str4, ',');
            getline(s, pat.mobile, ',');

            if (requsetMobile == pat.mobile)
            {
                getline(s, str6, ',');
                getline(s, str7, ',');
                getline(s, str8, ',');
                getline(s, str9, ',');
                getline(s, str10, ',');
                getline(s, str12);
                pat.pid = 0;
                pat.sex = str3[0];
                pat.pAge = stringToNumber(str4);
                pat.h = stringToNumber(str7);
                pat.w = stringToNumber(str8);
                pat.hospitalized = (str9 == "Y");
                pat.alive = (str10 == "Y");
                checkingRecords.push_back(pat);
                additionalDetails.push_back(str12);
            }
        }
        fst.close();
        cout << "\n";
        cout << checkingRecords.size() << " input record exist\n";
        for (int i = 0; i < checkingRecords.size(); i++)
            checkingRecords[i].displayDetailsFromHistory(additionalDetails[i]);
    }
    return;
}

void patient::hospitalize() //
{
    cout << "\nSearch for the patient.\n";
    retrieveDetails();
    if (pid == -1)
        return;
    hospital::patientDetailList[pid].hospitalized = 1;
    string s, strTemp, corrected;
    stringstream str;
    fstream fst, fout;
    str << fName << "," << lName
        << "," << sex << "," << pAge << "," << mobile
        << "," << h << "," << w << "," << ((hospitalized) ? "Y" : "N")
        << ","
        << ((alive) ? "Y" : "N")
        << ",N"
        << "\n";
    getline(str >> ws, s);
    str << fName << "," << lName
        << "," << sex << "," << pAge << "," << mobile
        << "," << h << "," << w << ","
        << "Y,"
        << ((alive) ? "Y,N\n" : "N,N\n");
    getline(str >> ws, corrected);
    fst.open("./csvFile/patientsHistory.csv", ios::in);
    fout.open("./csvFile/strTemp.csv", ios::out);
    while (getline(fst, strTemp))
    {
        if (strTemp == s)
            fout << corrected << "\n";
        else
            fout << strTemp << "\n";
    }
    fst.close();
    fout.close();
    s.erase();
    strTemp.erase();
    remove("./csvFile/patientsHistory.csv");
    rename("./csvFile/strTemp.csv", "./csvFile/patientsHistory.csv");
    cout << fName << " " << lName << " hospitalized successfully!\n";
    return;
}
void patient::reportADeath()
{
    cout << "\nSearch for the patient.\n";
    retrieveDetails();
    if (pid == -1)
        return;
    hospital::patientDetailList[pid].alive = 0;
    if (!hospital::patientDetailList[pid].hospitalized)
        hospital::patientDetailList.erase(pid);
    string s, strTemp, corrected;
    stringstream str;
    fstream fst, fout;
    str << fName << "," << lName
        << "," << sex << "," << pAge << "," << mobile
        << "," << h << "," << w << "," << ((hospitalized) ? "Y" : "N")
        << ","
        << ((alive) ? "Y" : "N")
        << ",N"
        << "\n";
    getline(str, s);
    fst.open("./csvFile/patientsHistory.csv", ios::in);
    fout.open("./csvFile/strTemp.csv", ios::out);
    while (getline(fst, strTemp))
    {
        if (strTemp == s)
        {
            fout << fName << "," << lName
                 << "," << sex << "," << pAge << "," << mobile << ","
                 << "," << h << "," << w << "," << ((hospitalized) ? "Y,N,N\n" : "N,N,N\n");
        }
        else
            fout << strTemp << "\n";
    }
    fst.close();
    fout.close();
    s.erase();
    strTemp.erase();
    remove("./csvFile/patientsHistory.csv");
    rename("./csvFile/strTemp.csv", "./csvFile/patientsHistory.csv");
    cout << fName << " " << lName << " reported dead, we hope their soul rests in peace, amen!\n";
    return;
}
void patient::deletePerson()
{
    cout << "\nSearch for the patient you want to discharge.\n";
    retrieveDetails();
    if (pid == -1)
        return;
    if (!hospitalized)
    {
        cout << "\nPatient wasn't hospitalized, can't be discharged!\n\n";
        return;
    }
    hospital::patientDetailList.erase(pid);
    string s, strTemp;
    stringstream str;
    fstream fst, fout;
    str << fName << "," << lName
        << "," << sex << "," << pAge << "," << mobile
        << "," << h << "," << w << "," << ((hospitalized) ? "Y" : "N")
        << ","
        << ((alive) ? "Y" : "N")
        << ",N"
        << "\n";
    getline(str, s);
    fst.open("./csvFile/patientsHistory.csv", ios::in);
    fout.open("./csvFile/strTemp.csv", ios::out);
    while (getline(fst, strTemp))
    {
        if (strTemp == s)
        {
            fout << fName << "," << lName
                 << "," << sex << "," << pAge << "," << mobile
                 << "," << h << "," << w << "," << ((hospitalized) ? "Y" : "N")
                 << ","
                 << ((alive) ? "Y" : "N")
                 << ",Y"
                 << "\n";
        }
        else
            fout << strTemp << "\n";
    }
    fst.close();
    fout.close();
    s.erase();
    strTemp.erase();
    remove("./csvFile/patientsHistory.csv");
    rename("./csvFile/strTemp.csv", "./csvFile/patientsHistory.csv");
    cout << fName << " " << lName << " discharged!\n";
    return;
}
void appointmentsControlMenu()
{
    bool quit = false;
    while (!quit)
    {
        int appPurpose = 0;
        cout << "\n=================================================================================\n";
        cout << "\n=================================================================================\n";
        cout << "\n\n";
        cout << "\nchoose your option:\n\n";

        cout << "===========================\n";
        cout << "===========================\n";
        cout << "(01) : Schedule an appointment\n";
        cout << "(02) : Retrieve appointment details\n";
        cout << "(03) : Display all appointments\n\n";
        cout << "(-1) : Go back\n";
        cout << "===========================\n\n";
        cout << "Input your choice: ";
        cin >> appPurpose;

        if (appPurpose == 1)
        {
            appointment app;
            app.book();
        }
        else if (appPurpose == 2)
        {
            appointment app;
            app.retrieveDetails();
            app.displayDetails();
        }
        else if (appPurpose == 3)
        {
            hospital::retriveAppointmentsDetail();
        }
        else if (appPurpose == -1)
        {
            quit = true;
            break;
        }
        else
        {
            cout << "Not valid choice!\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << endl;
        cout << "\nPress ENTER to continue...\n";
        cout << endl;

        getchar();
    }
    return;
}

void patientsControlMenu()
{
    bool quit = false;
    while (!quit)
    {
        int appPurpose = 0;
        cout << "\n=================================================================================\n";
        cout << "\n=================================================================================\n";
        cout << "\nChoose your option:\n\n";

        cout << "===========================\n";
        cout << "===========================\n";
        cout << "(01) : add a new patient\n";
        cout << "(02) : Getting patient details\n";
        cout << "(03) : Admit a added patient to the hospital\n";
        cout << "(04) : Getting report list a patient's death\n";
        cout << "(05) : Discharge a patient or release their remains\n";
        cout << "(06) : Retrieve patient details from past history\n";
        cout << "(07) : Getting all details of added patients\n\n";
        cout << "(-1) : Go back\n";
        cout << "===========================\n\n";
        cout << "Input your choice: ";
        cin >> appPurpose;

        if (appPurpose == 1)
        {
            patient pat;
            pat.createPerson();
        }
        else if (appPurpose == 2)
        {
            patient pat;
            pat.retrieveDetails(1);
            pat.displayDetails();
        }
        else if (appPurpose == 3)
        {
            patient pat;
            pat.hospitalize();
        }
        else if (appPurpose == 4)
        {
            patient pat;
            pat.reportADeath();
        }
        else if (appPurpose == 5)
        {
            patient pat;
            pat.deletePerson();
        }
        else if (appPurpose == 6)
        {
            patient pat;
            pat.retrieveDetailsFromHistory();
        }
        else if (appPurpose == 7)
        {
            hospital::retrivePatientDetails();
        }
        else if (appPurpose == -1)
        {
            quit = true;
            break;
        }
        else
        {
            cout << "Not valid choice!\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\nPress ENTER to continue...\n";
        cout << endl;

        getchar();
    }
    return;
}
void doctorsControlMenu()
{
    bool quit = false;
    while (!quit)
    {
        int appPurpose = 0;
        cout << "\n=================================================================================\n";
        cout << "\n=================================================================================\n";
        cout << "\nChoose your option:\n\n";

        cout << "===========================\n";
        cout << "===========================\n";
        cout << "(01) : Add a new doctor\n";
        cout << "(02) : Getting doctor details\n";
        cout << "(03) : Remove a doctor\n";
        cout << "(04) : Retrieve doctor details from past history\n";
        cout << "(05) : Getting details of all added doctors\n\n";
        cout << "(-1) : Go back\n";
        cout << "===========================\n\n";
        cout << "Input your choice: ";
        cin >> appPurpose;

        if (appPurpose == 1)
        {
            doctor doc1;
            doc1.createPerson();
        }
        else if (appPurpose == 2)
        {
            doctor doc1;
            doc1.retrieveDetails(1);
            doc1.displayDetails();
        }
        else if (appPurpose == 3)
        {
            doctor doc1;
            doc1.deletePerson();
        }
        else if (appPurpose == 4)
        {
            doctor doc1;
            doc1.retrieveDetailsFromHistory();
        }
        else if (appPurpose == 5)
        {
            hospital::retriveDoctorDetails();
        }
        else if (appPurpose == -1)
        {
            quit = true;
            break;
        }
        else
        {
            cout << "Not valid choice!\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\nPress ENTER to continue...\n";
        cout << endl;

        getchar();
    }
    return;
}

void nursesControlMenu()
{
    bool quit = false;
    while (!quit)
    {
        int appPurpose = 0;
        cout << "\n=================================================================================\n";
        cout << "\n=================================================================================\n";
        cout << "\nChoose your option:\n\n";

        cout << "===========================\n";
        cout << "===========================\n";
        cout << "(01) : Add a new nurse\n";
        cout << "(02) : Getting nurse details\n";
        cout << "(03) : Remove a nurse\n";
        cout << "(04) : Retrieve nurse details from past history\n";
        cout << "(05) : Getting details of all Added nurses\n\n";
        cout << "(-1) : Go back\n";
        cout << "===========================\n\n";
        cout << "Input your choice: ";
        cin >> appPurpose;

        if (appPurpose == 1)
        {
            nurse nur;
            nur.createPerson();
        }
        else if (appPurpose == 2)
        {
            nurse nur;
            nur.retrieveDetails(1);
            nur.displayDetails();
        }
        else if (appPurpose == 3)
        {
            nurse nur;
            nur.deletePerson();
        }
        else if (appPurpose == 4)
        {
            nurse nur;
            nur.retrieveDetailsFromHistory();
        }
        else if (appPurpose == 5)
        {
            hospital::retriveNursesDetails();
        }
        else if (appPurpose == -1)
        {
            quit = true;
            break;
        }
        else
        {
            cout << "Not valid choice!\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\nPress ENTER to continue...\n";
        cout << endl;

        getchar();
    }
    return;
}
int main()
{
    fstream fst;
    fst.open("./csvFile/appointmentDetails.csv", ios::in);
    string strTemp, s, colum;
    getline(fst, colum);
    getline(fst, strTemp);
    fst.close();
    stringstream str(strTemp);
    getline(str, s, ',');
    getline(str, s, ',');
    int date, month, year;
    if (s != "")
        cout << "\n\nLast usage date (DD-MM-YYYY) : " << s.substr(6, 2) + "-" + s.substr(4, 2) + "-" + s.substr(0, 4) + "\n";
    cout << "\nPlease Input Today's Date (DD-MM-YYYY) :\n\nInput Day: ";
    cin >> date;
    while (date < 1 || date > 31)
    {
        cout << "Not valid Day! Please enter a valid day: ";
        cin >> date;
    }
    cout << "Input Month: ";
    cin >> month;
    while (month < 1 || month > 12)
    {
        cout << "Not valid Month! Please enter a valid month: ";
        cin >> month;
    }
    cout << "Input Year (YYYY): ";
    cin >> year;
    yearDetails = year * 10000 + month * 100 + date;
    if (stoi(((s == "") ? ("0") : (s))) < yearDetails)
    {
        fst.open("./csvFile/strTemp.csv", ios::out);
        fst << colum << "\n";
        fst.close();
        remove("./csvFile/appointmentDetails.csv");
        rename("./csvFile/strTemp.csv", "./csvFile/appointmentDetails.csv");
        fstream fout("./csvFile/strTemp.csv", ios::out);
        fst.open("./csvFile/doctors.csv", ios::in);
        getline(fst, strTemp);
        fout << strTemp << endl;
        while (getline(fst, strTemp))
        {
            if (strTemp.size())
                strTemp[strTemp.size() - 1] = '0';
            fout << strTemp << endl;
        }
        fst.close();
        fout.close();
        remove("./csvFile/doctors.csv");
        rename("./csvFile/strTemp.csv", "./csvFile/doctors.csv");
    }
    else if (stoi(s) > yearDetails && s != "")
    {
        cout << "\nEntered date detected wrong!\nToday's date can't be older than the previous usage date, which is : "
             << s.substr(6, 2) + "-" + s.substr(4, 2) + "-" + s.substr(0, 4) + "\n";
        return 0;
    }
    {
        doctor d1;
        patient pat;
        nurse nur;
        appointment a2;
    }
    while (1)
    {
        int personType = 0;
        cout << "\n=================================================================================\n";
        cout << "\nSelect a person Type:\n\n";

        cout << "============ Welcome to the Home ===============\n";
        cout << "===========================\n";
        cout << "(01) : APPOINTMENTS\n";
        cout << "(02) : PATIENTS\n";
        cout << "(03) : DOCTORS\n";
        cout << "(04) : NURSES\n";
        cout << "(-1) : EXIT\n";
        cout << "===========================\n\n";
        cout << "Input your choice: ";
        cin >> personType;
        cout << "\n=================================================================================\n";
        cout << "\n";
        if (personType == -1)
        {
            cout << "\n=================================================================================\n";
            cout << "\nShutting Down System...\n";
            cout << "\n=================================================================================\n";
            break;
        }
        else if (personType == 1)
        {
            appointmentsControlMenu();
        }
        else if (personType == 2)
        {
            patientsControlMenu();
        }
        else if (personType == 3)
        {
            doctorsControlMenu();
        }
        else if (personType == 4)
        {
            nursesControlMenu();
        }
        else
        {
            cout << "\nInvalid Choice!\n";
        }

        cout << endl;
    }
    {
        doctor d1;
        patient pat;
        nurse nur;
        appointment a2;
    }

    return 0;
}