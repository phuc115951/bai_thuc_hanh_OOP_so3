#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

int nhapSoNguyen(string thongBao) {
    int giaTri;
    while (true) {
        cout << thongBao;
        if (cin >> giaTri) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return giaTri;
        }
        cout << "Du lieu khong hop le! Nhap lai.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double nhapSoThuc(string thongBao) {
    double giaTri;
    while (true) {
        cout << thongBao;
        if (cin >> giaTri && giaTri >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return giaTri;
        }
        cout << "Du lieu khong hop le! Nhap lai.\n";
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
    Vehicle(int ma, string loai, double thoiGian) {
        maXe = ma;
        loaiXe = loai;
        thoiGianVao = time(nullptr);
        thoiGianDo = thoiGian;
        phiDo = calculateFee();
    }

    int getMaXe() const {
        return maXe;
    }

    string getLoaiXe() const {
        return loaiXe;
    }

    double getPhiDo() const {
        return phiDo;
    }

    double getThoiGianDo() const {
        return thoiGianDo;
    }

    void setMaXe(int ma) {
        maXe = ma;
    }

    void setLoaiXe(string loai) {
        loaiXe = loai;
        phiDo = calculateFee();
    }

    void setThoiGianDo(double thoiGian) {
        thoiGianDo = thoiGian;
        phiDo = calculateFee();
    }

    double calculateFee() const {
        double donGia = 0;

        if (loaiXe == "Xe may") {
            donGia = 5000;
        }
        else if (loaiXe == "O to") {
            donGia = 15000;
        }
        else if (loaiXe == "Xe tai") {
            donGia = 20000;
        }

        return donGia * thoiGianDo;
    }

    void display() const {
        cout << left
             << setw(12) << maXe
             << setw(15) << loaiXe
             << setw(15) << thoiGianDo
             << setw(15) << fixed << setprecision(0)
             << phiDo << endl;

        tm* thoiGian = localtime(&thoiGianVao);
        if (thoiGian != nullptr) {
            cout << "Thoi gian vao bai: "
                 << put_time(thoiGian, "%d/%m/%Y %H:%M:%S")
                 << endl;
        }
    }
};

class ParkingLot {
private:
    int parkID;
    char size;
    int capacity;
    int currentVehicleCount;
    Vehicle** vehicles;

    void resize(int newCapacity) {
        if (newCapacity <= capacity) {
            return;
        }

        Vehicle** mangMoi = new Vehicle*[newCapacity];

        for (int i = 0; i < newCapacity; i++) {
            mangMoi[i] = nullptr;
        }

        for (int i = 0; i < currentVehicleCount; i++) {
            mangMoi[i] = vehicles[i];
        }

        delete[] vehicles;
        vehicles = mangMoi;
        capacity = newCapacity;
    }

public:
    ParkingLot(int id, char kichThuoc) {
        parkID = id;
        size = kichThuoc;

        if (size == 'S' || size == 's') {
            capacity = 1;
            size = 'S';
        }
        else if (size == 'M' || size == 'm') {
            capacity = 2;
            size = 'M';
        }
        else if (size == 'L' || size == 'l') {
            capacity = 3;
            size = 'L';
        }
        else {
            capacity = 1;
            size = 'S';
        }

        currentVehicleCount = 0;
        vehicles = new Vehicle*[capacity];

        for (int i = 0; i < capacity; i++) {
            vehicles[i] = nullptr;
        }
    }

    ~ParkingLot() {
        for (int i = 0; i < currentVehicleCount; i++) {
            delete vehicles[i];
            vehicles[i] = nullptr;
        }

        delete[] vehicles;
        vehicles = nullptr;
    }

    ParkingLot(const ParkingLot& other) {
        parkID = other.parkID;
        size = other.size;
        capacity = other.capacity;
        currentVehicleCount = other.currentVehicleCount;

        vehicles = new Vehicle*[capacity];

        for (int i = 0; i < capacity; i++) {
            vehicles[i] = nullptr;
        }

        for (int i = 0; i < currentVehicleCount; i++) {
            if (other.vehicles[i] != nullptr) {
                vehicles[i] = new Vehicle(*other.vehicles[i]);
            }
        }
    }

    ParkingLot& operator=(const ParkingLot& other) {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < currentVehicleCount; i++) {
            delete vehicles[i];
        }
        delete[] vehicles;

        parkID = other.parkID;
        size = other.size;
        capacity = other.capacity;
        currentVehicleCount = other.currentVehicleCount;

        vehicles = new Vehicle*[capacity];

        for (int i = 0; i < capacity; i++) {
            vehicles[i] = nullptr;
        }

        for (int i = 0; i < currentVehicleCount; i++) {
            if (other.vehicles[i] != nullptr) {
                vehicles[i] = new Vehicle(*other.vehicles[i]);
            }
        }

        return *this;
    }

    int getParkID() const {
        return parkID;
    }

    int getCurrentVehicleCount() const {
        return currentVehicleCount;
    }

    int getCapacity() const {
        return capacity;
    }

    char getSize() const {
        return size;
    }

    bool addVehicle(const Vehicle& v) {
        if (currentVehicleCount == capacity) {
            resize(capacity * 2);
        }

        for (int i = 0; i < capacity; i++) {
            if (vehicles[i] == nullptr) {
                vehicles[i] = new Vehicle(v);
                currentVehicleCount++;
                cout << "Them xe thanh cong!\n";
                return true;
            }
        }

        return false;
    }

    bool removeVehicle(int vID) {
        for (int i = 0; i < currentVehicleCount; i++) {
            if (vehicles[i] != nullptr &&
                vehicles[i]->getMaXe() == vID) {

                delete vehicles[i];

                for (int j = i; j < currentVehicleCount - 1; j++) {
                    vehicles[j] = vehicles[j + 1];
                }

                vehicles[currentVehicleCount - 1] = nullptr;
                currentVehicleCount--;

                cout << "Xoa xe thanh cong!\n";
                return true;
            }
        }

        cout << "Khong tim thay xe!\n";
        return false;
    }

    Vehicle* findVehicle(int ma) const {
        for (int i = 0; i < currentVehicleCount; i++) {
            if (vehicles[i] != nullptr &&
                vehicles[i]->getMaXe() == ma) {
                return vehicles[i];
            }
        }

        return nullptr;
    }

    void displayVehicles() const {
        cout << "\nBai do ID: " << parkID << endl;
        cout << "Kich thuoc: " << size << endl;
        cout << "Suc chua: " << currentVehicleCount
             << "/" << capacity << endl;

        if (currentVehicleCount == 0) {
            cout << "Bai do chua co xe!\n";
            return;
        }

        cout << left
             << setw(12) << "Ma xe"
             << setw(15) << "Loai xe"
             << setw(15) << "Gio do"
             << setw(15) << "Phi do" << endl;

        cout << string(57, '-') << endl;

        for (int i = 0; i < currentVehicleCount; i++) {
            if (vehicles[i] != nullptr) {
                vehicles[i]->display();
            }
        }
    }

    bool displayByType(string loai) const {
        bool timThay = false;

        for (int i = 0; i < currentVehicleCount; i++) {
            if (vehicles[i] != nullptr &&
                vehicles[i]->getLoaiXe() == loai) {
                if (!timThay) {
                    cout << left
                         << setw(12) << "Ma xe"
                         << setw(15) << "Loai xe"
                         << setw(15) << "Gio do"
                         << setw(15) << "Phi do" << endl;
                }
                vehicles[i]->display();
                timThay = true;
            }
        }

        return timThay;
    }

    double getTotalFee() const {
        double tongPhi = 0;

        for (int i = 0; i < currentVehicleCount; i++) {
            if (vehicles[i] != nullptr) {
                tongPhi += vehicles[i]->getPhiDo();
            }
        }

        return tongPhi;
    }
};

class SystemInterface {
private:
    int lotCapacity;
    int currentLotCount;
    ParkingLot** parkingLots;

public:
    SystemInterface() {
        lotCapacity = 5;
        currentLotCount = 0;

        parkingLots = new ParkingLot*[lotCapacity];

        for (int i = 0; i < lotCapacity; i++) {
            parkingLots[i] = nullptr;
        }
    }

    ~SystemInterface() {
        for (int i = 0; i < currentLotCount; i++) {
            delete parkingLots[i];
            parkingLots[i] = nullptr;
        }

        delete[] parkingLots;
        parkingLots = nullptr;
    }

    SystemInterface(const SystemInterface& other) {
        lotCapacity = other.lotCapacity;
        currentLotCount = other.currentLotCount;

        parkingLots = new ParkingLot*[lotCapacity];

        for (int i = 0; i < lotCapacity; i++) {
            parkingLots[i] = nullptr;
        }

        for (int i = 0; i < currentLotCount; i++) {
            if (other.parkingLots[i] != nullptr) {
                parkingLots[i] =
                    new ParkingLot(*other.parkingLots[i]);
            }
        }
    }

    SystemInterface& operator=(const SystemInterface& other) {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < currentLotCount; i++) {
            delete parkingLots[i];
        }
        delete[] parkingLots;

        lotCapacity = other.lotCapacity;
        currentLotCount = other.currentLotCount;

        parkingLots = new ParkingLot*[lotCapacity];

        for (int i = 0; i < lotCapacity; i++) {
            parkingLots[i] = nullptr;
        }

        for (int i = 0; i < currentLotCount; i++) {
            if (other.parkingLots[i] != nullptr) {
                parkingLots[i] =
                    new ParkingLot(*other.parkingLots[i]);
            }
        }

        return *this;
    }

    void resizeSystem(int newCapacity) {
        if (newCapacity <= lotCapacity) {
            return;
        }

        ParkingLot** mangMoi =
            new ParkingLot*[newCapacity];

        for (int i = 0; i < newCapacity; i++) {
            mangMoi[i] = nullptr;
        }

        for (int i = 0; i < currentLotCount; i++) {
            mangMoi[i] = parkingLots[i];
        }

        delete[] parkingLots;
        parkingLots = mangMoi;
        lotCapacity = newCapacity;
    }

    ParkingLot* findLot(int id) const {
        for (int i = 0; i < currentLotCount; i++) {
            if (parkingLots[i] != nullptr &&
                parkingLots[i]->getParkID() == id) {
                return parkingLots[i];
            }
        }

        return nullptr;
    }

    void createParkingLot() {
        int id = nhapSoNguyen("Nhap ma bai do: ");

        if (findLot(id) != nullptr) {
            cout << "Ma bai do da ton tai!\n";
            return;
        }

        char kichThuoc;

        cout << "Nhap kich thuoc bai (S/M/L): ";
        cin >> kichThuoc;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (kichThuoc != 'S' && kichThuoc != 's' &&
            kichThuoc != 'M' && kichThuoc != 'm' &&
            kichThuoc != 'L' && kichThuoc != 'l') {
            cout << "Kich thuoc khong hop le!\n";
            return;
        }

        if (currentLotCount == lotCapacity) {
            resizeSystem(lotCapacity * 2);
        }

        parkingLots[currentLotCount] =
            new ParkingLot(id, kichThuoc);

        currentLotCount++;

        cout << "Tao bai do thanh cong!\n";
    }

    void addVehicleToLot() {
        int id = nhapSoNguyen("Nhap ma bai do: ");
        ParkingLot* baiDo = findLot(id);

        if (baiDo == nullptr) {
            cout << "Khong tim thay bai do!\n";
            return;
        }

        int maXe = nhapSoNguyen("Nhap ma xe: ");

        for (int i = 0; i < currentLotCount; i++) {
            if (parkingLots[i] != nullptr &&
                parkingLots[i]->findVehicle(maXe) != nullptr) {
                cout << "Ma xe da ton tai!\n";
                return;
            }
        }

        cout << "\nLoai xe:\n";
        cout << "1. Xe may\n";
        cout << "2. O to\n";
        cout << "3. Xe tai\n";

        int luaChon = nhapSoNguyen("Chon loai xe: ");
        string loaiXe;

        switch (luaChon) {
            case 1:
                loaiXe = "Xe may";
                break;
            case 2:
                loaiXe = "O to";
                break;
            case 3:
                loaiXe = "Xe tai";
                break;
            default:
                cout << "Loai xe khong hop le!\n";
                return;
        }

        double thoiGian =
            nhapSoThuc("Nhap thoi gian do (gio): ");

        Vehicle xeMoi(maXe, loaiXe, thoiGian);
        baiDo->addVehicle(xeMoi);
    }

    void removeParkingLot() {
        int id = nhapSoNguyen("Nhap ma bai do can xoa: ");
        int viTri = -1;

        for (int i = 0; i < currentLotCount; i++) {
            if (parkingLots[i] != nullptr &&
                parkingLots[i]->getParkID() == id) {
                viTri = i;
                break;
            }
        }

        if (viTri == -1) {
            cout << "Khong tim thay bai do!\n";
            return;
        }

        delete parkingLots[viTri];

        for (int i = viTri; i < currentLotCount - 1; i++) {
            parkingLots[i] = parkingLots[i + 1];
        }

        parkingLots[currentLotCount - 1] = nullptr;
        currentLotCount--;

        cout << "Xoa bai do thanh cong!\n";
    }

    void removeVehicleFromLot() {
        int id = nhapSoNguyen("Nhap ma bai do: ");
        ParkingLot* baiDo = findLot(id);

        if (baiDo == nullptr) {
            cout << "Khong tim thay bai do!\n";
            return;
        }

        int maXe = nhapSoNguyen("Nhap ma xe can xoa: ");
        baiDo->removeVehicle(maXe);
    }

    void displayAllLots() const {
        cout << "\n========== DANH SACH BAI DO ==========\n";

        if (currentLotCount == 0) {
            cout << "He thong chua co bai do!\n";
            return;
        }

        for (int i = 0; i < currentLotCount; i++) {
            if (parkingLots[i] != nullptr) {
                cout << "\nBai do ID: "
                     << parkingLots[i]->getParkID();

                cout << "\nKich thuoc: "
                     << parkingLots[i]->getSize();

                cout << "\nSo xe: "
                     << parkingLots[i]->getCurrentVehicleCount()
                     << "/" << parkingLots[i]->getCapacity();

                cout << "\n-----------------------------------\n";
            }
        }
    }

    void displayVehiclesInLot() const {
        int id = nhapSoNguyen("Nhap ma bai do: ");
        ParkingLot* baiDo = findLot(id);

        if (baiDo == nullptr) {
            cout << "Khong tim thay bai do!\n";
            return;
        }

        baiDo->displayVehicles();
    }

    void displayVehiclesByType() const {
        cout << "\n1. Xe may\n";
        cout << "2. O to\n";
        cout << "3. Xe tai\n";

        int luaChon = nhapSoNguyen("Chon loai xe: ");
        string loaiXe;

        switch (luaChon) {
            case 1:
                loaiXe = "Xe may";
                break;
            case 2:
                loaiXe = "O to";
                break;
            case 3:
                loaiXe = "Xe tai";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
                return;
        }

        bool timThay = false;

        cout << "\nDanh sach xe loai: " << loaiXe << endl;

        for (int i = 0; i < currentLotCount; i++) {
            if (parkingLots[i] != nullptr) {
                cout << "\nBai do ID: "
                     << parkingLots[i]->getParkID() << endl;

                if (parkingLots[i]->displayByType(loaiXe)) {
                    timThay = true;
                }
            }
        }

        if (!timThay) {
            cout << "Khong co xe thuoc loai nay!\n";
        }
    }

    void calculateAverageFee() const {
        double tongPhi = 0;
        int tongSoXe = 0;

        for (int i = 0; i < currentLotCount; i++) {
            if (parkingLots[i] != nullptr) {
                tongPhi += parkingLots[i]->getTotalFee();
                tongSoXe +=
                    parkingLots[i]->getCurrentVehicleCount();
            }
        }

        if (tongSoXe == 0) {
            cout << "Chua co xe trong he thong!\n";
            return;
        }

        double trungBinh = tongPhi / tongSoXe;

        cout << fixed << setprecision(0);
        cout << "\nTong so xe: " << tongSoXe << endl;
        cout << "Tong phi do: " << tongPhi << " VND\n";
        cout << "Phi do trung binh: "
             << trungBinh << " VND\n";
    }

    void runMenu() {
        int luaChon;

        do {
            cout << "\n";
            cout << "============================================\n";
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
                case 1:
                    createParkingLot();
                    break;
                case 2:
                    addVehicleToLot();
                    break;
                case 3:
                    removeParkingLot();
                    break;
                case 4:
                    removeVehicleFromLot();
                    break;
                case 5:
                    displayAllLots();
                    break;
                case 6:
                    displayVehiclesInLot();
                    break;
                case 7:
                    displayVehiclesByType();
                    break;
                case 8:
                    calculateAverageFee();
                    break;
                case 9:
                    cout << "\nDang giai phong bo nho...\n";
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
    heThong.runMenu();
    return 0;
}
