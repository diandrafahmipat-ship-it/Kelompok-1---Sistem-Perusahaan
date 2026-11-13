#include "departemen.h"

void inisialisasiList(ListDepartemen &LD) {
    LD.firstParent = NULL;
}

adrParent createParent(DataDepartemen inputDept) {
    adrParent alokasiBaru = new NodeDepartemen;
    alokasiBaru->infoParent = inputDept;
    alokasiBaru->subKaryawan.firstChild = NULL;
    alokasiBaru->nextParent = NULL;
    return alokasiBaru;
}

void insertParent(ListDepartemen &LD, adrParent elemenDept) {
    if (elemenDept == NULL) {
        return;
    }
    if (findParent(LD, elemenDept->infoParent.departmentId) != NULL) {
        cout << "[!] Gagal: DEPARTMENT_ID " << elemenDept->infoParent.departmentId << " sudah terdaftar.\n";
        delete elemenDept;
        return;
    }
    if (LD.firstParent == NULL) {
        LD.firstParent = elemenDept;
    } else {
        adrParent penunjuk = LD.firstParent;
        while (penunjuk->nextParent != NULL) {
            penunjuk = penunjuk->nextParent;
        }
        penunjuk->nextParent = elemenDept;
    }
}

adrParent findParent(ListDepartemen LD, int idDeptCari) {
    adrParent penunjuk = LD.firstParent;
    while (penunjuk != NULL) {
        if (penunjuk->infoParent.departmentId == idDeptCari) {
            return penunjuk;
        }
        penunjuk = penunjuk->nextParent;
    }
    return NULL;
}

void deleteParent(ListDepartemen &LD, int idDeptHapus) {
    if (LD.firstParent == NULL) {
        cout << "[!] List departemen masih kosong.\n";
        return;
    }

    adrParent targetDept = LD.firstParent;
    adrParent pendahuluDept = NULL;

    while (targetDept != NULL && targetDept->infoParent.departmentId != idDeptHapus) {
        pendahuluDept = targetDept;
        targetDept = targetDept->nextParent;
    }

    if (targetDept == NULL) {
        cout << "[!] DEPARTMENT_ID " << idDeptHapus << " tidak ditemukan.\n";
        return;
    }

    adrChild telusurKar = targetDept->subKaryawan.firstChild;
    while (telusurKar != NULL) {
        adrChild hapusKar = telusurKar;
        telusurKar = telusurKar->nextChild;
        delete hapusKar;
    }
    targetDept->subKaryawan.firstChild = NULL;

    if (pendahuluDept == NULL) {
        LD.firstParent = targetDept->nextParent;
    } else {
        pendahuluDept->nextParent = targetDept->nextParent;
    }

    cout << "[+] Departemen " << targetDept->infoParent.departmentName
         << " (DEPARTMENT_ID: " << idDeptHapus << ") beserta seluruh karyawannya telah dihapus.\n";
    delete targetDept;
}

void printParent(ListDepartemen LD) {
    if (LD.firstParent == NULL) {
        cout << "[!] Belum ada data departemen.\n";
        return;
    }

    cout << "\n================================================================================\n";
    cout << left << setw(16) << "DEPARTMENT_ID"
         << setw(24) << "DEPARTMENT_NAME"
         << setw(14) << "MANAGER_ID"
         << setw(14) << "LOCATION_ID"
         << "JML_EMP\n";
    cout << "================================================================================\n";

    adrParent penunjuk = LD.firstParent;
    while (penunjuk != NULL) {
        cout << left << setw(16) << penunjuk->infoParent.departmentId
             << setw(24) << penunjuk->infoParent.departmentName
             << setw(14) << penunjuk->infoParent.managerId
             << setw(14) << penunjuk->infoParent.locationId
             << hitungKaryawanDept(penunjuk) << " orang\n";
        penunjuk = penunjuk->nextParent;
    }
    cout << "================================================================================\n";
}

adrChild createChild(DataKaryawan inputKar) {
    adrChild alokasiKar = new NodeKaryawan;
    alokasiKar->infoChild = inputKar;
    alokasiKar->nextChild = NULL;
    return alokasiKar;
}

int hitungKaryawanDept(adrParent indukDept) {
    if (indukDept == NULL) {
        return 0;
    }
    int jumlah = 0;
    adrChild penunjuk = indukDept->subKaryawan.firstChild;
    while (penunjuk != NULL) {
        jumlah++;
        penunjuk = penunjuk->nextChild;
    }
    return jumlah;
}

void insertChild(adrParent indukDept, adrChild elemenKar) {
    if (indukDept == NULL || elemenKar == NULL) {
        cout << "[!] Gagal menambahkan karyawan: Departemen induk tidak valid.\n";
        return;
    }

    if (findChildPadaDept(indukDept, elemenKar->infoChild.employeeId) != NULL) {
        cout << "[!] Gagal: EMPLOYEE_ID " << elemenKar->infoChild.employeeId << " sudah terdaftar di departemen ini.\n";
        delete elemenKar;
        return;
    }

    elemenKar->infoChild.departmentId = indukDept->infoParent.departmentId;

    if (indukDept->subKaryawan.firstChild == NULL) {
        indukDept->subKaryawan.firstChild = elemenKar;
    } else {
        adrChild penunjuk = indukDept->subKaryawan.firstChild;
        while (penunjuk->nextChild != NULL) {
            penunjuk = penunjuk->nextChild;
        }
        penunjuk->nextChild = elemenKar;
    }
}

adrChild findChildPadaDept(adrParent indukDept, int idKarCari) {
    if (indukDept == NULL) {
        return NULL;
    }
    adrChild penunjuk = indukDept->subKaryawan.firstChild;
    while (penunjuk != NULL) {
        if (penunjuk->infoChild.employeeId == idKarCari) {
            return penunjuk;
        }
        penunjuk = penunjuk->nextChild;
    }
    return NULL;
}

adrChild findChild(ListDepartemen LD, int idKarCari, adrParent &lokasiDept) {
    lokasiDept = NULL;
    adrParent telusurDept = LD.firstParent;
    while (telusurDept != NULL) {
        adrChild ditemukan = findChildPadaDept(telusurDept, idKarCari);
        if (ditemukan != NULL) {
            lokasiDept = telusurDept;
            return ditemukan;
        }
        telusurDept = telusurDept->nextParent;
    }
    return NULL;
}

void deleteChild(adrParent indukDept, int idKarHapus) {
    if (indukDept == NULL) {
        cout << "[!] Departemen induk tidak ditemukan.\n";
        return;
    }
    if (indukDept->subKaryawan.firstChild == NULL) {
        cout << "[!] Departemen " << indukDept->infoParent.departmentName << " tidak memiliki data karyawan.\n";
        return;
    }

    adrChild targetKar = indukDept->subKaryawan.firstChild;
    adrChild pendahuluKar = NULL;

    while (targetKar != NULL && targetKar->infoChild.employeeId != idKarHapus) {
        pendahuluKar = targetKar;
        targetKar = targetKar->nextChild;
    }

    if (targetKar == NULL) {
        cout << "[!] Karyawan dengan EMPLOYEE_ID " << idKarHapus << " tidak ditemukan di departemen " << indukDept->infoParent.departmentName << ".\n";
        return;
    }

    if (pendahuluKar == NULL) {
        indukDept->subKaryawan.firstChild = targetKar->nextChild;
    } else {
        pendahuluKar->nextChild = targetKar->nextChild;
    }

    cout << "[+] Karyawan " << targetKar->infoChild.firstName << " " << targetKar->infoChild.lastName
         << " (EMPLOYEE_ID: " << idKarHapus << ") berhasil dihapus dari departemen " << indukDept->infoParent.departmentName << ".\n";
    delete targetKar;
}

void printChild(adrParent indukDept) {
    if (indukDept == NULL) {
        cout << "[!] Departemen tidak ditemukan.\n";
        return;
    }

    cout << "\n------------------------------------------------------------------------------------------------------------------\n";
    cout << "DEPARTMENT_ID   : " << indukDept->infoParent.departmentId << "\n";
    cout << "DEPARTMENT_NAME : " << indukDept->infoParent.departmentName << "\n";
    cout << "MANAGER_ID      : " << indukDept->infoParent.managerId << " | LOCATION_ID : " << indukDept->infoParent.locationId << "\n";
    cout << "------------------------------------------------------------------------------------------------------------------\n";

    adrChild penunjuk = indukDept->subKaryawan.firstChild;
    if (penunjuk == NULL) {
        cout << "  (Tidak ada karyawan pada departemen ini)\n";
    } else {
        cout << left << setw(8) << "EMP_ID"
             << setw(12) << "FIRST_NAME"
             << setw(12) << "LAST_NAME"
             << setw(10) << "EMAIL"
             << setw(14) << "PHONE_NUMBER"
             << setw(11) << "HIRE_DATE"
             << setw(12) << "JOB_ID"
             << setw(9) << "SALARY"
             << setw(7) << "COMM"
             << setw(8) << "MGR_ID"
             << "DEPT_ID\n";
        cout << "------------------------------------------------------------------------------------------------------------------\n";
        while (penunjuk != NULL) {
            cout << left << setw(8) << penunjuk->infoChild.employeeId
                 << setw(12) << penunjuk->infoChild.firstName
                 << setw(12) << penunjuk->infoChild.lastName
                 << setw(10) << penunjuk->infoChild.email
                 << setw(14) << penunjuk->infoChild.phoneNumber
                 << setw(11) << penunjuk->infoChild.hireDate
                 << setw(12) << penunjuk->infoChild.jobId
                 << setw(9) << penunjuk->infoChild.salary
                 << setw(7) << penunjuk->infoChild.commissionPct
                 << setw(8) << penunjuk->infoChild.managerId
                 << penunjuk->infoChild.departmentId << "\n";
            penunjuk = penunjuk->nextChild;
        }
    }
    cout << "------------------------------------------------------------------------------------------------------------------\n";
}

void printAll(ListDepartemen LD) {
    if (LD.firstParent == NULL) {
        cout << "\n[!] Struktur Multi Linked List kosong.\n";
        return;
    }

    cout << "\n==================================================================================================================\n";
    cout << "              STRUKTUR MULTI LINKED LIST: DEPARTMENTS.CSV (PARENT) & EMPLOYEES.CSV (CHILD)                        \n";
    cout << "==================================================================================================================\n";

    adrParent telusurDept = LD.firstParent;
    while (telusurDept != NULL) {
        cout << "\n[PARENT - DEPT_ID: " << telusurDept->infoParent.departmentId << "] "
             << telusurDept->infoParent.departmentName
             << " | MANAGER_ID: " << telusurDept->infoParent.managerId
             << " | LOCATION_ID: " << telusurDept->infoParent.locationId
             << " | Total Child: " << hitungKaryawanDept(telusurDept) << "\n";

        adrChild telusurKar = telusurDept->subKaryawan.firstChild;
        if (telusurKar == NULL) {
            cout << "   +-- (Belum ada karyawan terdaftar)\n";
        } else {
            while (telusurKar != NULL) {
                string cabang = (telusurKar->nextChild == NULL) ? "   +-- " : "   |-- ";
                string namaLengkap = telusurKar->infoChild.firstName + " " + telusurKar->infoChild.lastName;
                cout << cabang << "[ID:" << right << setw(3) << telusurKar->infoChild.employeeId << "] "
                     << left << setw(18) << namaLengkap
                     << " | Email:" << setw(9) << telusurKar->infoChild.email
                     << " | Ph:" << setw(12) << telusurKar->infoChild.phoneNumber
                     << " | Hire:" << setw(9) << telusurKar->infoChild.hireDate
                     << " | Job:" << setw(10) << telusurKar->infoChild.jobId
                     << " | $" << setw(6) << telusurKar->infoChild.salary
                     << " | C:" << setw(2) << telusurKar->infoChild.commissionPct
                     << " | Mgr:" << telusurKar->infoChild.managerId << "\n";
                telusurKar = telusurKar->nextChild;
            }
        }
        telusurDept = telusurDept->nextParent;
    }
    cout << "\n==================================================================================================================\n";
}

bool rotasiKaryawan(ListDepartemen &LD, int idKarTarget, int idDeptLama, int idDeptBaru) {
    if (idDeptLama == idDeptBaru) {
        cout << "[!] DEPARTMENT_ID asal dan tujuan tidak boleh sama.\n";
        return false;
    }

    adrParent deptAsal = findParent(LD, idDeptLama);
    adrParent deptTujuan = findParent(LD, idDeptBaru);

    if (deptAsal == NULL || deptTujuan == NULL) {
        cout << "[!] DEPARTMENT_ID asal atau tujuan tidak ditemukan.\n";
        return false;
    }

    adrChild nodePindah = deptAsal->subKaryawan.firstChild;
    adrChild pendahulu = NULL;

    while (nodePindah != NULL && nodePindah->infoChild.employeeId != idKarTarget) {
        pendahulu = nodePindah;
        nodePindah = nodePindah->nextChild;
    }

    if (nodePindah == NULL) {
        cout << "[!] EMPLOYEE_ID " << idKarTarget << " tidak ditemukan pada departemen " << deptAsal->infoParent.departmentName << ".\n";
        return false;
    }

    if (pendahulu == NULL) {
        deptAsal->subKaryawan.firstChild = nodePindah->nextChild;
    } else {
        pendahulu->nextChild = nodePindah->nextChild;
    }

    nodePindah->nextChild = NULL;
    insertChild(deptTujuan, nodePindah);

    cout << "[+] Mutasi Berhasil: " << nodePindah->infoChild.firstName << " " << nodePindah->infoChild.lastName
         << " (EMP_ID: " << idKarTarget << ") dipindahkan dari " << deptAsal->infoParent.departmentName
         << " (ID: " << idDeptLama << ") ke " << deptTujuan->infoParent.departmentName << " (ID: " << idDeptBaru << ").\n";
    return true;
}

void evaluasiGajiDepartemen(ListDepartemen LD) {
    if (LD.firstParent == NULL) {
        cout << "[!] Data departemen masih kosong.\n";
        return;
    }

    long long akumulasiGajiPerusahaan = 0;
    int akumulasiKaryawan = 0;
    adrChild karGajiTertinggi = NULL;
    adrParent deptGajiTertinggi = NULL;

    cout << "\n========================================================================================\n";
    cout << "               ANALISIS ANGGARAN GAJI (SALARY) DEPARTEMEN PERUSAHAAN                    \n";
    cout << "========================================================================================\n";
    cout << left << setw(12) << "DEPT_ID"
         << setw(24) << "DEPARTMENT_NAME"
         << setw(16) << "JML_KARYAWAN"
         << setw(18) << "TOTAL_SALARY"
         << "RATA_RATA_SALARY\n";
    cout << "----------------------------------------------------------------------------------------\n";

    adrParent telusurDept = LD.firstParent;
    while (telusurDept != NULL) {
        long long totalGajiDept = 0;
        int cacahKar = 0;
        adrChild telusurKar = telusurDept->subKaryawan.firstChild;

        while (telusurKar != NULL) {
            totalGajiDept += telusurKar->infoChild.salary;
            cacahKar++;
            if (karGajiTertinggi == NULL || telusurKar->infoChild.salary > karGajiTertinggi->infoChild.salary) {
                karGajiTertinggi = telusurKar;
                deptGajiTertinggi = telusurDept;
            }
            telusurKar = telusurKar->nextChild;
        }

        long long rataGaji = (cacahKar > 0) ? (totalGajiDept / cacahKar) : 0;
        cout << left << setw(12) << telusurDept->infoParent.departmentId
             << setw(24) << telusurDept->infoParent.departmentName
             << setw(16) << cacahKar
             << "$" << left << setw(17) << totalGajiDept
             << "$" << rataGaji << "\n";

        akumulasiGajiPerusahaan += totalGajiDept;
        akumulasiKaryawan += cacahKar;
        telusurDept = telusurDept->nextParent;
    }

    cout << "----------------------------------------------------------------------------------------\n";
    cout << "Total Seluruh Karyawan Aktif : " << akumulasiKaryawan << " Orang\n";
    cout << "Total Beban Gaji Perusahaan  : $" << akumulasiGajiPerusahaan << "\n";
    if (karGajiTertinggi != NULL && deptGajiTertinggi != NULL) {
        cout << "Karyawan Gaji Tertinggi      : " << karGajiTertinggi->infoChild.firstName << " " << karGajiTertinggi->infoChild.lastName
             << " (EMP_ID: " << karGajiTertinggi->infoChild.employeeId << ", JOB_ID: " << karGajiTertinggi->infoChild.jobId
             << ", Dept: " << deptGajiTertinggi->infoParent.departmentName << ") sebesar $" << karGajiTertinggi->infoChild.salary << "\n";
    }
    cout << "========================================================================================\n";
}

void muatDatasetCSV(ListDepartemen &LD) {
    insertParent(LD, createParent({10, "Administration", 200, 1700}));
    insertParent(LD, createParent({20, "Marketing", 201, 1800}));
    insertParent(LD, createParent({30, "Purchasing", 114, 1700}));
    insertParent(LD, createParent({40, "Human Resources", 203, 2400}));
    insertParent(LD, createParent({50, "Shipping", 121, 1500}));
    insertParent(LD, createParent({60, "IT", 103, 1400}));
    insertParent(LD, createParent({70, "Public Relations", 204, 2700}));
    insertParent(LD, createParent({90, "Executive", 100, 1700}));
    insertParent(LD, createParent({100, "Finance", 108, 1700}));
    insertParent(LD, createParent({110, "Accounting", 205, 1700}));

    adrParent d10 = findParent(LD, 10);
    insertChild(d10, createChild({200, "Jennifer", "Whalen", "JWHALEN", "515.123.4444", "17-SEP-03", "AD_ASST", 4400, "-", "101", 10}));

    adrParent d20 = findParent(LD, 20);
    insertChild(d20, createChild({201, "Michael", "Hartstein", "MHARTSTE", "515.123.5555", "17-FEB-04", "MK_MAN", 13000, "-", "100", 20}));
    insertChild(d20, createChild({202, "Pat", "Fay", "PFAY", "603.123.6666", "17-AUG-05", "MK_REP", 6000, "-", "201", 20}));

    adrParent d30 = findParent(LD, 30);
    insertChild(d30, createChild({114, "Den", "Raphaely", "DRAPHEAL", "515.127.4561", "07-DEC-02", "PU_MAN", 11000, "-", "100", 30}));
    insertChild(d30, createChild({115, "Alexander", "Khoo", "AKHOO", "515.127.4562", "18-MAY-03", "PU_CLERK", 3100, "-", "114", 30}));

    adrParent d40 = findParent(LD, 40);
    insertChild(d40, createChild({203, "Susan", "Mavris", "SMAVRIS", "515.123.7777", "07-JUN-02", "HR_REP", 6500, "-", "101", 40}));

    adrParent d50 = findParent(LD, 50);
    insertChild(d50, createChild({198, "Donald", "OConnell", "DOCONNEL", "650.507.9833", "21-JUN-07", "SH_CLERK", 2600, "-", "124", 50}));
    insertChild(d50, createChild({199, "Douglas", "Grant", "DGRANT", "650.507.9844", "13-JAN-08", "SH_CLERK", 2600, "-", "124", 50}));
    insertChild(d50, createChild({120, "Matthew", "Weiss", "MWEISS", "650.123.1234", "18-JUL-04", "ST_MAN", 8000, "-", "100", 50}));
    insertChild(d50, createChild({121, "Adam", "Fripp", "AFRIPP", "650.123.2234", "10-APR-05", "ST_MAN", 8200, "-", "100", 50}));

    adrParent d60 = findParent(LD, 60);
    insertChild(d60, createChild({103, "Alexander", "Hunold", "AHUNOLD", "590.423.4567", "03-JAN-06", "IT_PROG", 9000, "-", "102", 60}));
    insertChild(d60, createChild({104, "Bruce", "Ernst", "BERNST", "590.423.4568", "21-MAY-07", "IT_PROG", 6000, "-", "103", 60}));
    insertChild(d60, createChild({105, "David", "Austin", "DAUSTIN", "590.423.4569", "25-JUN-05", "IT_PROG", 4800, "-", "103", 60}));
    insertChild(d60, createChild({106, "Valli", "Pataballa", "VPATABAL", "590.423.4560", "05-FEB-06", "IT_PROG", 4800, "-", "103", 60}));
    insertChild(d60, createChild({107, "Diana", "Lorentz", "DLORENTZ", "590.423.5567", "07-FEB-07", "IT_PROG", 4200, "-", "103", 60}));

    adrParent d70 = findParent(LD, 70);
    insertChild(d70, createChild({204, "Hermann", "Baer", "HBAER", "515.123.8888", "07-JUN-02", "PR_REP", 10000, "-", "101", 70}));

    adrParent d90 = findParent(LD, 90);
    insertChild(d90, createChild({100, "Steven", "King", "SKING", "515.123.4567", "17-JUN-03", "AD_PRES", 24000, "-", "-", 90}));
    insertChild(d90, createChild({101, "Neena", "Kochhar", "NKOCHHAR", "515.123.4568", "21-SEP-05", "AD_VP", 17000, "-", "100", 90}));
    insertChild(d90, createChild({102, "Lex", "De Haan", "LDEHAAN", "515.123.4569", "13-JAN-01", "AD_VP", 17000, "-", "100", 90}));

    adrParent d100 = findParent(LD, 100);
    insertChild(d100, createChild({108, "Nancy", "Greenberg", "NGREENBE", "515.124.4569", "17-AUG-02", "FI_MGR", 12008, "-", "101", 100}));
    insertChild(d100, createChild({109, "Daniel", "Faviet", "DFAVIET", "515.124.4169", "16-AUG-02", "FI_ACCOUNT", 9000, "-", "108", 100}));
    insertChild(d100, createChild({110, "John", "Chen", "JCHEN", "515.124.4269", "28-SEP-05", "FI_ACCOUNT", 8200, "-", "108", 100}));

    adrParent d110 = findParent(LD, 110);
    insertChild(d110, createChild({205, "Shelley", "Higgins", "SHIGGINS", "515.123.8080", "07-JUN-02", "AC_MGR", 12008, "-", "101", 110}));
    insertChild(d110, createChild({206, "William", "Gietz", "WGIETZ", "515.123.8181", "07-JUN-02", "AC_ACCOUNT", 8300, "-", "205", 110}));
}
