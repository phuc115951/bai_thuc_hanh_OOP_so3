
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>
#include <cctype>
#include <cmath>
#include <utility>
using namespace std;

int nhapSoNguyen(string thongBao) {
    int giaTri;
    while (true) {
        cout << thongBao;
        if (cin >> giaTri) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return giaTri;
        }
        cout << "Du lieu khong hop le!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double nhapSoThuc(string thongBao) {
    double giaTri;
    while (true) {
        cout << thongBao;
        if (cin >> giaTri && isfinite(giaTri) && giaTri >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return giaTri;
        }
        cout << "Du lieu khong hop le!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

class Vehicle {
private:
    int maXe;
    string loaiXe;
    time_t thoiGianVao;
    double thoiGianDo;
    double phiDo;

public:
    Vehicle(int ma, string loai, double gio) {
        maXe = ma;
        loaiXe = loai;
        thoiGianVao = time(NULL);
        thoiGianDo = gio;
        phiDo = tinhPhi();
    }

    int layMaXe() const {
        return maXe;
    }

    string layLoaiXe() const {
        return loaiXe;
    }

    double layPhiDo() const {
        return phiDo;
    }

    double layThoiGianDo() const {
        return thoiGianDo;
    }

    void datMaXe(int ma) {
        maXe = ma;
    }

    void datLoaiXe(string loai) {
        loaiXe = loai;
        phiDo = tinhPhi();
    }

    void datThoiGianDo(double gio) {
        if (gio >= 0 && isfinite(gio)) {
            thoiGianDo = gio;
            phiDo = tinhPhi();
        }
    }

    double tinhPhi() const {
        double donGia = 0;

        if (loaiXe == "Xe may")
            donGia = 5000;
        else if (loaiXe == "O to")
            donGia = 15000;
        else if (loaiXe == "Xe tai")
            donGia = 20000;

        return donGia * thoiGianDo;
    }

    void hienThi() const {
        cout << left << setw(12) << maXe
             << setw(15) << loaiXe
             << setw(15) << thoiGianDo
             << fixed << setprecision(0) << phiDo << endl;

        tm* thoiGian = localtime(&thoiGianVao);

        if (thoiGian != NULL) {
            cout << "Thoi gian vao bai: "
                 << setfill('0')
                 << setw(2) << thoiGian->tm_mday << "/"
                 << setw(2) << thoiGian->tm_mon + 1 << "/"
                 << thoiGian->tm_year + 1900 << " "
                 << setw(2) << thoiGian->tm_hour << ":"
                 << setw(2) << thoiGian->tm_min << ":"
                 << setw(2) << thoiGian->tm_sec
                 << setfill(' ') << endl;
        }
    }
};

class ParkingLot {
private:
    int maBaiDo;
    char kichThuoc;
    int sucChua;
    int soXeHienTai;
    Vehicle** danhSachXe;

    void tangSucChua(int sucChuaMoi) {
        if (sucChuaMoi <= sucChua)
            return;

        Vehicle** mangMoi = new Vehicle*[sucChuaMoi]();

        for (int i = 0; i < soXeHienTai; i++)
            mangMoi[i] = danhSachXe[i];

        delete[] danhSachXe;
        danhSachXe = mangMoi;
        sucChua = sucChuaMoi;
    }

public:
    ParkingLot(int ma, char kichThuocBai) {
        maBaiDo = ma;
        kichThuoc = toupper((unsigned char)kichThuocBai);

        if (kichThuoc != 'S' &&
            kichThuoc != 'M' &&
            kichThuoc != 'L')
            kichThuoc = 'S';

        sucChua = (kichThuoc == 'S') ? 1 :
                  (kichThuoc == 'M') ? 2 : 3;

        soXeHienTai = 0;
        danhSachXe = new Vehicle*[sucChua]();
    }

    ~ParkingLot() {
        for (int i = 0; i < soXeHienTai; i++)
            delete danhSachXe[i];

        delete[] danhSachXe;
    }

    ParkingLot(const ParkingLot& khac) {
        maBaiDo = khac.maBaiDo;
        kichThuoc = khac.kichThuoc;
        sucChua = khac.sucChua;
        soXeHienTai = khac.soXeHienTai;

        danhSachXe = new Vehicle*[sucChua]();

        try {
            for (int i = 0; i < soXeHienTai; i++)
                danhSachXe[i] = new Vehicle(*khac.danhSachXe[i]);
        }
        catch (...) {
            for (int i = 0; i < soXeHienTai; i++)
                delete danhSachXe[i];

            delete[] danhSachXe;
            throw;
        }
    }

    ParkingLot& operator=(const ParkingLot& khac) {
        if (this == &khac)
            return *this;

        ParkingLot tam(khac);

        swap(maBaiDo, tam.maBaiDo);
        swap(kichThuoc, tam.kichThuoc);
        swap(sucChua, tam.sucChua);
        swap(soXeHienTai, tam.soXeHienTai);
        swap(danhSachXe, tam.danhSachXe);

        return *this;
    }

    int layMaBaiDo() const {
        return maBaiDo;
    }

    int laySoXeHienTai() const {
        return soXeHienTai;
    }

    int laySucChua() const {
        return sucChua;
    }

    char layKichThuoc() const {
        return kichThuoc;
    }

    bool themXe(const Vehicle& xe) {
        if (soXeHienTai == sucChua)
            tangSucChua(sucChua * 2);

        danhSachXe[soXeHienTai] = new Vehicle(xe);
        soXeHienTai++;

        cout << "Them xe thanh cong!\n";
        return true;
    }

    bool xoaXe(int ma) {
        for (int i = 0; i < soXeHienTai; i++) {
            if (danhSachXe[i]->layMaXe() == ma) {
                delete danhSachXe[i];

                for (int j = i; j < soXeHienTai - 1; j++)
                    danhSachXe[j] = danhSachXe[j + 1];

                soXeHienTai--;
                danhSachXe[soXeHienTai] = NULL;

                cout << "Xoa xe thanh cong!\n";
                return true;
            }
        }

        cout << "Khong tim thay xe!\n";
        return false;
    }

    Vehicle* timXe(int ma) const {
        for (int i = 0; i < soXeHienTai; i++) {
            if (danhSachXe[i]->layMaXe() == ma)
                return danhSachXe[i];
        }

        return NULL;
    }

    void hienThiDanhSachXe() const {
        cout << "\nBai do ID: " << maBaiDo
             << "\nKich thuoc: " << kichThuoc
             << "\nSuc chua: " << soXeHienTai
             << "/" << sucChua << endl;

        if (soXeHienTai == 0) {
            cout << "Bai do chua co xe!\n";
            return;
        }

        cout << left << setw(12) << "Ma xe"
             << setw(15) << "Loai xe"
             << setw(15) << "Gio do"
             << "Phi do\n";

        cout << string(57, '-') << endl;

        for (int i = 0; i < soXeHienTai; i++)
            danhSachXe[i]->hienThi();
    }

    bool hienThiTheoLoai(string loai) const {
        bool timThay = false;

        for (int i = 0; i < soXeHienTai; i++) {
            if (danhSachXe[i]->layLoaiXe() == loai) {
                if (!timThay) {
                    cout << left << setw(12) << "Ma xe"
                         << setw(15) << "Loai xe"
                         << setw(15) << "Gio do"
                         << "Phi do\n";
                }

                danhSachXe[i]->hienThi();
                timThay = true;
            }
        }

        return timThay;
    }

    double tinhTongPhi() const {
        double tongPhi = 0;

        for (int i = 0; i < soXeHienTai; i++)
            tongPhi += danhSachXe[i]->layPhiDo();

        return tongPhi;
    }
};

class SystemInterface {
private:
    int sucChuaBaiDo;
    int soBaiDoHienTai;
    ParkingLot** danhSachBaiDo;

    void tangSucChua(int sucChuaMoi) {
        if (sucChuaMoi <= sucChuaBaiDo)
            return;

        ParkingLot** mangMoi = new ParkingLot*[sucChuaMoi]();

        for (int i = 0; i < soBaiDoHienTai; i++)
            mangMoi[i] = danhSachBaiDo[i];

        delete[] danhSachBaiDo;
        danhSachBaiDo = mangMoi;
        sucChuaBaiDo = sucChuaMoi;
    }

public:
    SystemInterface() {
        sucChuaBaiDo = 5;
        soBaiDoHienTai = 0;
        danhSachBaiDo = new ParkingLot*[sucChuaBaiDo]();
    }

    ~SystemInterface() {
        for (int i = 0; i < soBaiDoHienTai; i++)
            delete danhSachBaiDo[i];

        delete[] danhSachBaiDo;
    }

    SystemInterface(const SystemInterface& khac) {
        sucChuaBaiDo = khac.sucChuaBaiDo;
        soBaiDoHienTai = khac.soBaiDoHienTai;
        danhSachBaiDo = new ParkingLot*[sucChuaBaiDo]();

        try {
            for (int i = 0; i < soBaiDoHienTai; i++)
                danhSachBaiDo[i] =
                    new ParkingLot(*khac.danhSachBaiDo[i]);
        }
        catch (...) {
            for (int i = 0; i < soBaiDoHienTai; i++)
                delete danhSachBaiDo[i];

            delete[] danhSachBaiDo;
            throw;
        }
    }

    SystemInterface& operator=(const SystemInterface& khac) {
        if (this == &khac)
            return *this;

        SystemInterface tam(khac);

        swap(sucChuaBaiDo, tam.sucChuaBaiDo);
        swap(soBaiDoHienTai, tam.soBaiDoHienTai);
        swap(danhSachBaiDo, tam.danhSachBaiDo);

        return *this;
    }

    ParkingLot* timBaiDo(int ma) const {
        for (int i = 0; i < soBaiDoHienTai; i++) {
            if (danhSachBaiDo[i]->layMaBaiDo() == ma)
                return danhSachBaiDo[i];
        }

        return NULL;
    }

    void taoBaiDo() {
        int ma = nhapSoNguyen("Nhap ma bai do: ");

        if (timBaiDo(ma) != NULL) {
            cout << "Ma bai do da ton tai!\n";
            return;
        }

        char kichThuoc;
        cout << "Nhap kich thuoc (S/M/L): ";
        cin >> kichThuoc;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        kichThuoc = toupper((unsigned char)kichThuoc);

        if (kichThuoc != 'S' &&
            kichThuoc != 'M' &&
            kichThuoc != 'L') {
            cout << "Kich thuoc khong hop le!\n";
            return;
        }

        if (soBaiDoHienTai == sucChuaBaiDo)
            tangSucChua(sucChuaBaiDo * 2);

        danhSachBaiDo[soBaiDoHienTai] =
            new ParkingLot(ma, kichThuoc);

        soBaiDoHienTai++;
        cout << "Tao bai do thanh cong!\n";
    }

    void themXeVaoBai() {
        int maBai = nhapSoNguyen("Nhap ma bai do: ");
        ParkingLot* baiDo = timBaiDo(maBai);

        if (baiDo == NULL) {
            cout << "Khong tim thay bai do!\n";
            return;
        }

        int maXe = nhapSoNguyen("Nhap ma xe: ");

        for (int i = 0; i < soBaiDoHienTai; i++) {
            if (danhSachBaiDo[i]->timXe(maXe) != NULL) {
                cout << "Ma xe da ton tai!\n";
                return;
            }
        }

        cout << "\n1. Xe may\n2. O to\n3. Xe tai\n";

        int luaChon = nhapSoNguyen("Chon loai xe: ");
        string loaiXe;

        switch (luaChon) {
            case 1: loaiXe = "Xe may"; break;
            case 2: loaiXe = "O to"; break;
            case 3: loaiXe = "Xe tai"; break;
            default:
                cout << "Loai xe khong hop le!\n";
                return;
        }

        double gio = nhapSoThuc("Nhap thoi gian do (gio): ");

        Vehicle xeMoi(maXe, loaiXe, gio);
        baiDo->themXe(xeMoi);
    }

    void xoaBaiDo() {
        int ma = nhapSoNguyen("Nhap ma bai do can xoa: ");
        int viTri = -1;

        for (int i = 0; i < soBaiDoHienTai; i++) {
            if (danhSachBaiDo[i]->layMaBaiDo() == ma) {
                viTri = i;
                break;
            }
        }

        if (viTri == -1) {
            cout << "Khong tim thay bai do!\n";
            return;
        }

        delete danhSachBaiDo[viTri];

        for (int i = viTri; i < soBaiDoHienTai - 1; i++)
            danhSachBaiDo[i] = danhSachBaiDo[i + 1];

        soBaiDoHienTai--;
        danhSachBaiDo[soBaiDoHienTai] = NULL;

        cout << "Xoa bai do thanh cong!\n";
    }

    void layXeRa() {
        int maBai = nhapSoNguyen("Nhap ma bai do: ");
        ParkingLot* baiDo = timBaiDo(maBai);

        if (baiDo == NULL) {
            cout << "Khong tim thay bai do!\n";
            return;
        }

        int maXe = nhapSoNguyen("Nhap ma xe can xoa: ");
        baiDo->xoaXe(maXe);
    }

    void hienThiTatCaBaiDo() const {
        cout << "\n========== DANH SACH BAI DO ==========\n";

        if (soBaiDoHienTai == 0) {
            cout << "He thong chua co bai do!\n";
            return;
        }

        for (int i = 0; i < soBaiDoHienTai; i++) {
            cout << "\nBai do ID: "
                 << danhSachBaiDo[i]->layMaBaiDo()
                 << "\nKich thuoc: "
                 << danhSachBaiDo[i]->layKichThuoc()
                 << "\nSo xe: "
                 << danhSachBaiDo[i]->laySoXeHienTai()
                 << "/" << danhSachBaiDo[i]->laySucChua()
                 << "\n-----------------------------------\n";
        }
    }

    void hienThiXeTheoBai() const {
        int ma = nhapSoNguyen("Nhap ma bai do: ");
        ParkingLot* baiDo = timBaiDo(ma);

        if (baiDo != NULL)
            baiDo->hienThiDanhSachXe();
        else
            cout << "Khong tim thay bai do!\n";
    }

    void hienThiXeTheoLoai() const {
        cout << "\n1. Xe may\n2. O to\n3. Xe tai\n";

        int luaChon = nhapSoNguyen("Chon loai xe: ");
        string loaiXe;

        switch (luaChon) {
            case 1: loaiXe = "Xe may"; break;
            case 2: loaiXe = "O to"; break;
            case 3: loaiXe = "Xe tai"; break;
            default:
                cout << "Lua chon khong hop le!\n";
                return;
        }

        bool timThay = false;

        cout << "\nDanh sach xe loai: " << loaiXe << endl;

        for (int i = 0; i < soBaiDoHienTai; i++) {
            cout << "\nBai do ID: "
                 << danhSachBaiDo[i]->layMaBaiDo() << endl;

            if (danhSachBaiDo[i]->hienThiTheoLoai(loaiXe))
                timThay = true;
        }

        if (!timThay)
            cout << "Khong co xe thuoc loai nay!\n";
    }

    void tinhPhiTrungBinh() const {
        double tongPhi = 0;
        int tongXe = 0;

        for (int i = 0; i < soBaiDoHienTai; i++) {
            tongPhi += danhSachBaiDo[i]->tinhTongPhi();
            tongXe += danhSachBaiDo[i]->laySoXeHienTai();
        }

        if (tongXe == 0) {
            cout << "Chua co xe trong he thong!\n";
            return;
        }

        cout << fixed << setprecision(0);
        cout << "\nTong so xe: " << tongXe;
        cout << "\nTong phi do: " << tongPhi << " VND";
        cout << "\nPhi do trung binh: "
             << tongPhi / tongXe << " VND\n";
    }

    void chayMenu() {
        int luaChon;

        do {
            cout << "\n============================================\n";
            cout << "       HE THONG QUAN LY BAI DO XE\n";
            cout << "============================================\n";
            cout << "1. Tao bai do xe moi\n";
            cout << "2. Them xe vao bai do\n";
            cout << "3. Xoa mot bai do xe\n";
            cout << "4. Lay xe ra khoi bai do\n";
            cout << "5. Hien thi danh sach tat ca bai do\n";
            cout << "6. Hien thi danh sach xe theo bai do\n";
            cout << "7. Liet ke xe theo loai phuong tien\n";
            cout << "8. Tom tat phi do xe trung binh\n";
            cout << "9. Thoat chuong trinh\n";
            cout << "============================================\n";

            luaChon = nhapSoNguyen("Nhap lua chon: ");

            switch (luaChon) {
                case 1: taoBaiDo(); break;
                case 2: themXeVaoBai(); break;
                case 3: xoaBaiDo(); break;
                case 4: layXeRa(); break;
                case 5: hienThiTatCaBaiDo(); break;
                case 6: hienThiXeTheoBai(); break;
                case 7: hienThiXeTheoLoai(); break;
                case 8: tinhPhiTrungBinh(); break;
                case 9:
                    cout << "Da thoat chuong trinh!\n";
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
            }

        } while (luaChon != 9);
    }
};

int main() {
    SystemInterface heThong;
    heThong.chayMenu();
    return 0;
}

