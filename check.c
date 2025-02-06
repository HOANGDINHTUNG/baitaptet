//
// Created by HOANG DINH TUNG on 2/6/2025.
//
// Triển khai hàm
#include <stdio.h>
#include "C:\Users\HOANG DINH TUNG\CLionProjects\ldanhsachsinhvien\include/check.h"
#include "C:\Users\HOANG DINH TUNG\CLionProjects\ldanhsachsinhvien\/include/datatype.h"
// Hàm kiểm tra số điện thoại có hợp lệ hay không
int checkPhoneNumber(char *phoneNumber){
    int length=(int)strlen(phoneNumber);
    // Kiểm tra số điện thoại có đúng 10 chữ số hay không
    if(length!=10){
        return 0;
    }
    // Kiểm tra kí tự đầu có phai là số 0 hay không
    if(*phoneNumber!='0'){
        return 0;
    }
    // Kiểm tra số điện thoại có chữ cái hay không
    for(int i=1;i<length;i++){
        if(*(phoneNumber+i)<48||*(phoneNumber+i)>57){
            return 0;
        }
    }
    return 1;
}

// Hàm kiểm tra ID của lớp
int checkIdClass(char *ID){
    int length=(int)strlen(ID);
    // Mã lớp không quá 5 kí tự
    if(length>6){
        return 0;
    }
    // Kiểm tra kí tự cuối có phải chữ hoa hay không
    if(*(ID+length-1)<65||*(ID+length-1)>90){
        return 0;
    }
    // Kiểm tra các kí tự đầu có phải là số hay không
    for(int i=0;i<length-1;i++){
        if(*(ID+i)<48||*(ID+i)>57){
            return 0;
        }
    }
    return 1;
}

// Hàm kiểm tra ID của sinh viên
int checkIdStudent(char *student){
    int length=(int) strlen(student);
    // Mã sinh viên không quá 6 kí tự
    if(length>6){
        return 0;
    }
    // Kiểm tra 2 kí tự đầu có chữ SV hay không
    if(student[0]!='S'||student[1]!='V'){
        return 0;
    }
    // Kiểm tra các kí tự sau có phải chữ số hay không
    for(int i=2;i<length;i++){
        if(*(student+i)<48||*(student+i)>57){
            return 0;
        }
    }
    return 1;
}

// Kiểm tra Email xem có đúng hay không
int checkEmailStudent(char *Email){
    char tempEmail[10]="@gmail.com";
    char *res=strstr(Email,tempEmail);
    if(res == NULL){
        return 0;
    }
    return 1;
}

// Hàm kiểm tra xem mã SV có tồn tại hay chưa
int checkIdExistStudent(char *Id,int number,Student *stu){
    for(int i=0;i<number;i++){
        printf("Id : %s\n",stu[i].name);
        if(strcmp(Id,stu[i].id)==0){
            return 1;
            // Mã số SV tồn tại
        }
    }
    return 0;
    // Mã số SV không tồn tại
}

// Hàm kiểm tra xem mã lớp có tồn tại hay chưa
int checkIdExistClass(char Id[6],int number,Class *cla1){

    for(int k=0;k<number;k++){
        printf("ma Sv %s\n",cla1[k].id);
    }
    for(int i=0;i<number;i++){
        if(strcmp(Id,cla1[i].id)==0){
            return 1;
            // Mã số lớp tồn tại
        }
    }
    return 0;
    // Mã số lớp không tồn tại
}

// Hàm kiểm tra ngày sinh có hợp lệ hay không
int checkBirthdayValid(const char *birthday){
    int date[3];
    int i=0,j=0,num=0;
    // Lặp lại cho đến cuối chuỗi
    while(birthday[i] != '\0'){
        if(birthday[i]=='/'){
            date[j++]=num;
            num=0;//reset lại kết quả
        }
        else{
            num=num*10+(birthday[i]-'0');//chuyển từ kí sang số
        }
        i++;
    }
    date[j]=num;
    // Kiểm tra tính hợp lệ của ngày tháng năm nhập vào
    if(date[2]>0){
        // Trường hợp năm nhuận
        if(date[2]%4==0&&date[2]%100!=0||date[2]%400==0){
            if(date[1]==2){
                if(date[0]<1||date[0]>29){
                    return 0;
                }
            }
            else if(date[1]==4||date[1]==6||date[1]==9||date[1]==11){
                if(date[0]<1||date[0]>30){
                    return 0;
                }
            }
            else if(date[1]==1||date[1]==3||date[1]==5||date[1]==7||date[1]==8||date[1]==10||date[1]==12){
                if(date[0]<1||date[0]>31){
                    return 0;
                }
            }
        }
        // Trường hợp năm không nhuận
        else{
            if(date[1]==2){
                if(date[0]<1||date[0]>28){
                    return 0;
                }
            }
            else if(date[1]==4||date[1]==6||date[1]==9||date[1]==11){
                if(date[0]<1||date[0]>30){
                    return 0;
                }
            }
            else if(date[1]==1||date[1]==3||date[1]==5||date[1]==7||date[1]==8||date[1]==10||date[1]==12){
                if(date[0]<1||date[0]>31){
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
    }
    else{
        return 0;
    }
    return 1;
}

