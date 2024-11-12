#include <iostream>
#include <string>
using namespace std;

struct Patient {
    int id;
    string name;
    string dateOfBirth;
    string contact;
};

void searchPatientByID(Patient patients[], int n, int targetID) {
    for (int i = 0; i < n; i++) {
        if (patients[i].id == targetID) {
            cout << "Bệnh nhân tìm thấy: " << patients[i].name 
                 << ", Ngày sinh: " << patients[i].dateOfBirth 
                 << ", Liên hệ: " << patients[i].contact << endl;
            return;
        }
    }
    cout << "Bệnh nhân không tìm thấy." << endl;
}

int main() {
    Patient patients[] = {
        {1, "Nguyen Van A", "01/01/1980", "0123456789"},
        {2, "Le Thi B", "02/02/1990", "0987654321"},
        {3, "Tran Van C", "03/03/2000", "0765432189"}
    };
    int n = sizeof(patients) / sizeof(patients[0]);
    int targetID = 2;
    searchPatientByID(patients, n, targetID);
    return 0;
}
