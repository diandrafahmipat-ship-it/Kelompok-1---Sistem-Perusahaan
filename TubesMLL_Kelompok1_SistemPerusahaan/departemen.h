#ifndef DEPARTEMEN_H_INCLUDED
#define DEPARTEMEN_H_INCLUDED

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct DataDepartemen {
    int departmentId;
    string departmentName;
    int managerId;
    int locationId;
};

struct DataKaryawan {
    int employeeId;
    string firstName;
    string lastName;
    string email;
    string phoneNumber;
    string hireDate;
    string jobId;
    int salary;
    string commissionPct;
    string managerId;
    int departmentId;
};

typedef struct NodeDepartemen *adrParent;
typedef struct NodeKaryawan *adrChild;

struct ListKaryawan {
    adrChild firstChild;
};

struct NodeKaryawan {
    DataKaryawan infoChild;
    adrChild nextChild;
};

struct NodeDepartemen {
    DataDepartemen infoParent;
    ListKaryawan subKaryawan;
    adrParent nextParent;
};

struct ListDepartemen {
    adrParent firstParent;
};

void inisialisasiList(ListDepartemen &LD);
adrParent createParent(DataDepartemen inputDept);
void insertParent(ListDepartemen &LD, adrParent elemenDept);
adrParent findParent(ListDepartemen LD, int idDeptCari);
void deleteParent(ListDepartemen &LD, int idDeptHapus);
void printParent(ListDepartemen LD);

adrChild createChild(DataKaryawan inputKar);
int hitungKaryawanDept(adrParent indukDept);
void insertChild(adrParent indukDept, adrChild elemenKar);
adrChild findChildPadaDept(adrParent indukDept, int idKarCari);
adrChild findChild(ListDepartemen LD, int idKarCari, adrParent &lokasiDept);
void deleteChild(adrParent indukDept, int idKarHapus);
void printChild(adrParent indukDept);

void printAll(ListDepartemen LD);

bool rotasiKaryawan(ListDepartemen &LD, int idKarTarget, int idDeptLama, int idDeptBaru);
void evaluasiGajiDepartemen(ListDepartemen LD);
void muatDatasetCSV(ListDepartemen &LD);

#endif
