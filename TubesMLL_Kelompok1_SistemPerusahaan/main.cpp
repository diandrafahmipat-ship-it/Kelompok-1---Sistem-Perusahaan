#include "departemen.h"

void tampilMenu() {
    cout << "\n==========================================================================\n";
    cout << "   SISTEM PERUSAHAAN MULTI LINKED LIST (DEPARTMENTS.CSV & EMPLOYEES.CSV)  \n";
    cout << "==========================================================================\n";
    cout << " [1] Insert Parent  (Tambah Departemen Baru)\n";
    cout << " [2] Delete Parent  (Hapus Departemen Beserta Seluruh Karyawannya)\n";
    cout << " [3] Search Parent  (Cari Departemen Berdasarkan DEPARTMENT_ID)\n";
    cout << " [4] Print Parent   (Tampilkan Seluruh Tabel DEPARTMENTS)\n";
    cout << " [5] Insert Child   (Tambah Karyawan ke Departemen Tertentu)\n";
    cout << " [6] Delete Child   (Hapus Karyawan dari Departemen Tertentu)\n";
    cout << " [7] Find Child     (Cari Karyawan Berdasarkan EMPLOYEE_ID)\n";
    cout << " [8] Print Child    (Tampilkan Tabel EMPLOYEES Berdasarkan Departemen)\n";
    cout << " [9] Print All      (Tampilkan Seluruh Struktur Multi Linked List)\n";
    cout << " [10] Fitur Kreatif : Mutasi / Rotasi Karyawan Lintas Departemen\n";
    cout << " [11] Fitur Kreatif : Evaluasi & Rekapitulasi Gaji (Salary) Departemen\n";
    cout << " [0] Keluar Program\n";
    cout << "==========================================================================\n";
    cout << "Pilih menu operasi (0-11): ";
}

int main() {
    ListDepartemen daftarUtama;
    inisialisasiList(daftarUtama);
    muatDatasetCSV(daftarUtama);

    cout << "[+] Dataset CSV berhasil dimuat (10 Departemen & 24 Karyawan dengan 11 atribut lengkap).\n";

    int menuDipilih = -1;
    while (menuDipilih != 0) {
        tampilMenu();
        if (!(cin >> menuDipilih)) {
            cin.clear();
            cin.ignore(1000, '\n');
            menuDipilih = -1;
            cout << "[!] Input harus berupa angka.\n";
            continue;
        }
        cin.ignore();

        if (menuDipilih == 1) {
            DataDepartemen dBaru;
            cout << "\n--- Insert Parent (Tambah Departemen) ---\n";
            cout << "Masukkan DEPARTMENT_ID (contoh: 80)        : ";
            cin >> dBaru.departmentId;
            cin.ignore();
            cout << "Masukkan DEPARTMENT_NAME (contoh: Sales)   : ";
            getline(cin, dBaru.departmentName);
            cout << "Masukkan MANAGER_ID (contoh: 145)          : ";
            cin >> dBaru.managerId;
            cout << "Masukkan LOCATION_ID (contoh: 2500)        : ";
            cin >> dBaru.locationId;
            cin.ignore();

            insertParent(daftarUtama, createParent(dBaru));
            cout << "[+] Proses penambahan departemen selesai.\n";

        } else if (menuDipilih == 2) {
            int idHapus;
            cout << "\n--- Delete Parent (Hapus Departemen) ---\n";
            cout << "Masukkan DEPARTMENT_ID yang akan dihapus: ";
            cin >> idHapus;
            cin.ignore();
            deleteParent(daftarUtama, idHapus);

        } else if (menuDipilih == 3) {
            int idCari;
            cout << "\n--- Search Parent (Cari Departemen) ---\n";
            cout << "Masukkan DEPARTMENT_ID yang dicari: ";
            cin >> idCari;
            cin.ignore();
            adrParent hasilDept = findParent(daftarUtama, idCari);
            if (hasilDept != NULL) {
                cout << "\n[+] Departemen Ditemukan!\n";
                cout << "    DEPARTMENT_ID   : " << hasilDept->infoParent.departmentId << "\n";
                cout << "    DEPARTMENT_NAME : " << hasilDept->infoParent.departmentName << "\n";
                cout << "    MANAGER_ID      : " << hasilDept->infoParent.managerId << "\n";
                cout << "    LOCATION_ID     : " << hasilDept->infoParent.locationId << "\n";
                cout << "    Jumlah Karyawan : " << hitungKaryawanDept(hasilDept) << " orang\n";
            } else {
                cout << "[!] DEPARTMENT_ID " << idCari << " tidak ditemukan.\n";
            }

        } else if (menuDipilih == 4) {
            printParent(daftarUtama);

        } else if (menuDipilih == 5) {
            int idTargetDept;
            cout << "\n--- Insert Child (Tambah Karyawan ke Departemen) ---\n";
            cout << "Masukkan DEPARTMENT_ID tujuan: ";
            cin >> idTargetDept;
            cin.ignore();

            adrParent nodeInduk = findParent(daftarUtama, idTargetDept);
            if (nodeInduk == NULL) {
                cout << "[!] DEPARTMENT_ID " << idTargetDept << " tidak ditemukan.\n";
            } else {
                DataKaryawan kBaru;
                cout << "Masukkan EMPLOYEE_ID (contoh: 111)           : ";
                cin >> kBaru.employeeId;
                cin.ignore();
                cout << "Masukkan FIRST_NAME (contoh: Ismael)         : ";
                getline(cin, kBaru.firstName);
                cout << "Masukkan LAST_NAME (contoh: Sciarra)         : ";
                getline(cin, kBaru.lastName);
                cout << "Masukkan EMAIL (contoh: ISCIARRA)            : ";
                getline(cin, kBaru.email);
                cout << "Masukkan PHONE_NUMBER (contoh: 515.124.4369) : ";
                getline(cin, kBaru.phoneNumber);
                cout << "Masukkan HIRE_DATE (contoh: 30-SEP-05)       : ";
                getline(cin, kBaru.hireDate);
                cout << "Masukkan JOB_ID (contoh: FI_ACCOUNT)         : ";
                getline(cin, kBaru.jobId);
                cout << "Masukkan SALARY (contoh: 7700)               : ";
                cin >> kBaru.salary;
                cin.ignore();
                cout << "Masukkan COMMISSION_PCT (isi - jika kosong)  : ";
                getline(cin, kBaru.commissionPct);
                cout << "Masukkan MANAGER_ID (contoh: 108)            : ";
                getline(cin, kBaru.managerId);
                kBaru.departmentId = idTargetDept;

                int sebelum = hitungKaryawanDept(nodeInduk);
                insertChild(nodeInduk, createChild(kBaru));
                if (hitungKaryawanDept(nodeInduk) > sebelum) {
                    cout << "[+] Karyawan berhasil ditambahkan ke departemen " << nodeInduk->infoParent.departmentName << ".\n";
                }
            }

        } else if (menuDipilih == 6) {
            int idTargetDept, idKarHapus;
            cout << "\n--- Delete Child (Hapus Karyawan dari Departemen) ---\n";
            cout << "Masukkan DEPARTMENT_ID induk          : ";
            cin >> idTargetDept;
            cout << "Masukkan EMPLOYEE_ID yang akan dihapus: ";
            cin >> idKarHapus;
            cin.ignore();

            adrParent nodeInduk = findParent(daftarUtama, idTargetDept);
            deleteChild(nodeInduk, idKarHapus);

        } else if (menuDipilih == 7) {
            int idKarCari;
            cout << "\n--- Find Child (Cari Data Karyawan) ---\n";
            cout << "Masukkan EMPLOYEE_ID yang dicari: ";
            cin >> idKarCari;
            cin.ignore();

            adrParent deptInduk = NULL;
            adrChild hasilKar = findChild(daftarUtama, idKarCari, deptInduk);
            if (hasilKar != NULL && deptInduk != NULL) {
                cout << "\n[+] Karyawan Ditemukan!\n";
                cout << "    EMPLOYEE_ID     : " << hasilKar->infoChild.employeeId << "\n";
                cout << "    FIRST_NAME      : " << hasilKar->infoChild.firstName << "\n";
                cout << "    LAST_NAME       : " << hasilKar->infoChild.lastName << "\n";
                cout << "    EMAIL           : " << hasilKar->infoChild.email << "\n";
                cout << "    PHONE_NUMBER    : " << hasilKar->infoChild.phoneNumber << "\n";
                cout << "    HIRE_DATE       : " << hasilKar->infoChild.hireDate << "\n";
                cout << "    JOB_ID          : " << hasilKar->infoChild.jobId << "\n";
                cout << "    SALARY          : $" << hasilKar->infoChild.salary << "\n";
                cout << "    COMMISSION_PCT  : " << hasilKar->infoChild.commissionPct << "\n";
                cout << "    MANAGER_ID      : " << hasilKar->infoChild.managerId << "\n";
                cout << "    DEPARTMENT_ID   : " << hasilKar->infoChild.departmentId
                     << " (" << deptInduk->infoParent.departmentName << ")\n";
            } else {
                cout << "[!] Karyawan dengan EMPLOYEE_ID " << idKarCari << " tidak ditemukan.\n";
            }

        } else if (menuDipilih == 8) {
            int idTargetDept;
            cout << "\n--- Print Child (Tampilkan Karyawan Berdasarkan Departemen) ---\n";
            cout << "Masukkan DEPARTMENT_ID: ";
            cin >> idTargetDept;
            cin.ignore();
            printChild(findParent(daftarUtama, idTargetDept));

        } else if (menuDipilih == 9) {
            printAll(daftarUtama);

        } else if (menuDipilih == 10) {
            int idKar, idAsal, idTujuan;
            cout << "\n--- Mutasi / Rotasi Karyawan Lintas Departemen ---\n";
            cout << "Masukkan EMPLOYEE_ID yang akan dimutasi : ";
            cin >> idKar;
            cout << "Masukkan DEPARTMENT_ID Asal             : ";
            cin >> idAsal;
            cout << "Masukkan DEPARTMENT_ID Tujuan           : ";
            cin >> idTujuan;
            cin.ignore();
            rotasiKaryawan(daftarUtama, idKar, idAsal, idTujuan);

        } else if (menuDipilih == 11) {
            evaluasiGajiDepartemen(daftarUtama);

        } else if (menuDipilih == 0) {
            cout << "\nProgram selesai dijalankan.\n";
        } else {
            cout << "[!] Pilihan menu tidak valid.\n";
        }
    }

    return 0;
}
