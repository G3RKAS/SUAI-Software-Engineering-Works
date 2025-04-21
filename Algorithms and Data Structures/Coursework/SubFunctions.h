#pragma once
#include "ctime"
#include <string>
using namespace std;

// ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜
string GetDateByTime(time_t arg1);

// ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
bool IsPassportValid(string ID);

bool IsSimValid(string ID);

bool IsYearValid(int year);

// ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜

int GetInt(int a=0, int b=0);

int GetValidYear();

string GetPassportNo();

string GetSimNo();
