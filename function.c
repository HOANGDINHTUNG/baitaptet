//
// Created by HOANG DINH TUNG on 2/6/2025.
//
// Triển khai hàm
#include "C:\Users\HOANG DINH TUNG\CLionProjects\ldanhsachsinhvien/include/function.h"
#include "check.c"
char* statusClass(int n) {
    if(n==0){
        return "Dang cho";
    }
    else if(n==1){
        return "Dang hoc";
    }
    else if(n==2){
        return "Ket thuc";
    }
    return 0;
}

// Trạng thái sinh viên
char* statusStudent(int n){
    if(n==0){
        return "Dang hoc";
    }
    else if(n==1){
        return "Bo hoc";
    }
    else if(n==2){
        return "Tot nghiep";
    }
    else if(n==3){
        return "Tot nghiep som";
    }
    else if(n==4){
        return "Bao luu";
    }
    else if(n==5){
        return "Dinh chi";
    }
    return 0;
}

// Hiển hiện menu chính
void showMenuMain(){
    printf("|-------------------PTIT------------------|\n");
    printf("%-42s%-s\n","| 1.Quan ly lop hoc","|");
    printf("%-42s%-s\n","| 2.Quan ly sinh vien","|");
    printf("%-42s%-s\n","| 3.Thong ke","|");
    printf("%-42s%-s\n","| 0.Thoat","|");
    printf("|-----------------------------------------|\n");
}

// Hiển thị menu lớp học
void showMenuClass(){
    printf("|-------------------CLASS-----------------|\n");
    printf("%-42s%-s\n","| 1.Xem danh sach lop hoc","|");
    printf("%-42s%-s\n","| 2.Them moi lop hoc","|");
    printf("%-42s%-s\n","| 3.Chinh sua thong tin lop hoc","|");
    printf("%-42s%-s\n","| 4.Xoa lop hoc","|");
    printf("%-42s%-s\n","| 0.Quay lai","|");
    printf("|-----------------------------------------|\n");
}

// Hiển thị menu quản lý sinh viên
void showMenuStudent(){
    printf("|-----------------STUDENT-----------------|\n");
    printf("%-42s%-s\n","| 1.Xem danh sach sinh vien","|");
    printf("%-42s%-s\n","| 2.Them moi sinh vien","|");
    printf("%-42s%-s\n","| 3.Chinh sua thong tin sinh vien","|");
    printf("%-42s%-s\n","| 4.Xem chi tiet thong tin sinh vien","|");
    printf("%-42s%-s\n","| 5.Xoa sinh vien","|");
    printf("%-42s%-s\n","| 0.Quay lai","|");
    printf("|-----------------------------------------|\n");
}

// xem danh sach lop hoc
//void showInfoClass(Class *infor,int number){
//    printf("+--------+--------------------+----INFORMATION CLASS---------+----+---------------+\n");
//    printf("|%-8s|%-20s|%-30s|%-4s|%-15s|\n","ID","NAME","MAJORS","SIZE","STATUS");
//    printf("+--------+--------------------+------------------------------+----+---------------+\n");
//    for(int i=0;i<number;i++){
//        printf("|%-8s|%-20s|%-30s|%-4d|%-15s|\n" , infor[i].id , infor[i].name , infor[i].majors , infor[i].size, statusClass(infor[i].status));
//        printf("+--------+--------------------+------------------------------+----+---------------+\n");
//    }
//}

// chinh sua danh sach lop hoc

// Viết thông tin lớp vào file
void saveClassToBinaryFile(Class *cla){
    // Tạo và mở file viết
    FILE *f=fopen(FILE_NAME,"ab");
    if(f==NULL){
        printf("Khong the mo %s de ghi!!!\n",FILE_NAME);
        return;
    }
    // Ghi số lượng lớp vào file
    fwrite(cla,sizeof(Class),1,f);
    printf("Luu file thanh cong!!!!\n");
    // Đóng file
    fclose(f);
}

// Đếm khóa học
int countCourse(Course *courses, Class *cla, int number) {
    int count=0;
    for (int i = 0; i < number; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(courses[j].name, cla[i].majors) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            if (count < MAX) {
                strcpy(courses[count].name, cla[i].majors);
                (count)++;
            }
        }
    }
    return count;
}

// Đếm số lớp đang hoạt động, kết thúc, đang chờ
void countStatusClass(){
    for(int j = 0; j < numClass; j++){
        if(cla1[j].status==0){
            ++classIsWaiting;
        }
        else if(cla1[j].status==1){
            ++classIsActive;
        }
        else{
            ++classIsInactive;
        }
    }
}

// Đếm số lượng tất cả SV của mỗi lớp
void countStudentinClass(){
    for(int j = 0; j < numClass; j++){
        numStudent+=cla1[j].size;// Cộng số học sinh vào tổng
        if(cla1[j].status==0){
            stuWaitClass+=cla1[j].size;// Số hoc sinh đợi lớp
        }
        else if(cla1[j].status==1){
            studentIsStudying+=cla1[j].size;// Số học sinh đang học
        }
        else if(cla1[j].status==2){
            reserveStudy+=cla1[j].size;// Số học sinh bảo lưu đình chỉ
        }
    }
}

// Đếm số lượng trạng thái từng sinh viên
void numbersStudent(){
    for(int i=0;i<numStudent;i++){
        if(stu[i].status==0){
            studentIsStudying++;
        }
        else if(stu[i].status==1){
            stuWaitClass++;
        }
        else if(stu[i].status==2||stu[i].status==3){
            studentGraduate++;
        }
        else if(stu[i].status==4||stu[i].status==5){
            reserveStudy++;
        }
    }
}

// Đọc thông tin cua lớp từ file
void readClassFromBinaryFile(int mode){
    FILE *f=fopen(FILE_NAME,"rb");
    if(f==NULL){
        printf("File %s khong tin tai hoac chu co du lieu!!!\n",FILE_NAME);
        return;
    }
    numClass=0;
    Class cla;
    if(mode==1){
        printf("+--------+-------------------INFORMATION CLASS--------------------+----+---------------+\n");
        printf("|%-8s|%-30s|%-25s|%-4s|%-15s|\n","ID","NAME","MAJORS","SIZE","STATUS");
        printf("+--------+------------------------------+-------------------------+----+---------------+\n");
    }
    while(fread(&cla,sizeof(Class),1,f)){
        cla1[numClass++] = cla; // Lưu lớp vào mảng và tăng số lượng lớp
        if(mode==1){
            printf("|%-8s|%-30s|%-25s|%-4d|%-15s|\n" , cla.id , cla.name , cla.majors , cla.size, statusClass(cla.status));
            printf("+--------+------------------------------+-------------------------+----+---------------+\n");
        }
    }
    numMajors = countCourse(course1,cla1,numClass);
    countStatusClass();
    // Đóng file
    fclose(f);
}

// Nhập vào các thông tin của lớp học
void inputInfoClass(Class *infor,int *i,int index,int mode) {
    if(mode==0){
        printf("Moi nhap vao so luong lop muon them : ");
        scanf("%d",i);
        getchar();
    }
    // Nhập từng thông tin của sinh viên
    for(int j=0;j<*i;j++){
        if(mode==1){
            j=index;
        }
        if(mode==0){
            do{
                fflush(stdin);
                printf("Moi nhap vao vao ma so lop (Vd: 36E) : ");
                fgets(infor[j].id,sizeof(infor[j].id),stdin);
                infor[j].id[strcspn(infor[j].id,"\n")]='\0';
                if(!checkIdClass(infor[j].id)){
                    printf("Nhap ma lop khong dung dinh dang!!!\n");
                }
//                else if(checkIdExistClass(infor[j].id,numClass,cla1)){
//                    printf("Ma so lop da ton tai, vui long nhap lai!!\n");
//                }
                else{
                    printf("Nhap ma lop thanh cong!!!\n");
                    break;
                }
            }while(1);
        }
        fflush(stdin);
        printf("Moi nhap vao ten lop : ");
        fgets(infor[j].name,sizeof(infor[j].name),stdin);
        infor[j].name[strcspn(infor[j].name,"\n")]='\0';
        fflush(stdin);
        printf("Moi nhap vao chuyen nganh : ");
        fgets(infor[j].majors,sizeof(infor[j].majors),stdin);
        infor[j].majors[strcspn(infor[j].majors,"\n")]='\0';
        do{
            fflush(stdin);
            printf("Moi nhap vao si so lop (<=40) : ");
            scanf("%d",&infor[j].size);
        }while(infor[j].size>40||infor[j].size<0);
        numStudent+=infor[j].size;
        do{
            printf("Moi nhap vao trang thai (0,1,2) : ");
            scanf("%d",&infor[j].status);
        } while (infor[j].status<0||infor[j].status>2);
        if(mode==0){
            saveClassToBinaryFile(&infor[j]);// lưu thông tin vào file nhị phân
        }
    }
}

// Tìm lớp học theo mã lớp
int findIdByClass(const char *findIdClass) {
    for(int i=0;i<numClass;i++){
        if(strcmp(cla1[i].id,findIdClass)==0){
            return i;
        }
    }
    return -1;
}

// Chỉnh sửa thông tin lớp học
void editInforClass() {
    readClassFromBinaryFile(1);
    int n=1;
    if(numClass==0){
        printf("khong co lop hoc nao de chinh sua!!!!\n");
        return;
    }
    fflush(stdin);
    char ma[8];
    printf("Moi nhap vao ma lop muon chinh sua : ");
    fgets(ma, sizeof(ma), stdin);
    ma[strcspn(ma, "\n")] = '\0';
    // Lấy chỉ số của ID trong mang danh sách lớp
    int index = findIdByClass(ma);
    if (index == -1) {
        printf("Khong tim thay ma lop!!!!\n");
        return;
    }
    // Hiển thị thông tin cũ trước khi sửa
    printf("Hien thi thong tin cu : \n");
    printf("Ma lop: %s\n", cla1[index].id);
    printf("Ten lop: %s\n", cla1[index].name);
    printf("Chuyen nganh: %s\n", cla1[index].majors);
    printf("Si so: %d\n", cla1[index].size);
    printf("Trang thai: %s\n", statusClass(cla1[index].status));
    // Cập nhật lại thông tin
    inputInfoClass(cla1,&n , index, 1);
    // Ghi lại thông tin vào file
    FILE *f=fopen(FILE_NAME, "wb");
    if(f==NULL){
        printf("File %s khong tin tai hoac chu co du lieu!!!\n",FILE_NAME);
        return;
    }
    // Đóng file
    fwrite(cla1, sizeof(Class), numClass, f);
    fclose(f);
    printf("Cap nhat thong tin lop hoc thanh cong!\n");
}

// Xóa lớp học
void deleteClass(){
    // Đọc file và lưu vào cla1
    readClassFromBinaryFile(1);
    // Nhập ID
    char ma[8];
    fflush(stdin);
    printf("Moi nhap vao ma so lop de xoa : ");
    fgets(ma,sizeof(ma),stdin);
    ma[strcspn(ma,"\n")]='\0';
    // Tìm lớp bằng mã
    int index = findIdByClass(ma);
    if(index==-1){
        printf("Khong tim thap ma lop!!!\n");
        return;
    }
    if(cla1[index].size==0){
        // Nếu lớp học không có học sinh
        for(int i=index;i<numClass-1;i++){
            *(cla1 + i) = *(cla1 + i + 1);
        }
        --(numClass);
        // Ghi lại thông tin vao file
        FILE *f=fopen(FILE_NAME, "wb");
        if(f==NULL){
            printf("File %s khong tin tai hoac chu co du lieu!!!\n",FILE_NAME);
            return;
        }
        // Đóng file
        fwrite(cla1, sizeof(Class), numClass, f);
        fclose(f);
        printf("Xoa lop hoc thanh cong!!!\n");
        return;
    }
    else{
        printf("Khong the xoa lop vi con sinh vien!!!\n");
        return;
    }
}

// Lựa chọn tính năng trong menu quản lý lớp học
void choiceMenuClass() {
    while (1) {
        readClassFromBinaryFile(0);
        showMenuClass();
        int choice,newCount;
        printf("Moi nhap vao su lua chon cua ban : ");
        scanf("%d", &choice);
        switch (choice) {
            // Hiển thị thông tin của các lớp học
            case 1: {
                readClassFromBinaryFile(1);
                break;
            }
                // Thêm mới một lớp học
            case 2: {
                if(numClass==MAX) {
                    printf("Tong so luong lop hoc da day, khong the them!!!!!\n");
                    break;
                }
                inputInfoClass(cla1,&newCount,1,0);
                break;
            }
                // Chỉnh sửa thông tin của lớp học
            case 3: {
                editInforClass();
                break;
            }
                // Xóa 1 lớp học
            case 4:{
                deleteClass();
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
            printf("Tro lai menu!!!\n");
            break;
        }
    }
}

// xem danh sach sinh vien
//void showInforStudent(Student *infor,int number){
//    printf("+--------+--------------------+-INFORMATION STUDENT+--------------------+---------------+\n");
//    printf("|%-8s|%-20s|%-20s|%-20s|%-15s|\n","ID","NAME","BIRTHDAY","CLASS","STATUS");
//    printf("+--------+--------------------+--------------------+--------------------+---------------+\n");
//    for(int i=0;i<number;i++){
//        printf("|%-8s|%-20s|%-20s|%-20s|%-15s|\n" , infor[i].id , infor[i].name ,infor[i].birthday ,infor[i].class,statusStudent(infor[i].status));
//        printf("+--------+--------------------+--------------------+--------------------+---------------+\n");
//    }
//}

// Nhập ID và xuất ra tên lớp
char *findClass(char *findIdClass) {
    //char *findIdClass : Là id nhập vào để kiểm tra
    //Class listId[] : Là danh sách id của lớp trong mảng
    for (int i = 0; i < numClass; i++) {
        if (strcmp(findIdClass, cla1[i].id) == 0) {
            return cla1[i].name;
        }
    }
    return "Chua co lop hoc!!!";
}

// Nhập mã lớp cho sinh viên
void inputIdClassByStudent(Student *students,int i){
    char ma[8];
    fflush(stdin);
    printf("Moi nhap vao ma lop cua SV : ");
    fgets(ma,sizeof(ma),stdin);
    ma[strcspn(ma,"\n")]='\0';// Loại bỏ kí tự xuống dòng
    strcpy(students[i].class,findClass(ma));
//    // Nhập mã tìm vị trí
//    int ID= findIdByClass(ma);
//    // Cập nhật thông tin
//    if(cla1[ID].size==40){
//        printf("SV cua lop da day, khong the them!!!\n");
//        return;
//    }
//    else{
//        cla1[ID].size++;
//    }
//    // Ghi lại thông tin vòa file
//    // Mở đóng file
//    FILE *f=fopen(FILE_NAME, "wb");
//    if(f==NULL){
//        printf("File %s khong tin tai hoac chu co du lieu!!!\n",FILE_NAME);
//        return;
//    }
//    // Đóng file
//    fwrite(cla1, sizeof(Class), numClass, f);
//    fclose(f);
}

// Lưu thông tin vào file nhị phân
void saveStudentToBinaryFile(Student *student1){
    FILE *f=fopen(FILE_NAME1,"ab");
    if(f==NULL){
        printf("Khong the mo %s file!!!\n",FILE_NAME1);
        return;
    }
    // Lưu từng học sinh vao file
    fwrite(student1,sizeof(Student),1,f);
    // Đóng file
    printf("Luu file thanh cong!!!\n");
    fclose(f);
}

// Đọc thông tin từ file
void readStudentByBinaryFile(int mode){
    FILE *f=fopen(FILE_NAME1,"rb");
    if(f==NULL){
        printf("Khong the mo file!!!\n");
        return;
    }
    numStudent=0;
    Student stu1;
    // Đọc thông tin từng sinh viên
    if(mode==1){
        printf("+--------+------------------------------+-INFORMATION STUDENT+--------------------+---------------+\n");
        printf("|%-8s|%-30s|%-20s|%-20s|%-15s|\n","ID","NAME","BIRTHDAY","CLASS","STATUS");
        printf("+--------+------------------------------+--------------------+--------------------+---------------+\n");
    }
    while(fread(&stu1,sizeof(Student),1,f)){
        stu[numStudent++]=stu1;// Lưu từng thông tin SV vào mảng stu
        if(mode==1){
            printf("|%-8s|%-30s|%-20s|%-20s|%-15s|\n" , stu1.id , stu1.name ,stu1.birthday ,stu1.class,statusStudent(stu1.status));
            printf("+--------+------------------------------+--------------------+--------------------+---------------+\n");
        }
    }
    numbersStudent();
    countStudentinClass();
    // Đóng file
    fclose(f);
}

// Nhập các thông tin cho sinh viên
void inputInfoStudent(Student *infor,int *i,int index,int mode){
    if(mode==0){
        printf("Moi nhap vao so luong sinh vien muon them : ");
        scanf("%d",i);
        getchar();// Xóa kí tự cuối
    }
    for(int j=0;j<*i;j++){
        if(mode==1){
            j=index;
        }
        if(mode==0){
            do{
                fflush(stdin);
                printf("Moi nhap vao vao ma so sinh vien (vd: SV001) : ");
                fgets(infor[j].id,sizeof(infor[j].id),stdin);
                infor[j].id[strcspn(infor[j].id,"\n")]='\0';
                if(!checkIdStudent(infor[j].id)){
                    printf("Ma SV khong dung, vui long nhap lai!!\n");
                }
//                else if(checkIdExistStudent(infor[j].id,numStudent,stu)){
//                    printf("Ma sinh vien da ton tai, vui long nhap lai!!!\n");
//                }
                else{
                    printf("ma sinh vien hop le!!!\n");
                    break;
                }
            }while(1);
        }
        fflush(stdin);
        printf("Moi nhap vao ten sinh vien : ");
        fgets(infor[j].name,sizeof(infor[j].name),stdin);
        infor[j].name[strcspn(infor[j].name,"\n")]='\0';
        fflush(stdin);
        printf("Moi nhap vao gioi tinh (nam hoac nu) : ");
        fgets(infor[j].sex,sizeof(infor[j].sex),stdin);
        infor[j].sex[strcspn(infor[j].sex,"\n")]='\0';
        do{
            fflush(stdin);
            printf("Moi nhap vao so dien thoai : ");
            fgets(infor[j].phoneNumber,sizeof(infor[j].phoneNumber),stdin);
            infor[j].phoneNumber[strcspn(infor[j].phoneNumber,"\n")]='\0';
            // Kiểm tra số điện thoại nhập vào có hợp lệ hay không
            if(!checkPhoneNumber(infor[j].phoneNumber)){
                printf("So dien thoai khong hop le, vui long nhap lai!!\n");
            }
            else{
                printf("So dien thoai hop le!!!\n");
                break;
            }
        }while(1);
        do{
            fflush(stdin);
            printf("Moi nhap vao email : ");
            fgets(infor[j].email,sizeof(infor[j].email),stdin);
            infor[j].email[strcspn(infor[j].email,"\n")]='\0';
            if(!checkEmailStudent(infor[j].email)){
                printf("Email khong hop le!!!\n");
            }
            else{
                printf("Ghi Email thanh cong!!!\n");
                break;
            }
        }while(1);
        do{
            fflush(stdin);
            printf("Moi nhap vao ngay thang nam sinh (dd/mm/yyyy) : ");
            fgets(infor[j].birthday,sizeof(infor[j].birthday),stdin);
            infor[j].birthday[strcspn(infor[j].birthday,"\n")]='\0';
            if(!checkBirthdayValid(infor[j].birthday)){
                printf("Ngay sinh khong hop le, vui long nhap lai!!!\n");
            }
            else{
                printf("Ngay sinh hop le!!!\n");
                break;
            }
        }while(1);
        fflush(stdin);
        printf("Moi nhap vao dia chi : ");
        fgets(infor[j].address,sizeof(infor[j].address),stdin);
        infor[j].address[strcspn(infor[j].address,"\n")]='\0';
        fflush(stdin);
        inputIdClassByStudent(infor,j);
        fflush(stdin);
        do{
            printf("Moi nhap vao trang thai (0,1,2,3,4,5) : ");
            scanf("%d",&infor[j].status);
        }while(infor[j].status<0||infor[j].status>5);
        if(mode==0){
            saveStudentToBinaryFile(&infor[j]);
        }
        if(mode==1){
            break;
        }
    }
}

// Tìm kiếm ID của sinh viên
int findIdByStudent( char *findIdStudent) {
    for(int i=0;i<numStudent;i++){
        if(strcmp(stu[i].id,findIdStudent)==0){
            return i;
        }
    }
    return -1;
}

// Xem thông tin chi tiết của một sinh viên
void showDetailsInforStudent(Student *infor,int number){
    char ma[8];
    int mode=0;
    fflush(stdin);
    printf("Moi nhap vao ma SV muon xem thong tin chi tiet : ");
    fgets(ma,sizeof(ma),stdin);
    ma[strcspn(ma,"\n")]='\0';
    for(int i=0; i < number; i++){
        if(strcmp(infor[i].id,ma)==0){
            mode=1;
            printf("Ma SV la : %s\n",infor[i].id);
            printf("Ho va ten : la %s\n",infor[i].name);
            printf("Gioi tinh : %s\n",infor[i].sex);
            printf("So dien thoai lien lac : %s\n",infor[i].phoneNumber);
            printf("Dia chi email : %s\n",infor[i].email);
            printf("Ngay thang nam sinh : %s\n",infor[i].birthday);
            printf("Dia chi nha : %s\n",infor[i].address);
            printf("Ten lop dang hoc : %s\n",infor[i].class);
            printf("Trang thai hien tai : %s\n", statusStudent(infor[i].status));
            break;
        }
    }
    if(mode==0){
        printf("Khong tim thay ma SV!!!!\n");
    }
}

// Chỉnh sửa thông tin sinh viên
void editInforStudent(){
    int n=1;
    char ma[8];// Xâu mã sinh viên
    // Nhập Id để tìm kiếm
    fflush(stdin);
    printf("Moi nhap vao ma sinh vien muon chinh sua : ");
    fgets(ma,sizeof(ma),stdin);
    ma[strcspn(ma,"\n")]='\0';
    // Tiềm kiếm vị trí sinh viên trong danh sách
    int index= findIdByStudent(ma);
    if(index==-1){
        printf("Ma sinh vien khong ton tai!!!\n");
        return;
    }
    // Hiển thị thông tin trước khi sửa
    printf("Thong tin sinh vien truoc khi sua!!!\n");
    printf("ID: %s\n", stu[index].id);
    printf("Ten: %s\n", stu[index].name);
    printf("Gioi tinh: %s\n", stu[index].sex);
    printf("So dien thoai: %s\n", stu[index].phoneNumber);
    printf("Email: %s\n", stu[index].email);
    printf("Ngay sinh: %s\n", stu[index].birthday);
    printf("Dia chi: %s\n", stu[index].address);
    printf("Lop: %s\n", stu[index].class);
    printf("Trang thai: %s\n", statusStudent(stu[index].status));
    // Nhập từng thông tin cho sinh viên
    inputInfoStudent(stu,&n,index,1);
    // Ghi lại thông tin vào file
    FILE *f=fopen(FILE_NAME1,"wb");
    if(f==NULL){
        printf("Khong the mo %s file!!!\n",FILE_NAME1);
        return;
    }
    fwrite(stu,sizeof(Student),numStudent,f);
    // Đóng file
    fclose(f);
}

// Xóa 1 sinh viên
void deleteStudent(){
    // Nhập ID SV
    char ma[8];
    fflush(stdin);
    printf("Moi nhap vao ma so SV de xoa : ");
    fgets(ma,sizeof(ma),stdin);
    ma[strcspn(ma,"\n")]='\0';
    // Tim kiếm ID trong danh sách
    int index=findIdByStudent(ma);
    // Nếu lớp học không có học sinh
    for(int i=index;i<numStudent-1;i++){
        *(stu + i) = *(stu + i + 1);
    }
    --(numStudent);
    // Ghi lại thông tin vao file
    FILE *f=fopen(FILE_NAME1, "wb");
    if(f==NULL){
        printf("File %s khong tin tai hoac chu co du lieu!!!\n",FILE_NAME1);
        return;
    }
    // Đóng file
    fwrite(stu, sizeof(Student), numStudent, f);
    fclose(f);
    printf("Xoa SV thanh cong!!!\n");
}

// Lựa chọn tính năng trong menu quản lý sinh viên
void choiceMenuStudent(){
    while (1) {
        showMenuStudent();
        // Lưu thông tin từ file vào mảng stu
        readStudentByBinaryFile(0);
        // Chọn chức năng
        int choice,newCount;
        printf("Moi nhap vao su lua chon cua ban : ");
        scanf("%d", &choice);
        switch (choice) {
            // Hiển thị thông tin của các SV
            case 1: {
                readStudentByBinaryFile(1);
                break;
            }
                // Thêm mới 1 SV
            case 2: {
                // Mở file viết
                if(numStudent==MAX){
                    printf("SV da day, khong the them!!!\n");
                    break;
                }
                inputInfoStudent(stu,&newCount,1,0);
                break;
            }
                // Chỉnh sửa thông tin của một SV
            case 3: {
                editInforStudent();
                break;
            }
                // Xem thông tin chi tiết của một SV
            case 4:{
                showDetailsInforStudent(stu,numStudent);
                break;
            }
                // Xóa 1 sinh viên
            case 5:{
                deleteStudent();
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
            printf("Tro lai menu!!!\n");
            break;
        }
    }
}

//thong ke tat ca
void courseStatistics(){
    readClassFromBinaryFile(0);
    readStudentByBinaryFile(0);
    printf("_______________________________________________\n");
    printf("|%-45s|\n","  THONG KE KHOA HOC");
    printf("|%-40s%-5d|\n","  So khoa hoc:",numMajors);
    printf("|%-45s|\n","  THONG KE LOP HOC");
    printf("|%-40s%-5d|\n","  So lop hoc:",numClass);
    printf("|%-40s%-5d|\n","  So lop dang hoat dong:",classIsActive);
    printf("|%-40s%-5d|\n","  So lop da ket thuc:",classIsInactive);
    printf("|%-40s%-5d|\n","  So lop dang cho:",classIsWaiting);
    printf("|%-45s|\n","  THONG KE SINH VIEN");
    printf("|%-40s%-5d|\n","  Tong so SV:",numStudent);
    printf("|%-40s%-5d|\n","  So SV cho lop:",stuWaitClass);
    printf("|%-40s%-5d|\n","  So SV dang hoc:",studentIsStudying);
    printf("|%-40s%-5d|\n","  So SV bao luu dinh chi:",reserveStudy);
    printf("|%-40s%-5d|\n","  So SV da tot nghiep:",studentGraduate);
    printf("_______________________________________________\n");
}
