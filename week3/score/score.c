#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 81

typedef struct {
  int no;
  char studentId[10];
  char name[30];
  char phone[12];
  float mark;
} Student;

int countLine(FILE *fin);
Student* getStudent(FILE *fin, int totalLine);
void inputMark(Student *student, int totalLine, FILE *fout);

int main(int argc, char* argv[]) {
  //Student *student = (Student *) malloc(sizeof(Student));
  Student *student;
  FILE *fptr1, *fptr2;
  char filename1[] = "data.txt";
  char filename2[] = "bangdiem.txt";
  int totalLine;
  
  if ((fptr1 = fopen(filename1, "r")) == NULL) {
    printf("Cannot open %s\n", filename1);
    return 0;
  }
  
  if((fptr2 = fopen(filename2, "w")) == NULL) {
    printf("Cannot open %s\n", filename2);
    return 0;
  }

  //  fscanf(fptr1, "%d%s%s%s", &(student->no), student->studentId ,student->name, student->phone);
  totalLine =  countLine(fptr1);
  fclose(fptr1);
  if ((fptr1 = fopen(filename1, "r")) == NULL) {
    printf("Cannot open %s\n", filename1);
    return 0;
  }
  student = getStudent(fptr1, totalLine);
  inputMark(student, totalLine, fptr2);
  fclose(fptr1);
  fclose(fptr2);
  free(student);
  return 0;
}

int countLine(FILE *fin) {
  char buff[MAX_LEN];
  int count = 0;
  while(fgets(buff, MAX_LEN, fin) != NULL) {
    count++;
  }
  printf("count %d\n", count);
  return count;
};

Student* getStudent(FILE *fin, int totalLine) {
  printf("total Line %d\n", totalLine);
  Student *studentTmp = (Student* ) malloc(totalLine * sizeof(Student));
  int i;
  for (i = 0; i < totalLine; i++) {
    fscanf(fin, "%d%s%[^0-9]%s", &studentTmp->no, studentTmp->studentId, studentTmp->name, studentTmp->phone);
    printf("%-2d%-10s%-30s%-12s\n", studentTmp->no, studentTmp->studentId, studentTmp->name, studentTmp->phone);
    studentTmp++;
  }

  studentTmp = studentTmp - totalLine;

  return studentTmp;
}

void inputMark(Student *student, int totalLine, FILE *fout) {
  int i;
  for (i = 0; i < totalLine; i++) {
    printf("Enter the mark for student %s: ", student[i].name);
    scanf("%f", &student[i].mark);
    printf("mark %f\n", student[i].mark);
    fprintf(fout, "%-2d%-10s%-25s%-12s%-2.2f\n", student[i].no, student[i].studentId, student[i].name, student[i].phone, student[i].mark);  
  }
}
