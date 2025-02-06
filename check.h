//
// Created by HOANG DINH TUNG on 2/5/2025.
//
#include <string.h>
#ifndef LDANHSACHSINHVIEN_CHECK_H
#define LDANHSACHSINHVIEN_CHECK_H
// Hàm kiểm tra số điện thoại có hợp lệ hay không
int checkPhoneNumber(char *phoneNumber);

// Hàm kiểm tra ID của lớp
int checkIdClass(char *ID);

// Hàm kiểm tra ID của sinh viên
int checkIdStudent(char *student);

// Kiểm tra Email xem có đúng hay không
int checkEmailStudent(char *Email);

// Hàm kiểm tra xem mã SV có tồn tại hay chưa
int checkIdExistStudent(char *Id,int number,Student *stu);

// Hàm kiểm tra xem mã lớp có tồn tại hay chưa
int checkIdExistClass(char *Id,int number,Class *cla1);

// Hàm kiểm tra ngày sinh có hợp lệ hay không
int checkBirthdayValid(const char *birthday);
#endif //LDANHSACHSINHVIEN_CHECK_H
