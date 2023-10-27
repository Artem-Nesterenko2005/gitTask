#pragma once

#include <stdbool.h>

//��������� ��� �����
typedef struct Stack Stack;

//�������� ������� �� ���� �����
Stack* push(Stack* top, char data);

//��������� ���� �� ����������� ���������
bool isEmpty(Stack* top);

//������� ������� � ����� �����
Stack* pop(Stack* top);

//��������� �� ������ � ����� �����
int top(Stack* stack);
