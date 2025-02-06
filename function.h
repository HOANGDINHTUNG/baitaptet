//
// Created by HOANG DINH TUNG on 1/21/2025.
// Khai báo các hàm nguyên mẫu
#ifndef LDANHSACHSINHVIEN_FUNCTION_H
#define LDANHSACHSINHVIEN_FUNCTION_H
#include<stdio.h>
#include<string.h>
#include"datatype.h"
#define MAX 1000
Class cla1[MAX];
Student stu[MAX];
Course course1[MAX];
int numClass=0;// Tổng số lớp
int numStudent=0;// Tổng số SV
int numMajors=0;// Tổng số khóa học
int classIsWaiting=0;// Đếm số lớp đang đợi
int classIsActive=0;// Đếm số lớp đang hoạt động
int classIsInactive=0;// Đếm số lớp học đã kết thúc
int stuWaitClass=0;// Số SV đang chờ lớp
int reserveStudy=0;// Số SV bảo lưu, đình chỉ
int studentIsStudying=0;// Số SV đang học
int studentGraduate=0;// Số sinh viên đã tốt nghiệp
#define FILE_NAME "data/Baithuchanh.dat"
#define FILE_NAME1 "data/Baithuchanhs.dat"
// Trạng thái lớp học
char* statusClass(int n);

// Trạng thái sinh viên
char* statusStudent(int n);

// Hiển hiện menu chính
void showMenuMain();

// Hiển thị menu lớp học
void showMenuClass();

// Hiển thị menu quản lý sinh viên
void showMenuStudent();

// Viết thông tin lớp vào file
void saveClassToBinaryFile(Class *cla);

// Đếm khóa học
int countCourse(Course *courses, Class *cla, int number);

// Đếm số lớp đang hoạt động, kết thúc, đang chờ
void countStatusClass();

// Đếm số lượng tất cả SV của mỗi lớp
void countStudentinClass();

// Đếm số lượng trạng thái từng sinh viên
void numbersStudent();

// Đọc thông tin cua lớp từ file
void readClassFromBinaryFile(int mode);

// Nhập vào các thông tin của lớp học
void inputInfoClass(Class *infor,int *i,int index,int mode);

// Tìm lớp học theo mã lớp
int findIdByClass(const char *findIdClass);

// Chỉnh sửa thông tin lớp học
void editInforClass();

// Xóa lớp học
void deleteClass();

// Lựa chọn tính năng trong menu quản lý lớp học
void choiceMenuClass();

// Nhập ID và xuất ra tên lớp
char *findClass(char *findIdClass);

// Nhập mã lớp cho sinh viên
void inputIdClassByStudent(Student *students,int i);

// Lưu thông tin vào file nhị phân
void saveStudentToBinaryFile(Student *student1);

// Đọc thông tin từ file
void readStudentByBinaryFile(int mode);

// Nhập các thông tin cho sinh viên
void inputInfoStudent(Student *infor,int *i,int index,int mode);

// Tìm kiếm ID của sinh viên
int findIdByStudent( char *findIdStudent);

// Xem thông tin chi tiết của một sinh viên
void showDetailsInforStudent(Student *infor,int number);

// Chỉnh sửa thông tin sinh viên
void editInforStudent();

// Xóa 1 sinh viên
void deleteStudent();

// Lựa chọn tính năng trong menu quản lý sinh viên
void choiceMenuStudent();

//thong ke tat ca
void courseStatistics();
#endif //LDANHSACHSINHVIEN_FUNCTION_H
