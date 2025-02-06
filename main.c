#include <stdio.h>
#include "src/function.c"
int main() {
    int choice;
    while (1) {
        showMenuMain();
        printf("Moi nhap vao su lua chon cua ban : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                choiceMenuClass();
                break;
            }
            case 2: {
                choiceMenuStudent();
                break;
            }
            case 3: {
                courseStatistics();
                break;
            }
            case 0: {
                break;
            }
            default:
                printf("Lua chon cua ban khong co trong menu!!!!\n");
                break;
        }
        if (choice == 0) {
            break;
        }
    }
    return 0;
}
