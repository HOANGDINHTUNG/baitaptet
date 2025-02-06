//
// Created by HOANG DINH TUNG on 1/21/2025.
//

#ifndef LDANHSACHSINHVIEN_DATATYPE_H
#define LDANHSACHSINHVIEN_DATATYPE_H
typedef struct{
    char id[6];// Mã sinh viên
    char name[25];// Tên sinh viên
    char sex[5];// Giới tính sinh viên
    char phoneNumber[11];// Số diệp thoại
    char email[20];// Địa chỉ email
    char birthday[15];// Ngày tháng năm sinh
    char address[50];// Địa chỉ nhà
    char class[20];// Lớp sinh viên đang học
    int status;// Trạng thái lớp học tướng ướng với đang học, bỏ học, tốt nghiệp, tốt nghiệp sớm, bảo lưu, đình chỉ
}Student;
typedef struct{
    char id[6]; // Mã phòng học
    char name[30]; // Tên lớp học
    char majors[25];// Ngành học
    Student  list[40]; // Danh sách sinh viên có trong lớp
    int size;// Sĩ số lớp học
    int status;// Trạng thái lớp học gồm đang chờ, đang học và đã kết thúc
}Class;
typedef struct{
    char name[50];// Tên lớp học
}Course;
#endif //LDANHSACHSINHVIEN_DATATYPE_H
