#include <stdio.h>
#include <string.h>

typedef struct {
    int maSP;
    char tenSP[50];
    float giaNhap;
    float giaBan;
    int soLuong;
} SanPham;

float doanhThu = 0;

void nhapThongTinSanPham(SanPham* sp) {
    printf("Nhap ma san pham: ");
    scanf("%d", &sp->maSP);
    printf("Nhap ten san pham: ");
    getchar();
    fgets(sp->tenSP, sizeof(sp->tenSP), stdin);
    sp->tenSP[strcspn(sp->tenSP, "\n")] = '\0';
    printf("Nhap gia nhap: ");
    scanf("%f", &sp->giaNhap);
    printf("Nhap gia ban: ");
    scanf("%f", &sp->giaBan);
    printf("Nhap so luong: ");
    scanf("%d", &sp->soLuong);
}

void hienThiSanPham(SanPham* sp) {
    printf("Ma SP: %d, Ten SP: %s, Gia Nhap: %.2f, Gia Ban: %.2f, So Luong: %d\n",
           sp->maSP, sp->tenSP, sp->giaNhap, sp->giaBan, sp->soLuong);
}

void hienThiDanhSachSanPham(SanPham ds[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nSan pham %d:\n", i + 1);
        hienThiSanPham(&ds[i]);
    }
}

int timSanPhamTheoMa(SanPham ds[], int n, int maSP) {
    for (int i = 0; i < n; i++) {
        if (ds[i].maSP == maSP) {
            return i;
        }
    }
    return -1;
}

void nhapSanPham(SanPham ds[], int* n) {
    SanPham sp;
    nhapThongTinSanPham(&sp);

    int index = timSanPhamTheoMa(ds, *n, sp.maSP);
    if (index != -1) {
        ds[index].soLuong += sp.soLuong;
        printf("San pham da ton tai, tang so luong len %d\n", ds[index].soLuong);
    } else {
        if (*n >= 100) {
            printf("Danh sach da day!\n");
            return;
        }
        ds[*n] = sp;
        (*n)++;
    }

    doanhThu -= sp.soLuong * sp.giaNhap;
}

void capNhatThongTinSanPham(SanPham ds[], int n, int maSP) {
    int index = timSanPhamTheoMa(ds, n, maSP);
    if (index != -1) {
        printf("Nhap thong tin moi cho san pham co ma: %d\n", maSP);
        nhapThongTinSanPham(&ds[index]);
        printf("Thong tin da duoc cap nhat.\n");
    } else {
        printf("Khong tim thay san pham voi ma: %d\n", maSP);
    }
}

void sapXepSanPhamTheoGia(SanPham ds[], int n, int tangDan) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((tangDan && ds[i].giaBan > ds[j].giaBan) || (!tangDan && ds[i].giaBan < ds[j].giaBan)) {
                SanPham temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
}

void timKiemSanPham(SanPham ds[], int n, const char* tenSP) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(ds[i].tenSP, tenSP) != NULL) {
            hienThiSanPham(&ds[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay san pham co ten: %s\n", tenSP);
    }
}

void banSanPham(SanPham ds[], int n, int maSP, int soLuongBan) {
    int index = timSanPhamTheoMa(ds, n, maSP);
    if (index != -1) {
        if (ds[index].soLuong == 0) {
            printf("San pham da het hang!\n");
        } else if (soLuongBan > ds[index].soLuong) {
            printf("Khong du hang de ban!\n");
        } else {
            ds[index].soLuong -= soLuongBan;
            doanhThu += soLuongBan * ds[index].giaBan;
            printf("Ban thanh cong %d san pham!\n", soLuongBan);
        }
    } else {
        printf("Khong tim thay san pham voi ma: %d\n", maSP);
    }
}

int main() {
    SanPham ds[100];
    int n = 0;
    int choice;

    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Nhap san pham\n");
        printf("4. Cap nhat thong tin san pham\n");
        printf("5. Sap xep san pham theo gia (tang/giam)\n");
        printf("6. Tim kiem san pham\n");
        printf("7. Ban san pham\n");
        printf("8. Doanh thu hien tai\n");
        printf("9. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap so luong san pham: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("\nNhap thong tin san pham %d:\n", i + 1);
                    nhapThongTinSanPham(&ds[i]);
                    doanhThu -= ds[i].soLuong * ds[i].giaNhap;
                }
                break;
            case 2:
                printf("\nDanh sach san pham:\n");
                hienThiDanhSachSanPham(ds, n);
                break;
            case 3:
                nhapSanPham(ds, &n);
                break;
            case 4: {
                int maSP;
                printf("Nhap ma san pham can cap nhat: ");
                scanf("%d", &maSP);
                capNhatThongTinSanPham(ds, n, maSP);
                break;
            }
            case 5: {
                int tangDan;
                printf("Nhap 1 de sap xep tang dan, 0 de sap xep giam dan: ");
                scanf("%d", &tangDan);
                sapXepSanPhamTheoGia(ds, n, tangDan);
                printf("Danh sach sau khi sap xep:\n");
                hienThiDanhSachSanPham(ds, n);
                break;
            }
            case 6: {
                char tenSP[50];
                printf("Nhap ten san pham can tim: ");
                getchar();
                fgets(tenSP, sizeof(tenSP), stdin);
                tenSP[strcspn(tenSP, "\n")] = '\0';
                timKiemSanPham(ds, n, tenSP);
                break;
            }
            case 7: {
                int maSP, soLuongBan;
                printf("Nhap ma san pham can ban: ");
                scanf("%d", &maSP);
                printf("Nhap so luong can ban: ");
                scanf("%d", &soLuongBan);
                banSanPham(ds, n, maSP, soLuongBan);
                break;
            }
            case 8:
                printf("Doanh thu hien tai: %.2f\n", doanhThu);
                break;
            case 9:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 9);

    return 0;
}
