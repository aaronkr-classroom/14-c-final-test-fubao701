#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 20
#define FILE_NAME "students.dat"

typedef struct {
    char name[NAME_LEN];
    int kor;
    int eng;
    int math;
    int total;
    float avg;
    int rank;
} Student;

void loadData(Student students[], int* count);
void addStudent(Student students[], int* count);
void saveData(Student students[], int count);
void calculateRank(Student students[], int count);
void printStudents(Student students[], int count);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    int menu;

    while (1) {
        printf("\n[Menu]\n");
        printf("1. .dat 파일에서 데이터 읽기\n");
        printf("2. 추가 학생 정보 입력\n");
        printf("3. .dat 파일 저장\n");
        printf("4. 성적 확인 (평균 계산 등)\n");
        printf("5. 종료\n");
        printf("-------------------\n");
        printf("선택(1~5): ");
        scanf_s("%d", &menu);

        switch (menu) {
        case 1:
            loadData(students, &count);
            break;
        case 2:
            addStudent(students, &count);
            break;
        case 3:
            saveData(students, count);
            break;
        case 4:
            calculateRank(students, count);
            printStudents(students, count);
            break;
        case 5:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다.\n");
        }
    }
}

/* 1. 파일에서 데이터 읽기 */
void loadData(Student students[], int* count) {
    FILE* fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("파일이 존재하지 않습니다.\n");
        return;
    }

    fread(count, sizeof(int), 1, fp);
    fread(students, sizeof(Student), *count, fp);
    fclose(fp);

    printf("%d명의 학생 정보를 읽었습니다.\n", *count);
}

/* 2. 학생 정보 추가 */
void addStudent(Student students[], int* count) {
    if (*count >= MAX_STUDENTS) {
        printf("더 이상 학생을 추가할 수 없습니다.\n");
        return;
    }

    Student* s = &students[*count];

    printf("이름: ");
    scanf_s("%s", s->name, NAME_LEN);

    printf("국어 점수: ");
    scanf_s("%d", &s->kor);

    printf("영어 점수: ");
    scanf_s("%d", &s->eng);

    printf("수학 점수: ");
    scanf_s("%d", &s->math);

    s->total = s->kor + s->eng + s->math;
    s->avg = s->total / 3.0f;

    (*count)++;
    printf("학생 정보가 추가되었습니다.\n");
}

/* 3. 파일에 저장 */
void saveData(Student students[], int count) {
    FILE* fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        printf("파일 저장 실패.\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), count, fp);
    fclose(fp);

    printf("파일에 저장되었습니다.\n");
}

/* 4. 등수 계산 */
void calculateRank(Student students[], int count) {
    for (int i = 0; i < count; i++) {
        students[i].rank = 1;
        for (int j = 0; j < count; j++) {
            if (students[j].total > students[i].total) {
                students[i].rank++;
            }
        }
    }
}

/* 성적 출력 */
void printStudents(Student students[], int count) {
    printf("\n이름\t국어\t영어\t수학\t총점\t평균\t등수\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%.2f\t%d\n",
            students[i].name,
            students[i].kor,
            students[i].eng,
            students[i].math,
            students[i].total,
            students[i].avg,
            students[i].rank);
    }
}
