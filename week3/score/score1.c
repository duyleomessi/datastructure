#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_LEN 81

typedef struct {
  int no;
  char studentId[10];
  char name[30];
  char phone[12];
  float mark;
} Student;

int getLineOfFile(FILE *fin);
Student *readToArray(FILE *fin, int totalLine);
void readToBinaryFile(FILE *fout, Student *student, int totalLine);
void readBinaryToArray(FILE *fin, int totalLine);

int main(int argc, char *argv[]) {
  Student *student;
  int n;
  FILE *fptr1, *fptr2;
  char filename1[] = "bangdiem.txt";
  char filename2[] = "bangdiem.dat";

  if ((fptr1 = fopen(filename1, "r")) == NULL) {
    printf("Cannot open %s\n", filename1);
    return 1;
  }

  if ((fptr2 = fopen(filename2, "w+b")) == NULL) {
    printf("Cannot open %s\n", filename2);
    return 1;
  }

  n = getLineOfFile(fptr1);
  rewind(fptr1);
  student = readToArray(fptr1, n);
  if (student == NULL) {
    printf("Memory allocated failed\n");
    return 1;
  }
  readToBinaryFile(fptr2, student, n);
  rewind(fptr2);
  readBinaryToArray(fptr2, n);
  free(student);
  fclose(fptr1);
  fclose(fptr2);
  return 0;
}

int getLineOfFile(FILE *fin) {
  char buff[MAX_LEN];
  int count = 0;
  while (fgets(buff, MAX_LEN, fin) != NULL) {
    count++;
  }
  // printf("count is %d\n", count);
  return count;
}

Student *readToArray(FILE *fin, int totalLine) {
  Student *student = (Student *) malloc(totalLine * sizeof(Student));
  int i;
  for (i = 0; i < totalLine; i++) {
    //fscanf(fin, "%d%s%[^0-9]%s%f", &student[i].no, student[i].studentId, student[i].name, student[i].phone, &student[i].mark);
    fscanf(fin, "%d%s%30[a-zA-Z ]%s%f", &student->no, student->studentId, student->name, student->phone, &student->mark);
    student++;
  }
  student = student - totalLine;
  return student;
}

void readToBinaryFile(FILE *fout, Student *student, int totalLine) {
  fwrite(student, sizeof(Student), totalLine, fout);
}

void readBinaryToArray(FILE *fin, int totalLine) {
  Student *student = (Student *)malloc(totalLine * sizeof(Student));
  int i;
  
  fread(student, sizeof(Student), totalLine, fin);
  for (i = 0; i < totalLine; i++) {
    printf("%-2d%-10s%-25s%-12s%-2.2f\n", student[i].no, student[i].studentId, student[i].name, student[i].phone, student[i].mark);
  }
  free(student);
}
