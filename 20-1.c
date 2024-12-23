#include <stdio.h>
#include <string.h>

// Khai bao cau truc Sach
typedef struct {
    int maSach;
    char tenSach[50];
    char tacGia[50];
    float giaTien;
    char theLoai[30];
} Sach;

void nhapThongTinSach(Sach* s) {
    printf("Nhap ma sach: ");
    scanf("%d", &s->maSach);
    getchar();
    printf("Nhap ten sach: ");
    fgets(s->tenSach, sizeof(s->tenSach), stdin);
    s->tenSach[strcspn(s->tenSach, "\n")] = '\0';
    printf("Nhap tac gia: ");
    fgets(s->tacGia, sizeof(s->tacGia), stdin);
    s->tacGia[strcspn(s->tacGia, "\n")] = '\0';

    printf("Nhap gia tien: ");
    scanf("%f", &s->giaTien);
    getchar();

    printf("Nhap the loai: ");
    fgets(s->theLoai, sizeof(s->theLoai), stdin);
    s->theLoai[strcspn(s->theLoai, "\n")] = '\0';
}

void hienThiThongTinSach(Sach* s) {
    printf("Ma Sach: %d, Ten Sach: %s, Tac Gia: %s, Gia Tien: %.3f, The Loai: %s\n",
           s->maSach, s->tenSach, s->tacGia, s->giaTien, s->theLoai);
}

void hienThiDanhSachSach(Sach ds[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nSach %d:\n", i + 1);
        hienThiThongTinSach(&ds[i]);
    }
}

void themSachVaoViTri(Sach ds[], int* n, int viTri) {
    if (*n >= 100) {
        printf("Danh sach da day!\n");
        return;
    }

    if (viTri < 0 || viTri > *n) {
        printf("Vi tri khong hop le!\n");
        return;
    }

    for (int i = *n; i > viTri; i--) {
        ds[i] = ds[i - 1];
    }

    printf("Nhap thong tin sach can them:\n");
    nhapThongTinSach(&ds[viTri]);
    (*n)++;
}

void xoaSachTheoMa(Sach ds[], int* n, int maSach) {
    for (int i = 0; i < *n; i++) {
        if (ds[i].maSach == maSach) {
            for (int j = i; j < *n - 1; j++) {
                ds[j] = ds[j + 1];
            }
            (*n)--;
            printf("Da xoa sach co ma: %d\n", maSach);
            return;
        }
    }
    printf("Khong tim thay sach voi ma: %d\n", maSach);
}

void capNhatThongTinSach(Sach ds[], int n, int maSach) {
    for (int i = 0; i < n; i++) {
        if (ds[i].maSach == maSach) {
            printf("Nhap thong tin moi cho sach co ma: %d\n", maSach);
            nhapThongTinSach(&ds[i]);
            printf("Thong tin da duoc cap nhat.\n");
            return;
        }
    }
    printf("Khong tim thay sach voi ma: %d\n", maSach);
}

void sapXepSachTheoGia(Sach ds[], int n, int tangDan) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((tangDan && ds[i].giaTien > ds[j].giaTien) || (!tangDan && ds[i].giaTien < ds[j].giaTien)) {
                Sach temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
}

void timKiemSachTheoTen(Sach ds[], int n, const char* tenSach) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(ds[i].tenSach, tenSach) != NULL) {
            hienThiThongTinSach(&ds[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay sach co ten: %s\n", tenSach);
    }
}

int main() {
    Sach ds[100];
    int n = 0;
    int choice;

    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin sach\n");
        printf("2. Hien thi thong tin sach\n");
        printf("3. Them sach vao vi tri\n");
        printf("4. Xoa sach theo ma sach\n");
        printf("5. Cap nhat thong tin sach theo ma sach\n");
        printf("6. Sap xep sach theo gia (tang/giam)\n");
        printf("7. Tim kiem sach theo ten sach\n");
        printf("8. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap so luong sach: ");
                scanf("%d", &n);
                getchar();
                for (int i = 0; i < n; i++) {
                    printf("\nNhap thong tin sach %d:\n", i + 1);
                    nhapThongTinSach(&ds[i]);
                }
                break;
            case 2:
                printf("\nDanh sach sach:\n");
                hienThiDanhSachSach(ds, n);
                break;
            case 3: {
                int viTri;
                printf("Nhap vi tri can them: ");
                scanf("%d", &viTri);
                themSachVaoViTri(ds, &n, viTri);
                break;
            }
            case 4: {
                int maSach;
                printf("Nhap ma sach can xoa: ");
                scanf("%d", &maSach);
                xoaSachTheoMa(ds, &n, maSach);
                break;
            }
            case 5: {
                int maSach;
                printf("Nhap ma sach can cap nhat: ");
                scanf("%d", &maSach);
                capNhatThongTinSach(ds, n, maSach);
                break;
            }
            case 6: {
                int tangDan;
                printf("Nhap 1 de sap xep tang dan, 0 de sap xep giam dan: ");
                scanf("%d", &tangDan);
                sapXepSachTheoGia(ds, n, tangDan);
                printf("Danh sach sau khi sap xep:\n");
                hienThiDanhSachSach(ds, n);
                break;
            }
            case 7: {
                char tenSach[50];
                printf("Nhap ten sach can tim: ");
                getchar();
                fgets(tenSach, sizeof(tenSach), stdin);
                tenSach[strcspn(tenSach, "\n")] = '\0';
                timKiemSachTheoTen(ds, n, tenSach);
                break;
            }
            case 8:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 8);

    return 0;
}
